# LDAP interface for KDB+
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/kxsystems/ldap?include_prereleases)](https://github.com/kxsystems/ldap/releases) [![Travis (.org) branch](https://img.shields.io/travis/kxsystems/ldap/master?label=travis%20build)](https://travis-ci.org/kxsystems/ldap/branches)

## Introduction

TODO

## Documentation

Documentation outlining the functionality available for this interface can be found [here](https://code.kx.com/q/interfaces/ldap). (*URL NOT CURRENT OPERATIONAL - SEE CODE.KX.COM SECTION BELOW*)

## New to kdb+ ?

Kdb+ is the world's fastest time-series database, optimized for ingesting, analyzing and storing massive amounts of structured data. To get started with kdb+, please visit https://code.kx.com/q/learn/ for downloads and developer information. For general information, visit https://kx.com/

## Running 

### Download

Download the latest release from our [releases page](https://github.com/KxSystems/ldap/releases)

### Installation

#### Linux

TODO

#### Windows

TODO

#### Mac

TODO

## Building Interface From Source

### Linux

#### Linux OpenLdap Builds

TODO

#### Building Linux Interface

TODO

### Windows

#### Windows OpenLdap Builds

Pre-built OpenLdap Windows libraries can be retrieved using pacman package manager (supplied with msys2). The package is [mingw-w64-x86_64-openldap](https://packages.msys2.org/package/mingw-w64-x86_64-openldap). Example instruction for install

```
# update database of packages
pacman -Fy
# search for openldap package name
pacman -Ss openldap
# list contents of package prior to install
pacman -Fl <x64 package name found in prev search>
# install package
pacman -S <x64 package name found in prev search>
```

##### Converting msys2 provided libldap.dll to libldap.lib for use with Visual Studio

Use the provided dll2lib.bat to convert liblber.dll and libldap.dll (found in the mingw64/bin dir of your msys2 install).

```
dll2lib.bat liblber.dll
dll2lib.bat libldap.dll
```

Move the resulting liblber.lib and libldap.lib to the mingw64/lib dir of your msys2 install.

### Building Windows Interface

##### Example build command using Visual Studio 2019

Open 'x64 Native Tools Command Prompt for VS 2019' as supplied with Visual Studio.

Go to the downloaded source & enter the build directory. Run the following builds commands

```
set BUILD_HOME=<dir containing lib and include directory of the openldap library>
cmake -G "Visual Studio 16 2019" -A x64 ..
MSBuild.exe INSTALL.vcxproj /m /nologo /verbosity:normal /p:Configuration=Release /p:Platform=x64
```

Created libs/etc can then be found in the newly created kdbldap dir

### Mac

#### Mac OpenLdap Builds

TODO

#### Building Mac Interface

TODO

## OpenLdap License

Thirdparty OpenLdap license

The OpenLDAP Public License  Version 2.8, 17 August 2003 Redistribution and use of this software and associated documentation ("Software"), with or without modification, are permitted provided that the following conditions are met: 1. Redistributions in source form must retain copyright statements   and notices, 2. Redistributions in binary form must reproduce applicable copyright   statements and notices, this list of conditions, and the following   disclaimer in the documentation and/or other materials provided   with the distribution, and 3. Redistributions must contain a verbatim copy of this document. The OpenLDAP Foundation may revise this license from time to time. Each revision is distinguished by a version number.  You may use this Software under terms of this license revision or under the terms of any subsequent revision of the license. THIS SOFTWARE IS PROVIDED BY THE OPENLDAP FOUNDATION AND ITS CONTRIBUTORS ``AS IS'' AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OPENLDAP FOUNDATION, ITS CONTRIBUTORS, OR THE AUTHOR(S) OR OWNER(S) OF THE SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. The names of the authors and copyright holders must not be used in advertising or otherwise to promote the sale, use or other dealing in this Software without specific, written prior permission.  Title to copyright in this Software shall at all times remain with copyright holders. OpenLDAP is a registered trademark of the OpenLDAP Foundation. Copyright 1999-2003 The OpenLDAP Foundation, Redwood City, California, USA.  All Rights Reserved.  Permission to copy and distribute verbatim copies of this document is granted.

# Code.kx.com Content

## Overview

TODO

## Function Reference

### .ldap.init

Initializes the session with LDAP server connection details. Connection will occur on first operation. Does not create a connection. Reference [ldap_initialize](https://www.openldap.org/software/man.cgi?query=ldap_init&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release)

Syntax: `.ldap.init[sess;uris]`

Where

- sess is an int/long that you will use to track the session in subsequent calls. Should be a unique number for each session you wish to initialize. The number can only be reused to refer to a session after a .ldap.unbind.
- uris is a symbol list. Each URI in the list must follow the format of schema://host:port , where schema is 'ldap','ldaps','ldapi', or 'cldap'.

Returns 0 if successful.

### .ldap.setOption

Sets options per session that affect LDAP operating procedures. Reference [ldap_set_option](https://www.openldap.org/software/man.cgi?query=ldap_set_option&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release)

Syntax: `.ldap.setOption[sess;option;value]`

Where

- sess is an int/long that represents the session previously created via .ldap.init
- option is a symbol for the option you wish to set. See supported options below.
- value is the value relating to the option. The data type depends on the option selected (see below)

Supported LDAP options

- LDAP_OPT_CONNECT_ASYNC (value data type int/long)
- LDAP_OPT_DEBUG_LEVEL (value data type int/long)
- LDAP_OPT_DEREF (value data type int/long)
- LDAP_OPT_DIAGNOSTIC_MESSAGE (value data type string/symbol)
- LDAP_OPT_NETWORK_TIMEOUT (value data type int/long - representing microseconds)
- LDAP_OPT_MATCHED_DN (value data type string/symbol)
- LDAP_OPT_PROTOCOL_VERSION (value data type int/long)
- LDAP_OPT_REFERRALS (value data type int/long)
- LDAP_OPT_RESULT_CODE (value data type int/long)
- LDAP_OPT_SIZELIMIT (value data type int/long)
- LDAP_OPT_TIMELIMIT (value data type int/long)
- LDAP_OPT_TIMEOUT (value data type int/long - representing microseconds)

Supported SASL options

- LDAP_OPT_X_SASL_MAXBUFSIZE (value data type long)
- LDAP_OPT_X_SASL_NOCANON (value data type int/long)
- LDAP_OPT_X_SASL_SECPROPS (value data type string/symbol)
- LDAP_OPT_X_SASL_SSF_EXTERNAL (value data type long)
- LDAP_OPT_X_SASL_SSF_MAX (value data type long)
- LDAP_OPT_X_SASL_SSF_MIN (value data type long)

Supported TCP options

- LDAP_OPT_X_KEEPALIVE_IDLE (value data type int/long)
- LDAP_OPT_X_KEEPALIVE_PROBES (value data type int/long)
- LDAP_OPT_X_KEEPALIVE_INTERVAL (value data type int/long)

Supported TLS options

- LDAP_OPT_X_TLS_CACERTDIR (value data type string/symbol)
- LDAP_OPT_X_TLS_CACERTFILE (value data type string/symbol)
- LDAP_OPT_X_TLS_CERTFILE (value data type string/symbol)
- LDAP_OPT_X_TLS_CIPHER_SUITE (value data type string/symbol)
- LDAP_OPT_X_TLS_CRLCHECK (value data type int/long)
- LDAP_OPT_X_TLS_CRLFILE (value data type string/symbol)
- LDAP_OPT_X_TLS_DHFILE (value data type string/symbol)
- LDAP_OPT_X_TLS_KEYFILE (value data type string/symbol)
- LDAP_OPT_X_TLS_NEWCTX (value data type int/long)
- LDAP_OPT_X_TLS_PROTOCOL_MIN (value data type int/long)
- LDAP_OPT_X_TLS_RANDOM_FILE (value data type string/symbol)
- LDAP_OPT_X_TLS_REQUIRE_CERT (value data type int/long)

### .ldap.setGlobalOption

Sets options globally that affect LDAP operating procedures. Reference .ldap.setOption for params & details.

Syntax: `.ldap.setGlobalOption[option;value]`

### .ldap.getOption

Gets session options that affect LDAP operating procedures. Reference [ldap_set_option](https://www.openldap.org/software/man.cgi?query=ldap_set_option&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release)

Syntax: `.ldap.getOption[sess;option]`

Where

- sess is an int/long that represents the session previously created via .ldap.init
- option is a symbol for the option you wish to get. See supported options below

Value returned from function depends on options used. Supported LDAP options

- LDAP_OPT_API_FEATURE_INFO (returns dict containing feature version info - subset of LDAP_OPT_API_INFO)
- LDAP_OPT_API_INFO (returns dict containing API version info)
- LDAP_OPT_CONNECT_ASYNC (returns int)
- LDAP_OPT_DEBUG_LEVEL (returns int)
- LDAP_OPT_DEREF (returns int)
- LDAP_OPT_DESC (returns int)
- LDAP_OPT_DIAGNOSTIC_MESSAGE (returns string)
- LDAP_OPT_MATCHED_DN (returns string)
- LDAP_OPT_NETWORK_TIMEOUT (return int representing microseconds)
- LDAP_OPT_PROTOCOL_VERSION (returns int)
- LDAP_OPT_REFERRALS (returns int)
- LDAP_OPT_RESULT_CODE (returns int)
- LDAP_OPT_SIZELIMIT (returns int)
- LDAP_OPT_TIMELIMIT (returns int)
- LDAP_OPT_TIMEOUT (return int representing microseconds)

Supported SASL options

- LDAP_OPT_X_SASL_AUTHCID (returns string)
- LDAP_OPT_X_SASL_AUTHZID (returns string)
- LDAP_OPT_X_SASL_MAXBUFSIZE (returns long)
- LDAP_OPT_X_SASL_MECH (returns string)
- LDAP_OPT_X_SASL_MECHLIST (returns string)
- LDAP_OPT_X_SASL_NOCANON (returns int)
- LDAP_OPT_X_SASL_REALM (returns string)
- LDAP_OPT_X_SASL_SSF (returns long)
- LDAP_OPT_X_SASL_SSF_MAX (returns long)
- LDAP_OPT_X_SASL_SSF_MIN (returns long)
- LDAP_OPT_X_SASL_USERNAME (returns string)

Supported TCP options

- LDAP_OPT_X_KEEPALIVE_IDLE (returns int)
- LDAP_OPT_X_KEEPALIVE_PROBES (returns int)
- LDAP_OPT_X_KEEPALIVE_INTERVAL (returns int)

Supported TLS options

- LDAP_OPT_X_TLS_CACERTDIR (returns string)
- LDAP_OPT_X_TLS_CACERTFILE (returns string)
- LDAP_OPT_X_TLS_CERTFILE (returns string)
- LDAP_OPT_X_TLS_CIPHER_SUITE (returns string)
- LDAP_OPT_X_TLS_CRLCHECK (returns int)
- LDAP_OPT_X_TLS_CRLFILE (returns string)
- LDAP_OPT_X_TLS_DHFILE (returns string)
- LDAP_OPT_X_TLS_KEYFILE (returns string)
- LDAP_OPT_X_TLS_PROTOCOL_MIN (returns int)
- LDAP_OPT_X_TLS_RANDOM_FILE (returns string)
- LDAP_OPT_X_TLS_REQUIRE_CERT (returns int)

### .ldap.getGlobalOption

Gets options globally that affect LDAP operating procedures. Reference .ldap.getOption for details and parameter details

Syntax: `.ldap.getGlobalOption[option]`

### .ldap.bind_s

Synchronous bind operations are used to authenticate clients (and the users or applications behind them) to the directory server, to establish an authorization identity that will be used for subsequent operations processed on that connection, and to specify the LDAP protocol version that the client will use. See [here](https://ldap.com/the-ldap-bind-operation/) for reference documentation

Syntax: `.ldap.bind_s[sess;dn;cred;mech]`

Where

- sess is an int/long that represents the session previously created via .ldap.init
- dn is a string/symbol. The DN of the user to authenticate. This should be empty for anonymous simple authentication, and is typically empty for SASL authentication because most SASL mechanisms identify the target account in the encoded credentials. It must be non-empty for non-anonymous simple authentication.
- cred is a string/symbol. LDAP credentials (e.g. password). Pass empty string/symbol when no password required for connection.
- mech is a string/symbol. Pass an empty string to use the default LDAP_SASL_SIMPLE mechanism. Query the attribute 'supportedSASLMechanisms' from the  server's rootDSE for the list of SASL mechanisms the server supports.

Returns a dict consisting of 

- ReturnCode - integer. See error code reference  within this document.
- Credentials - byte array which is the credentials returned by the server. Contents are empty for LDAP_SASL_SIMPLE, though for other SASL mechanisms, the credentials may need to be used with other security related functions (which may be external to LDAP). Reference documentation for your security mechanism.

### .ldap.search_s

Synchronous search for partial or complete copies of entries based on a search criteria.

Syntax: .ldap.search_s[sess;baseDn;scope;filter;attrs;attrsOnly;timeLimit;sizeLimit]

Where

- sess is an int/long that represents the session previously created via .ldap.init
- baseDn is a string/symbol. The base of the subtree to search from. An empty string/symbol can be used to search from the root (or when a DN is not known).
- scope  is an int/long. Can be set to one of the following values:
  - 0 (LDAP_SCOPE_BASE) Only the entry specified will be considered in the search & no subordinates used
  - 1 (LDAP_SCOPE_ONELEVEL) Only search the immediate children of entry specified. Will not use the entry specified or further subordinates from the children.
  - 2 (LDAP_SCOPE_SUBTREE) To search the entry and all subordinates
  - 3 (LDAP_SCOPE_CHILDREN) To search all of the subordinates
- filter is a string/symbol. The filter to be applied to the search ([reference](https://ldap.com/ldap-filters/))
- attrs is a symbol list. The set of attributes to include in the result. If a specific set of attribute descriptions are listed, then only those attributes should be included in matching entries. The special value “*” indicates that all user attributes should be included in matching entries. The special value “+” indicates that all operational attributes should be included in matching entries. The special value “1.1” indicates that no attributes should be included in matching entries. Some servers may also support the ability to use the “@” symbol followed by an object class name (e.g., “@inetOrgPerson”) to request all attributes associated with that object class. If the set of attributes to request is empty, then the server should behave as if the value “*” was specified to request that all user attributes be included in entries that are returned.
- attrsOnly is an int/long. Should be set to a non-zero value if only attribute descriptions are wanted. It should be set to zero (0) if both attributes descriptions and attribute values are wanted.
- timeLimit is an int/long. Max number of microseconds to wait for a result. 0 represents no limit. Note that the server may impose its own limit.
- sizeLimit is an int/long. Max number of entries to use in the result. 0 represents no limit. Note that the server may impose its own limit.

Returns a dict consisting of 

- ReturnCode - integer. See error code reference within this document
- Entries - table consisting of DNs and Attributes. Attribute forms a dictionary, were each attribute may contain one or more values.
- Referrals - list of strings providing the referrals that can be searched to gain access to the required info (if server supports referrals)

### .ldap.unbind_s

Synchronous unbind from the directory, terminate the current association, and free resources.

Syntax: `.ldap.unbind_s[sess]`

Where 

- sess is an int/long that represents the session previously created via .ldap.init. The number should not longer be used unless .ldap.init and .ldap.bind_s has been used to create a new session.

### .ldap.err2string

Returns a string description of an LDAP error code. The error codes are negative for an API error, 0 for success, and positive for a LDAP result code

Syntax: `.ldap.err2string[err]`

Where 

- err is an ldap error code (see error code reference  within this document)

## Error Code Reference

The function .ldap.err2string call can provide a string representation of the error code.

0 = Success

### Protocol Codes

-ve values

Reference IANA registered result codes [here](https://www.iana.org/assignments/ldap-parameters/ldap-parameters.xhtml#ldap-parameters-6)

### API Error Codes

+ve values

| Code | Name                         | Details                                                      |
| ---- | ---------------------------- | ------------------------------------------------------------ |
| -1   | LDAP_SERVER_DOWN             | The LDAP library can't contact the LDAP server.              |
| -2   | LDAP_LOCAL_ERROR             | Some local  error  occurred.   This  is  usually  a failed dynamic memory allocation. |
| -3   | LDAP_ENCODING_ERROR          | An  error  was  encountered  encoding parameters to send to the LDAP server. |
| -4   | LDAP_DECODING_ERROR          | An error was encountered decoding a result from the LDAP server. |
| -5   | LDAP_TIMEOUT                 | A  timelimit  was  exceeded  while  waiting  for  a result.  |
| -6   | LDAP_AUTH_UNKNOWN            | The authentication method specified to  ldap_bind()  is not known. |
| -7   | LDAP_FILTER_ERROR            | An  invalid  filter  was  supplied to ldap_search() (e.g., unbalanced parentheses). |
| -8   | LDAP_USER_CANCELLED          | Indicates the user cancelled the operation.                  |
| -9   | LDAP_PARAM_ERROR             | An ldap routine was called with a bad parameter.             |
| -10  | LDAP_NO_MEMORY               | An memory  allocation  (e.g.,  [malloc(3)](https://www.openldap.org/software/man.cgi?query=malloc&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release)  or  other  dynamic  memory  allocator)  call failed in an ldap library routine. |
| -11  | LDAP_CONNECT_ERROR           | Indicates a connection problem.                              |
| -12  | LDAP_NOT_SUPPORTED           | Indicates the routine was called in  a  manner  not supported by the library. |
| -13  | LDAP_CONTROL_NOT_FOUND       | Indicates  the  control  provided is unknown to the client library. |
| -14  | LDAP_NO_RESULTS_RETURNED     | Indicates no results returned.                               |
| -16  | LDAP_CLIENT_LOOP             | Indicates the library has detected a  loop  in  its processing. |
| -17  | LDAP_REFERRAL_LIMIT_EXCEEDED | Indicates the referral limit has been exceeded.              |
| -18  | LDAP_X_CONNECTING            |                                                              |



