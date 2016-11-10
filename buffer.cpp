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
                printf("Buffer: [");
                for(int i = 0; i < 5; i++)
                    {
                        if(buf[i] != 0)
                            {
                                printf("%d",buf[i]);
                                if((i+1) != 6 && buf[i+1] != 0)
                                    {
                                        printf(",");
                                    }
                            }
                        
                    }
                printf("]\n");
    }

