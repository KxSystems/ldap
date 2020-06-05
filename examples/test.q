\l ldap.q
\c 25 2000

globalSession:1i
.ldap.init[globalSession;enlist `$"ldap://host.docker.internal:389"]
.ldap.setOption[globalSession;`LDAP_OPT_PROTOCOL_VERSION;3]
.ldap.getOption[globalSession;`LDAP_OPT_API_INFO]
.ldap.bind_s[globalSession;`$"";`$"";`$""]
res1:.ldap.search_s[globalSession;`$"";0;`$"(objectClass=*)";`$();0;0;0]
res1
res2:.ldap.search_s[globalSession;`$"ou=people,dc=planetexpress,dc=com";2;`$"(objectClass=*)";enlist `$"1.1";0;0;0]
res2
.ldap.unbind_s[globalSession]