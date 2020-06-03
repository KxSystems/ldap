cmake_minimum_required(VERSION 2.8)
project(ldapkdb C)

set (CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DKXVER=3")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -DKXVER=3")

set(MY_LIBRARY_NAME kdbldap)
file(GLOB SRC_FILES src/*.c)
set_source_files_properties(${SRC_FILES} PROPERTIES LANGUAGE C)

message(STATUS "Generator : ${CMAKE_GENERATOR}")
message(STATUS "Build Tool : ${CMAKE_BUILD_TOOL}")
message(STATUS "Solace API : $ENV{LDAP_API_DIR}")

find_library(OPENLDAP_LIBRARY
    NAMES ldap wldap32
)

if (CMAKE_GENERATOR MATCHES "Visual Studio")
    set(LINK_LIBS "${CMAKE_BINARY_DIR}/q.lib") 
    set(LBER_LIBRARY "")
else()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-strict-aliasing")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-strict-aliasing")
    find_library(LBER_LIBRARY
        NAMES lber
    )
endif()
    
add_library (${MY_LIBRARY_NAME} SHARED ${SRC_FILES})

IF(APPLE)
   set_target_properties(${MY_LIBRARY_NAME} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
   set_target_properties(${MY_LIBRARY_NAME} PROPERTIES SUFFIX .so)
endif()

target_link_libraries(${MY_LIBRARY_NAME} ${LBER_LIBRARY} ${OPENLDAP_LIBRARY} ${LINK_LIBS})
set_target_properties(${MY_LIBRARY_NAME} PROPERTIES PREFIX "")

install(FILES README.md install.sh install.bat DESTINATION ${PROJECT_BINARY_DIR}/kdbldap/)
install(DIRECTORY examples DESTINATION ${PROJECT_BINARY_DIR}/kdbldap)
install(DIRECTORY script DESTINATION ${PROJECT_BINARY_DIR}/kdbldap)
install(TARGETS ${MY_LIBRARY_NAME} DESTINATION ${PROJECT_BINARY_DIR}/kdbldap/lib OPTIONAL)
