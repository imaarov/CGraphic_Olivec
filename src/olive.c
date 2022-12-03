#ifndef OLIVE_C_
#define OLIVE_C_

void olivec_fill(uint32_t *pixels, size_t width, size_t height,
                 uint32_t color) {
  for (size_t i = 0; i < width * height; ++i) {
    pixels[i] = color;
  }
}

typedef int Errno;

#define RETURN_DEFER(VALUE)                                                    \
  do {                                                                         \
    result = (VALUE);                                                          \
    goto defer;                                                                \
  } while (0);

Errno olive_save_to_ppm_file(uint32_t *pixels, size_t width, size_t height,
                             const char *file_path) {
  int result = 0;
  FILE *f = NULL;

  f = fopen(file_path, "wb");
  if (f == NULL)
    RETURN_DEFER(errno);

  fprintf(f, "P6\n%zu %zu 255\n", width, height);
  if (ferror(f))
    RETURN_DEFER(errno);

  for (size_t i = 0; i < width * height; ++i) {
    // 0xAABBGGRR
    uint32_t pixel = pixels[i];
    uint8_t bytes[3] = {pixel & 0xFF, (pixel >> 8 * 1) & 0xFF,
                        (pixel >> 8 * 2) & 0xFF};
    fwrite(bytes, sizeof(bytes), 1, f);
    if (ferror(f))
      RETURN_DEFER(errno);
  }

defer:
  if (f)
    fclose(f);
  return result;
}

#endif // OLIVE_C_
