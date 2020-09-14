\l ldap.q
\c 25 2000

// Retrieve optional arguments for the example (default = example to be run from Kx docker image)
dockerHost:enlist "host.docker.internal";
cliOpts:.Q.def[``host!(`;dockerHost)].Q.opt .z.x
if[dockerHost~cliOpts`host;
  -1"Example is using 'host.docker.internal' to define host.\nIf not running in the Kx docker ",
    "image set '-host x.x.x.x' on command line\n"
  ]

mainSession:1i
timeout:3000000

-1"### Creating global options";
TLSRequireCert :.ldap.setGlobalOption[`LDAP_OPT_X_TLS_REQUIRE_CERT;3]
$[0i~TLSRequireCert;
  [-1"'Request to globally set 'TLS_REQUIRE_CERT' option successfully processed'";];
  [-2"'Request to globally set 'TLS_REQUIRE_CERT' option failed with return: '",
     .ldap.err2string[TLSRequireCert],"'. Exiting.\n";
   exit 1]
  ]

protocolVersion:.ldap.setGlobalOption[`LDAP_OPT_PROTOCOL_VERSION;3]
$[0i~protocolVersion;
  [-1"'Request to globally set 'LDAP_OPT_PROTOCOL_VERSION' option successfully processed'";];
  [-2"'Request to globally set 'LDAP_OPT_PROTOCOL_VERSION' option failed with return: '",
     .ldap.err2string[protocolVersion],"'. Exiting.\n";
   exit 1]
  ]

networkTimeout :.ldap.setGlobalOption[`LDAP_OPT_NETWORK_TIMEOUT;timeout]
$[0i~networkTimeout;
  [-1"'Request to globally set 'LDAP_OPT_NETWORK_TIMEOUT' option successfully processed'";];
  [-2"'Request to globally set 'LDAP_OPT_NETWORK_TIMEOUT' option failed with return: '",
     .ldap.err2string[networkTimeout],"'. Exiting.\n";
   exit 1]
  ]


-1"\n\n### Configuring LDAP server to use";
sessionInit:.ldap.init[mainSession;enlist `$"ldap://",cliOpts[`host;0],":389"]
$[0i~sessionInit;
  [-1"'Request to initialize a session successfully processed'";];
  [-2"'Request to initialize a session failed with return: '",
     .ldap.err2string[sessionInit],"'. Exiting.\n";
   exit 1]
  ]


-1"\n\n### Retrieve session options";
-1"TLS Require Cert: ",string .ldap.getOption[mainSession;`LDAP_OPT_X_TLS_REQUIRE_CERT];
-1"Protocol version: ",string .ldap.getOption[mainSession;`LDAP_OPT_PROTOCOL_VERSION];
-1"Network timeout: ", string .ldap.getOption[mainSession;`LDAP_OPT_NETWORK_TIMEOUT];

-1"\n\n### Connecting and searching for base attributes using anon bind";
anonSearch:.ldap.search[mainSession;::;.ldap.LDAP_SCOPE_BASE;`$"(objectClass=*)";::;0;0;0]
$[0i~anonSearch`ReturnCode;
  [-1"'Request to run anonymous base attribute search successfully processed'";];
  [-2"'Request to run anonymous base attribute search failed with return: '",
     .ldap.err2string[anonSearch`ReturnCode],"'. Exiting.\n";
   exit 1]
  ]
-1"\n### Complex subtree search results";
show anonSearch
-1"";

exit 0
