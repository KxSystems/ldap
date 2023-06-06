\d .ldap

/  intialise ldap functions
init:`kdbldap 2:(`kdbldap_init;2)
startTLS:`kdbldap 2:(`kdbldap_start_tls;1)
setOption:`kdbldap 2:(`kdbldap_set_option;3)
setGlobalOption:`kdbldap 2:(`kdbldap_set_global_option;2)
getOption:`kdbldap 2:(`kdbldap_get_option;2)
getGlobalOption:`kdbldap 2:(`kdbldap_get_global_option;1)
bind_s:`kdbldap 2:(`kdbldap_bind_s;4)
interactive_bind_s:`kdbldap 2:(`kdbldap_interactive_bind_s;5)
search_s:`kdbldap 2:(`kdbldap_search_s;8)
unbind_s:`kdbldap 2:(`kdbldap_unbind_s;1)
err2string:`kdbldap 2:(`kdbldap_err2string;1)

LDAP_SCOPE_BASE:0
LDAP_SCOPE_ONELEVEL:1
LDAP_SCOPE_SUBTREE:2
LDAP_SCOPE_CHILDREN:3

LDAP_OPT_ON:-1i
LDAP_OPT_OFF:0i

LDAP_DEREF_NEVER:0i
LDAP_DEREF_SEARCHING:1i
LDAP_DEREF_FINDING:2i
LDAP_DEREF_ALWAYS:3i

LDAP_SASL_AUTOMATIC:0i
LDAP_SASL_INTERACTIVE:1i
LDAP_SASL_QUIET:2i

bind:{[sess;customDict]
  defaultKeys:`dn`cred`mech;
  defaultVals:```;
  defaultDict:defaultKeys!defaultVals;
  if[customDict~(::);customDict:()!()];
  if[99h<>type customDict;'"customDict must be (::) or a dictionary"];
  updDict:defaultDict,customDict;
  bindSession:bind_s[sess;;;]. updDict defaultKeys;
  bindSession
  }

interactiveBind:{[sess;customDict]
  defaultKeys:`dn`flag`mech`cb;
  defaultVals:(`;LDAP_SASL_AUTOMATIC;`;`);
  defaultDict:defaultKeys!defaultVals;
  if[customDict~(::);customDict:()!()];
  if[99h<>type customDict;'"customDict must be (::) or a dictionary"];
  updDict:defaultDict,customDict;
  bindSession:interactive_bind_s[sess;;;]. updDict defaultKeys;
  bindSession
  }

search:{[sess;scope;filter;customDict]
  defaultKeys:`baseDN`attr`attrsOnly`timeLimit`sizeLimit;
  defaultVals:(`$"";`$();0;0;0);
  defaultDict:defaultKeys!defaultVals;
  if[customDict~(::);customDict:()!()];
  if[99h<>type customDict;'"customDict must be (::) or a dictionary"];
  updDict:defaultDict,customDict;
  searchRes:search_s[sess;;scope;filter;;;;]. updDict defaultKeys;
  searchRes
  }

unbind:unbind_s

\d .
