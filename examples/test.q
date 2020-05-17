\l ldap.q
\c 25 2000

.ldap.init[enlist `$"ldap://127.0.0.1:389"]
.ldap.setOption[1b;17i;1i]