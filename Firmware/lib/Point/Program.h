#include <inttypes.h>

struct Instruction {
    uint8_t x;
    uint8_t y;
    uint8_t p;
};

struct Program {
    Instruction ins[1024*10];
};
