#include <pebble.h>

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 2


static Window *s_main_window;
static SimpleMenuLayer *s_simple_menu_layer;

static SimpleMenuSection sections[NUM_MENU_SECTIONS];
static SimpleMenuItem menu_items[NUM_MENU_ITEMS];

//typedef void(* SimpleMenuLayerSelectCallback)(int index, void *context)

void menu_item_callback(int index, void *context) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Menu item %d clicked", index);
}

static void menu_callback() {
    // uhh
}

static void setup_menu_items() {
    APP_LOG(APP_LOG_LEVEL_DEBUG , "start setup_menu_items");
    // Create two menu items
    menu_items[0].title = "Menu Item 1";
    menu_items[0].callback = menu_item_callback;
    menu_items[1].title = "Menu Item 2";
    menu_items[1].callback = menu_item_callback;
    APP_LOG(APP_LOG_LEVEL_DEBUG , "end setup_menu_items");
}

static void main_window_load(Window *window) {
    APP_LOG(APP_LOG_LEVEL_DEBUG , "start main_window_load");
    setup_menu_items();
    int i;
    for (i = 0; i < NUM_MENU_SECTIONS; i++) {
        sections[i].items = menu_items;
        sections[i].num_items = NUM_MENU_ITEMS;
        sections[i].title = "Menu 1";
    }
    APP_LOG(APP_LOG_LEVEL_DEBUG , "Create the menu layer");
    s_simple_menu_layer = simple_menu_layer_create(GRect(0, 55, 144, 50),
                            s_main_window,
                            sections,
                            NUM_MENU_SECTIONS,
                            menu_callback);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Add child");
    layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(s_simple_menu_layer));
    APP_LOG(APP_LOG_LEVEL_DEBUG , "end main_window_load");
}

static void main_window_unload(Window *window) {
    simple_menu_layer_destroy(s_simple_menu_layer);
}


static void init() {
    // Create main Window element and assign to pointer
    s_main_window = window_create();

    // Set handlers to manage the elements inside the Window
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload
    });

    // Show the Window on the watch, with animated=true
    window_stack_push(s_main_window, true);
}

static void deinit() {
    window_destroy(s_main_window);
}
    
int main(void) {
    init();
    app_event_loop();
    deinit();
}