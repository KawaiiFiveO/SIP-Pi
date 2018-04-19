# Sip-Tools - Automated calls and answering machine
- sipcall - Automated calls over SIP/VOIP with TTS
- sipserv - Answering machine for SIP/VOIP with TTS

Dependencies:
- PJSUA API (http://www.pjsip.org)
- eSpeak (http://espeak.sourceforge.net)

Copyright (C) 2012 by _Andre Wussow_, desk@binerry.de

major changes 2017 by _Fabian Huslik, github.com/fabianhu_

more changes 2018 by  _Kaito Cross, github.com/KaitoCross_

For more informations please visit http://binerry.de/post/29180946733/raspberry-pi-caller-and-answering-machine.

## Installation on Raspberry Pi 2/3 with Raspian
1. Build and install PjSIP as explained below
2. install eSpeak `sudo apt-get install espeak espeak-data`

3. If output of DTMF digits through GPIO in sipserv is needed: (if not, skip to step 6)
4. install wiringPi as outlined on http://wiringpi.com/download-and-install/
5. after executing `./build` as described in link, run sudo make install for wiringPi

6. Download this folder to Raspberry Pi
7. If output of DTMF digits in sipserv (answer machine) through GPIO is needed: execute `make sipserv-gpio` in SIP-Pi folder in Terminal
8. If forwarding the 4 last DTMF digits to a tcp server is needed, run `make sipserv-tcp` instead
9. `make sipcall` if you need the standalone phone software as well
8. If the mentioned output options are not needed, just execute `make all` in SIP-Pi folder in Terminal instead

9. configure `sipserv.cfg` to your needs (see example configuration)
10. test drive using`sudo ./sipserv --config-file sipserv.cfg`
11. this is not(yet) a "real" service, so include `./sipserv-ctrl.sh start` command into your favourite autostart.
12. stop the SIP service using `sipserv-ctrl.sh stop`
13. install lame `sudo apt-get install lame` for the MP3 compression of recordings (mail.sh)

## sipserv

Pickup a call, have a welcome message played or read.
Do some actions by pressing (DTMF) keys on your phone.
Get 4-bit DTMF key value through GPIO if wished.
This service uses a generic approach. All actions are configurable via config file.
One special usage is the special ability to record the caller while playing the intro.
Please contact your lawyer, if this is legal in your country.
With the sample configuration you can have a blacklist and only the special (=blacklisted) calls answered.


### Usage:   (if GPIO output needed, has to run as root)
  `sipserv [options]`   

### Commandline:
#### Mandatory options:
* --config-file=string   _Set config file_   

#### Optional options:
* -s=int       _Silent mode (hide info messages) (0/1)_   

### Config file:
#### Mandatory options:
* ipv6=int	_IPv6 usage (0/1) Only set to 1 if you want to use IPv6 exclusively_
* sd=string   _Set sip provider domain._   
* su=string   _Set sip username._   
* sp=string   _Set sip password._   
* ln=string   _Language identifier for espeak TTS (e.g. en = English or de = German)._

* tts=string  _String to be read as a intro message_

#### _determine DTMF Key digit encoding_
* dtmf-encoding=int _Set DTMF digit output binary encoding (0=linear/1=MT8870 scheme) (default linear)_

#### _and at least one dtmf key configuration (X = dtmf-key index):_
* dtmf.X.active=int           _Set dtmf-setting active (0/1)._   
* dtmf.X.description=string   _Set description._
* dtmf.X.audio-response=      _Set audio response wav file to play; tts for that DTMF key will not be read, if this parameter is given. File format is Microsoft WAV (signed 16 bit) Mono, 22 kHz;_
* dtmf.X.tts-intro=string     _Set tts intro._   
* dtmf.X.tts-answer=string    _Set tts answer._   
* dtmf.X.cmd=string           _Set shell command._   

#### Optional options:
* rc=int      _Record call (0=no/1=yes)_   
* af=string   _announcement wav file to play; tts will not be read, if this parameter is given. File format is Microsoft WAV (signed 16 bit) Mono, 22 kHz;_ 
* cmd=string  _command to check if the call should be taken; the wildcard # will be replaced with the calling phone number; should return a "1" as first char, if you want to take the call._
* am=string   _aftermath: command to be executed after call ends. Will be called with two parameters: $1 = Phone number $2 = recorded file name_
* gpio-en=int _enable output of DTMF digits on Raspberry Pi wiringPi GPIO_

#### options for DTMF forwarding to TCP server:
* dtmf-value-forward-srv=string  _Set domain name of tcp server_

#### options for DTMF digit output on Raspberry Pi GPIO
The GPIO output function is based on wiringPi and uses the wiringPi numbering scheme.
It outputs the digits as 4-bit binary number.
When GPIO output has been enabled, you have to define all 4 output ports and the interrupt port.
To define them, put this into the config file:
* gpio-0=int _Port number goes here instead of int_
* gpio-1=int _Port number goes here instead of int_
* gpio-2=int _Port number goes here instead of int_
* gpio-3=int _Port number goes here instead of int_
* gpio-interrupt=int  _Port number goes here instead of int_
The interrupt port is often needed by the microprocesser that reads those digits.
Connect it to the interrupt port of your other microprocesser and configure that controller as needed to respond to the interrupt.

#### a sample configuration can be found in sipserv-sample.cfg
  
### sipserv can be controlled with
```bash
sudo ./sipserv-ctrl.sh start and
sudo ./sipserv-ctrl.sh stop
```

Changelog since fabianhu's version:
* Implemented IPv6 Support
* added option for wavefile being played instead of an tts file when DTMF key has been pressed
* added *, #, 0, and A-D into processable DTMF-signals
* added forwarding of last 4 DTMF digits to TCP server after # is pressed
## Build PjSIP

### build directly on Raspberry Pi:

```bash
cd ~/tmp # any temporary directory
wget http://www.pjsip.org/release/2.7.1/pjproject-2.7.1.tar.bz2
tar xvfj pjproject-2.7.1.tar.bz2
cd pjproject-2.7.1/
./configure --disable-video --disable-libwebrtc

nano pjlib/include/pj/config_site.h (add next line into file:)
#define PJ_HAS_IPV6 1

navigate back to pjproject-2.7.1 folder

make dep 
make
sudo make install
```
You will have plenty of time to drink some Dr. Pepper during `make`. Enjoy while waiting.

### Cross build of PjSIP for Raspberry:

```sh
export CC=/opt/raspi_tools/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc
export LD=/opt/raspi_tools/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc
export CROSS_COMPILE=/opt/raspi_tools/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-
#export AR+=" -rcs"

export LDFLAGS="-L/opt/raspi_tools/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/lib/gcc/arm-linux-gnueabihf/4.8.3 -L/opt/raspi_tools/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/lib -ldl -lc"

./aconfigure --host=arm-elf-linux --prefix=$(pwd)/tmp_build --disable-video --disable-libwebrtc

Add into pjlib/include/pj/config_site.h:
#define PJ_HAS_IPV6 1

navigate back to pjproject-2.7.1 folder

make dep

make
```

# sipcall

Make outgoing calls with your Pi.

## Usage:
* sipcall [options]   

## Mandatory options:
* -sd=string   _Set sip provider domain._   
* -su=string   _Set sip username._   
* -sp=string   _Set sip password._   
* -pn=string   _Set target phone number to call_   
* -tts=string  _Text to speak_   

## Optional options:
* -ttsf=string _TTS speech file name_   
* -rcf=string  _Record call file name_   
* -mr=int      _Repeat message x-times_   
* -s=int       _Silent mode (hide info messages) (0/1)_   
* -ipv6=int    _IPv6 mode (use IPv6 exclusively) (0/1)_
  
_see also source of sipcall-sample.sh_


# License

This tools are free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This tools are distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
