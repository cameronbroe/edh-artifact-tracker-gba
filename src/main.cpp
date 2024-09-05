#include "bn_core.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_actions.h"
#include "bn_regular_bg_builder.h"
#include "bn_regular_bg_attributes.h"

#include "bn_regular_bg_items_counter_bg.h"

#include "bn_sprite_items_apple.h"
#include "bn_sprite_items_gold_pile.h"
#include "bn_sprite_items_parchment_new.h"

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
    text_generator.generate(40, 0, counter_string, text_sprites);
}

int main()
{
    bn::core::init();

    bn::sprite_text_generator counter_text_generator(fixed_32x64_sprite_font);
    // counter_text_generator.set_center_alignment();

    bn::vector<bn::sprite_ptr, 2> counter_sprites;

    bn::regular_bg_ptr counter_bg = bn::regular_bg_items::counter_bg.create_bg(0, 0);
    counter_bg.set_visible(true);

    bn::sprite_ptr food_sprite = bn::sprite_items::apple.create_sprite(-92, -56);
    bn::sprite_ptr treasure_sprite = bn::sprite_items::gold_pile.create_sprite(-92, 0);
    bn::sprite_ptr clue_sprite = bn::sprite_items::parchment_new.create_sprite(-92, 56);

    while(true)
    {
        if(bn::keypad::a_pressed()) {
            if(counter < 20) { counter++; }
        } else if(bn::keypad::b_pressed()) {
            if(counter > 0) { counter--; }
        } else if(bn::keypad::select_pressed()) {
            counter = 0;
        }
        update_counter(counter_text_generator, counter_sprites);
        bn::core::update();
    }
}
