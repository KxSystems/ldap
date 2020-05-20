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

TODO 

### .ldap.getOption

TODO

### .ldap.bind

TODO

### .ldap.search

TODO

