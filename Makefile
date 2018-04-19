all: sipcall sipserv

sipcall: sipcall.c
	cc -o $@ $< `pkg-config --cflags --libs libpjproject`
	
sipserv: sipserv.c
	cc -o $@ $< `pkg-config --cflags --libs libpjproject`

sipserv-gpio: sipserv.c
		cc -o sipserv $< `pkg-config --cflags --libs libpjproject`  -L/usr/local/lib -lwiringPi -Dgpioenable

sipserv-tcp: sipserv.c
		cc -o sipserv $< `pkg-config --cflags --libs libpjproject`  -L/usr/local/lib -lwiringPi -lphread -Dgpioenable -Dtcpmodule 
clean:
	rm -rf sipcall
	rm -rf sipserv

