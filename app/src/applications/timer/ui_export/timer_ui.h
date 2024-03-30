#pragma once

#include <lvgl.h>
#include <inttypes.h>

#include "managers/zsw_notification_manager.h"

#define MAX_NBR_TIMERS 6

typedef void(*on_play_pause_pressed)(bool pressed, int id);

void timer_ui_page_create(lv_obj_t *root, on_play_pause_pressed close_cb);
void timer_ui_page_close(void);
void timer_ui_page_add_timer_list_item(int id);
