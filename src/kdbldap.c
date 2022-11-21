#ifdef _WIN32
#include <winsock2.h>
#endif
#include <ldap.h>
#include "kdbldap.h"
#include <stdio.h>
#include <stdlib.h>
#include "sessions.h"

#define CHECK_PARAM_TYPE(x,y,z) {if (x->t != y) return krr((S)"Function " #z " called with incorrect param type for " #x "");}
#define CHECK_PARAM_STRING_TYPE(x,z) {if (x->t != -KS && x->t != KC) return krr((S)"Function " #z " called with incorrect param type for " #x "");}
#define CHECK_PARAM_BYTESTRING_TYPE(x,z) {if (x->t != -KS && x->t != KG && x->t != KC) return krr((S)"Function " #z " called with incorrect param type for " #x "");}
#define CHECK_PARAM_INT_TYPE(x,z) {if (x->t != -KI && x->t != -KJ) return krr((S)"Function " #z " called with incorrect param type for " #x "");}
#define CHECK_SESSION(x) {if (0==x) return krr((S)"unknown session used");}
static int getInt(K val)
{
    if (val->t==-KI)
        return val->i;
    return (int)val->j;
}

static char* createString(K in)
{
    char* newStr = NULL;
    int len = 1;
    if (in->t == KC || in->t == KG)
    {
        len = (in->n) + 1;
        newStr = (char*)malloc(len);
        memcpy(newStr,in->G0,len-1);
    }
    else if (in->t == -KS)
    {
        len = strlen(in->s)+1;
        newStr = (char*)malloc(len);
        memcpy(newStr,in->s,len-1);
    }
    else
        newStr = (char*)malloc(len);
    newStr[len-1]='\0';
    return newStr;
}

static int getStringLen(K in)
{
    if (in->t == KC || in->t == KG)
        return in->n;
    else if (in->t == -KS)
        return strlen(in->s);
    return 0;
}

K kdbldap_init(K sess, K uris)
{
    CHECK_PARAM_INT_TYPE(sess,"init");
    CHECK_PARAM_TYPE(uris,KS,"init");
    char* csvUris = NULL;
    int x,currentLen = 0;
    int idx = getInt(sess);
    for (x=0;x<uris->n;x++)
    {
        char* uri = kS(uris)[x];
        int uriLen = strlen(uri);
        csvUris = realloc(csvUris,currentLen+uriLen+1);
        memcpy(csvUris+currentLen,uri,uriLen);
        currentLen += uriLen;
        if (x==uris->n-1)
            csvUris[currentLen]='\0';
        else
            csvUris[currentLen]=',';
        ++currentLen;
    }
    LDAP* session = NULL;
    int res = ldap_initialize( &session, csvUris);
    free(csvUris);
    if (LDAP_SUCCESS == res)
        addSession(idx,session);
    return ki(res);
}

K kdbldap_start_tls(K sess)
{
    CHECK_PARAM_INT_TYPE(sess,"start_tls");
    int idx = getInt(sess);
    void* session = getSession(idx);
    CHECK_SESSION(session);
    int res= ldap_start_tls_s(session,NULL,NULL);
    return ki(res);
}

static K setStringOption(LDAP* ld, int option, K value)
{
    CHECK_PARAM_STRING_TYPE(value,"set_option");
    char* valueStr = createString(value);
    int res = ldap_set_option(ld, option, valueStr);
    free(valueStr);
    return ki(res);
}

static K setIntOption(LDAP* ld, int option, K value)
{
    CHECK_PARAM_INT_TYPE(value,"set_option");
    int val = getInt(value);
    return ki(ldap_set_option(ld, option, &val));
} 

static K setBerLenOption(LDAP* ld, int option, K value)
{
    CHECK_PARAM_TYPE(value,-KJ,"set_option");
    ber_len_t val = value->j;
    return ki(ldap_set_option(ld, option, &val));
} 

static K setTimevalOption(LDAP* ld, int option, K value)
{
    CHECK_PARAM_INT_TYPE(value,"set_option");
    int val = getInt(value);
    struct timeval timeVal = {val/1000000, val%1000000};
    return ki(ldap_set_option(ld, option, &timeVal));
}

static K set_option(LDAP* ld, K option,K value)
{
    CHECK_PARAM_TYPE(option,-KS,"set_option");
    
    /* LDAP SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_CONNECT_ASYNC")==0)
        return setIntOption(ld,LDAP_OPT_CONNECT_ASYNC,value);
    if (strcmp(option->s,"LDAP_OPT_DEBUG_LEVEL")==0)
        return setIntOption(ld,LDAP_OPT_DEBUG_LEVEL,value);
    if (strcmp(option->s,"LDAP_OPT_DEREF")==0)
        return setIntOption(ld,LDAP_OPT_DEREF,value);
    if (strcmp(option->s,"LDAP_OPT_DIAGNOSTIC_MESSAGE")==0)
        return setStringOption(ld,LDAP_OPT_DIAGNOSTIC_MESSAGE,value);
    if (strcmp(option->s,"LDAP_OPT_MATCHED_DN")==0)
        return setStringOption(ld,LDAP_OPT_MATCHED_DN,value);
    if (strcmp(option->s,"LDAP_OPT_NETWORK_TIMEOUT")==0)
        return setTimevalOption(ld,LDAP_OPT_NETWORK_TIMEOUT,value);
    if (strcmp(option->s,"LDAP_OPT_PROTOCOL_VERSION")==0)
        return setIntOption(ld,LDAP_OPT_PROTOCOL_VERSION,value);
    if (strcmp(option->s,"LDAP_OPT_REFERRALS")==0)
    {
        CHECK_PARAM_INT_TYPE(value,"set_option");
        int val = getInt(value);
        if (val==0)
            return ki(ldap_set_option(ld, LDAP_OPT_REFERRALS, LDAP_OPT_OFF));
        return ki(ldap_set_option(ld, LDAP_OPT_REFERRALS, LDAP_OPT_ON));
    }
    if (strcmp(option->s,"LDAP_OPT_RESULT_CODE")==0)
        return setIntOption(ld,LDAP_OPT_RESULT_CODE,value);
    if (strcmp(option->s,"LDAP_OPT_SIZELIMIT")==0)
        return setIntOption(ld,LDAP_OPT_SIZELIMIT,value);
    if (strcmp(option->s,"LDAP_OPT_TIMELIMIT")==0)
        return setIntOption(ld,LDAP_OPT_TIMELIMIT,value);
    if (strcmp(option->s,"LDAP_OPT_TIMEOUT")==0)
        return setTimevalOption(ld,LDAP_OPT_TIMEOUT,value);
    /* SASL SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_X_SASL_MAXBUFSIZE")==0)
        return setBerLenOption(ld,LDAP_OPT_X_SASL_MAXBUFSIZE,value);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_NOCANON")==0)
        return setIntOption(ld,LDAP_OPT_X_SASL_NOCANON,value);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_SECPROPS")==0)
        return setStringOption(ld,LDAP_OPT_X_SASL_SECPROPS,value);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_SSF_EXTERNAL")==0)
        return setBerLenOption(ld,LDAP_OPT_X_SASL_SSF_EXTERNAL,value);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_SSF_MAX")==0)
        return setBerLenOption(ld,LDAP_OPT_X_SASL_SSF_MAX,value);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_SSF_MIN")==0)
        return setBerLenOption(ld,LDAP_OPT_X_SASL_SSF_MIN,value);
    /* TCP SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_IDLE")==0)
        return setIntOption(ld,LDAP_OPT_X_KEEPALIVE_IDLE,value);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_PROBES")==0)
        return setIntOption(ld,LDAP_OPT_X_KEEPALIVE_PROBES,value);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_INTERVAL")==0)
        return setIntOption(ld,LDAP_OPT_X_KEEPALIVE_INTERVAL,value);
    /* TLS SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CACERTDIR")==0)
        return setStringOption(ld,LDAP_OPT_X_TLS_CACERTDIR,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CACERTFILE")==0)
        return setStringOption(ld,LDAP_OPT_X_TLS_CACERTFILE,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CERTFILE")==0)
        return setStringOption(ld,LDAP_OPT_X_TLS_CERTFILE,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CIPHER_SUITE")==0)
        return setStringOption(ld,LDAP_OPT_X_TLS_CIPHER_SUITE,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CRLCHECK")==0)
        return setIntOption(ld,LDAP_OPT_X_TLS_CRLCHECK,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CRLFILE")==0)
        return setStringOption(ld,LDAP_OPT_X_TLS_CRLFILE,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_DHFILE")==0)
        return setStringOption(ld,LDAP_OPT_X_TLS_DHFILE,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_KEYFILE")==0)
        return setStringOption(ld,LDAP_OPT_X_TLS_KEYFILE,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_NEWCTX")==0)
        return setIntOption(ld,LDAP_OPT_X_TLS_NEWCTX,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_PROTOCOL_MIN")==0)
        return setIntOption(ld,LDAP_OPT_X_TLS_PROTOCOL_MIN,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_RANDOM_FILE")==0)
        return setStringOption(ld,LDAP_OPT_X_TLS_RANDOM_FILE,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_REQUIRE_CERT")==0)
        return setIntOption(ld,LDAP_OPT_X_TLS_REQUIRE_CERT,value);
    return krr("Unsupported option");
}

K kdbldap_set_global_option(K option,K value)
{
    return set_option(NULL,option,value);
}

K kdbldap_set_option(K sess,K option,K value)
{
    CHECK_PARAM_INT_TYPE(sess,"set_option");
    int idx = getInt(sess);
    void* session = getSession(idx);
    CHECK_SESSION(session);
    return set_option(session,option,value);
}

static K getStringOption(LDAP* ld, int option)
{
    char* valueStr = NULL;
    ldap_get_option(ld, option, &valueStr);
    if (valueStr)
    {
        K val = kp(valueStr);
        ldap_memfree(valueStr);
        return val;
    }
    return kp("");
}

static K getIntOption(LDAP* ld, int option)
{
    int res=0;
    ldap_get_option(ld, option, &res);
    return ki(res);
} 

static K getBerLenOption(LDAP* ld, int option)
{
    ber_len_t res;
    ldap_get_option(ld, option, &res);
    return kj(res);
}

static K getTimevalOption(LDAP* ld, int option)
{
    int res=0;
    struct timeval* timeVal = NULL;
    ldap_get_option(ld, option, &timeVal);
    if (timeVal==NULL)
        return ki(0);
    res = (timeVal->tv_sec * 1000000) + timeVal->tv_usec;
    ldap_memfree(timeVal);
    return ki(res);
}

static K get_option(LDAP* ld,K option)
{
    CHECK_PARAM_TYPE(option,-KS,"set_option");
    
    /* LDAP SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_API_FEATURE_INFO")==0)
    {
        int featureCnt = 0;
        LDAPAPIInfo info;
        info.ldapai_info_version = LDAP_API_INFO_VERSION;
        int res = ldap_get_option(ld, LDAP_OPT_API_INFO, &info);
        if (res != LDAP_OPT_SUCCESS)
            return krr("Problem retrieving option");
        ldap_memfree(info.ldapai_vendor_name);
        if (info.ldapai_extensions != NULL)
        {
            for(featureCnt=0; info.ldapai_extensions[featureCnt] != NULL; featureCnt++);
            K keys = ktn(KS,featureCnt);
            K vals = ktn(KI,featureCnt);
            int i=0;
            for(i=0; info.ldapai_extensions[i] != NULL; i++)
            {
                kS(keys)[i]=ss((char*)info.ldapai_extensions[i]);
                LDAPAPIFeatureInfo featInfo;
                featInfo.ldapaif_info_version = LDAP_FEATURE_INFO_VERSION;
                featInfo.ldapaif_name = info.ldapai_extensions[i];
                featInfo.ldapaif_version = 0;
                ldap_get_option(ld, LDAP_OPT_API_FEATURE_INFO, &featInfo);
                kI(vals)[i]=featInfo.ldapaif_version;
                ldap_memfree(info.ldapai_extensions[i]);
            }
            ldap_memfree(info.ldapai_extensions);
            return xD(keys,vals);
        }
        return xD(ktn(KS,0),ktn(KI,0));
    }
    if (strcmp(option->s,"LDAP_OPT_API_INFO")==0)
    {
        LDAPAPIInfo info;
        info.ldapai_info_version = LDAP_API_INFO_VERSION;
        int res = ldap_get_option(ld, LDAP_OPT_API_INFO, &info);
        if (res != LDAP_OPT_SUCCESS)
            return krr("Problem retrieving option");

        K ext = ktn(KS,0);
        if (info.ldapai_extensions != NULL)
        {
           int i=0;
           for(i=0; info.ldapai_extensions[i] != NULL; i++);
           r0(ext);
           ext = ktn(KS,i);
           for(i=0; info.ldapai_extensions[i] != NULL; i++)
           {
                kS(ext)[i]=ss(info.ldapai_extensions[i]);
                ldap_memfree(info.ldapai_extensions[i]);
           }
           ldap_memfree(info.ldapai_extensions);
        }

        K keys = ktn(KS,5);
        kS(keys)[0]=ss((char*)"apiVersion");
        kS(keys)[1]=ss((char*)"protocolVersion");
        kS(keys)[2]=ss((char*)"vendorVersion");
        kS(keys)[3]=ss((char*)"vendorName");
        kS(keys)[4]=ss((char*)"ext");
        K vals = knk(5,ki(info.ldapai_api_version),ki(info.ldapai_protocol_version),ki(info.ldapai_vendor_version),ks(info.ldapai_vendor_name),ext);

        ldap_memfree(info.ldapai_vendor_name);
        return xD(keys,vals);
    }
    if (strcmp(option->s,"LDAP_OPT_CONNECT_ASYNC")==0)
        return getIntOption(ld,LDAP_OPT_CONNECT_ASYNC);
    if (strcmp(option->s,"LDAP_OPT_DEBUG_LEVEL")==0)
        return getIntOption(ld,LDAP_OPT_DEBUG_LEVEL);
    if (strcmp(option->s,"LDAP_OPT_DEREF")==0)
        return getIntOption(ld,LDAP_OPT_DEREF);
    if (strcmp(option->s,"LDAP_OPT_DESC")==0)
        return getIntOption(ld,LDAP_OPT_DESC);
    if (strcmp(option->s,"LDAP_OPT_DIAGNOSTIC_MESSAGE")==0)
        return getStringOption(ld,LDAP_OPT_DIAGNOSTIC_MESSAGE);
    if (strcmp(option->s,"LDAP_OPT_NETWORK_TIMEOUT")==0)
        return getTimevalOption(ld,LDAP_OPT_NETWORK_TIMEOUT);
    if (strcmp(option->s,"LDAP_OPT_MATCHED_DN")==0)
        return getStringOption(ld,LDAP_OPT_MATCHED_DN);
    if (strcmp(option->s,"LDAP_OPT_PROTOCOL_VERSION")==0)
        return getIntOption(ld,LDAP_OPT_PROTOCOL_VERSION);
    if (strcmp(option->s,"LDAP_OPT_REFERRALS")==0)
        return getIntOption(ld,LDAP_OPT_REFERRALS);
    if (strcmp(option->s,"LDAP_OPT_RESULT_CODE")==0)
        return getIntOption(ld,LDAP_OPT_RESULT_CODE);
    if (strcmp(option->s,"LDAP_OPT_SIZELIMIT")==0)
        return getIntOption(ld,LDAP_OPT_SIZELIMIT);
    if (strcmp(option->s,"LDAP_OPT_TIMELIMIT")==0)
        return getIntOption(ld,LDAP_OPT_TIMELIMIT);
    if (strcmp(option->s,"LDAP_OPT_TIMEOUT")==0)
        return getTimevalOption(ld,LDAP_OPT_TIMEOUT);
    /* SASL SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_X_SASL_AUTHCID")==0)
        return getStringOption(ld,LDAP_OPT_X_SASL_AUTHCID);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_AUTHZID")==0)
        return getStringOption(ld,LDAP_OPT_X_SASL_AUTHZID);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_MAXBUFSIZE")==0)
        return getBerLenOption(ld,LDAP_OPT_X_SASL_MAXBUFSIZE);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_MECH")==0)
        return getStringOption(ld,LDAP_OPT_X_SASL_MECH);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_MECHLIST")==0)
        return getStringOption(ld,LDAP_OPT_X_SASL_MECHLIST);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_NOCANON")==0)
        return getIntOption(ld,LDAP_OPT_X_SASL_NOCANON);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_REALM")==0)
        return getStringOption(ld,LDAP_OPT_X_SASL_REALM);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_SSF")==0)
        return getBerLenOption(ld,LDAP_OPT_X_SASL_SSF);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_SSF_MAX")==0)
        return getBerLenOption(ld,LDAP_OPT_X_SASL_SSF_MAX);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_SSF_MIN")==0)
        return getBerLenOption(ld,LDAP_OPT_X_SASL_SSF_MIN);
    if (strcmp(option->s,"LDAP_OPT_X_SASL_USERNAME")==0)
        return getStringOption(ld,LDAP_OPT_X_SASL_USERNAME);
    /* TCP SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_IDLE")==0)
        return getIntOption(ld,LDAP_OPT_X_KEEPALIVE_IDLE);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_PROBES")==0)
        return getIntOption(ld,LDAP_OPT_X_KEEPALIVE_PROBES);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_INTERVAL")==0)
        return getIntOption(ld,LDAP_OPT_X_KEEPALIVE_INTERVAL);
    /* TLS SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CACERTDIR")==0)
        return getStringOption(ld,LDAP_OPT_X_TLS_CACERTDIR);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CACERTFILE")==0)
        return getStringOption(ld,LDAP_OPT_X_TLS_CACERTFILE);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CERTFILE")==0)
        return getStringOption(ld,LDAP_OPT_X_TLS_CERTFILE);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CIPHER_SUITE")==0)
        return getStringOption(ld,LDAP_OPT_X_TLS_CIPHER_SUITE);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CRLCHECK")==0)
        return getIntOption(ld,LDAP_OPT_X_TLS_CRLCHECK);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_CRLFILE")==0)
        return getStringOption(ld,LDAP_OPT_X_TLS_CRLFILE);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_DHFILE")==0)
        return getStringOption(ld,LDAP_OPT_X_TLS_DHFILE);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_KEYFILE")==0)
        return getStringOption(ld,LDAP_OPT_X_TLS_KEYFILE);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_PROTOCOL_MIN")==0)
        return getIntOption(ld,LDAP_OPT_X_TLS_PROTOCOL_MIN);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_RANDOM_FILE")==0)
        return getStringOption(ld,LDAP_OPT_X_TLS_RANDOM_FILE);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_REQUIRE_CERT")==0)
        return getIntOption(ld,LDAP_OPT_X_TLS_REQUIRE_CERT);
    return krr("Unsupported option");
}

K kdbldap_get_global_option(K option)
{
    return get_option(NULL,option);
}

K kdbldap_get_option(K sess,K option)
{
    CHECK_PARAM_INT_TYPE(sess,"get_option");
    int idx = getInt(sess);
    void* session = getSession(idx);
    CHECK_SESSION(session);
    return get_option(session,option);
}

K kdbldap_bind_s(K sess, K dn, K cred, K mech)
{
    CHECK_PARAM_STRING_TYPE(dn,"bind");
    CHECK_PARAM_BYTESTRING_TYPE(cred,"bind");
    CHECK_PARAM_STRING_TYPE(mech,"bind");
    CHECK_PARAM_INT_TYPE(sess,"bind");
    int idx = getInt(sess);
    void* session = getSession(idx);
    CHECK_SESSION(session);
    char* dnStr = createString(dn);
    char* credStr = createString(cred);
    char* mechStr = createString(mech);
    struct berval* scred = NULL;
    struct berval pass = { 0, NULL };
    ber_str2bv(credStr,getStringLen(cred),0,&pass);
    int res = ldap_sasl_bind_s( session,dnStr,((mechStr[0]=='\0')?LDAP_SASL_SIMPLE:mechStr),&pass,NULL,NULL,&scred);
    free(dnStr);
    free(credStr);
    free(mechStr);
    
    int credSize = 0;
    if (scred!=NULL)
        credSize = scred->bv_len;

    K resultkeys = ktn(KS,2);
    kS(resultkeys)[0]=ss((char*)"ReturnCode");
    kS(resultkeys)[1]=ss((char*)"Credentials");
    K resultvals = knk(0);
    jk(&resultvals,ki(res));
    K creds = ktn(KG, credSize);
    if (credSize > 0)
        memcpy(cred->G0, scred->bv_val, scred->bv_len);
    jk(&resultvals,creds);

    ber_bvfree(scred);
    return xD(resultkeys,resultvals);;
}

K kdbldap_search_s(K sess,K baseDn, K scope, K filter, K attrs, K attrsOnly, K timeLimit, K sizeLimit)
{
    CHECK_PARAM_STRING_TYPE(baseDn,"search");
    CHECK_PARAM_INT_TYPE(scope,"search");
    CHECK_PARAM_STRING_TYPE(filter,"search");
    CHECK_PARAM_TYPE(attrs,KS,"search");
    CHECK_PARAM_INT_TYPE(attrsOnly,"search");
    CHECK_PARAM_INT_TYPE(timeLimit,"search");
    CHECK_PARAM_INT_TYPE(sizeLimit,"search");
    CHECK_PARAM_INT_TYPE(sess,"search");
    int idx = getInt(sess);
    void* session = getSession(idx);
    CHECK_SESSION(session);
    char* baseStr = createString(baseDn);
    char* filterStr = createString(filter);
    int scopeInt = getInt(scope);
    int attrsOnlyInt = getInt(attrsOnly);
    int maxTime = getInt(timeLimit);
    int maxSize = getInt(sizeLimit);
    char** attrsArr = NULL;
    struct timeval timeout = {maxTime/1000000, maxTime%1000000};
    if (attrs->n > 0)
    {
        attrsArr = malloc (((attrs->n)+1) * sizeof(char*));
        int x=0;
        for (x=0;x<attrs->n;x++)
            attrsArr[x]=kS(attrs)[x];
        attrsArr[x]=NULL;
    }
    LDAPMessage* msg = NULL;
    int res = ldap_search_ext_s(
              session,
              baseStr,
              scopeInt,  /* e.g. LDAP_SCOPE_SUBTREE */
              ((filterStr[0]=='\0')?NULL:filterStr),
              attrsArr, /* char* attrs[] */
              attrsOnlyInt, /* 0 = attribute values and descriptions, otherwise just descriptions */
              NULL, /* LDAPControl **serverctrls. NULL for no serverctrls. Not currently used */
              NULL, /* LDAPControl **clientctrls. NULL for no clientctrls. Not currently used */
              (maxTime>0?(&timeout):NULL), /* struct timeval *timeout. NULL is not time limit */
              maxSize,  /* 0 is LDAP_NO_LIMIT */
              &msg);
    free(attrsArr);
    free(filterStr);
    free(baseStr);
    if (msg != NULL)
    {
        K Kentries = knk(0);
        K Kattrs = knk(0);
        LDAPMessage* entry = NULL;
        for (entry=ldap_first_entry(session,msg);entry!=NULL;entry=ldap_next_entry(session,entry))
        {
            //K Kentry = knk(0);
            char* entryDn = ldap_get_dn(session,entry);
            if (entryDn)
            {
                jk(&Kentries,kp(entryDn));
                ldap_memfree(entryDn);
            }
            else
                jk(&Kentries,kp((char*)""));
            BerElement* pBer = NULL;
            char* attribute = NULL;
            K KattrsNames = ktn(KS,0);
            K kAttrsVals = knk(0);
            for (attribute=ldap_first_attribute(session,entry,&pBer);attribute!=NULL;attribute=ldap_next_attribute(session,entry,pBer))
            {
                K kAttrVal = knk(0);
                struct berval** vals = ldap_get_values_len(session,entry,attribute);
                if (vals!=NULL)
                {
                    int valCount = ldap_count_values_len(vals);
                    int valPos;
                    for (valPos=0;valPos<valCount;valPos++)
                        jk(&kAttrVal,kpn((char*)vals[valPos]->bv_val,vals[valPos]->bv_len));
                    ldap_value_free_len(vals);
                }
                js(&KattrsNames,ss(attribute));
                jk(&kAttrsVals,kAttrVal);
                ldap_memfree(attribute);
            }
            jk(&Kattrs,xD(KattrsNames,kAttrsVals));
        }
        K entrykeys = ktn(KS,2);
        kS(entrykeys)[0]=ss((char*)"DN");
        kS(entrykeys)[1]=ss((char*)"Attributes");
        K values = knk(0);
        jk(&values,Kentries);
        jk(&values,Kattrs);
        K KallEntries = xT(xD(entrykeys,values));

        K Kreferrals = knk(0);
        for(entry=ldap_first_reference(session,msg);entry!=NULL;entry=ldap_next_reference(session,entry))
        {
            char **refs = NULL;
            if (ldap_parse_reference(session, entry, &refs, NULL, 0) != LDAP_SUCCESS)
                continue;
            if (refs == NULL)
                continue;
            int i=0;
            for (i=0; refs[i] != NULL; i++)
                jk(&Kreferrals,kp(refs[i]));
            ber_memvfree((void**)refs);
        }
        ldap_msgfree(msg);

        K resultkeys = ktn(KS,3);
        kS(resultkeys)[0]=ss((char*)"ReturnCode");
        kS(resultkeys)[1]=ss((char*)"Entries");
        kS(resultkeys)[2]=ss((char*)"Referrals");
        K resultvals = knk(0);
        jk(&resultvals,ki(res));
        jk(&resultvals,KallEntries);
        jk(&resultvals,Kreferrals);
        return xD(resultkeys,resultvals);
    }        
    K entrykeys = ktn(KS,2);
    kS(entrykeys)[0]=ss((char*)"DN");
    kS(entrykeys)[1]=ss((char*)"Attributes");
    K values = knk(0);
    K KallEntries = xT(xD(entrykeys,values));

    K resultkeys = ktn(KS,3);
    kS(resultkeys)[0]=ss((char*)"ReturnCode");
    kS(resultkeys)[1]=ss((char*)"Entries");
    kS(resultkeys)[2]=ss((char*)"Referrals");
    K resultvals = knk(0);
    jk(&resultvals,ki(res));
    jk(&resultvals,KallEntries);
    jk(&resultvals,knk(0));
    return xD(resultkeys,resultvals);
}

K kdbldap_unbind_s(K sess)
{
    CHECK_PARAM_INT_TYPE(sess,"unbind");
    int idx = getInt(sess);
    void* session = getSession(idx);
    CHECK_SESSION(session);
    int res = ldap_unbind_ext_s(session,NULL,NULL);
    if (LDAP_SUCCESS == res)
        removeSession(idx);
    return ki(res);
}

K kdbldap_err2string(K err)
{
    CHECK_PARAM_INT_TYPE(err,"err2string");
    int errInt = getInt(err);
    return kp(ldap_err2string(errInt));
}
