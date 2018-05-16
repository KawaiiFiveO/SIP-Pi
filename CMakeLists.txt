cmake_minimum_required(VERSION 3.9)
project(SIP_Pi_master)



set(CMAKE_CXX_STANDARD 11)

# add extra include directories
include_directories(/home/kaito/compile/pjproject-2.7/pjlib/include)
include_directories(/home/kaito/compile/pjproject-2.7/pjlib-util/include)
include_directories(/home/kaito/compile/pjproject-2.7/pjmedia/include)
include_directories(/home/kaito/compile/pjproject-2.7/pjsip/include)
include_directories(/home/kaito/compile/pjproject-2.7/pjnath/include)
include_directories(/home/kaito/Hochschule/GitHub/SIP-Pi)
include_directories(/home/kaito/Hochschule/GitHub/SIP-Pi/wiringPi/wiringPi)

# add extra lib directories
include_directories(/home/kaito/compile/pjproject-2.7/pjlib/lib)
include_directories(/home/kaito/compile/pjproject-2.7/pjlib-util/lib)
include_directories(/home/kaito/compile/pjproject-2.7/pjmedia/lib)
include_directories(/home/kaito/compile/pjproject-2.7/pjsip/lib)
include_directories(/home/kaito/compile/pjproject-2.7/pjnath/lib)

# specify the executable (no libraries here)
link_directories(/home/kaito/Hochschule/GitHub/SIP-Pi)
link_directories(/home/kaito/compile/pjproject-2.7/pjlib/include)
link_directories(/home/kaito/compile/pjproject-2.7/pjlib-util/include)
link_directories(/home/kaito/compile/pjproject-2.7/pjmedia/include)
link_directories(/home/kaito/compile/pjproject-2.7/pjsip/include)
link_directories(/home/kaito/compile/pjproject-2.7/pjnath/include)
link_directories(/home/kaito/Hochschule/GitHub/SIP-Pi/wiringPi/wiringPi)

link_directories(/home/kaito/compile/pjproject-2.7/pjlib/lib)
link_directories(/home/kaito/compile/pjproject-2.7/pjlib-util/lib)
link_directories(/home/kaito/compile/pjproject-2.7/pjmedia/lib)
link_directories(/home/kaito/compile/pjproject-2.7/pjsip/lib)
link_directories(/home/kaito/compile/pjproject-2.7/pjnath/lib)
add_executable(SIP_Pi_master
        sipserv.c pi-out.c sipserv-structs.h tcpsocket.c)
# specify the dependency on an extra library
#target_link_libraries(hello_clion check.a)
target_link_libraries(SIP_Pi_master /home/kaito/compile/pjproject-2.7/pjlib/include/pjsua-lib/pjsua.h /home/kaito/Hochschule/GitHub/SIP-Pi/wiringPi/wiringPi/wiringPi.h)


