**************************TO RUN*******************************
g++ driver.cpp buffer.cpp -lpthread

dont forget to link the lpthread 

***************************************************************



CS433 Programming Assignment 4
Multi-threaded Programing for the Producer-Consumer Problem (100 points)


Implement project 3 on pages 253-255 of the textbook. You should solve the producer-consumer problem
using the Pthreads API. You program should be able to create multiple producer and consumer threads.


Three parameters are passed on the command line:
1. How long the main thread sleep before terminating (in seconds)
2. The number of producer threads
3. The number of consumer threads


In order to study the behaviors of concurrent threads, keep track and print out the content of the shared
buffer during the execution of the threads when an item is added or consumed. For example, print message
like
"item 2 inserted by a producer. The current content of the buffer is [4, 5, 2]".


Make sure the program works correctly. You need to include <pthread.h> header file and link the pthread
library using "-lpthread".










Extra Credits:
You may gain extra credits for this assignment by doing more work beyond the requirements, for example
implementing the bounded buffer as a monitor using mutex and condition variables or other things interesting
or creative. The extra credit depends on the amount of extra work you do but will be no more than 10
points. Clearly describe the additional work you do in the report if you want to claim extra credits.
1