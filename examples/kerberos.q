\c 10000 10000
\l ldap.q
// Retrieve optional arguments for the example (default = example to be run from Kx docker image)
dockerHost:enlist "host.docker.internal";
cliOpts:.Q.def[``host!(`;dockerHost)].Q.opt .z.x
if[dockerHost~cliOpts`host;
  -1"Example is using 'host.docker.internal' to define host.\nIf not running in the Kx docker ",
    "image set '-host x.x.x.x' on command line\n"
  ]

mainSession:0i;

-1"### Get LDAP_OPT_X_SASL_MECHLIST value";
.ldap.getGlobalOption[`LDAP_OPT_X_SASL_MECHLIST]

-1"### Set LDAP server for session";
sessionInit:.ldap.init[mainSession;enlist `$"ldap://",cliOpts[`host;0],":389"]
$[0i~sessionInit;
  [-1"'Request to initialize a session successfully processed'";];
  [-2"'Request to initialize a session failed with return: '",
     .ldap.err2string[sessionInit],"'. Exiting.\n";
   exit 1]
  ]

.ldap.setOption[mainSession;`LDAP_OPT_X_SASL_SSF_MAX;0];
.ldap.setOption[mainSession;`LDAP_OPT_PROTOCOL_VERSION;3];

-1"### Bind to LDAP server using GSSAPI";
bindSession:.ldap.interactiveBind[mainSession;(`mech`flag)!("GSSAPI";.ldap.LDAP_SASL_AUTOMATIC)];
$[0i~bindSession;
  [-1"'Request to bind to sessions server successfully processed'";];
  [-2"Request to bind to server failed with return: '",
   .ldap.err2string[bindSession],"'. Exiting.\n";
   exit 1]
  ]

-1"### DONE";
