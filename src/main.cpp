#include "bn_core.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "fixed_32x64_sprite_font.h"

static int counter = 0;

void update_counter(
    bn::sprite_text_generator& text_generator, 
    bn::vector<bn::sprite_ptr, 2>& text_sprites
) {
    bn::string<2> counter_string;
    bn::ostringstream counter_string_stream(counter_string);
    counter_string_stream.append(counter);

    text_sprites.clear();
    text_generator.generate(0, 0, counter_string, text_sprites);
}

int main()
{
    bn::core::init();

    bn::sprite_text_generator counter_text_generator(fixed_32x64_sprite_font);
    counter_text_generator.set_center_alignment();

    bn::vector<bn::sprite_ptr, 2> counter_sprites;

    while(true)
    {
        if(bn::keypad::a_pressed()) {
            if(counter < 20) { counter++; }
        } else if(bn::keypad::b_pressed()) {
            if(counter > 0) { counter--; }
        }
        update_counter(counter_text_generator, counter_sprites);
        bn::core::update();
    }
}
