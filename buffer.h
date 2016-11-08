#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE 5
typedef int buffer_item;


#include <stdio.h>


class buffer
    {
        private:
            int in;
            int out;
            int count;
            buffer_item *buf;
        public:
            buffer();    
        public:
            int insert_item(buffer_item item);
            int remove_item(buffer_item *item);
            void displayBuffer();
    };



#endif