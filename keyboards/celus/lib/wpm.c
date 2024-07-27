#include "wpm.h"
#include "oled_driver.h"

void render_wpm(void) {
    oled_set_cursor(17,4);
    oled_write_ln("WPM", false);
    oled_set_cursor(17,5);
    oled_write_ln("123", false);
}
