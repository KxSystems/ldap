\l ldap.q
\c 25 2000

.ldap.init[enlist `$"ldap://host.docker.internal:389"]
.ldap.setOption[`LDAP_OPT_PROTOCOL_VERSION;3]
.ldap.getOption[`LDAP_OPT_API_INFO]
.ldap.bind[`$"";`$""]
.ldap.search[`$"";0;`$"(objectClass=*)";`$();0;0;0]
.ldap.search[`$"ou=people,dc=planetexpress,dc=com";2;`$"(objectClass=*)";enlist `$"1.1";0;0;0]
.ldap.unbind[0]