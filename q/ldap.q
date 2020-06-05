\d .ldap

/  intialise ldap functions
init:`kdbldap 2:(`kdbldap_init;2)
setOption:`kdbldap 2:(`kdbldap_set_option;3)
setGlobalOption:`kdbldap 2:(`kdbldap_set_global_option;2)
getOption:`kdbldap 2:(`kdbldap_get_option;2)
getGlobalOption:`kdbldap 2:(`kdbldap_get_global_option;1)
bind_s:`kdbldap 2:(`kdbldap_bind_s;4)
search_s:`kdbldap 2:(`kdbldap_search_s;8)
unbind_s:`kdbldap 2:(`kdbldap_unbind_s;1)
err2string:`kdbldap 2:(`kdbldap_err2string;1)

LDAP_SCOPE_BASE:0
LDAP_SCOPE_ONELEVEL:1
LDAP_SCOPE_SUBTREE:2
LDAP_SCOPE_CHILDREN:3

\d .
