GCC = gcc

CMAIN=timestampsWithout

all: timestampsWithout.o
	$(GCC) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)

cleanAll:
		rm -f *.o *~ $(CMAIN) *.txt
