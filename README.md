# LDAP interface for KDB+
## Introduction

TODO

## Documentation

Documentation outlining the functionality available for this interface can be found [here](https://code.kx.com/q/interfaces/ldap). (*URL NOT CURRENT OPERATIONAL - SEE CODE.KX.COM SECTION BELOW*)

## New to kdb+ ?

Kdb+ is the world's fastest time-series database, optimized for ingesting, analyzing and storing massive amounts of structured data. To get started with kdb+, please visit https://code.kx.com/q/learn/ for downloads and developer information. For general information, visit https://kx.com/

## Running 

TODO

## Building Interface From Source

TODO

# Code.kx.com Content

## Overview

TODO

## Reference

### .ldap.init

Initializes the session with LDAP server connection details. Connection will occur on first operation. Does not create a connection. Reference [ldap_initialize](https://www.openldap.org/software/man.cgi?query=ldap_init&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release)

Syntax: `.ldap.init[uris]`

Where

- uris is a symbol list. Each URI in the list must follow the format of schema://host:port , where schema is 'ldap','ldaps','ldapi', or 'cldap'.

Returns 0 if successful.

### .ldap.setOption

Sets options globally or per session that affect LDAP operating procedures. Reference [ldap_set_option](https://www.openldap.org/software/man.cgi?query=ldap_set_option&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release)

Syntax: `.ldap.setOption[global;option;value]`

Where

- global is a boolean on whether to set the value globally (true) or for the session (false)
- option is a symbol for the option you wish to set. See supported options below.
- value is the value relating to the option. The data type depends on the option selected (see below)

Supported LDAP options

- LDAP_OPT_CONNECT_ASYNC (value data type int/long)
- LDAP_OPT_DEBUG_LEVEL (value data type int/long)
- LDAP_OPT_DEREF (value data type int/long)
- LDAP_OPT_PROTOCOL_VERSION (value data type int/long)
- LDAP_OPT_REFERRALS (value data type int/long)
- LDAP_OPT_RESULT_CODE (value data type int/long)
- LDAP_OPT_SIZELIMIT (value data type int/long)
- LDAP_OPT_TIMELIMIT (value data type int/long)
- TODO further options

Supported SASL options

- LDAP_OPT_X_SASL_NOCANON (value data type int/long)
- TODO

Supported TCP options

- LDAP_OPT_X_KEEPALIVE_IDLE (value data type int/long)
- LDAP_OPT_X_KEEPALIVE_PROBES (value data type int/long)
- LDAP_OPT_X_KEEPALIVE_INTERVAL (value data type int/long)

Supported TLS options

- LDAP_OPT_X_TLS_NEWCTX (value data type int/long)
- LDAP_OPT_X_TLS_PROTOCOL_MIN (value data type int/long)
- LDAP_OPT_X_TLS_REQUIRE_CERT (value data type int/long)
- TODO

### .ldap.getOption

Gets options globally or per session that affect LDAP operating procedures. Reference [ldap_set_option](https://www.openldap.org/software/man.cgi?query=ldap_set_option&sektion=3&apropos=0&manpath=OpenLDAP+2.4-Release)

Syntax: `.ldap.getOption[global;option]`

Where

- global is a boolean on whether to set the value globally (true) or for the session (false)
- option is a symbol for the option you wish to get. See supported options below

Value returned from function depends on options used. Supported LDAP options

- LDAP_OPT_API_INFO (returns dict containing API version info)
- LDAP_OPT_CONNECT_ASYNC (returns int)
- LDAP_OPT_DEBUG_LEVEL (returns int)
- LDAP_OPT_DEREF (returns int)
- LDAP_OPT_PROTOCOL_VERSION (returns int)
- LDAP_OPT_REFERRALS (returns int)
- LDAP_OPT_RESULT_CODE (returns int)
- LDAP_OPT_SIZELIMIT (returns int)
- LDAP_OPT_TIMELIMIT (returns int)

Supported SASL options

- LDAP_OPT_X_SASL_NOCANON (returns int)
- TODO

Supported TCP options

- LDAP_OPT_X_KEEPALIVE_IDLE (returns int)
- LDAP_OPT_X_KEEPALIVE_PROBES (returns int)
- LDAP_OPT_X_KEEPALIVE_INTERVAL (returns int)

Supported TLS options

- LDAP_OPT_X_TLS_PROTOCOL_MIN (returns int)
- LDAP_OPT_X_TLS_REQUIRE_CERT (returns int)
- TODO

### .ldap.bind

TODO

### .ldap.search

TODO

