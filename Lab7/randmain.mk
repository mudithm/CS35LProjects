randlibsw.so: randlibsw.o
	$(CC) -shared -o randlibsw.so randlibsw.o

randlibhw.so: randlibhw.o
	$(CC) -shared -o randlibhw.so randlibhw.o

randlibsw.o: randlibsw.c
	$(CC) $(CFLAGS) -fPIC -c randlibsw.c

randlibhw.o: randlibhw.c
	$(CC) $(CFLAGS) -fPIC -c randlibhw.c

randcpuid.o: randcpuid.c
	$(CC) $(CFLAGS) randcpuid.c -c

randmain.o: randmain.c
	$(CC) $(CFLAGS) randmain.c -c

randmain: randmain.o randcpuid.o
	$(CC) randmain.o randcpuid.o -ldl -Wl,-rpath=$PWD -o randmain
