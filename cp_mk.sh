#!/bin/bash

# script to do a "hardwired cross compile" by pushing the file to my pi and compile it there via ssh.
# ssh key added to the known keys on raspberry.

scp ./sipserv.c pi@pi3.local:SIP-Pi/sipserv.c
ssh pi@pi3.local << EOF
cd SIP-Pi 
./sipserv-ctrl.sh stop
make
EOF

