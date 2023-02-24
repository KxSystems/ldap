# LDAP interface for kdb+

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/kxsystems/ldap?include_prereleases)](https://github.com/kxsystems/ldap/releases) [![Travis (.org) branch](https://img.shields.io/travis/kxsystems/ldap/master?label=travis%20build)](https://travis-ci.org/kxsystems/ldap/branches)



This interface allows kdb+ to interact with the Lightweight Directory Access Protocol (LDAP). This API permits a client to authenticate and search against an LDAP server. The interface is a thin wrapper around the open-source OpenLdap library. General info on this API is available [here](https://www.openldap.org/software/man.cgi?query=ldap&sektion=3&apropos=0&manpath=OpenLdap+2.4-Release).

In addition to authentication and authorization uses, depending on the data stored on your LDAP server, it could be used to access data for analytics e.g.

- company staff turnover (if user creation date/leave dates/etc recorded)
- IT equipment approaching end of life (if hardware details recorded)
- staff departmental memberships

## New to kdb+ ?

Kdb+ is the world's fastest time-series database, optimized for ingesting, analyzing and storing massive amounts of structured data. To get started with kdb+, please visit https://code.kx.com/q/ for downloads and developer information. For general information, visit https://kx.com/

## New to LDAP?

General information is available [here](https://ldap.com/). 

## API Documentation

:point_right:
[**Documentation**](documentation.md)

## Running 

### Download

Download the latest release from our [releases page](https://github.com/KxSystems/ldap/releases)

### Installation

#### Linux

Prior to using this interface, the OpenLdap library package should be installed (e.g. RedHat releases may include OpenLdap package by default), which includes `libldap.so`. The latest OpenLdap can also be built and installed from source, by obtaining the latest release from [here](https://openldap.org/).

To install this kdb+ LDAP library and scripts, either

- run the provided `install.sh`

or

- copy `kdbldap.so` which was built or downloaded earlier to your kdb+ folder. If on a Linux 64-bit machine with kdb+ installed in `/usr/local/q`, place the shared library into `/usr/local/q/l64/`.
- the q script to load the ldap API (`ldap.q`) can be placed in the current working directory or within the kdb+ install directory.

#### Windows

You can build OpenLdap from [source](https://openldap.org/software/download/), or use a package manager, such as pacman, provided with [msys64](https://www.msys2.org/). Move the OpenLdap libs from your install  (e.g. if using mssys and pacman, these libs may be found in the `mingw64\bin` directory) to the kdb+ `w64` directory. The OpenLdap libs required are:

- `libcrypto-1_1-x64.dll`
- `liblber.dll`
- `libldap.dll`
- `libsasl2-3.dll`
- `libssl-1_1-x64.dll`

To install the library and scripts interface that this repo provides, either

- run the provided `install.bat`

or

- copy `kdbldap.dll` which was built or downloaded earlier, to your kdb+ install binary dir e.g. if kdb+ installed at `C:\q`, place the shared library into `C:\q\w64\`.
- copy the q script to load the LDAP API (`ldap.q`) in the current working directory or within the kdb+ install directory.

#### macOS (Intel)

You can build OpenLdap from [source](https://openldap.org/software/download/), or use a package manager such as HomeBrew. The [HomeBrew](https://brew.sh/) package manager provides a installation of OpenLdap. Once HomeBrew is available on your Mac, run the following to install OpenLdap

```bash
brew install OpenLdap
```

To install the library and scripts, either

- run the provided `install.sh`

or

- Copy `kdbldap.so` which was built or downloaded earlier, to your kdb+ install binary dir e.g. if kdb+ installed at `/usr/local/q`, place the shared library into `/usr/local/q/m64/`..
- The q script to load the ldap API (`ldap.q`) can be placed in the current working directory or within the kdb+ install directory.

## Building the interface from source

### Linux

#### Linux OpenLdap builds

The latest release of OpenLdap is at https://www.openldap.org/software/release.

For example, the 2.6.3 release is available in source form from 

https://www.openldap.org/software/download/openldap/openldap-release/openldap-2.6.3.tgz 

To build/install, unzip the downloaded source and run

```bash
./configure --disable-slapd --with-tls=openssl
make
make install
```

#### Building the Linux interface

After installing OpenLdap, to create a build within the `build` directory run the following:

```bash
cd build
cmake ../
make install
```

You should then find the resulting files in a newly created `api` dir within the `build` directory.

### Windows

#### Windows OpenLdap builds

Pre-built OpenLdap Windows libraries can be retrieved using pacman package manager (supplied with MSYS2). The package is [`mingw-w64-x86_64-openldap`](https://packages.msys2.org/package/mingw-w64-x86_64-openldap). Example instruction for install

```shell
# update database of packages
pacman -Fy
# search for OpenLdap package name
pacman -Ss OpenLdap
# list contents of package prior to install
pacman -Fl <x64 package name found in prev search>
# install package
pacman -S <x64 package name found in prev search>
```

##### Converting MSYS2-provided `libldap.dll` to `libldap.lib` for use with Visual Studio

Use the provided `dll2lib.bat` to convert `liblber.dll` and `libldap.dll` (found in the `mingw64/bin` dir of your MSYS2 install).

The batch file `dll2lib.bat` should be run from a VS command prompt in order to use tools from Visual Studio.

```shell
dll2lib.bat liblber.dll
dll2lib.bat libldap.dll
```

Move the resulting `liblber.lib` and `libldap.lib` to the `mingw64/lib` dir of your MSYS2 install.

### Building Windows interface

##### Example build command using Visual Studio 2019

Open _x64 Native Tools Command Prompt for VS 2019_ as supplied with Visual Studio.

Go to the downloaded source and enter the `build` directory. Run the following builds commands

```shell
set BUILD_HOME=<dir containing lib and include directory of the OpenLdap library>
cmake -G "Visual Studio 16 2019" -A x64 ..
MSBuild.exe INSTALL.vcxproj /m /nologo /verbosity:normal /p:Configuration=Release /p:Platform=x64
```

Created libs/etc can then be found in the newly created `kdbldap` dir

### macOS

#### macOS OpenLdap builds

The [HomeBrew](https://brew.sh/) install manager installs OpenLdap. Once HomeBrew is available on your machine, run the following to install OpenLdap

```bash
brew install openldap
```

#### Building the macOS interface

Building the interface from source requires `gcc`, `gcc c++`, `make` and `cmake` packages installed on your development machine (e.g. Xcode for Mac).

Follow these steps

1. Install OpenLdap (see above)
2. Set an environment variable `BUILD_HOME` to the location on the installed OpenLdap
3. Run `cmake`
4. Run `make install`

For example, on Linux/macOS, to create a build within the `build` directory

```bash
export BUILD_HOME=/usr/local/opt/OpenLdap/
cd build
cmake ../
make install
```

You should then find the resulting files in a newly created `api` dir within the `build` directory.

## OpenLdap license

> Third-party OpenLdap license
> 
> The OpenLdap Public License  Version 2.8, 17 August 2003 Redistribution and use of this software and associated documentation ("Software"), with or without modification, are permitted provided that the following conditions are met: 1. Redistributions in source form must retain copyright statements   and notices, 2. Redistributions in binary form must reproduce applicable copyright   statements and notices, this list of conditions, and the following   disclaimer in the documentation and/or other materials provided   with the distribution, and 3. Redistributions must contain a verbatim copy of this document. The OpenLdap Foundation may revise this license from time to time. Each revision is distinguished by a version number.  You may use this Software under terms of this license revision or under the terms of any subsequent revision of the license. THIS SOFTWARE IS PROVIDED BY THE OpenLdap FOUNDATION AND ITS CONTRIBUTORS “AS IS” AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenLdap FOUNDATION, ITS CONTRIBUTORS, OR THE AUTHOR(S) OR OWNER(S) OF THE SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. The names of the authors and copyright holders must not be used in advertising or otherwise to promote the sale, use or other dealing in this Software without specific, written prior permission.  Title to copyright in this Software shall at all times remain with copyright holders. OpenLdap is a registered trademark of the OpenLdap Foundation. Copyright 1999-2003 The OpenLdap Foundation, Redwood City, California, USA.  All Rights Reserved.  Permission to copy and distribute verbatim copies of this document is granted.

<!-- FIXME

is in the :open_file_folder: [`docs`](docs) folder.

 -->
