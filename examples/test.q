\l ldap.q
\c 25 2000

globalSession:1i

-1"### Set LDAP server for session";
.ldap.init[globalSession;enlist `$"ldap://host.docker.internal:389"]

-1"### Set session options";
.ldap.setOption[globalSession;`LDAP_OPT_PROTOCOL_VERSION;3]
.ldap.getOption[globalSession;`LDAP_OPT_API_INFO]

-1"### Bind to sessions server";
.ldap.bind_s[globalSession;`$"";`$"";`$""]

-1"### Search at base level";
res1:.ldap.search_s[globalSession;`$"";.ldap.LDAP_SCOPE_BASE;`$"(objectClass=*)";`$();0;0;0]
if[0i<>res1`ReturnCode;-2"### Request failed with : ",.ldap.err2string[res1`ReturnCode];exit 1;]
-1"### Search results";
show res1

-1"### Search from ou=people,dc=planetexpress,dc=com and subtree below for Amy, get givenName and email";
res2:.ldap.search_s[globalSession;`$"ou=people,dc=planetexpress,dc=com";.ldap.LDAP_SCOPE_SUBTREE;"(cn=Amy Wong)";(`$"mail";`$"givenName");0;0;0]
if[0i<>res2`ReturnCode;-2"### Request failed with : ",.ldap.err2string[res2`ReturnCode];exit 1;]
-1"### Search results";
show res2

-1"### UnBind from session";
.ldap.unbind_s[globalSession]