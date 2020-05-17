#include <ldap.h>
#include "kdbldap.h"
#include <stdio.h>

#define CHECK_PARAM_TYPE(x,y,z) {if (x->t != y) return krr((S)"Function " #z " called with incorrect param type for " #x "");}

static LDAP* LDAP_SESSION = NULL;

K kdbldap_init(K todo)
{
    /* TODO parse URIs from list */
    char* URI = "ldap://127.0.0.1:389";
    return ki(ldap_initialize( &LDAP_SESSION, URI));
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