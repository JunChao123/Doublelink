LIB_NAME = -ldblink
LIB_PATH = -L ./
DESTFILE = dblink
INPUTFILE = dblink.c dblink.h 
obj = dbmain.o

dblink: $(obj) libdblink.a
	gcc -o $(DESTFILE) $(obj) $(LIB_NAME) $(LIB_PATH)

libdblink.a: dblink.o
	ar -cr libdblink.a dblink.o

dblink.o: $(INPUTFILE)
	gcc -c dblink.c

dbmain.o: dbmain.c dblink.h
	gcc -c dbmain.c

clean:
	rm -f $(DESTFILE) *.o *.a
