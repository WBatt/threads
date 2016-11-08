#include "buffer.h"

buffer::buffer(){
    buf = new buffer_item[BUFFER_SIZE];
    in = 0;
    out = 0;
    count = 0;
}


int buffer::insert_item(buffer_item item) 
    {
        while(count == BUFFER_SIZE){}
        if(count != BUFFER_SIZE)
            {
                buf[in] = item;
                in = (in + 1) % BUFFER_SIZE;
                count++;
                return 0;
            }
        return -1;  //error condition
    }


int buffer::remove_item(buffer_item *item) 
    {
        while(count == 0){}
        if(count!=0)
            {
                *item = buf[out];
                buf[out] = 0;
                out = (out + 1) % BUFFER_SIZE;
                count--;
                return 0;
            }
        return -1;  //error condition
    }

void buffer::displayBuffer()
    {
                printf("Buffer: [%d,%d,%d,%d,%d]\n",buf[0],buf[1],buf[2],buf[3],buf[4]);
        
    }

