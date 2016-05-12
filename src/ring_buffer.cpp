#include "inc/ring_buffer.h"

uint8_t incriment(uint8_t index){
    if (index == RING_BUFFER_SIZE){
        index = 0;
    } else {
        index += 1;
    }
    return index;
}

int8_t ring_buffer_init (ring_buffer &buffer){
    buffer.head = 0;
    buffer.tail = 0;
}

bool ring_buffer_empty (ring_buffer &buffer){
    return buffer.tail == buffer.head;
}

bool ring_buffer_full (ring_buffer &buffer){
    return buffer.tail == incriment(buffer.head);
}

int8_t ring_buffer_flush (ring_buffer &buffer){
    buffer.head = buffer.tail;
    
    return RING_BUFFER_OK;
}

int8_t ring_buffer_write (ring_buffer &buffer, uint8_t in){
    if (ring_buffer_full(buffer)) 
        buffer.tail = incriment(buffer.tail);
    buffer.data[buffer.head] = in;
    buffer.head = incriment(buffer.head);

    return RING_BUFFER_OK;
}

int8_t ring_buffer_read (ring_buffer &buffer, uint8_t *out){
    bool buffer_empty = ring_buffer_empty(buffer);
    if (!buffer_empty){
        *out = buffer.data[buffer.tail];
        buffer.tail = incriment(buffer. tail);
    }
    return (buffer_empty ? 
        RING_BUFFER_EMPTY : 
        RING_BUFFER_OK);
}



