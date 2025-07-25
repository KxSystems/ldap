# kdb+ interface for LDAP (Examples)

The scripts below are in the `examples` folder of the interface.
They provide insight into the different capabilities of the interface.

## Requirements

1. The LDAP interface installed as described in the interface’s [`README.md`](../README.md)
2. The folder `q/` containing `ldap.q` placed either in the examples folder or (preferably) in the your `QHOME` directory.
3. Running LDAP server. If you do not have an LDAP server to connect to, various example LDAP servers exist (e.g. [https://github.com/rroemhild/docker-test-openldapi](https://github.com/rroemhild/docker-test-openldap))

## Running Examples

### root_dse.q

Queries the servers rootDSE. Depending on the functionality your server supports & config, it may show attributes such as supportedSASLMechanisms (supported security mechanisms for use in bind). 

Reference [here](https://ldapwiki.com/wiki/RootDSE) for details other attributes that may be populated. 

The `rootDSE` is often used to discover what functionality an LDAP server may support & information to identify the type of LDAP server (e.g. vendor details). The `rootDSE` can be subject to access restrictions, so your server may require you to do a specific bind to retrieve these details.

The connection details within the script may need altered to communicate with your LDAP server.

```bash
q root_dse.q -host 127.0.0.1
```

### search.q

Shows an example of an ldap search that works with the example LDAP server available from [https://github.com/rroemhild/docker-test-openldapi](https://github.com/rroemhild/docker-test-openldapi). 

The script includes searches such as searching for a user’s email (This example server does not require a bind with user dn/password).

```bash
q search.q -host 127.0.0.1
```

### kerberos.q

Shows an example of binding to an ldap server that uses kerberos authentication. Not all ldap servers avail of this feature. Contact your LDAP server admin for details.

Prior to running, kinit should be executed in order to perform a kerberos user login e.g. `kinit user01` which has been enabled on your LDAP server.

Requires OpenLdap to have been built with Cryus SASL (e.g. on centos, this is the cyrus-sasl-devel package). Prior to running, the Cyrus SASL plugin which supports GSSAPI authentication (e.g. on centos, this is the cyrus-sasl-gssapi package) should be installed. 

When running, the value of the ldap option `LDAP_OPT_X_SASL_MECHLIST` returned, should include GSSAPI (if the correct SASL packages have been installed). Without this, the bind will fail.

```bash
q kerberos.q -host ldap.edt.org
```

### digestMD5.q

Shows an example of binding to an ldap server that uses DIGEST-MD5 authentication. Not all ldap servers avail of this feature. Contact your LDAP server admin for details.

Requires OpenLdap to have been built with Cryus SASL. Prior to running, the Cyrus SASL plugin which supports DIGEST-MD5 authentication (e.g. on Ubuntu, these are the `sasl2-bin` and `libsasl2-modules` packages) should be installed.

When running, the value of the ldap option LDAP_OPT_X_SASL_MECHLIST returned, should include `DIGEST-MD5` (if the correct SASL packages have been installed). Without this, the bind will fail.

Prior to binding, the callback function `cb` should be defined:-

```q
ksaslcb:{[id; challenge; prompt; def]   
 :$[id~.ldap.SASL_CB_USER;(0i; "peter");
    id~.ldap.SASL_CB_AUTHNAME;(0i; "peter");
    id~.ldap.SASL_CB_PASS;(0i; "myPassword");
    (1i; "")];
 };
bindResult:.ldap.interactiveBind[globalSession;(`mech`flag`cb)!("DIGEST-MD5";.ldap.LDAP_SASL_QUIET;`ksaslcb)];
```