#ifndef KDBLDAP_H_
#define KDBLDAP_H_

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
 * @param sess int/long that you will use to track the session in subsequent calls
 * @param uris Symbol List type. List of connection URIs.
 * e.g. ldap://127.0.0.1:389
 */
EXP K kdbldap_init(K sess,K uris);

/**
 * Sets options globally that affect LDAP operating procedures
 * 
 * @param option a symbol for the option you wish to set globally
 * @param value value of the option (type depends on option selected)
 */
EXP K kdbldap_set_global_option(K option,K value);

/**
 * Sets session options that affect LDAP operating procedures
 * 
 * @param sess int/long that represents the session previously created via .ldap.init
 * @param option a symbol for the option you wish to set for the session 
 * @param value value of the option (type depends on option selected)
 */
EXP K kdbldap_set_option(K sess,K option,K value);

/**
 * Gets options globally that affect LDAP operating procedures
 * 
 * @param option a symbol for the global option you wish to get
 */
EXP K kdbldap_get_global_option(K option);

/**
 * Gets session options that affect LDAP operating procedures
 * 
 * @param sess int/long that represents the session previously created via .ldap.init
 * @param option a symbol for the option you wish to get for the session
 */
EXP K kdbldap_get_option(K sess,K option);

/**
 * Synchronous bind operations are used to authenticate clients (and the users or applications behind them) 
 * to the directory server
 * 
 * @param sess int/long that represents the session previously created via .ldap.init
 * @param dn string/symbol. The DN of the user to authenticate
 * @param cred char/byte array or symbol. LDAP credentials (e.g. password). Pass empty string/symbol or generic null when no password required for connection.
 * @param mech string/symbol. Auth mechanism. Pass an empty string or generic null to use the default LDAP_SASL_SIMPLE mechanism
 */
EXP K kdbldap_bind_s(K sess, K dn, K cred, K mech);

/**
 * Synchronous search for partial or complete copies of entries based on a search criteria. 
 * 
 * @param sess int/long that represents the session previously created via .ldap.init
 * @param baseDn string/symbol. The base of the subtree to search from.
 * @param scope int/long 0 (LDAP_SCOPE_BASE), 1 (LDAP_SCOPE_ONELEVEL), 2 (LDAP_SCOPE_SUBTREE), 3 (LDAP_SCOPE_CHILDREN)
 * @param filter string/symbol. The filter to be applied to the search
 * @param attrs symbol list. The set of attributes to include in the result.
 * @param attrsOnly int/long. Should be set to a non-zero value if only attribute descriptions are wanted. 
 * It should be set to zero (0) if both attributes descriptions and attribute values are wanted
 * @param timeLimit int/long. Max number of microseconds to wait for a result. 0 represents no limit. Note that the server may impose its own limit.
 * @param sizeLimit int/long. Max number of entries to use in the result. 0 represents no limit. Note that the server may impose its own limit
 */
EXP K kdbldap_search_s(K sess, K baseDn, K scope, K filter, K attrs, K attrsOnly, K timeLimit, K sizeLimit);

/**
 * Synchronous unbind from the directory, terminate the current association, and free resources.
 * 
 * @param sess int/long that represents the session previously created via .ldap.init
 */
EXP K kdbldap_unbind_s(K sess);

/** 
 * Returns string representation of an ldap error code
 * 
 * @param err Int representing ldap error code
 */
EXP K kdbldap_err2string(K err);

#ifdef __cplusplus
}
#endif

#endif