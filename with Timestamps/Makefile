GCC = gcc
# CFLAGS = -fopenmp -pthread -fcilkplus -O3 -msse

CMAIN=timestampsWith

all: timestampsWith.o
	$(GCC) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)

cleanAll:
		rm -f *.o *~ $(CMAIN) *.txt


# all: qsort-main.o qsort-sequential.o parqsort.o
# 	$(GCC) $(CFLAGS) $^ -o $(CMAIN)
#
# qsort-sequential.o: qsort-sequential.c
# 	$(GCC) -c -pthread $(CFLAGS) $^
#
# # parqsort.o: parqsort.c qsort-main.o qsort-sequential.o
# # 	gcc -pthread -O3 -o $@ $^

# clean:
# 	rm -f *.o *~ $(CMAIN)
