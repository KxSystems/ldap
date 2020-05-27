#ifndef DELTALDAP_H_
#define DELTALDAP_H_

#include "k.h"

#ifdef _WIN32
#define EXP __declspec(dllexport)
#else
#define EXP
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialise library with list of potential LDAP servers
 * to use.
 * 
 * @param uris Symbol List type. List of connection URIs.
 * e.g. ldap://127.0.0.1:389
 */
EXP K kdbldap_init(K uris);

/* TODO */
EXP K kdbldap_set_global_option(K option,K value);

/* TODO */
EXP K kdbldap_set_option(K option,K value);

/* TODO */
EXP K kdbldap_get_global_option(K option);

/* TODO */
EXP K kdbldap_get_option(K option);

/* TODO */
EXP K kdbldap_bind(K dn, K cred);

/* TODO */
EXP K kdbldap_search(K baseDn, K scope, K filter, K attrs, K attrsOnly, K timeLimit, K sizeLimit);

/* TODO */
EXP K kdbldap_unbind(K unused);

EXP K kdbldap_err2string(K err);

#ifdef __cplusplus
}
#endif

#endif