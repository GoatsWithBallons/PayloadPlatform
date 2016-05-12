#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

#define RING_BUFFER_SIZE 256

#define RING_BUFFER_OK 1
#define RING_BUFFER_EMPTY -1

typedef struct {
    uint8_t data[RING_BUFFER_SIZE];
    uint8_t head, tail;
} ring_buffer;

int8_t ring_buffer_init (ring_buffer &buffer);
bool ring_buffer__empty (ring_buffer &buffer);
bool ring_buffer_full (ring_buffer &buffer);
int8_t ring_buffer_flush (ring_buffer &buffer);
int8_t ring_buffer_write (ring_buffer &buffer, uint8_t in);
int8_t ring_buffer_read (ring_buffer &buffer, uint8_t *out);

#endif
