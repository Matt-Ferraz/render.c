#include "stdio.h"
#include "render.c"
#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#define WIDTH 800
#define HEIGHT 600

// Allocating memory
static uint32_t pixels[HEIGHT * WIDTH];

int main(void) {
    renderc_fill(pixels, WIDTH, HEIGHT, 0xFF00FF00);
    renderc_fill_rect(pixels, WIDTH, HEIGHT, 10, 10, 30, 30, 0xFF0000FF);
    const char *file_path = "out.ppm";
    Errno err = renderc_save_to_ppm(pixels, WIDTH, HEIGHT, file_path);
    if(err) {
        fprintf(stderr, "FAIL: could not complete file\n");
        return 1;
    }
    return 0;
}
