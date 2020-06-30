# kdb+ interface for Solace (Examples)

## Installation

Follow the installation steps from main README.md.

Note, as per the installation steps, that `script/ldap.q` should be placed in the examples directory or in the KDB+ installation directory.

## Example LDAP server

If you do not have an LDAP server to connect to, various example LDAP servers exist (e.g. [https://github.com/rroemhild/docker-test-openldapi](https://github.com/rroemhild/docker-test-openldap))

## Running Examples

### root_dse.q

Queries the servers rootDSE. Depending on the functionality your server supports & config, it may show attributes such as supportedSASLMechanisms (supported security mechanisms for use in bind). Reference [here](https://ldapwiki.com/wiki/RootDSE) for details other attributes that may be populated. The rootDSE is often used to discover what functionality an LDAP server may support & information to identify the type of LDAP server (e.g. vendor details). The rootDSE can be subject to access restrictions, so your server may require you to do a specific bind to retrieve these details.

The connection details within the script may need altered to communicate with your LDAP server.

Example 

`q root_dse.q`

### search.q

Created to show an example of an ldap search that works with the example LDAP server available from [https://github.com/rroemhild/docker-test-openldapi](https://github.com/rroemhild/docker-test-openldapi). Example searches provided in the script, such as searching for a users email. NOTE: this example server does not require a bind with user dn/password.

Example

`q search.q`
