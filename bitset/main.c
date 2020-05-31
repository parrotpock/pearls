//
//  main.c
//  programmingpearls

#include <fcntl.h>
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t  size;
    int8_t *bitset;
} Bitset;

Bitset bitset_init(size_t size) {
    // Initialise the struct and malloc the memory
    // The caller needs to check if the bitset is initialised or set to NULL, i.e. that the malloc didnt fail.
    Bitset bs;
    // We can fit 8 elements per byte, so the size of the bitset is (size/8) + 1 if there's a remainder.
    size_t actualSize = size / 8;
    if(size % 8 != 0) {
        actualSize += 1;
    }
    bs.bitset = (int8_t*) calloc(actualSize, 1);
    bs.size   = actualSize;
    return bs;
}

void bitset_destroy(Bitset bs) {
    free(bs.bitset);
}

void bitset_setval(Bitset bs, size_t elem, int8_t val) {
    assert(elem < (bs.size * 8));
    assert(val == 0 || val == 1);
    // First find the index into the bitarray
    size_t idx = elem / 8;
    // Next use the remainder to work out which bit to set
    size_t bitidx = elem % 8;
    if(val == 0) {
        bs.bitset[idx] &= (1 << bitidx) ^ (0xFF);
    } else if (val == 1) {
        bs.bitset[idx] |= (1 << bitidx);
    }
}

int8_t bitset_getval(Bitset bs, size_t elem) {
    assert(elem < (bs.size * 8));
    size_t idx = elem / 8;
    size_t bitidx = elem % 8;
    int8_t val = bs.bitset[idx];
    val = (val >> bitidx) & 1;
    return val;
}

void bitset_test() {
    int size = 1;
    Bitset bs = bitset_init(size);
    printf("Bitset.size: %zu\n", bs.size);
    printf("Bitset.val: %d\n", bs.bitset[0]);
    bitset_setval(bs, 5, 1);
    printf("Bitset.val: %d\n", bs.bitset[0]);
    bitset_setval(bs, 1, 1);
    printf("Bitset.val: %d\n", bs.bitset[0]);
    for(int i = 0; i < 8; i++) {
        if(bitset_getval(bs, i)) {
            printf("Set: %d\n", i);
        }
    }
    
    printf("%s\n", "Unsetting number 5");
    bitset_setval(bs, 5, 0);
    for(int i = 0; i < 8; i++) {
        if(bitset_getval(bs, i)) {
            printf("Set: %d\n", i);
        }
    }
    
    printf("%s\n", "Unsetting number 1");
    bitset_setval(bs, 1, 0);
    for(int i = 0; i < 8; i++) {
        if(bitset_getval(bs, i)) {
            printf("Set: %d\n", i);
        }
    }
}

int main(int argc, char **argv) {
    int size = 10000000;
#ifdef TESTING_ONLY 
    bitset_test();
    return 0;
#endif
    
    Bitset bs = bitset_init(size);
    FILE *fd = fopen("/Users/rob/data.txt", "r");
    if(fd < 0) {
        printf("%s\n", "Error opening the file");
        return -1;
    }
    int32_t elem = 0;
    while(!feof(fd)) {
        fscanf(fd, "%d\n", &elem);
        bitset_setval(bs, elem, 1);
    }
    
    for(int i = 0; i < size; i++) {
        if(bitset_getval(bs, i)) {
            printf("%d\n", i);
        }
    }
    return 0;
}
