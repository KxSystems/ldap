#!/bin/bash

mkdir cbuild

if [ "$TRAVIS_OS_NAME" == "osx" ]; then
  brew install openldap
  mkdir cbuild
  cp -r /usr/local/opt/openldap/lib ./cbuild/
  cp -r /usr/local/opt/openldap/include ./cbuild/
elif [ "$TRAVIS_OS_NAME" == "linux" ]; then
  wget -q https://www.openldap.org/software//download/OpenLDAP/openldap-release/openldap-2.4.50.tgz 
  tar xvf openldap-2.4.50.tgz -C ./cbuild --strip-components=1
  cd cbuild
  ./configure --disable-slapd --with-tls=openssl
  make
  make install
  cd ..
elif [ "$TRAVIS_OS_NAME" == "windows" ]; then
  choco list -localonly
  if [ ! -f C:/tools/msys64/msys2_shell.cmd ]; then rm -rf C:/tools/msys64; fi
  choco install --no-progress msys2 --params "/NoUpdate"
  powershell Install-WindowsFeature Net-Framework-Core
  choco install wixtoolset
  RefreshEnv.cmd
  export SETARCH="cmd.exe //C C:/tools/msys64/msys2_shell.cmd -defterm -mingw64 -no-start -full-path -here -c \$\* --"
  $SETARCH pacman -Fy
  $SETARCH pacman -Sv --noconfirm --needed mingw-w64-x86_64-openldap
  echo "doing dll creation"
  echo $PWD
  chmod +x ./dll2lib.bat
  export DUMPBIN_PATH="/c/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin/"
  export PATH=$PATH:$DUMPBIN_PATH
  env
  echo "running dll2lib.bat to create lib file"
  ./dll2lib.bat C:/tools/msys64/mingw64/bin/liblber.dll
  ./dll2lib.bat C:/tools/msys64/mingw64/bin/libldap.dll
  echo "done lib file creation"
  cp -r /c/tools/msys64/mingw64/include ./cbuild/
  mkdir ./cbuild/lib
  cp /c/tools/msys64/mingw64/bin/*lib ./cbuild/lib/
else
  echo "$TRAVIS_OS_NAME is currently not supported"  
fi
