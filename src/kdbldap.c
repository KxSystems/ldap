
#include <ldap.h>
#include "kdbldap.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK_PARAM_TYPE(x,y,z) {if (x->t != y) return krr((S)"Function " #z " called with incorrect param type for " #x "");}
#define CHECK_PARAM_STRING_TYPE(x,z) {if (x->t != -KS && x->t != KC) return krr((S)"Function " #z " called with incorrect param type for " #x "");}
#define CHECK_PARAM_INT_TYPE(x,z) {if (x->t != -KI && x->t != -KJ) return krr((S)"Function " #z " called with incorrect param type for " #x "");}

static LDAP* LDAP_SESSION = NULL;

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
    if (in->t == KC)
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

K kdbldap_init(K uris)
{
    CHECK_PARAM_TYPE(uris,KS,"init");
    char* csvUris = NULL;
    int x,currentLen = 0;
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
    return ki(ldap_initialize( &LDAP_SESSION, csvUris));
}

static K setIntOption(LDAP* ld, int option, K value)
{
    CHECK_PARAM_INT_TYPE(value,"set_option");
    int val = getInt(value);
    return ki(ldap_set_option(ld, option, &val));
} 

K kdbldap_set_option(K global, K option,K value)
{
    CHECK_PARAM_TYPE(global,-KB,"set_option");
    CHECK_PARAM_TYPE(option,-KS,"set_option");
    LDAP* ld = (global->g)?NULL:LDAP_SESSION;
    
    /* LDAP SUPPORTED OPTIONS */
    /* TODO LDAP_OPT_CLIENT_CONTROLS */
    /* TODO LDAP_OPT_CONNECT_CB */
    /* TODO LDAP_OPT_DIAGNOSTIC_MESSAGE */
    /* TODO LDAP_OPT_MATCHED_DN */
    /* TODO LDAP_OPT_NETWORK_TIMEOUT */
    /* TODO LDAP_OPT_SERVER_CONTROLS */
    /* TODO LDAP_OPT_TIMEOUT */
    if (strcmp(option->s,"LDAP_OPT_CONNECT_ASYNC")==0)
        return setIntOption(ld,LDAP_OPT_CONNECT_ASYNC,value);
    if (strcmp(option->s,"LDAP_OPT_DEBUG_LEVEL")==0)
        return setIntOption(ld,LDAP_OPT_DEBUG_LEVEL,value);
    if (strcmp(option->s,"LDAP_OPT_DEREF")==0)
        return setIntOption(ld,LDAP_OPT_DEREF,value);
    if (strcmp(option->s,"LDAP_OPT_PROTOCOL_VERSION")==0)
        return setIntOption(ld,LDAP_OPT_PROTOCOL_VERSION,value);
    if (strcmp(option->s,"LDAP_OPT_REFERRALS")==0)
        return setIntOption(ld,LDAP_OPT_REFERRALS,value);
    if (strcmp(option->s,"LDAP_OPT_RESULT_CODE")==0)
        return setIntOption(ld,LDAP_OPT_RESULT_CODE,value);
    if (strcmp(option->s,"LDAP_OPT_SIZELIMIT")==0)
        return setIntOption(ld,LDAP_OPT_SIZELIMIT,value);
    if (strcmp(option->s,"LDAP_OPT_TIMELIMIT")==0)
        return setIntOption(ld,LDAP_OPT_TIMELIMIT,value);
    /* SASL SUPPORTED OPTIONS */
    /* TODO LDAP_OPT_X_SASL_MAXBUFSIZE */
    if (strcmp(option->s,"LDAP_OPT_X_SASL_NOCANON")==0)
        return setIntOption(ld,LDAP_OPT_X_SASL_NOCANON,value);
    /* TODO LDAP_OPT_X_SASL_SECPROPS */
    /* TODO LDAP_OPT_X_SASL_SSF_EXTERNAL */
    /* TODO LDAP_OPT_X_SASL_SSF_MAX */
    /* TODO LDAP_OPT_X_SASL_SSF_MIN */
    /* TCP SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_IDLE")==0)
        return setIntOption(ld,LDAP_OPT_X_KEEPALIVE_IDLE,value);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_PROBES")==0)
        return setIntOption(ld,LDAP_OPT_X_KEEPALIVE_PROBES,value);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_INTERVAL")==0)
        return setIntOption(ld,LDAP_OPT_X_KEEPALIVE_INTERVAL,value);
    /* TLS SUPPORTED OPTIONS */
    /* TODO LDAP_OPT_X_TLS_CACERTDIR */
    /* TODO LDAP_OPT_X_TLS_CACERTFILE */
    /* TODO LDAP_OPT_X_TLS_CERTFILE */
    /* TODO LDAP_OPT_X_TLS_CIPHER_SUITE */
    /* TODO LDAP_OPT_X_TLS_CONNECT_ARG */
    /* TODO LDAP_OPT_X_TLS_CONNECT_CB */
    /* TODO LDAP_OPT_X_TLS_CRLCHECK */
    /* TODO LDAP_OPT_X_TLS_CRLFILE */
    /* TODO LDAP_OPT_X_TLS_CTX */
    /* TODO LDAP_OPT_X_TLS_DHFILE */
    /* TODO LDAP_OPT_X_TLS_KEYFILE */
    if (strcmp(option->s,"LDAP_OPT_X_TLS_NEWCTX")==0)
        return setIntOption(ld,LDAP_OPT_X_TLS_NEWCTX,value);
    if (strcmp(option->s,"LDAP_OPT_X_TLS_PROTOCOL_MIN")==0)
        return setIntOption(ld,LDAP_OPT_X_TLS_PROTOCOL_MIN,value);
    /* TODO LDAP_OPT_X_TLS_RANDOM_FILE */
    if (strcmp(option->s,"LDAP_OPT_X_TLS_REQUIRE_CERT")==0)
        return setIntOption(ld,LDAP_OPT_X_TLS_REQUIRE_CERT,value);
    return krr("Unsupported option");
}

static K getIntOption(LDAP* ld, int option)
{
    int res=0;
    ldap_get_option(ld, option, &res);
    return ki(res);
} 

K kdbldap_get_option(K global,K option)
{
    CHECK_PARAM_TYPE(global,-KB,"set_option");
    CHECK_PARAM_TYPE(option,-KS,"set_option");
    LDAP* ld = (global->g)?NULL:LDAP_SESSION;
    
    /* LDAP SUPPORTED OPTIONS */
    /* TODO LDAP_OPT_API_FEATURE_INFO */
    /* TODO LDAP_OPT_CLIENT_CONTROLS */
    /* TODO LDAP_OPT_CONNECT_CB */
    /* TODO LDAP_OPT_DESC (int) */
    /* TODO LDAP_OPT_DIAGNOSTIC_MESSAGE */
    /* TODO LDAP_OPT_MATCHED_DN */
    /* TODO LDAP_OPT_NETWORK_TIMEOUT */
    /* TODO LDAP_OPT_SERVER_CONTROLS */
    /* TODO LDAP_OPT_SESSION_REFCNT (int) */
    /* TODO LDAP_OPT_SOCKBUF */
    /* TODO LDAP_OPT_TIMEOUT */
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
                kS(ext)[0]=ss(info.ldapai_extensions[i]);
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
    /* SASL SUPPORTED OPTIONS */
    /* TODO LDAP_OPT_X_SASL_AUTHCID */
    /* TODO LDAP_OPT_X_SASL_AUTHZID */
    /* TODO LDAP_OPT_X_SASL_MAXBUFSIZE */
    /* TODO LDAP_OPT_X_SASL_MECH */
    /* TODO LDAP_OPT_X_SASL_MECHLIST */
    if (strcmp(option->s,"LDAP_OPT_X_SASL_NOCANON")==0)
        return getIntOption(ld,LDAP_OPT_X_SASL_NOCANON);
    /* TODO LDAP_OPT_X_SASL_REALM */
    /* TODO LDAP_OPT_X_SASL_SSF */
    /* TODO LDAP_OPT_X_SASL_SSF_MAX */
    /* TODO LDAP_OPT_X_SASL_SSF_MIN */
    /* TODO LDAP_OPT_X_SASL_USERNAME */
    /* TCP SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_IDLE")==0)
        return getIntOption(ld,LDAP_OPT_X_KEEPALIVE_IDLE);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_PROBES")==0)
        return getIntOption(ld,LDAP_OPT_X_KEEPALIVE_PROBES);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_INTERVAL")==0)
        return getIntOption(ld,LDAP_OPT_X_KEEPALIVE_INTERVAL);
    /* TLS SUPPORTED OPTIONS */
    /* TODO LDAP_OPT_X_TLS_CACERTDIR */
    /* TODO LDAP_OPT_X_TLS_CACERTFILE */
    /* TODO LDAP_OPT_X_TLS_CERTFILE */
    /* TODO LDAP_OPT_X_TLS_CIPHER_SUITE */
    /* TODO LDAP_OPT_X_TLS_CONNECT_ARG */
    /* TODO LDAP_OPT_X_TLS_CONNECT_CB */
    /* TODO LDAP_OPT_X_TLS_CRLCHECK */
    /* TODO LDAP_OPT_X_TLS_CRLFILE */
    /* TODO LDAP_OPT_X_TLS_CTX */
    /* TODO LDAP_OPT_X_TLS_DHFILE */
    /* TODO LDAP_OPT_X_TLS_KEYFILE */
    if (strcmp(option->s,"LDAP_OPT_X_TLS_PROTOCOL_MIN")==0)
        return getIntOption(ld,LDAP_OPT_X_TLS_PROTOCOL_MIN);
    /* TODO LDAP_OPT_X_TLS_RANDOM_FILE */
    if (strcmp(option->s,"LDAP_OPT_X_TLS_REQUIRE_CERT")==0)
        return getIntOption(ld,LDAP_OPT_X_TLS_REQUIRE_CERT);
    /* TODO LDAP_OPT_X_TLS_SSL_CTX */
    return krr("Unsupported option");
}

K kdbldap_bind(K dn, K cred)
{
    CHECK_PARAM_STRING_TYPE(dn,"bind");
    CHECK_PARAM_STRING_TYPE(cred,"cred");
    char* dnStr = createString(dn);
    char* credStr = createString(cred);
    struct berval pass = { 0, NULL };
    ber_str2bv(credStr,0,0,&pass);
    /* TODO other bind params */
    int res = ldap_sasl_bind_s( LDAP_SESSION,dnStr,LDAP_SASL_SIMPLE,&pass,NULL,NULL,NULL);
    free(dnStr);
    free(credStr);
    return ki(res);
}

K kdbldap_search(K baseDn, K scope, K filter, K attrsOnly)
{
    CHECK_PARAM_STRING_TYPE(baseDn,"search");
    CHECK_PARAM_INT_TYPE(scope,"search");
    CHECK_PARAM_STRING_TYPE(filter,"search");
    CHECK_PARAM_INT_TYPE(attrsOnly,"search");
    char* baseStr = createString(baseDn);
    char* filterStr = createString(filter);
    int scopeInt = getInt(scope);
    int attrsOnlyInt = getInt(attrsOnly);
    LDAPMessage* msg = NULL;
    int res = ldap_search_ext_s(
              LDAP_SESSION,
              baseStr,
              scopeInt,  /* e.g. LDAP_SCOPE_SUBTREE */
              filterStr,
              NULL, /* char* attrs[] */
              attrsOnlyInt, /* 0 = attribute values and descriptions, otherwise just descriptions */
              NULL, /* LDAPControl **serverctrls */
              NULL, /* LDAPControl **clientctrls */
              NULL, /* struct timeval *timeout */
              LDAP_NO_LIMIT,  /* int sizelimit e.g. LDAP_NO_LIMIT */
              &msg);
    free(filterStr);
    free(baseStr);
    switch (res)
    {
        case LDAP_SIZELIMIT_EXCEEDED:
        case LDAP_TIMELIMIT_EXCEEDED:
        case LDAP_SUCCESS:
        {
            K Kentries = knk(0);
            LDAPMessage* entry = NULL;
            for (entry=ldap_first_entry(LDAP_SESSION,msg);entry!=NULL;entry=ldap_next_entry(LDAP_SESSION,entry))
            {
                K Kentry = knk(0);
                char* entryDn = ldap_get_dn(LDAP_SESSION,entry);
                if (entryDn)
                {
                    jk(&Kentry,kp(entryDn));
                    ldap_memfree(entryDn);
                }
                else
                    jk(&Kentry,kp((char*)""));
                BerElement* pBer = NULL;
                char* attribute = NULL;
                K Kattrs = knk(0);
                for (attribute=ldap_first_attribute(LDAP_SESSION,entry,&pBer);attribute!=NULL;attribute=ldap_next_attribute(LDAP_SESSION,entry,pBer))
                {
                    K kAttrVals = knk(0);
                    struct berval** vals = ldap_get_values_len(LDAP_SESSION,entry,attribute);
                    if (vals!=NULL)
                    {
                        int valCount = ldap_count_values_len(vals);
                        int valPos;
                        for (valPos=0;valPos<valCount;valPos++)
                            jk(&kAttrVals,kpn((char*)vals[valPos]->bv_val,vals[valPos]->bv_len));
                        ldap_value_free_len(vals);
                    }
                    K Kattribute = knk(2,ks(attribute),kAttrVals);
                    jk(&Kattrs,Kattribute);
                    ldap_memfree(attribute);
                }
                jk(&Kentry,Kattrs);
                jk(&Kentries,Kentry);
            }
            ldap_msgfree(msg);
            /* TODO indication of result code in return value incase of truncation */
            return Kentries;
        }
        default:
        {
            ldap_msgfree(msg);
            return ki(res);
        }
    }
}