#!/bin/bash   


CC=gcc #o gcc?


#-O0 Means “no optimization”: this level compiles the fastest and generates the most debuggable code.
#-O1 Somewhere between -O0 and -O2.
#-O2 Moderate level of optimization which enables most optimizations.
#-O3 Like -O2, except that it enables optimizations that take longer to perform or that may generate larger code 
#         (in an attempt to make the program run faster).
OPTIONS="-O2" 

OPTIONS=${OPTIONS}" -lpthread"


${CC} ${OPTIONS} 6.1_threads.c -o 6.1_threads
${CC} ${OPTIONS} 6.2_producer_consumer_semaphore.c -o 6.2_producer_consumer_semaphore
${CC} ${OPTIONS} 6.3_reader_writer_semaphore.c -o 6.3_reader_writer_semaphore
${CC} ${OPTIONS} 6.4_producer_consumer_pthread.c -o 6.4_producer_consumer_pthread
