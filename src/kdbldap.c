
#include <ldap.h>
#include "kdbldap.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK_PARAM_TYPE(x,y,z) {if (x->t != y) return krr((S)"Function " #z " called with incorrect param type for " #x "");}
#define CHECK_PARAM_INT_TYPE(x,z) {if (x->t != -KI && x->t != -KJ) return krr((S)"Function " #z " called with incorrect param type for " #x "");}

static LDAP* LDAP_SESSION = NULL;

static int getInt(K val)
{
    if (val->t==-KI)
        return val->i;
    return (int)val->j;
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
    /* TODO other ldap options */
    /* SASL SUPPORTED OPTIONS - TODO */
    /* TCP SUPPORTED OPTIONS */
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_IDLE")==0)
        return setIntOption(ld,LDAP_OPT_X_KEEPALIVE_IDLE,value);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_PROBES")==0)
        return setIntOption(ld,LDAP_OPT_X_KEEPALIVE_PROBES,value);
    if (strcmp(option->s,"LDAP_OPT_X_KEEPALIVE_INTERVAL")==0)
        return setIntOption(ld,LDAP_OPT_X_KEEPALIVE_INTERVAL,value);
    /* TLS SUPPORTED OPTIONS - TODO */
    return krr("Unsupported option");
}

K kdbldap_get_option(K global,K option)
{
    CHECK_PARAM_TYPE(global,-KB,"set_option");
    CHECK_PARAM_TYPE(option,-KS,"set_option");
    LDAP* ld = (global->g)?NULL:LDAP_SESSION;
    
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
    /* TODO add other possible options */
    return krr("Unsupported option");
}