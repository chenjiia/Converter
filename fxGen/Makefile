PROGRAM = fxGen
CFILES = fxGenPre.c fxGen.c 
HEADERS = fxGenPre.h fxGen.h

CC = gcc
CFLAGS = -Wall

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	
$(PROGRAM): $(CFILES:.c=.o)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	-rm -f $(CFILES:.c=.o)
	-rm -f $(PROGRAM)
