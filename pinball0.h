#pragma once

#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cmath>
// #include <furi_hal_resources.h>
// #include <furi_hal_gpio.h>
#include <furi.h>
#include <dolphin/dolphin.h>
#include <storage/storage.h>
#include <notification/notification.h>
#include <notification/notification_messages.h>

#include "vec2.h"
#include "objects.h"

// #define DRAW_NORMALS

#define TAG     "Pinball0"
#define VERSION "v0.3"

// Vertical orientation
#define LCD_WIDTH  64
#define LCD_HEIGHT 128

typedef enum {
    EventTypeTick,
    EventTypeKey
} EventType;

typedef struct {
    EventType type;
    InputEvent input;
} PinballEvent;

typedef enum GameMode {
    GM_TableSelect,
    GM_Playing,
    GM_GameOver,
    GM_Error,
    GM_Settings,
    GM_About
} GameMode;

class TableList {
public:
    TableList() = default;
    ~TableList();

    typedef struct {
        FuriString* name;
        FuriString* filename;
    } TableMenuItem;

    std::vector<TableMenuItem> menu_items;
    int display_size; // how many can fit on screen
    int selected;
};

class Table;

typedef struct PinballApp {
    ~PinballApp();

    FuriMutex* mutex;

    TableList table_list;

    GameMode game_mode;
    Table* table; // data for the current table
    uint32_t tick;

    bool gameStarted;
    bool keys[4]; // which key was pressed?
    bool processing; // controls game loop and game objects

    // user settings
    struct {
        bool sound_enabled;
        bool vibrate_enabled;
        bool led_enabled;
        bool debug_mode;
    } settings;
    int selected_setting;
    int max_settings;

    // system objects
    Storage* storage;
    NotificationApp* notify; // allows us to blink/buzz during game
    char text[256]; // general temp buffer

} PinballApp;
