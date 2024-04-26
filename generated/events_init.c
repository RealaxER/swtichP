/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"


static void screen_br_close_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_brightless_cont, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_main, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_img_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_auto_lock_cont, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_main, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_img_4_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_timezone_cont, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_main, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_img_7_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.screen_main, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_language_cont, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_language_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_main, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_language_cont, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_timezone_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_main, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_timezone_cont, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_auto_lock_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_main, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_auto_lock_cont, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_brightness_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_main, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_brightless_cont, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
void events_init_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_br_close, screen_br_close_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_img_1, screen_img_1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_img_4, screen_img_4_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_img_7, screen_img_7_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_language, screen_language_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_timezone, screen_timezone_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_auto_lock, screen_auto_lock_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_brightness, screen_brightness_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
