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

#include "bn_sprite_items_summonings.h"

#include "bf_big_sprite_font.h"


#define MAX_TOKEN_COUNT 999

#define FOOD_Y -36
#define TREASURE_Y 0
#define CLUE_Y 36

#define ICON_X -62
#define TOTAL_X -30
#define TAPPED_X 30
#define UNTAPPED_X 0

#define SELECTION_X -92


static int food_count = 0;
static int treasure_count = 0;
static int clue_count = 0;

static int food_tapped_count = 0;
static int treasure_tapped_count = 0;
static int clue_tapped_count = 0;

// 0 = food
// 1 = treasure
// 2 = clue
static int selected_artifact = 0;

int calculate_untapped_count(int tapped, int total) {
    return total - tapped;
}

void update_food_counters(
    bn::sprite_text_generator& text_generator, 
    bn::vector<bn::sprite_ptr, 3>& count_sprites,
    bn::vector<bn::sprite_ptr, 3>& tapped_sprites,
    bn::vector<bn::sprite_ptr, 3>& untapped_sprites
) {
    bn::string<3> food_count_string;
    bn::ostringstream food_count_string_stream(food_count_string);
    food_count_string_stream.append(food_count);

    count_sprites.clear();
    text_generator.generate(TOTAL_X, FOOD_Y, food_count_string, count_sprites);

    bn::string<3> food_tapped_string;
    bn::ostringstream food_tapped_string_stream(food_tapped_string);
    food_tapped_string_stream.append(food_tapped_count);

    tapped_sprites.clear();
    text_generator.generate(TAPPED_X, FOOD_Y, food_tapped_string, tapped_sprites);

    bn::string<3> food_untapped_string;
    bn::ostringstream food_untapped_string_stream(food_untapped_string);
    food_untapped_string_stream.append(calculate_untapped_count(food_tapped_count, food_count));

    untapped_sprites.clear();
    text_generator.generate(UNTAPPED_X, FOOD_Y, food_untapped_string, untapped_sprites);
}

void update_treasure_counters(
    bn::sprite_text_generator& text_generator, 
    bn::vector<bn::sprite_ptr, 3>& count_sprites,
    bn::vector<bn::sprite_ptr, 3>& tapped_sprites,
    bn::vector<bn::sprite_ptr, 3>& untapped_sprites
) {
    bn::string<3> treasure_count_string;
    bn::ostringstream treasure_count_string_stream(treasure_count_string);
    treasure_count_string_stream.append(treasure_count);

    count_sprites.clear();
    text_generator.generate(TOTAL_X, TREASURE_Y, treasure_count_string, count_sprites);

    bn::string<3> treasure_tapped_string;
    bn::ostringstream treasure_tapped_string_stream(treasure_tapped_string);
    treasure_tapped_string_stream.append(treasure_tapped_count);

    tapped_sprites.clear();
    text_generator.generate(TAPPED_X, TREASURE_Y, treasure_tapped_string, tapped_sprites);

    bn::string<3> treasure_untapped_string;
    bn::ostringstream treasure_untapped_string_stream(treasure_untapped_string);
    treasure_untapped_string_stream.append(calculate_untapped_count(treasure_tapped_count, treasure_count));

    untapped_sprites.clear();
    text_generator.generate(UNTAPPED_X, TREASURE_Y, treasure_untapped_string, untapped_sprites);
}

void update_clue_counters(
    bn::sprite_text_generator& text_generator, 
    bn::vector<bn::sprite_ptr, 3>& count_sprites,
    bn::vector<bn::sprite_ptr, 3>& tapped_sprites,
    bn::vector<bn::sprite_ptr, 3>& untapped_sprites
) {
    bn::string<3> clue_count_string;
    bn::ostringstream clue_count_string_stream(clue_count_string);
    clue_count_string_stream.append(clue_count);

    count_sprites.clear();
    text_generator.generate(TOTAL_X, CLUE_Y, clue_count_string, count_sprites);

    bn::string<3> clue_tapped_string;
    bn::ostringstream clue_tapped_string_stream(clue_tapped_string);
    clue_tapped_string_stream.append(clue_tapped_count);

    tapped_sprites.clear();
    text_generator.generate(TAPPED_X, CLUE_Y, clue_tapped_string, tapped_sprites);

    bn::string<3> clue_untapped_string;
    bn::ostringstream clue_untapped_string_stream(clue_untapped_string);
    clue_untapped_string_stream.append(calculate_untapped_count(clue_tapped_count, clue_count));

    untapped_sprites.clear();
    text_generator.generate(UNTAPPED_X, CLUE_Y, clue_untapped_string, untapped_sprites);
}

void update_selection(bn::sprite_ptr selection_sprite) {
    switch(selected_artifact) {
        case 0:
            selection_sprite.set_position(SELECTION_X, FOOD_Y);
            break;
        case 1:
            selection_sprite.set_position(SELECTION_X, TREASURE_Y);
            break;
        case 2:
            selection_sprite.set_position(SELECTION_X, CLUE_Y);
            break;
        default:
            selection_sprite.set_position(SELECTION_X, FOOD_Y);
            break;
    }
}

void increment_selected_artifact() {
    switch(selected_artifact) {
        case 0:
            if(food_count < MAX_TOKEN_COUNT) food_count++;
            break;
        case 1:
            if(treasure_count < MAX_TOKEN_COUNT) treasure_count++;
            break;
        case 2:
            if(clue_count < MAX_TOKEN_COUNT) clue_count++;
            break;
        default:
            break;
    }
}

void decrement_selected_artifact() {
    switch(selected_artifact) {
        case 0:
            if(food_count > 0) food_count--;
            break;
        case 1:
            if(treasure_count > 0) treasure_count--;
            break;
        case 2:
            if(clue_count > 0) clue_count--;
            break;
        default:
            break;
    }
}

int main()
{
    bn::core::init();

    bn::sprite_text_generator counter_text_generator(bf::big_sprite_font);
    counter_text_generator.set_center_alignment();

    bn::vector<bn::sprite_ptr, 3> food_total_sprites;
    bn::vector<bn::sprite_ptr, 3> treasure_total_sprites;
    bn::vector<bn::sprite_ptr, 3> clue_total_sprites;

    bn::vector<bn::sprite_ptr, 3> food_tapped_sprites;
    bn::vector<bn::sprite_ptr, 3> treasure_tapped_sprites;
    bn::vector<bn::sprite_ptr, 3> clue_tapped_sprites;

    bn::vector<bn::sprite_ptr, 3> food_untapped_sprites;
    bn::vector<bn::sprite_ptr, 3> treasure_untapped_sprites;
    bn::vector<bn::sprite_ptr, 3> clue_untapped_sprites;

    bn::regular_bg_ptr counter_bg = bn::regular_bg_items::counter_bg.create_bg(0, 0);
    counter_bg.set_visible(true);

    bn::sprite_ptr food_sprite = bn::sprite_items::apple.create_sprite(ICON_X, FOOD_Y);
    food_sprite.set_scale(0.75);
    bn::sprite_ptr treasure_sprite = bn::sprite_items::gold_pile.create_sprite(ICON_X, TREASURE_Y);
    treasure_sprite.set_scale(0.75);
    bn::sprite_ptr clue_sprite = bn::sprite_items::parchment_new.create_sprite(ICON_X, CLUE_Y);
    clue_sprite.set_scale(0.75);

    bn::sprite_ptr selection_sprite = bn::sprite_items::summonings.create_sprite(SELECTION_X, -36);

    while(true)
    {
        // Handle selecting token type
        if(bn::keypad::up_pressed()) {
            if(selected_artifact == 0) {
                selected_artifact = 2;
            } else {
                selected_artifact--;
            }
        } else if(bn::keypad::down_pressed()) {
            selected_artifact = (selected_artifact + 1) % 3;
        }

        // Handle incrementing token type count by 1
        if(bn::keypad::right_pressed()) {
            increment_selected_artifact();
        } else if(bn::keypad::left_pressed()) {
            decrement_selected_artifact();
        }

        update_selection(selection_sprite);


        update_food_counters(counter_text_generator, food_total_sprites, food_tapped_sprites, food_untapped_sprites);
        update_treasure_counters(counter_text_generator, treasure_total_sprites, treasure_tapped_sprites, treasure_untapped_sprites);
        update_clue_counters(counter_text_generator, clue_total_sprites, clue_tapped_sprites, clue_untapped_sprites);
        bn::core::update();
    }
}
