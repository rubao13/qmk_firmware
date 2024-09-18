#include "wpm.h"
#include "oled_driver.h"
#include "quantum.h"

void render_wpm(void) {
    oled_set_cursor(2,1);
    oled_write_ln("WPM", false);
    oled_set_cursor(6,1);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
}
