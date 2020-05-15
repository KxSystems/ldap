docker build -f Dockerfile.build -t ldapdev .
docker run --rm -it -v C:\Users\sshanks\Development\ldap\:/source/code ldapdev /bin/bash -c "cd build && cmake .. && make"