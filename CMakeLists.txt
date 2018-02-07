cmake_minimum_required(VERSION 3.9)
project(SIP_Pi_master)



set(CMAKE_CXX_STANDARD 11)

# add extra include directories
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjlib\\include)
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjlib-util\\include)
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjmedia\\include)
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjsip\\include)
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjnath\\include)
include_directories(C:\\Users\\chris\\sciebo\\GitHub\\SIP-Pi)

# add extra lib directories
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjlib\\lib)
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjlib-util\\lib)
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjmedia\\lib)
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjsip\\lib)
include_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjnath\\lib)

# specify the executable (no libraries here)
link_directories(C:\\Users\\chris\\sciebo\\GitHub\\SIP-Pi)
link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjlib\\include)
link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjlib-util\\include)
link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjmedia\\include)
link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjsip\\include)
link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjnath\\include)

link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjlib\\lib)
link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjlib-util\\lib)
link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjmedia\\lib)
link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjsip\\lib)
link_directories(C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjnath\\lib)
add_executable(SIP_Pi_master
        sipcall.c
        sipserv.c pi-out.c)
# specify the dependency on an extra library
#target_link_libraries(hello_clion check.a)
target_link_libraries(SIP_Pi_master C:\\Users\\chris\\Downloads\\pjproject-2.7.1\\pjproject-2.7.1\\pjlib\\include\\pjsua-lib\\pjsua.h)


