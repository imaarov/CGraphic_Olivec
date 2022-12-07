#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "olive.c"

#define WIDTH 800
#define HEIGHT 600
#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH / COLS)
#define CELL_HEIGHT (HEIGHT / ROWS)
#define BACKGROUNF_COLOR 0xFF202020

static uint32_t pixels[HEIGHT * WIDTH];


bool checker_example()
{
  olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUNF_COLOR);
  
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      uint32_t color = BACKGROUNF_COLOR;
      if ((x + y) % 2 == 0) {
        color = 0xFF2020FF;
      }
      olive_fill_rect(pixels, WIDTH, HEIGHT, x * CELL_WIDTH, y * CELL_HEIGHT,
                      CELL_WIDTH, CELL_HEIGHT, color);
    }
  }
  // size_t rw = 50 * 4;
  // size_t rh = 30 * 4;
  const char *file_path = "checker_example.ppm";
  Errno err = olive_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
  if (err) {
    fprintf(stderr, "ERROR could not save the file %s: %s\n", file_path,
            strerror(errno));
    return false;
  }

  return true;
}


int main(void) {


  return 0;
}
