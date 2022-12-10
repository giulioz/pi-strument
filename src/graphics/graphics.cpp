#include "graphics.h"

#include "../devices/hardware.h"

void printString(const char *str, int x, int y) {
  uint16_t i = 0;
  while (str[i] != '\0') {
    CharInfo charInfo = sansserif_chars[str[i] - sansserif_baseIndex];
    for (int fntX = 0; fntX < charInfo.width; fntX++) {
      for (int fntY = 0; fntY < charInfo.height; fntY++) {
        st7789_set_cursor(y + (sansserif_lineHeight - fntY - charInfo.yoffset),
                          x + fntX + charInfo.xoffset);
        st7789_put(((uint16_t *)sansserif_map)[(fntX + charInfo.x) +
                                               (fntY + charInfo.y) * 256]);
      }
    }
    i += 1;
    x += charInfo.xadvance;
  }
}
