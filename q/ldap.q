\d .ldap

/  intialise ldap functions
init:`kdbldap 2:(`kdbldap_init;2)
setOption:`kdbldap 2:(`kdbldap_set_option;3)
setGlobalOption:`kdbldap 2:(`kdbldap_set_global_option;2)
getOption:`kdbldap 2:(`kdbldap_get_option;2)
getGlobalOption:`kdbldap 2:(`kdbldap_get_global_option;1)
bind:`kdbldap 2:(`kdbldap_bind;3)
search:`kdbldap 2:(`kdbldap_search;8)
unbind:`kdbldap 2:(`kdbldap_unbind;1)
err2string:`kdbldap 2:(`kdbldap_err2string;1)

\d .
