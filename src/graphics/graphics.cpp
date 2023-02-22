#include "graphics.h"

#include "../devices/hardware.h"

void printString(const char *str, int x, int y) {
  uint16_t i = 0;
  while (str[i] != '\0') {
    CharInfo charInfo = pixelfnt_chars[str[i] - pixelfnt_baseIndex];
    for (int fntX = 0; fntX < charInfo.width; fntX++) {
      for (int fntY = 0; fntY < charInfo.height; fntY++) {
        st7789_set_cursor(y + (pixelfnt_lineHeight - fntY - charInfo.yoffset),
                          x + fntX + charInfo.xoffset);
        if (pixelfnt_depth == 1) {
          st7789_put((pixelfnt_map)[(fntX + charInfo.x) +
                                    (fntY + charInfo.y) * pixelfnt_scaleW]
                         ? 0xffff
                         : 0x0000);
        } else if (pixelfnt_depth == 2) {
          st7789_put((
              (uint16_t *)pixelfnt_map)[(fntX + charInfo.x) +
                                        (fntY + charInfo.y) * pixelfnt_scaleW]);
        }
      }
    }
    i += 1;
    x += charInfo.xadvance;
  }
}
