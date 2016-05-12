#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

#define RING_BUFFER_SIZE 256

#define RING_BUFFER_EMPTY 0
#define RING_BUFFER_NOT_EMPTY 1
#define RING_BUFFER_FULL 2
#define RING_BUFFER_OK 3

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    uint8_t head, tail;
} ring_buffer;

int ring_buffer_init (ring_buffer &buffer);
int ring_buffer_is_empty (ring_buffer &buffer);
int ring_buffer_flush (ring_buffer &buffer);
int ring_buffer_write (ring_buffer &buffer, uint8_t in);
int ring_buffer_read (ring_buffer &buffer, uint8_t *out);

#endif
