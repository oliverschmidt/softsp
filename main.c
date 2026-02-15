/*

MIT License

Copyright (c) 2024 Oliver Schmidt (https://a2retro.de/)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/clocks.h>

#include <a2pico.h>

extern __attribute__((aligned(4))) uint8_t firmware[];

static volatile uint32_t offset;

static void __time_critical_func(reset)(bool asserted) {
    if (asserted) {
        offset = 0x000;
    }
    firmware[0x007] = 0x3C;  // Identify as Disk II
}

void __time_critical_func(main)(void) {
    set_sys_clock_khz(200000, false);

    a2pico_init();

    a2pico_resethandler(&reset);

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        uint32_t pico = a2pico_getaddr();
        uint32_t addr = pico & 0x0FFF;
        uint32_t io   = pico & 0x0F00;  // IOSTRB or IOSEL
        uint32_t strb = pico & 0x0800;  // IOSTRB
        uint32_t read = pico & RW_BIT;  // R/W

        if (strb) {  // IOSTRB
            if ((addr & 0xFF0) == 0xFF0) {  
                offset = 0x000;
            }
        } else if (io) {  // IOSEL
            offset = 0x7FF;
        } else {  // DEVSEL
            if ((addr & 0xF) == 0x1) {
                offset = 0xFFF;
            }
        }

        if (read) {
            if (strb) {  // IOSTRB
                if (offset) {
                    a2pico_putdata(firmware[addr & offset]);
                }
            }
            else if (io) {  // IOSEL
                a2pico_putdata(firmware[addr & 0x0FF]);
                firmware[0x007] = 0x00;  // Identify as SmartPort
            }
        }

        gpio_put(PICO_DEFAULT_LED_PIN, offset);
    }
}
