#include <ldap.h>
#include "kdbldap.h"
#include <stdio.h>

static LDAP* LDAP_SESSION = NULL;

K kdbldap_init(K todo)
{
    /* TODO parse URIs from list */
    char* URI = "ldap://127.0.0.1:389";
    return ki(ldap_initialize( &LDAP_SESSION, URI));
}

K kdbldap_set_option(K option,K value)
{
    /* TODO */
    printf("LDAP_OPT_PROTOCOL_VERSION is %d\n",LDAP_OPT_PROTOCOL_VERSION);
    // example - returnCode = ldap_set_option(pLdapConnection, LDAP_OPT_PROTOCOL_VERSION, (void*)&version);
    return ki(1);
}