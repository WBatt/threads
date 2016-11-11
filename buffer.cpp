#include "buffer.h"

buffer::buffer(){
    buf = new buffer_item[BUFFER_SIZE];
    in = 0;
    out = 0;
    count = 0;
}

int buffer::insert_item(buffer_item item) 
    {
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
        int start = out;
        int end = in;
        printf("Buffer: [");
        if(count != 0)
            {
                do
                    {
                        printf("%d",buf[start]);
                        if(((start + 1) % 5) != end)
                            {
                                printf(",");
                            }
                        start = (start + 1) % 5;
                    }while(start != end);
            }
        printf("]\n");
    }

