#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#define PCTR_FIXED (1 << 30)

int
main(void)
{
    uint32_t lo, hi, pctr_arg;

    pctr_arg = PCTR_FIXED | 0x1; // read first fixed-function counter

    /*
     * This will crash if the PCE flag in CR4 is not set.
     */
    __asm volatile (
        "mov %0, %%ecx\t\n"
        "rdpmc\t\n"
        // ---
        : "=a" (lo), "=d" (hi)  // outputs
        : "c" (pctr_arg)        // inputs
    );

    printf("ctr val = %" PRIu64 "\n", ((uint64_t) hi << 32) | lo);
}
