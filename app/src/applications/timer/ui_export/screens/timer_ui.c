#include "../timer_ui.h"

static lv_obj_t *ui_Home = NULL;
static lv_obj_t *ui_Time;
static lv_obj_t *ui_ContentContainer;
static lv_obj_t *ui_TimerPanel;
static lv_obj_t *ui_TimerBody;
static lv_obj_t *ui_StartPauseButton;
static lv_obj_t *ui_ResetButton;

typedef struct {
    lv_obj_t *time_label;
    bool active;
} timer_list_t;

static timer_list_t timer_list[MAX_NBR_TIMERS];
static on_play_pause_pressed play_pause_callback;

void timer_ui_page_create(lv_obj_t *root, on_play_pause_pressed on_play_pause_cb)
{
    assert(ui_Home == NULL);

    play_pause_callback = on_play_pause_cb;

    ui_Home = lv_obj_create(root);
    lv_obj_set_style_border_width(ui_Home, 0, LV_PART_MAIN);
    lv_obj_set_size(ui_Home, LV_PCT(100), LV_PCT(100));
    lv_obj_clear_flag( ui_Home, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_style_bg_color(ui_Home, lv_color_hex(0x333131), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_Home, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_Time = lv_label_create(ui_Home);
    lv_obj_set_width( ui_Time, LV_SIZE_CONTENT);
    lv_obj_set_height( ui_Time, LV_SIZE_CONTENT);
    lv_obj_set_align( ui_Time, LV_ALIGN_TOP_MID );
    lv_label_set_text(ui_Time,"23:49");
    lv_obj_set_style_text_color(ui_Time, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_text_opa(ui_Time, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_ContentContainer = lv_obj_create(ui_Home);
    lv_obj_remove_style_all(ui_ContentContainer);
    lv_obj_set_width( ui_ContentContainer, 240);
    lv_obj_set_height( ui_ContentContainer, 200);
    //lv_obj_clear_flag( ui_ContentContainer, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_flex_flow(ui_ContentContainer, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(ui_ContentContainer, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(ui_ContentContainer, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(ui_ContentContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_x( ui_ContentContainer, 120-12-100); // WatchWidth/2-padding-TimerPanelWidth/2
    lv_obj_set_y( ui_ContentContainer, 12*2);
    lv_obj_set_style_pad_row(ui_ContentContainer, 12, LV_PART_MAIN| LV_STATE_DEFAULT);
}

void timer_ui_page_close(void)
{
    lv_obj_del(ui_Home);
}

static void start_pause_pressed(lv_event_t *event)
{
    int id;

    id = (int)lv_event_get_user_data(event);
    timer_list[id].active = !timer_list[id].active;

    play_pause_callback(timer_list[id].active, id);
}

void timer_ui_page_add_timer_list_item(int id)
{
    ui_TimerPanel = lv_obj_create(ui_ContentContainer);
    lv_obj_set_width( ui_TimerPanel, 200);
    lv_obj_set_height( ui_TimerPanel, 50);
    lv_obj_clear_flag( ui_TimerPanel, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_style_bg_color(ui_TimerPanel, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_TimerPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_TimerPanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TimerPanel, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TimerPanel, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TimerPanel, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TimerPanel, 10, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_TimerBody = lv_label_create(ui_TimerPanel);
    lv_obj_set_width( ui_TimerBody, 64);
    lv_obj_set_height( ui_TimerBody, LV_SIZE_CONTENT);
    lv_obj_set_align( ui_TimerBody, LV_ALIGN_LEFT_MID );
    lv_label_set_long_mode(ui_TimerBody,LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_TimerBody,"22:23");
    lv_obj_set_style_text_color(ui_TimerBody, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_text_opa(ui_TimerBody, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimerBody, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_StartPauseButton = lv_btn_create(ui_TimerPanel);
    lv_obj_add_event_cb(ui_StartPauseButton, start_pause_pressed, LV_EVENT_CLICKED, (void*)id);
    lv_obj_set_width( ui_StartPauseButton, 30);
    lv_obj_set_height( ui_StartPauseButton, 30);
    lv_obj_set_x( ui_StartPauseButton, 75 );
    lv_obj_set_y( ui_StartPauseButton, 0 );
    lv_obj_set_align( ui_StartPauseButton, LV_ALIGN_CENTER );
    lv_obj_add_flag( ui_StartPauseButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );
    lv_obj_clear_flag( ui_StartPauseButton, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_style_radius(ui_StartPauseButton, 80, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_StartPauseButton, lv_color_hex(0xFF8427), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_StartPauseButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_StartPauseButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_border_opa(ui_StartPauseButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_StartPauseButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_StartPauseButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_ResetButton = lv_btn_create(ui_TimerPanel);
    lv_obj_set_width( ui_ResetButton, 30);
    lv_obj_set_height( ui_ResetButton, 30);
    lv_obj_set_x( ui_ResetButton, 35 );
    lv_obj_set_y( ui_ResetButton, 0 );
    lv_obj_set_align( ui_ResetButton, LV_ALIGN_CENTER );
    lv_obj_add_flag( ui_ResetButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );
    lv_obj_clear_flag( ui_ResetButton, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_style_radius(ui_ResetButton, 80, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ResetButton, lv_color_hex(0xFF8427), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_ResetButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ResetButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_border_opa(ui_ResetButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ResetButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ResetButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    timer_list[id].time_label = ui_TimerBody;
    timer_list[id].active = false;
}