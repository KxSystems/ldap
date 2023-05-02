# LDAP interface for kdb+

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/kxsystems/ldap?include_prereleases)](https://github.com/kxsystems/ldap/releases) [![Travis (.org) branch](https://img.shields.io/travis/kxsystems/ldap/master?label=travis%20build)](https://travis-ci.org/kxsystems/ldap/branches)


Lightweight Directory Access Protocol(LDAP) is a vendor-neutral protocol to interact with directory services. The open protocol that client/servers should implement is detailed on [RFC 4511](https://docs.ldap.com/specs/rfc4511.txt).

The protocol is often used by organizations for centralized authentication and storage of their resources such as users, groups, services, applications, etc. For example, a client application can find if a user is a member of a particular group to allow access to their service.

This interface allows kdb+ to interact with the Lightweight Directory Access Protocol (LDAP). This API permits a client to authenticate and search against an LDAP server. The interface is a thin wrapper around the open-source OpenLdap library. General info on this API is available [here](https://www.openldap.org/software/man.cgi?query=ldap&sektion=3&apropos=0&manpath=OpenLdap+2.4-Release).

In addition to authentication and authorization uses, depending on the data stored on your LDAP server, it could be used to access data for analytics e.g.

- company staff turnover (if user creation date/leave dates/etc recorded)
- IT equipment approaching end of life (if hardware details recorded)
- staff departmental memberships

Not all server vendors may provide the same set of features, so this API aims to be vendor-neutral for maximum flexibility.

## New to kdb+ ?

Kdb+ is the world's fastest time-series database, optimized for ingesting, analyzing and storing massive amounts of structured data. To get started with kdb+, please visit https://code.kx.com/q/ for downloads and developer information. For general information, visit https://kx.com/

## New to LDAP?

General information is available [here](https://ldap.com/). 

## API Documentation

:point_right: [`API reference`](docs/reference.md)

## Installation Documentation

:point_right: [`Install guide`](docs/install.md)

## Building From Source

:point_right: [`Building guide`](docs/build.md)

## Examples

:point_right: [`Examples guide`](examples/README.md)

## OpenLdap license

> Third-party OpenLdap license
> 
> The OpenLdap Public License  Version 2.8, 17 August 2003 Redistribution and use of this software and associated documentation ("Software"), with or without modification, are permitted provided that the following conditions are met: 1. Redistributions in source form must retain copyright statements   and notices, 2. Redistributions in binary form must reproduce applicable copyright   statements and notices, this list of conditions, and the following   disclaimer in the documentation and/or other materials provided   with the distribution, and 3. Redistributions must contain a verbatim copy of this document. The OpenLdap Foundation may revise this license from time to time. Each revision is distinguished by a version number.  You may use this Software under terms of this license revision or under the terms of any subsequent revision of the license. THIS SOFTWARE IS PROVIDED BY THE OpenLdap FOUNDATION AND ITS CONTRIBUTORS “AS IS” AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenLdap FOUNDATION, ITS CONTRIBUTORS, OR THE AUTHOR(S) OR OWNER(S) OF THE SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. The names of the authors and copyright holders must not be used in advertising or otherwise to promote the sale, use or other dealing in this Software without specific, written prior permission.  Title to copyright in this Software shall at all times remain with copyright holders. OpenLdap is a registered trademark of the OpenLdap Foundation. Copyright 1999-2003 The OpenLdap Foundation, Redwood City, California, USA.  All Rights Reserved.  Permission to copy and distribute verbatim copies of this document is granted.

<!-- FIXME

is in the :open_file_folder: [`docs`](docs) folder.

 -->
