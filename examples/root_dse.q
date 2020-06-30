\l ldap.q
\c 25 2000

mainSession:1i
timeout:3000000

-1"### Creating global options";
.ldap.setGlobalOption[`LDAP_OPT_X_TLS_REQUIRE_CERT;3]
.ldap.setGlobalOption[`LDAP_OPT_PROTOCOL_VERSION;3]
.ldap.setGlobalOption[`LDAP_OPT_NETWORK_TIMEOUT;timeout]

-1"### Configuring LDAP server to use";
.ldap.init[mainSession;enlist `$"ldap://host.docker.internal:389"]

-1"### TLS Require Cert ";string .ldap.getOption[mainSession;`LDAP_OPT_X_TLS_REQUIRE_CERT]
-1"### Protocol version ";string .ldap.getOption[mainSession;`LDAP_OPT_PROTOCOL_VERSION]
-1"### Network timeout ";string .ldap.getOption[mainSession;`LDAP_OPT_NETWORK_TIMEOUT]

-1"### Connecting and searching for base attributes using anon bind";
res:.ldap.search_s[mainSession;`$"";.ldap.LDAP_SCOPE_BASE;`$"(objectClass=*)";`$();0;0;0]

if[0i<>res`ReturnCode;-2"### Request failed with : ",.ldap.err2string[res`ReturnCode];exit 1;]

show res

exit 0
