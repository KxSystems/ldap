\l ldap.q
\c 25 2000

// Retrieve optional arguments for the example (default = example to be run from Kx docker image)
dockerHost:enlist "host.docker.internal";
cliOpts:.Q.def[``host!(`;dockerHost)].Q.opt .z.x
if[dockerHost~cliOpts`host;
  -1"Example is using 'host.docker.internal' to define host.\nIf not running in the Kx docker ",
    "image set '-host x.x.x.x' on command line\n"
  ]

globalSession:1i

-1"### Set LDAP server for session";
sessionInit:.ldap.init[globalSession;enlist `$"ldap://",cliOpts[`host;0],":389"]
$[0i~sessionInit;
  [-1"'Request to initialize a session successfully processed'";];
  [-2"'Request to initialize a session failed with return: '",
     .ldap.err2string[sessionInit],"'. Exiting.\n";
   exit 1]
  ]


-1"\n\n### Update protocol version option and display update";
protocolVersion:.ldap.setOption[globalSession;`LDAP_OPT_PROTOCOL_VERSION;3]
$[0i~protocolVersion;
  [-1"'Request to locally set 'LDAP_OPT_PROTOCOL_VERSION' option successfully processed'";];
  [-2"'Request to locally set 'LDAP_OPT_PROTOCOL_VERSION' option failed with return: '",
     .ldap.err2string[protocolVersion],"'. Exiting.\n";
   exit 1]
  ]
show .ldap.getOption[globalSession;`LDAP_OPT_API_INFO]


-1"\n\n### Bind to sessions server";
bindSession:.ldap.bind[globalSession;::]
$[0i~bindSession`ReturnCode;
  [-1"'Request to bind to sessions server successfully processed'";];
  [-2"Request to bind to server failed with return: '",
   .ldap.err2string[bindSession`ReturnCode],"'. Exiting.\n";
   exit 1]
  ]

-1"\n### Bind to session results";
show bindSession


-1"\n\n### Search at base level";
baseScope :.ldap.LDAP_SCOPE_BASE
baseFilter:"(objectClass=*)"
baseSearch:.ldap.search[globalSession;baseScope;baseFilter;::]
$[0i~ baseSearch`ReturnCode;
  [-1"'Request to search at base level successfully processed'";];
  [-2"Request to search at base level failed with return: '",
   .ldap.err2string[baseSearch`ReturnCode],"'. Exiting.\n";
   exit 1]
  ]
-1"\n### Base search results";
show baseSearch


-1"\n\n### Search from ou=people,dc=planetexpress,dc=com and subtree below for Amy. ",
  "Retrieve givenName and email";
// paramter definitions
customScope :.ldap.LDAP_SCOPE_SUBTREE
customFilter:"(cn=Amy Wong)"
customDict  :`baseDN`attr!(`$"ou=people,dc=planetexpress,dc=com";`mail`givenName)
complexSearch:.ldap.search[globalSession;customScope;customFilter;customDict]
$[0i~complexSearch`ReturnCode;
  [-1"'Request to apply complex subtree search successfully processed'";];
  [-2"Request to complete complex subtree search failed with return: '",
     .ldap.err2string[complexSearch`ReturnCode],"'. Exiting.\n";
   exit 1]
  ]
-1"\n### Complex subtree search results";
show complexSearch


-1"\n\n### UnBind from session";
unBindSession:.ldap.unbind[globalSession]
$[0i~unBindSession;
  [-1"'Request to unbind from the session successfully processed'.\n";];
  [-2"Request to unbind from session failed with return: '",
     unBindSession,"'. Exiting.\n";
   exit 1]
  ]

exit 0
