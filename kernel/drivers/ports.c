#include "ports.h"
/**
 * Read a byte from the specified port
 */
uint32_t port_byte_in (uint32_t port) {
    uint32_t result;
    /* Inline assembler syntax
     * !! Notice how the source and destination registers are switched from NASM !!
     *
     * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
     * '"d" (port)': map the C variable '(port)' into e'd'x register
     *
     * Inputs and outputs are separated by colons
     */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (uint32_t port, uint32_t data) {
    /* Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint32_t port_word_in (uint32_t port) {
    uint32_t result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (uint32_t port, uint32_t data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

uint32_t port_dword_in (uint32_t port) {
    uint32_t result;
    __asm__("inl %%dx, %%eax" : "=a" (result) : "d" (port));
    return result;
}

void port_dword_out (uint32_t port, uint32_t data) {
    __asm__("outl %%eax, %%dx" : : "a" (data), "d" (port));
}

void insl(uint32_t port, uint32_t addr, uint32_t cnt) {
  asm volatile("cld; rep insl" :
               "=D" (addr), "=c" (cnt) :
               "d" (port), "0" (addr), "1" (cnt) :
               "memory", "cc");
}
