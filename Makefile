binascii: binascii.c
	$(CC) $(CFLAGS) -Wall -pedantic -std=c99 -o $@ $< 
