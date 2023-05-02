# Building LDAP kdb+ library from source

-> Tip: Prebuilt libraries are available from the [release page](https://github.com/KxSystems/ldap/releases)

## Linux

### Linux OpenLdap builds

The latest release of OpenLdap is at https://www.openldap.org/software/release.

For example, the 2.6.3 release is available in source form from 

https://www.openldap.org/software/download/openldap/openldap-release/openldap-2.6.3.tgz 

To build/install, unzip the downloaded source and run

```bash
./configure --disable-slapd --with-tls=openssl
make
make install
```

### Building the Linux interface

After installing OpenLdap, to create a build within the `build` directory run the following:

```bash
cd build
cmake ../
make install
```

You should then find the resulting files in a newly created `api` dir within the `build` directory.

## Windows

### Windows OpenLdap builds

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

#### Converting MSYS2-provided `libldap.dll` to `libldap.lib` for use with Visual Studio

Use the provided `dll2lib.bat` to convert `liblber.dll` and `libldap.dll` (found in the `mingw64/bin` dir of your MSYS2 install).

The batch file `dll2lib.bat` should be run from a VS command prompt in order to use tools from Visual Studio.

```shell
dll2lib.bat liblber.dll
dll2lib.bat libldap.dll
```

Move the resulting `liblber.lib` and `libldap.lib` to the `mingw64/lib` dir of your MSYS2 install.

## Building Windows interface

#### Example build command using Visual Studio 2019

Open _x64 Native Tools Command Prompt for VS 2019_ as supplied with Visual Studio.

Go to the downloaded source and enter the `build` directory. Run the following builds commands

```shell
set BUILD_HOME=<dir containing lib and include directory of the OpenLdap library>
cmake -G "Visual Studio 16 2019" -A x64 ..
MSBuild.exe INSTALL.vcxproj /m /nologo /verbosity:normal /p:Configuration=Release /p:Platform=x64
```

Created libs/etc can then be found in the newly created `kdbldap` dir

## macOS

### macOS OpenLdap builds

The [HomeBrew](https://brew.sh/) install manager installs OpenLdap. Once HomeBrew is available on your machine, run the following to install OpenLdap

```bash
brew install openldap
```

### Building the macOS interface

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
