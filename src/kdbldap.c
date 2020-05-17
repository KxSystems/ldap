
#include <ldap.h>
#include "kdbldap.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK_PARAM_TYPE(x,y,z) {if (x->t != y) return krr((S)"Function " #z " called with incorrect param type for " #x "");}

static LDAP* LDAP_SESSION = NULL;

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

K kdbldap_set_option(K global, K option,K value)
{
    CHECK_PARAM_TYPE(global,-KB,"set_option");
    CHECK_PARAM_TYPE(option,-KI,"set_option");
    LDAP* ld = (global->g)?NULL:LDAP_SESSION;
    /* TODO */
    printf("LDAP_OPT_PROTOCOL_VERSION is %d\n",LDAP_OPT_PROTOCOL_VERSION);
    // example - returnCode = ldap_set_option(ld, option->i, (void*)&version);
    return ki(1);
}