#pragma once

typedef enum {
    UI_DASHBOARD,
    UI_MENU
} ui_mode_t;

extern ui_mode_t ui_mode;

void system_init();

void ui_notify_activity(void);
uint32_t getLast_activity(void);