#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"

#ifndef RENDER_C_
#define RENDER_C_
#define return_to_defer(val) do { result = (val); goto defer; } while (0)
typedef int Errno;

void renderc_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)
{
    for(size_t i = 0; i < width * height; i++) {
        pixels[i] = color;
    }
}

Errno renderc_save_to_ppm(uint32_t *pixels, size_t width, size_t height, const char *file_path)
{
    int result = 0;
    FILE *f = NULL;

    {
        f = fopen(file_path, "wb");
        if(f == NULL) return_to_defer(errno);
        fprintf(f, "P6\n%zu %zu 255\n", width, height);
        if(ferror(f)) return_to_defer(errno);

        for(size_t i = 0; i < width * height; i++) {
            // 0xAABBGGRR
            uint32_t pixel = pixels[i];
            uint8_t bytes[3] = {
                (pixel >> (8 * 2)) & 0xFF, // Red
                (pixel >> (8 * 1)) & 0xFF, // Green
                (pixel >> (8 * 0)) & 0xFF  // Blue
            };
            fwrite(bytes, sizeof(bytes), 1, f);
            if(ferror(f)) return_to_defer(errno);
        }
    }

defer:
    if(f) fclose(f);
    return result;
}

#endif // RENDER_C_
