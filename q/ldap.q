\d .ldap

/  intialise ldap functions
init:`kdbldap 2:(`kdbldap_init;1)
setOption:`kdbldap 2:(`kdbldap_set_option;3)
getOption:`kdbldap 2:(`kdbldap_get_option;2)
bind:`kdbldap 2:(`kdbldap_bind;2)
search:`kdbldap 2:(`kdbldap_search;4)

\d .
