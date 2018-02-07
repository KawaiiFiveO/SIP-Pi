all: sipcall sipserv

sipcall: sipcall.c
	cc -o $@ $< `pkg-config --cflags --libs libpjproject`
	
sipserv: sipserv.c
	cc -o $@ $< `pkg-config --cflags --libs libpjproject`  -L/usr/local/lib -lwiringPi
	
clean:
	rm -rf sipcall
	rm -rf sipserv

