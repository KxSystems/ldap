# LDAP kdb+ library installation

## Download

Download the latest release from our [releases page](https://github.com/KxSystems/ldap/releases)

## Installation

### Linux

Prior to using this interface, the OpenLdap library package should be installed (e.g. RedHat releases may include OpenLdap package by default), which includes `libldap.so`. The latest OpenLdap can also be built and installed from source, by obtaining the latest release from [here](https://openldap.org/).

To install this kdb+ LDAP library and scripts, either

- run the provided `install.sh`

or

- copy `kdbldap.so` which was built or downloaded earlier to your kdb+ folder. If on a Linux 64-bit machine with kdb+ installed in `/usr/local/q`, place the shared library into `/usr/local/q/l64/`.
- the q script to load the ldap API (`ldap.q`) can be placed in the current working directory or within the kdb+ install directory.

### Windows

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

### macOS (Intel)

You can build OpenLdap from [source](https://openldap.org/software/download/), or use a package manager such as HomeBrew. The [HomeBrew](https://brew.sh/) package manager provides a installation of OpenLdap. Once HomeBrew is available on your Mac, run the following to install OpenLdap

```bash
brew install OpenLdap
```

To install the library and scripts, either

- run the provided `install.sh`

or

- Copy `kdbldap.so` which was built or downloaded earlier, to your kdb+ install binary dir e.g. if kdb+ installed at `/usr/local/q`, place the shared library into `/usr/local/q/m64/`..
- The q script to load the ldap API (`ldap.q`) can be placed in the current working directory or within the kdb+ install directory.

