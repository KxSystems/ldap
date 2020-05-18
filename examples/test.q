\l ldap.q
\c 25 2000

.ldap.init[enlist `$"ldap://127.0.0.1:389"]
.ldap.setOption[1b;`LDAP_OPT_PROTOCOL_VERSION;3]
.ldap.getOption[0b;`LDAP_OPT_API_INFO]