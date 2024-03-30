#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/zbus/zbus.h>
#include <zephyr/logging/log.h>

#include "ui_export/timer_ui.h"
#include "managers/zsw_app_manager.h"

LOG_MODULE_REGISTER(timer_app, LOG_LEVEL_DBG);

static void timer_app_start(lv_obj_t *root, lv_group_t *group);
static void timer_app_stop(void);
static void on_timer_play_pause(bool active, int id);

LV_IMG_DECLARE(templates);

static application_t app = {
    .name = "Timer",
    .hidden = false,
    .icon = &templates,
    .start_func = timer_app_start,
    .stop_func = timer_app_stop
};

typedef struct {
    bool is_running;
    uint32_t time;
    uint32_t time_left;
} app_timer_t;

static app_timer_t timers[] = {
    {
        .is_running = false,
        .time = 60 * 5,
        .time_left = 60 * 5,
    },
    {
        .is_running = false,
        .time = 60 * 10,
        .time_left = 60 * 10,
    },
    {
        .is_running = false,
        .time = 60 * 20,
        .time_left = 60 * 20,
    },
};

static void timer_app_start(lv_obj_t *root, lv_group_t *group)
{
    timer_ui_page_create(root, on_timer_play_pause);

    for (int i = 0; i < ARRAY_SIZE(timers); i++) {
        timer_ui_page_add_timer_list_item(i);
    }
}

static void timer_app_stop(void)
{
    timer_ui_page_close();
}

static int timer_app_add(void)
{
    zsw_app_manager_add_application(&app);

    return 0;
}

static void on_timer_play_pause(bool active, int timer_id)
{
    printk("Pressed timer id: %d, active: %d, time: %d\n", timer_id, active, timers[timer_id].time);

}

SYS_INIT(timer_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);