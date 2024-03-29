# LDAP function reference

`.ldap.`   **LDAP interface**

[`bind`](#ldapbind)             Synchronous bind to authenticate client<br>
[`err2string`](#ldaperr2string)       String description of an LDAP error code<br>
[`getGlobalOption`](#ldapgetglobaloption)  Get global LDAP option<br>
[`getOption`](#ldapgetoption)        Get session LDAP option<br>
[`init`](#ldapinit)             Initialize session with LDAP server connection details<br>
[`interactiveBind`](#ldapinteractivebind)             Synchronous bind to authenticate client using SASL auth<br>
[`search`](#ldapsearch)           Synchronous search for partial or complete copies of entries<br>
[`setOption`](#ldapsetoption)        Set session LDAP option<br>
[`setGlobalOption`](#ldapsetglobaloption)  Set global LDAP option<br>
[`unbind`](#ldapunbind)           Synchronous unbind from the directory



## `.ldap.bind`

_Synchronous bind to authenticate client_

```txt
.ldap.bind[sess;opts]
```

Where

-   `sess` is an int or long that represents the session previously created via `.ldap.init`
-   `opts` is a generic null or a dictionary of non-default options for the bind operation

binds to the session and returns a result code and server credentials as a dictionary (can use anon or password binding).

Synchronous bind operations are used to authenticate clients (and the users or applications behind them) to the directory server, to establish an authorization identity that will be used for subsequent operations processed on that connection, and to specify the LDAP protocol version that the client will use.

:globe_with_meridians:
[The LDAP bind operation](https://ldap.com/the-ldap-bind-operation/)

Valid `opts` entries:

name | type | content | default
-----|------|---------|--------
`dn` | string or symbol | user to authenticate | Anonymous simple authentication. (Typical for SASL authentication as most SASL mechanisms identify the target account within the encoded credentials.)
`cred` | char/byte list or symbol | LDAP credentials, e.g. password | Assume no password required.
`mech` | string or symbol | SASL mechanism for authentication | If not present, defaults to LDAP_SASL_SIMPLE (simple authentication) which is represented by an empty string.<br><br>Query the attribute `supportedSASLMechanisms` from the  server’s `rootDSE` for the list of SASL mechanisms the server supports.

Result dictionary:

key         | type       | content
------------|------------|-----------------
`ReturnCode`  | integer    | [result code](#result-codes)
`Credentials` | byte array | credentials returned by the server<br><br>Empty for `LDAP_SASL_SIMPLE`; for other SASL mechanisms, the credentials may need to be used with other security-related functions, which may be external to LDAP.

:point_right:
[Security mechanisms](#security-mechanisms)

```q
// Complete a default bind to the server
q).ldap.bind[0i;::]
ReturnCode | 0i
Credentials| `byte$()

// Complete a bind to the server with non default parameters
q).ldap.bind[0i;enlist[`dn]!enlist `Tom]
ReturnCode | 0i
Credentials| `byte$()
```


## `.ldap.err2string`

_String description of an LDAP result code_

```txt
.ldap.err2string[err]
```

Where `err` is an integer LDAP result code, returns its string representation.

Result codes are negative for an API error, 0 for success, and positive for a LDAP error.

:point_right:
[Result codes](#result-codes)

```q
q).ldap.err2string[0]
"Success"
q).ldap.err2string[-9]
"Bad parameter to an ldap routine"
q).ldap.err2string[5]
"Compare False"
```


## `.ldap.getGlobalOption`

_Get global LDAP option_

```txt
.ldap.getGlobalOption[option]
```

Where `option` (symbol) is the option to get, returns [its value](#get-options).

```q
q).ldap.getGlobalOption[`LDAP_OPT_PROTOCOL_VERSION]
,3
q).ldap.getGlobalOption[`LDAP_OPT_X_TLS_REQUIRE_CERT]
,3
```


## `.ldap.getOption`

_Get session LDAP option_

```txt
.ldap.getOption[sess;option]
```

Where

-   `sess` (int or long) is the session previously created with `.ldap.init`
-   `option` (symbol) is the [option](#get-options) to get

returns the [value for `option`](#get-options).

```q
q).ldap.getOption[0i;`LDAP_OPT_PROTOCOL_VERSION]
,3
q).ldap.getOption[0i;`LDAP_OPT_NETWORK_TIMEOUT]
30000
```

:globe_with_meridians:
[`ldap_set_option`](https://www.openldap.org/software/man.cgi?query=ldap_set_option&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release)


## `.ldap.init`

_Initialize the session with LDAP server connection details_

```txt
.ldap.init[sess;uris]
```

Where

-   `sess` (int or long) is the session ID: unique for each session you initialize
-   `uris` (symbol list) URIs in the format `schema://host:port`

returns `0i` if successful, otherwise an LDAP error code.

Values for `schema`: `ldap`, `ldaps`, `ldapi` or `cldap`.

Connection occurs on first operation: `init` does not create a connection.

Use [`unbind`](#ldap-unbind) to free the session, after which the session ID can be reused.

:globe_with_meridians:
[`ldap_initialize`](https://www.openldap.org/software/man.cgi?query=ldap_init&sektion=3&apropos=0&manpath=openldap+2.4-release "www.openldap.org")


```q
// successfully execute initialization
q).ldap.init[0i;enlist `$"ldap://0.0.0.0:389"]
0i

// attempt to initialize with an incorrect 'schema'
q).ldap.init[1i;enlist `$"noldap://0.0.0.0:389"]
-9i

// retrieve error message for above error code
q).ldap.err2string[-9i]
"Bad parameter to an ldap routine"
```


## `.ldap.interactiveBind`

_Synchronous bind to authenticate client using SASL auth (e.g. kerberos)_

```txt
.ldap.interactiveBind[sess;opts]
```

Where

-   `sess` is an int or long that represents the session previously created via `.ldap.init`
-   `opts` is a generic null or a dictionary of non-default options for the bind operation

binds to the session and returns a result code and server credentials as a dictionary.

Synchronous bind operations are used to authenticate clients (and the users or applications behind them) to the directory server, to establish an authorization identity that will be used for subsequent operations processed on that connection, and to specify the LDAP protocol version that the client will use. Many SASL mechanisms require multiple message exchanges to perform a complete authentication.

:globe_with_meridians:
[The LDAP bind operation](https://ldap.com/the-ldap-bind-operation/)

Valid `opts` entries:

name | type | content | default
-----|------|---------|--------
`dn` | string or symbol | user to authenticate | Anonymous simple authentication. (Typical for SASL authentication as most SASL mechanisms identify the target account within the encoded credentials.)
`flag` | int | Can be .ldap.LDAP_SASL_AUTOMATIC, .ldap.LDAP_SASL_INTERACTIVE, .ldap.LDAP_SASL_QUIET
`mech` | string or symbol | SASL mechanism for authentication | `LDAP_SASL_SIMPLE`<br><br>Query the attribute `supportedSASLMechanisms` from the  server’s `rootDSE` for the list of SASL mechanisms the server supports. Query the option LDAP_OPT_X_SASL_MECHLIST to see what mechanisms are installed on the client machine.
`cb` | symbol | Symbol denoting a function in your q session with 4 arguments, used to process SASL sasl_interact_t data 1. id (long) 2. challenge (string) 3. prompt (string) 4. default result (string). Should return a mixed list (1st element an int for ldap [result code](#result-codes), 2nd element a char/byte vector used to populate the sasl_interact result field). Please view [Sasl Authentication section here](https://linux.die.net/man/3/ldap_sasl_bind_s) | Empty symbol (uses default callbacks with default values).

Returns an ldap [result code](#result-codes)

:point_right:
[Security mechanisms](#security-mechanisms)

```q
// Complete a bind to the server with GSSAPI security mech (kerberos), using SASL to automatically negotiate
q).ldap.interactiveBind[0i;(`mech`flag)!("GSSAPI";.ldap.LDAP_SASL_AUTOMATIC)]
0i
```


## `.ldap.search`

_Synchronous search for partial or complete copies of entries_

```txt
.ldap.search[sess;scope;filter;opts]
```

Where

-   `sess` (int or long) is a session ID previously created with [`.ldap.init`](#ldap-init)
-   `scope` (int long) is the [scope of the search](#scope)
-   `filter` (string or symbol) is the [filter to be applied](https://ldap.com/ldap-filters/ "ldap.com")
-   `opts` is the generic null or a dictionary of non-default options for the search

returns results as a dictionary.

:globe_with_meridians:
[The LDAP search operation](https://ldap.com/the-ldap-search-operation/)

Search options (`opts`):

name | type | content | default
-----|------|---------|--------
`baseDn` | string or symbol | base of the subtree to search from | search from the root (or when a DN is not known)
`attr` | symbol list | attributes to include in the result | `*` (all user attributes)
`attrsOnly` | int or long | return both attribute descriptions and values unless +ve, when return only descriptions | both
`timeLimit` | int or long | number of microseconds to wait for a result | 0 (no limit)<br><br>The server may impose its own limit.
`sizeLimit` | int or long | max number of entries to return | 0 (no limit)<br><br>The server may impose its own limit.

Special `attr` values: include in results
```txt
*     all user attributes
+     all operational attributes
1.1   no attributes
```

Some servers may also support the ability to use the `@` symbol followed by an object class name (e.g. `@inetOrgPerson`) to request all attributes associated with that object class.

Result dictionary:

key           | type    | explanation
--------------|---------|-----------------
`ReturnCode`  | integer | [result code](#result-codes)
`Entries`     | table   | DNs and attribute dictionaries
`Referrals`   | list    | list of strings providing the referrals that can be searched to gain access to the required info (if server supports referrals)

```q
// Run a blind/default search at base level
q)session:0i
q)scope  :.ldap.LDAP_SCOPE_BASE
q)filter :"(objectClass=*)"
q).ldap.search[session;scope;filter;::]
ReturnCode| 0i
Entries   | +`DN`Attributes!(,"";,(,`objectClass)!,("top";"OpenLDAProotDSE"))
Referrals | ()

// Run a non default search
q)session:0i
q)scope  :.ldap.LDAP_SCOPE_SUBTREE
q)filter :"(cn=Amy Wong)"
q)options:`baseDN`attr!(`$"ou=people,dc=planetexpress,dc=com";`mail`givenName)
q).ldap.search[session;scope;filter;options]
ReturnCode| 0i
Entries   | +`DN`Attributes!(,"cn=Amy Wong+sn=Kroker,ou=people,dc=planetexpress,dc=com";,`givenName`mail!(,"Amy";,"amy@planetexpress.com"))
Referrals | ()
```


## `.ldap.setGlobalOption`

_Set global LDAP option_

```txt
.ldap.setGlobalOption[option;value]
```

Where

-   `option` (symbol) is the [option](#set-options) to set
-   `value` is the [value](#set-options) to set for it

returns `0i` if successful, otherwise an [LDAP error code](#ldap-errors).

```q
q).ldap.setGlobalOption[0i;`LDAP_OPT_X_TLS_REQUIRE_CERT;3]
0i
q).ldap.setGlobalOption[0i;`LDAP_OPT_NETWORK_TIMEOUT ;30000]
0i
```

LDAP handles inherit their default settings from the global options in effect at the time the handle is created, i.e. if a global setting is made, all sessions initialized after that will inherit those settings but not any sessions created prior.


## `.ldap.setOption`

_Set session LDSAP option_

```txt
.ldap.setOption[sess;option;value]
```

Where

-   `sess` (int or long) is the session ID created with `.ldap.init`
-   `option` (symbol) is the [option](#set-options) to set
-   `value` is the [value](#set-options) to set for that option

returns `0i` if successful, otherwise an [LDAP error code](#ldap-errors).

:globe_with_meridians:
[`ldap_set_option`](https://www.openldap.org/software/man.cgi?query=ldap_set_option&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release "www.openldap.org")

```q
q).ldap.setOption[0i;`LDAP_OPT_PROTOCOL_VERSION;3]
0i
q).ldap.setOption[0i;`LDAP_OPT_NETWORK_TIMEOUT ;30000]
0i
```


## `.ldap.unbind`

_Synchronous unbind from the directory, terminate the current association, and free resources_

```txt
.ldap.unbind[sess]
```

Where `sess` (int or long) is the session ID created with `.ldap.init`, returns `0i` if successful, otherwise a LDAP error code.

> Tip: Invoke even if a session did not bind (or failed to bind), but had been initialized.

The session ID can be re-used when subsequently creating a new session with `.ldap.init`.

```q
q).ldap.unbind[0i]
0i
```

:globe_with_meridians:
[The LDAP unbind operation](https://ldap.com/the-ldap-unbind-operation/)


## Scope

```txt
LDAP_SCOPE_BASE      0  the specified entry and no subordinates
LDAP_SCOPE_ONELEVEL  1  immediate children of the specified entry;
                        not the entry itself, nor further subordinates
LDAP_SCOPE_SUBTREE   2  the specified entry and all subordinates
LDAP_SCOPE_CHILDREN  3  all of the subordinates
```

## Get options

Options are listed by protocol.

:globe_with_meridians:
[`ldap_get_option`](https://www.openldap.org/software/man.cgi?query=ldap_get_option&apropos=0&sektion=3&manpath=OpenLDAP+2.4-Release&arch=default&format=html "www.openldap.org")


### `LDAP`

```txt
LDAP_OPT_API_FEATURE_INFO     dictionary
LDAP_OPT_API_INFO             dictionary
LDAP_OPT_CONNECT_ASYNC        integer
LDAP_OPT_DEBUG_LEVEL          integer
LDAP_OPT_DEREF                integer        
LDAP_OPT_DESC                 integer        file descriptor associated to the socket buffer of ldap
LDAP_OPT_DIAGNOSTIC_MESSAGE   string         error string associated to the handle (useful for bind errors)
LDAP_OPT_MATCHED_DN           string         the matched DN
LDAP_OPT_NETWORK_TIMEOUT      integer        timeout in microseconds
LDAP_OPT_PROTOCOL_VERSION     integer        ldap protocol version
LDAP_OPT_REFERRALS            integer        implicitly chase referrals or not
LDAP_OPT_RESULT_CODE          integer        result code associated to the handle
LDAP_OPT_SIZELIMIT            integer        maximum number of entries to be returned by a search
LDAP_OPT_TIMELIMIT            integer        time limit after which a search operation should be terminated by the server
LDAP_OPT_TIMEOUT              integer        timeout in microseconds
```


### `SASL`

```txt
LDAP_OPT_X_SASL_AUTHCID      string          SASL authentication identity
LDAP_OPT_X_SASL_AUTHZID      string          SASL authorization identity
LDAP_OPT_X_SASL_MAXBUFSIZE   long            SASL maximum buffer size 
LDAP_OPT_X_SASL_MECH         string          the SASL mechanism
LDAP_OPT_X_SASL_MECHLIST     stringlist      list of the available mechanisms
LDAP_OPT_X_SASL_NOCANON      integer         Unset,the hostname is canonicalized (useful when DNS load balancers/etc in use).
LDAP_OPT_X_SASL_REALM        string          SASL realm
LDAP_OPT_X_SASL_SSF          long            SASL SSF
LDAP_OPT_X_SASL_SSF_MAX      long            SASL maximum SSF
LDAP_OPT_X_SASL_SSF_MIN      long            SASL minimum SSF
LDAP_OPT_X_SASL_USERNAME     string          SASL username
```


### `TCP`

```txt
LDAP_OPT_X_KEEPALIVE_IDLE      integer       number of seconds a connection needs to remain idle before TCP starts sending keepalive probes
LDAP_OPT_X_KEEPALIVE_PROBES    integer       maximum number of keepalive probes TCP should send before dropping the connection
LDAP_OPT_X_KEEPALIVE_INTERVAL  integer       interval in seconds between individual keepalive probes
```


### `TLS`

```txt
LDAP_OPT_X_TLS_CACERTDIR      string
LDAP_OPT_X_TLS_CACERTFILE     string
LDAP_OPT_X_TLS_CERTFILE       string
LDAP_OPT_X_TLS_CIPHER_SUITE   string
LDAP_OPT_X_TLS_CRLCHECK       integer
LDAP_OPT_X_TLS_CRLFILE        string
LDAP_OPT_X_TLS_DHFILE         string
LDAP_OPT_X_TLS_KEYFILE        string
LDAP_OPT_X_TLS_PROTOCOL_MIN   integer
LDAP_OPT_X_TLS_RANDOM_FILE    string
LDAP_OPT_X_TLS_REQUIRE_CERT   integer
```


## Set options

The options are listed by protocol.

:globe_with_meridians:
[`ldap_set_option`](https://www.openldap.org/software/man.cgi?query=ldap_set_option&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release "www.openldap.org")


### `LDAP`

```txt
LDAP_OPT_CONNECT_ASYNC       integer/long    set using value .ldap.LDAP_OPT_ON or .ldap.LDAP_OPT_OFF. When set, the library will call connect(2) and return, without waiting for response. This leaves the handle in a connecting state. Subsequent calls to library routines will poll for completion of the connect before performing further operations
LDAP_OPT_DEBUG_LEVEL         integer/long
LDAP_OPT_DEREF               integer/long    when alias dereferencing must occur
                                             one of: .ldap.LDAP_DEREF_NEVER
                                                     .ldap.LDAP_DEREF_SEARCHING
                                                     .ldap.LDAP_DEREF_FINDING
                                                     .ldap.LDAP_DEREF_ALWAYS
LDAP_OPT_DIAGNOSTIC_MESSAGE  string/symbol   error string associated to the LDAP handle
LDAP_OPT_NETWORK_TIMEOUT     integer/long    number of microseconds for timeout
LDAP_OPT_MATCHED_DN          string/symbol   the matched DN
LDAP_OPT_PROTOCOL_VERSION    integer/long    ldap protocol version
LDAP_OPT_REFERRALS           integer/long    set using value .ldap.LDAP_OPT_ON or .ldap.LDAP_OPT_OFF
LDAP_OPT_RESULT_CODE         integer/long    implicitly chase referrals or not
LDAP_OPT_SIZELIMIT           integer/long    maximum number of entries to be returned by a search
LDAP_OPT_TIMELIMIT           integer/long    time limit after which a search operation should be terminated by the server
LDAP_OPT_TIMEOUT             integer/long    number of microseconds for timeout
```


### `SASL`

```txt
LDAP_OPT_X_SASL_MAXBUFSIZE    long           SASL maximum buffer size
LDAP_OPT_X_SASL_NOCANON       integer/long   unset,the hostname is canonicalized (useful when DNS load balancers/etc in use). Set using value .ldap.LDAP_OPT_OFF or .ldap.LDAP_OPT_ON
LDAP_OPT_X_SASL_SECPROPS      string/symbol  comma-separated list of properties
LDAP_OPT_X_SASL_SSF_EXTERNAL  long           SASL SSF value related to an authentication performed using an EXTERNAL mechanism
LDAP_OPT_X_SASL_SSF_MAX       long           SASL maximum SSF
LDAP_OPT_X_SASL_SSF_MIN       long           SASL minimum SSF
```


### `TCP`

```txt
LDAP_OPT_X_KEEPALIVE_IDLE      integer/long  number of seconds a connection needs to remain idle before TCP starts sending keepalive probes
LDAP_OPT_X_KEEPALIVE_PROBES    integer/long  maximum number of keepalive probes TCP should send before dropping the connection
LDAP_OPT_X_KEEPALIVE_INTERVAL  integer/long  interval in seconds between individual keepalive probes
```


### `TLS`

```txt
LDAP_OPT_X_TLS_CACERTDIR      string/symbol
LDAP_OPT_X_TLS_CACERTFILE     string/symbol
LDAP_OPT_X_TLS_CERTFILE       string/symbol
LDAP_OPT_X_TLS_CIPHER_SUITE   string/symbol
LDAP_OPT_X_TLS_CRLCHECK       integer/long
LDAP_OPT_X_TLS_CRLFILE        string/symbol
LDAP_OPT_X_TLS_DHFILE         string/symbol
LDAP_OPT_X_TLS_KEYFILE        string/symbol
LDAP_OPT_X_TLS_NEWCTX         integer/long
LDAP_OPT_X_TLS_PROTOCOL_MIN   integer/long
LDAP_OPT_X_TLS_RANDOM_FILE    string/symbol
LDAP_OPT_X_TLS_REQUIRE_CERT   integer/long
```


## Result codes

Code `0i` indicates success.

```q
q).ldap.err2string 0i
"Success"
```


### LDAP errors

LDAP error codes are positive integers.

:globe_with_meridians:
[IANA result codes](https://www.iana.org/assignments/ldap-parameters/ldap-parameters.xhtml#ldap-parameters-6 "www.iana.org")


### API errors

API error codes are negative integers.

```txt
-1  LDAP_SERVER_DOWN              LDAP library can't contact the LDAP server
-2  LDAP_LOCAL_ERROR              local error (failed dynamic memory allocation?)
-3  LDAP_ENCODING_ERROR           error encoding parameters for LDAP server
-4  LDAP_DECODING_ERROR           error decoding result from the LDAP server
-5  LDAP_TIMEOUT                  time limit exceeded waiting for a result
-6  LDAP_AUTH_UNKNOWN             unknown authentication method specified
-7  LDAP_FILTER_ERROR             invalid filter specified to ldap_search 
                                  e.g. unbalanced parentheses
-8  LDAP_USER_CANCELLED           user cancelled the operation
-9  LDAP_PARAM_ERROR              LDAP routine called with a bad parameter
-10 LDAP_NO_MEMORY                memory allocation call failed in LDAP library 
                                  e.g. [malloc(3)](https://www.openldap.org/software/man.cgi?query=malloc&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release) or other dynamic memory allocator
-11 LDAP_CONNECT_ERROR            connection problem
-12 LDAP_NOT_SUPPORTED            routine not called as supported by the library
-13 LDAP_CONTROL_NOT_FOUND        specified control unknown to the client library
-14 LDAP_NO_RESULTS_RETURNED      no results returned
-16 LDAP_CLIENT_LOOP              processing loop detected by library
-17 LDAP_REFERRAL_LIMIT_EXCEEDED  referral limit exceeded
-18 LDAP_X_CONNECTING             an async connect attempt is ongoing
```


## Security mechanisms

LDAP supports a range of security mechanisms as part of the `bind` call. 
Check with your LDAP server admin what is supported for your system. 

> Tip: Often found in the root attribute `supportedSASLMechanisms`

Most of these checks are performed externally, in separate code related to your security mechanism.

For example, `DIGEST_MD5` is initially performed by calling `bind` with no credentials, `mech` set to `"DIGEST-MD5"`, and capturing the returned credential values from the server. Using the returned credentials to MD5-encode the user details, a second `bind` call is then made with the MD5-encoded details as the `cred` parameter. 
(Requires an additional MD5 library that is outside the scope of this interface.)

Examples:

-   [zheolong/melody-lib](https://github.com/zheolong/melody-lib/blob/master/libldap5/sources/ldap/common/digest_md5.c) (MD5)
-   [hajuuk/R7000](https://github.com/hajuuk/R7000/blob/master/ap/gpl/samba-3.0.13/source/libads/sasl.c) ([GSSAPI](https://en.wikipedia.org/wiki/Generic_Security_Services_Application_Program_Interface))
-   [illumos/illumos-gate](https://github.com/illumos/illumos-gate/blob/master/usr/src/lib/libldap5/sources/ldap/common/cram_md5.c) ([CRAM-MD5](https://en.wikipedia.org/wiki/CRAM-MD5))
