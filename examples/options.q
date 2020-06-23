\l ldap.q
\c 25 2000

mainSession:1i

.ldap.init[mainSession;enlist `$"ldap://host.docker.internal:389"]
timeout:3000000
.ldap.setGlobalOption[`LDAP_OPT_X_TLS_REQUIRE_CERT;3]
.ldap.setOption[mainSession;`LDAP_OPT_PROTOCOL_VERSION;3]
.ldap.setOption[mainSession;`LDAP_OPT_NETWORK_TIMEOUT;timeout]

res:.ldap.search_s[mainSession;`$"";.ldap.LDAP_SCOPE_BASE;`$"(objectClass=*)";`$();0;0;0]
res
((res`Entries)`Attributes)`supportedSASLMechanisms

