/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


void setup_scr_screen(lv_ui *ui)
{
	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen, 1280, 720);

	//Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_brightless_cont
	ui->screen_brightless_cont = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_brightless_cont, 0, 0);
	lv_obj_set_size(ui->screen_brightless_cont, 600, 600);
	lv_obj_set_scrollbar_mode(ui->screen_brightless_cont, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_brightless_cont, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_brightless_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_brightless_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_brightless_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_brightless_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_brightless_cont, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_brightless_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_brightless_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_brightless_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_brightless_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_brightless_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_br_save
	ui->screen_br_save = lv_img_create(ui->screen_brightless_cont);
	lv_obj_add_flag(ui->screen_br_save, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_br_save, &_save_alpha_141x72);
	lv_img_set_pivot(ui->screen_br_save, 50,50);
	lv_img_set_angle(ui->screen_br_save, 0);
	lv_obj_set_pos(ui->screen_br_save, 459, 0);
	lv_obj_set_size(ui->screen_br_save, 141, 72);

	//Write style for screen_br_save, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_br_save, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_br_name
	ui->screen_br_name = lv_label_create(ui->screen_brightless_cont);
	lv_label_set_text(ui->screen_br_name, "Brighless");
	lv_label_set_long_mode(ui->screen_br_name, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_br_name, 53, 8);
	lv_obj_set_size(ui->screen_br_name, 285, 42);

	//Write style for screen_br_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_br_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_br_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_br_name, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_br_name, &lv_font_arial_40, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_br_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_br_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_br_name, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_br_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_br_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_br_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_br_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_br_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_br_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_br_back
	ui->screen_br_back = lv_img_create(ui->screen_brightless_cont);
	lv_obj_add_flag(ui->screen_br_back, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_br_back, &_button_scene_alpha_600x200);
	lv_img_set_pivot(ui->screen_br_back, 50,50);
	lv_img_set_angle(ui->screen_br_back, 0);
	lv_obj_set_pos(ui->screen_br_back, 0, 105);
	lv_obj_set_size(ui->screen_br_back, 600, 200);

	//Write style for screen_br_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_br_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_br_slider
	ui->screen_br_slider = lv_slider_create(ui->screen_brightless_cont);
	lv_slider_set_range(ui->screen_br_slider, 0, 100);
	lv_slider_set_mode(ui->screen_br_slider, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_br_slider, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_br_slider, 20, 200);
	lv_obj_set_size(ui->screen_br_slider, 556, 64);

	//Write style for screen_br_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_br_slider, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_br_slider, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_br_slider, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_br_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_br_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_br_slider, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_br_slider, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_br_slider, lv_color_hex(0x94a0ab), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_br_slider, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_br_slider, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_br_slider, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_br_slider, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_br_value
	ui->screen_br_value = lv_label_create(ui->screen_brightless_cont);
	lv_label_set_text(ui->screen_br_value, "50%");
	lv_label_set_long_mode(ui->screen_br_value, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_br_value, 33, 134);
	lv_obj_set_size(ui->screen_br_value, 123, 42);

	//Write style for screen_br_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_br_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_br_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_br_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_br_value, &lv_font_arial_40, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_br_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_br_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_br_value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_br_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_br_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_br_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_br_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_br_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_br_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_br_close
	ui->screen_br_close = lv_img_create(ui->screen_brightless_cont);
	lv_obj_add_flag(ui->screen_br_close, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_br_close, &_icon_close_alpha_56x56);
	lv_img_set_pivot(ui->screen_br_close, 50,50);
	lv_img_set_angle(ui->screen_br_close, 0);
	lv_obj_set_pos(ui->screen_br_close, 0, 0);
	lv_obj_set_size(ui->screen_br_close, 56, 56);

	//Write style for screen_br_close, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_br_close, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_auto_lock_cont
	ui->screen_auto_lock_cont = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_auto_lock_cont, 0, 0);
	lv_obj_set_size(ui->screen_auto_lock_cont, 600, 600);
	lv_obj_set_scrollbar_mode(ui->screen_auto_lock_cont, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_auto_lock_cont, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_auto_lock_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_auto_lock_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_auto_lock_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_auto_lock_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_auto_lock_cont, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_auto_lock_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_auto_lock_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_auto_lock_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_auto_lock_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_auto_lock_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_3
	ui->screen_img_3 = lv_img_create(ui->screen_auto_lock_cont);
	lv_obj_add_flag(ui->screen_img_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_3, &_save_alpha_141x72);
	lv_img_set_pivot(ui->screen_img_3, 50,50);
	lv_img_set_angle(ui->screen_img_3, 0);
	lv_obj_set_pos(ui->screen_img_3, 459, 0);
	lv_obj_set_size(ui->screen_img_3, 141, 72);

	//Write style for screen_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_label_2
	ui->screen_label_2 = lv_label_create(ui->screen_auto_lock_cont);
	lv_label_set_text(ui->screen_label_2, "Auto-Lock\n\n");
	lv_label_set_long_mode(ui->screen_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_label_2, 53, 8);
	lv_obj_set_size(ui->screen_label_2, 285, 42);

	//Write style for screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_2, &lv_font_arial_40, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_2
	ui->screen_img_2 = lv_img_create(ui->screen_auto_lock_cont);
	lv_obj_add_flag(ui->screen_img_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_2, &_fake_autolock_alpha_600x495);
	lv_img_set_pivot(ui->screen_img_2, 50,50);
	lv_img_set_angle(ui->screen_img_2, 0);
	lv_obj_set_pos(ui->screen_img_2, 0, 105);
	lv_obj_set_size(ui->screen_img_2, 600, 495);

	//Write style for screen_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_1
	ui->screen_img_1 = lv_img_create(ui->screen_auto_lock_cont);
	lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_1, &_icon_close_alpha_56x56);
	lv_img_set_pivot(ui->screen_img_1, 50,50);
	lv_img_set_angle(ui->screen_img_1, 0);
	lv_obj_set_pos(ui->screen_img_1, 0, 0);
	lv_obj_set_size(ui->screen_img_1, 56, 56);

	//Write style for screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_timezone_cont
	ui->screen_timezone_cont = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_timezone_cont, 0, 0);
	lv_obj_set_size(ui->screen_timezone_cont, 600, 600);
	lv_obj_set_scrollbar_mode(ui->screen_timezone_cont, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_timezone_cont, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_timezone_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_timezone_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_timezone_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_timezone_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_timezone_cont, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_timezone_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_timezone_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_timezone_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_timezone_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_timezone_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_6
	ui->screen_img_6 = lv_img_create(ui->screen_timezone_cont);
	lv_obj_add_flag(ui->screen_img_6, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_6, &_save_alpha_141x72);
	lv_img_set_pivot(ui->screen_img_6, 50,50);
	lv_img_set_angle(ui->screen_img_6, 0);
	lv_obj_set_pos(ui->screen_img_6, 459, 0);
	lv_obj_set_size(ui->screen_img_6, 141, 72);

	//Write style for screen_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_label_3
	ui->screen_label_3 = lv_label_create(ui->screen_timezone_cont);
	lv_label_set_text(ui->screen_label_3, "Timezone\n\n\n");
	lv_label_set_long_mode(ui->screen_label_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_label_3, 53, 8);
	lv_obj_set_size(ui->screen_label_3, 285, 42);

	//Write style for screen_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_3, &lv_font_arial_40, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_5
	ui->screen_img_5 = lv_img_create(ui->screen_timezone_cont);
	lv_obj_add_flag(ui->screen_img_5, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_5, &_fake_timezone_alpha_600x495);
	lv_img_set_pivot(ui->screen_img_5, 50,50);
	lv_img_set_angle(ui->screen_img_5, 0);
	lv_obj_set_pos(ui->screen_img_5, 0, 105);
	lv_obj_set_size(ui->screen_img_5, 600, 495);

	//Write style for screen_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_4
	ui->screen_img_4 = lv_img_create(ui->screen_timezone_cont);
	lv_obj_add_flag(ui->screen_img_4, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_4, &_icon_close_alpha_56x56);
	lv_img_set_pivot(ui->screen_img_4, 50,50);
	lv_img_set_angle(ui->screen_img_4, 0);
	lv_obj_set_pos(ui->screen_img_4, 0, 0);
	lv_obj_set_size(ui->screen_img_4, 56, 56);

	//Write style for screen_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_language_cont
	ui->screen_language_cont = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_language_cont, 0, 0);
	lv_obj_set_size(ui->screen_language_cont, 600, 600);
	lv_obj_set_scrollbar_mode(ui->screen_language_cont, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_language_cont, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_language_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_language_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_language_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_language_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_language_cont, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_language_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_language_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_language_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_language_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_language_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_9
	ui->screen_img_9 = lv_img_create(ui->screen_language_cont);
	lv_obj_add_flag(ui->screen_img_9, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_9, &_save_alpha_141x72);
	lv_img_set_pivot(ui->screen_img_9, 50,50);
	lv_img_set_angle(ui->screen_img_9, 0);
	lv_obj_set_pos(ui->screen_img_9, 459, 0);
	lv_obj_set_size(ui->screen_img_9, 141, 72);

	//Write style for screen_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_label_4
	ui->screen_label_4 = lv_label_create(ui->screen_language_cont);
	lv_label_set_text(ui->screen_label_4, "Language\n\n\n");
	lv_label_set_long_mode(ui->screen_label_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_label_4, 53, 8);
	lv_obj_set_size(ui->screen_label_4, 285, 42);

	//Write style for screen_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_4, &lv_font_arial_40, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_8
	ui->screen_img_8 = lv_img_create(ui->screen_language_cont);
	lv_obj_add_flag(ui->screen_img_8, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_8, &_fake_langugae_alpha_600x495);
	lv_img_set_pivot(ui->screen_img_8, 50,50);
	lv_img_set_angle(ui->screen_img_8, 0);
	lv_obj_set_pos(ui->screen_img_8, 0, 105);
	lv_obj_set_size(ui->screen_img_8, 600, 495);

	//Write style for screen_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_7
	ui->screen_img_7 = lv_img_create(ui->screen_language_cont);
	lv_obj_add_flag(ui->screen_img_7, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_7, &_icon_close_alpha_56x56);
	lv_img_set_pivot(ui->screen_img_7, 50,50);
	lv_img_set_angle(ui->screen_img_7, 0);
	lv_obj_set_pos(ui->screen_img_7, 0, 0);
	lv_obj_set_size(ui->screen_img_7, 56, 56);

	//Write style for screen_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main
	ui->screen_main = lv_tileview_create(ui->screen);
	ui->screen_main_background = lv_tileview_add_tile(ui->screen_main, 0, 0, LV_DIR_BOTTOM);
	ui->screen_main_info = lv_tileview_add_tile(ui->screen_main, 0, 1, LV_DIR_TOP | LV_DIR_BOTTOM);
	ui->screen_main_setting = lv_tileview_add_tile(ui->screen_main, 0, 2, LV_DIR_TOP);
	lv_obj_set_pos(ui->screen_main, 0, 0);
	lv_obj_set_size(ui->screen_main, 600, 600);
	lv_obj_set_scrollbar_mode(ui->screen_main, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_main, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



	//Write codes screen_back_cont
	ui->screen_back_cont = lv_obj_create(ui->screen_main_background);
	lv_obj_set_pos(ui->screen_back_cont, 0, 0);
	lv_obj_set_size(ui->screen_back_cont, 600, 600);
	lv_obj_set_scrollbar_mode(ui->screen_back_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_back_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_back_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_back_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_back_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_back_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_back_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_back_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_back_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_back_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_back_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_back_img
	ui->screen_back_img = lv_img_create(ui->screen_back_cont);
	lv_obj_add_flag(ui->screen_back_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_back_img, &_back_1_alpha_600x600);
	lv_img_set_pivot(ui->screen_back_img, 50,50);
	lv_img_set_angle(ui->screen_back_img, 0);
	lv_obj_set_pos(ui->screen_back_img, 0, 0);
	lv_obj_set_size(ui->screen_back_img, 600, 600);

	//Write style for screen_back_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_back_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_back_clock
	ui->screen_back_clock = lv_label_create(ui->screen_back_cont);
	lv_label_set_text(ui->screen_back_clock, "08\n53");
	lv_label_set_long_mode(ui->screen_back_clock, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_back_clock, 0, 450);
	lv_obj_set_size(ui->screen_back_clock, 138, 126);

	//Write style for screen_back_clock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_back_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_back_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_back_clock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_back_clock, &lv_font_montserratMedium_60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_back_clock, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_back_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_back_clock, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_back_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_back_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_back_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_back_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_back_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_back_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_back_datetime
	ui->screen_back_datetime = lv_label_create(ui->screen_back_cont);
	lv_label_set_text(ui->screen_back_datetime, "20/04\n2024");
	lv_label_set_long_mode(ui->screen_back_datetime, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_back_datetime, 400, 500);
	lv_obj_set_size(ui->screen_back_datetime, 191, 92);

	//Write style for screen_back_datetime, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_back_datetime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_back_datetime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_back_datetime, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_back_datetime, &lv_font_montserratMedium_40, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_back_datetime, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_back_datetime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_back_datetime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_back_datetime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_back_datetime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_back_datetime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_back_datetime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_back_datetime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_back_datetime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_back_temp
	ui->screen_back_temp = lv_label_create(ui->screen_back_cont);
	lv_label_set_text(ui->screen_back_temp, "30 °C");
	lv_label_set_long_mode(ui->screen_back_temp, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_back_temp, 61, 14);
	lv_obj_set_size(ui->screen_back_temp, 111, 28);

	//Write style for screen_back_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_back_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_back_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_back_temp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_back_temp, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_back_temp, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_back_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_back_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_back_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_back_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_back_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_back_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_back_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_back_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_back_air
	ui->screen_back_air = lv_label_create(ui->screen_back_cont);
	lv_label_set_text(ui->screen_back_air, "125 AQI");
	lv_label_set_long_mode(ui->screen_back_air, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_back_air, 61, 56);
	lv_obj_set_size(ui->screen_back_air, 140, 28);

	//Write style for screen_back_air, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_back_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_back_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_back_air, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_back_air, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_back_air, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_back_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_back_air, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_back_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_back_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_back_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_back_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_back_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_back_air, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_back_icon_temp
	ui->screen_back_icon_temp = lv_img_create(ui->screen_back_cont);
	lv_obj_add_flag(ui->screen_back_icon_temp, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_back_icon_temp, &_sun_alpha_30x30);
	lv_img_set_pivot(ui->screen_back_icon_temp, 50,50);
	lv_img_set_angle(ui->screen_back_icon_temp, 0);
	lv_obj_set_pos(ui->screen_back_icon_temp, 25, 13);
	lv_obj_set_size(ui->screen_back_icon_temp, 30, 30);

	//Write style for screen_back_icon_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_back_icon_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_back_icon_air
	ui->screen_back_icon_air = lv_img_create(ui->screen_back_cont);
	lv_obj_add_flag(ui->screen_back_icon_air, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_back_icon_air, &_smile_alpha_30x30);
	lv_img_set_pivot(ui->screen_back_icon_air, 50,50);
	lv_img_set_angle(ui->screen_back_icon_air, 0);
	lv_obj_set_pos(ui->screen_back_icon_air, 25, 54);
	lv_obj_set_size(ui->screen_back_icon_air, 30, 30);

	//Write style for screen_back_icon_air, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_back_icon_air, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_info_tile
	ui->screen_info_tile = lv_tileview_create(ui->screen_main_info);
	ui->screen_info_tile_ethernet = lv_tileview_add_tile(ui->screen_info_tile, 0, 0, LV_DIR_RIGHT);
	ui->screen_info_tile_scene = lv_tileview_add_tile(ui->screen_info_tile, 1, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
	ui->screen_info_tile_device = lv_tileview_add_tile(ui->screen_info_tile, 2, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
	ui->screen_info_tile_ac_device = lv_tileview_add_tile(ui->screen_info_tile, 3, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
	ui->screen_info_tile_curtain = lv_tileview_add_tile(ui->screen_info_tile, 4, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
	ui->screen_info_tile_light = lv_tileview_add_tile(ui->screen_info_tile, 5, 0, LV_DIR_LEFT);
	lv_obj_set_pos(ui->screen_info_tile, 0, 0);
	lv_obj_set_size(ui->screen_info_tile, 600, 600);
	lv_obj_set_scrollbar_mode(ui->screen_info_tile, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_info_tile, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_info_tile, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_info_tile, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_info_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_info_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_info_tile, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_info_tile, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_info_tile, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_info_tile, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



	//Write codes screen_ether_cont
	ui->screen_ether_cont = lv_obj_create(ui->screen_info_tile_ethernet);
	lv_obj_set_pos(ui->screen_ether_cont, 0, 0);
	lv_obj_set_size(ui->screen_ether_cont, 600, 600);
	lv_obj_set_scrollbar_mode(ui->screen_ether_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_ether_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_ether_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_ether_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_ether_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_ether_cont, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_ether_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_ether_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_ether_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_ether_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_ether_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_ether_icon_lan
	ui->screen_ether_icon_lan = lv_img_create(ui->screen_ether_cont);
	lv_obj_add_flag(ui->screen_ether_icon_lan, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_ether_icon_lan, &_lan_alpha_80x80);
	lv_img_set_pivot(ui->screen_ether_icon_lan, 50,50);
	lv_img_set_angle(ui->screen_ether_icon_lan, 0);
	lv_obj_set_pos(ui->screen_ether_icon_lan, 260, 40);
	lv_obj_set_size(ui->screen_ether_icon_lan, 80, 80);

	//Write style for screen_ether_icon_lan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_ether_icon_lan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_ether_icon_qr
	ui->screen_ether_icon_qr = lv_img_create(ui->screen_ether_cont);
	lv_obj_add_flag(ui->screen_ether_icon_qr, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_ether_icon_qr, &_qr_alpha_100x100);
	lv_img_set_pivot(ui->screen_ether_icon_qr, 50,50);
	lv_img_set_angle(ui->screen_ether_icon_qr, 0);
	lv_obj_set_pos(ui->screen_ether_icon_qr, 250, 320);
	lv_obj_set_size(ui->screen_ether_icon_qr, 100, 100);

	//Write style for screen_ether_icon_qr, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_ether_icon_qr, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_ether_icon_or
	ui->screen_ether_icon_or = lv_img_create(ui->screen_ether_cont);
	lv_obj_add_flag(ui->screen_ether_icon_or, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_ether_icon_or, &_or_alpha_500x40);
	lv_img_set_pivot(ui->screen_ether_icon_or, 50,50);
	lv_img_set_angle(ui->screen_ether_icon_or, 0);
	lv_obj_set_pos(ui->screen_ether_icon_or, 50, 253);
	lv_obj_set_size(ui->screen_ether_icon_or, 500, 40);

	//Write style for screen_ether_icon_or, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_ether_icon_or, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_ether_text_info
	ui->screen_ether_text_info = lv_img_create(ui->screen_ether_cont);
	lv_obj_add_flag(ui->screen_ether_text_info, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_ether_text_info, &_info_alpha_500x80);
	lv_img_set_pivot(ui->screen_ether_text_info, 50,50);
	lv_img_set_angle(ui->screen_ether_text_info, 0);
	lv_obj_set_pos(ui->screen_ether_text_info, 50, 158);
	lv_obj_set_size(ui->screen_ether_text_info, 500, 80);

	//Write style for screen_ether_text_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_ether_text_info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_ether_text_scan
	ui->screen_ether_text_scan = lv_img_create(ui->screen_ether_cont);
	lv_obj_add_flag(ui->screen_ether_text_scan, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_ether_text_scan, &_scan_alpha_200x60);
	lv_img_set_pivot(ui->screen_ether_text_scan, 50,50);
	lv_img_set_angle(ui->screen_ether_text_scan, 0);
	lv_obj_set_pos(ui->screen_ether_text_scan, 200, 451);
	lv_obj_set_size(ui->screen_ether_text_scan, 200, 60);

	//Write style for screen_ether_text_scan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_ether_text_scan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_scene_2
	ui->screen_scene_2 = lv_obj_create(ui->screen_info_tile_scene);
	lv_obj_set_pos(ui->screen_scene_2, 320, 0);
	lv_obj_set_size(ui->screen_scene_2, 278, 142);
	lv_obj_set_scrollbar_mode(ui->screen_scene_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_scene_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_sce_butt2
	ui->screen_sce_butt2 = lv_img_create(ui->screen_scene_2);
	lv_obj_add_flag(ui->screen_sce_butt2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_sce_butt2, &_button_scene_alpha_278x142);
	lv_img_set_pivot(ui->screen_sce_butt2, 50,50);
	lv_img_set_angle(ui->screen_sce_butt2, 0);
	lv_obj_set_pos(ui->screen_sce_butt2, 0, 0);
	lv_obj_set_size(ui->screen_sce_butt2, 278, 142);

	//Write style for screen_sce_butt2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_sce_butt2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_sce_text2
	ui->screen_sce_text2 = lv_label_create(ui->screen_scene_2);
	lv_label_set_text(ui->screen_sce_text2, "Cảnh 2");
	lv_label_set_long_mode(ui->screen_sce_text2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_sce_text2, 86, 53);
	lv_obj_set_size(ui->screen_sce_text2, 183, 30);

	//Write style for screen_sce_text2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_sce_text2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_sce_text2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_sce_text2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_sce_text2, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_sce_text2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_sce_text2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_sce_text2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_sce_text2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_sce_text2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_sce_text2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_sce_text2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_sce_text2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_sce_text2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_sce_icon_2
	ui->screen_sce_icon_2 = lv_img_create(ui->screen_scene_2);
	lv_obj_add_flag(ui->screen_sce_icon_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_sce_icon_2, &_Plant_alpha_58x58);
	lv_img_set_pivot(ui->screen_sce_icon_2, 50,50);
	lv_img_set_angle(ui->screen_sce_icon_2, 0);
	lv_obj_set_pos(ui->screen_sce_icon_2, 18, 40);
	lv_obj_set_size(ui->screen_sce_icon_2, 58, 58);

	//Write style for screen_sce_icon_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_sce_icon_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_scene_1
	ui->screen_scene_1 = lv_obj_create(ui->screen_info_tile_scene);
	lv_obj_set_pos(ui->screen_scene_1, 0, 0);
	lv_obj_set_size(ui->screen_scene_1, 278, 142);
	lv_obj_set_scrollbar_mode(ui->screen_scene_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_scene_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_sce_butt1
	ui->screen_sce_butt1 = lv_img_create(ui->screen_scene_1);
	lv_obj_add_flag(ui->screen_sce_butt1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_sce_butt1, &_button_scene_alpha_278x142);
	lv_img_set_pivot(ui->screen_sce_butt1, 50,50);
	lv_img_set_angle(ui->screen_sce_butt1, 0);
	lv_obj_set_pos(ui->screen_sce_butt1, 0, 0);
	lv_obj_set_size(ui->screen_sce_butt1, 278, 142);

	//Write style for screen_sce_butt1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_sce_butt1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_sce_icon_1
	ui->screen_sce_icon_1 = lv_img_create(ui->screen_scene_1);
	lv_obj_add_flag(ui->screen_sce_icon_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_sce_icon_1, &_Welcome_alpha_58x58);
	lv_img_set_pivot(ui->screen_sce_icon_1, 50,50);
	lv_img_set_angle(ui->screen_sce_icon_1, 0);
	lv_obj_set_pos(ui->screen_sce_icon_1, 18, 40);
	lv_obj_set_size(ui->screen_sce_icon_1, 58, 58);

	//Write style for screen_sce_icon_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_sce_icon_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_sce_text1
	ui->screen_sce_text1 = lv_label_create(ui->screen_scene_1);
	lv_label_set_text(ui->screen_sce_text1, "Cảnh 1");
	lv_label_set_long_mode(ui->screen_sce_text1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_sce_text1, 86, 53);
	lv_obj_set_size(ui->screen_sce_text1, 183, 30);

	//Write style for screen_sce_text1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_sce_text1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_sce_text1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_sce_text1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_sce_text1, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_sce_text1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_sce_text1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_sce_text1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_sce_text1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_sce_text1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_sce_text1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_sce_text1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_sce_text1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_sce_text1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_scene_3
	ui->screen_scene_3 = lv_obj_create(ui->screen_info_tile_scene);
	lv_obj_set_pos(ui->screen_scene_3, 0, 162);
	lv_obj_set_size(ui->screen_scene_3, 278, 142);
	lv_obj_set_scrollbar_mode(ui->screen_scene_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_scene_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_sce_butt3
	ui->screen_sce_butt3 = lv_img_create(ui->screen_scene_3);
	lv_obj_add_flag(ui->screen_sce_butt3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_sce_butt3, &_button_scene_alpha_278x142);
	lv_img_set_pivot(ui->screen_sce_butt3, 50,50);
	lv_img_set_angle(ui->screen_sce_butt3, 0);
	lv_obj_set_pos(ui->screen_sce_butt3, 0, 0);
	lv_obj_set_size(ui->screen_sce_butt3, 278, 142);

	//Write style for screen_sce_butt3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_sce_butt3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_sce_text3
	ui->screen_sce_text3 = lv_label_create(ui->screen_scene_3);
	lv_label_set_text(ui->screen_sce_text3, "Cảnh 3\n");
	lv_label_set_long_mode(ui->screen_sce_text3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_sce_text3, 86, 53);
	lv_obj_set_size(ui->screen_sce_text3, 183, 30);

	//Write style for screen_sce_text3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_sce_text3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_sce_text3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_sce_text3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_sce_text3, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_sce_text3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_sce_text3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_sce_text3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_sce_text3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_sce_text3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_sce_text3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_sce_text3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_sce_text3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_sce_text3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_sce_icon_3
	ui->screen_sce_icon_3 = lv_img_create(ui->screen_scene_3);
	lv_obj_add_flag(ui->screen_sce_icon_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_sce_icon_3, &_Plant_alpha_58x58);
	lv_img_set_pivot(ui->screen_sce_icon_3, 50,50);
	lv_img_set_angle(ui->screen_sce_icon_3, 0);
	lv_obj_set_pos(ui->screen_sce_icon_3, 18, 40);
	lv_obj_set_size(ui->screen_sce_icon_3, 58, 58);

	//Write style for screen_sce_icon_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_sce_icon_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_device_2
	ui->screen_device_2 = lv_obj_create(ui->screen_info_tile_device);
	lv_obj_set_pos(ui->screen_device_2, 320, 0);
	lv_obj_set_size(ui->screen_device_2, 278, 204);
	lv_obj_set_scrollbar_mode(ui->screen_device_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_device_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_device_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_device_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_device_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_device_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_device_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_device_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_device_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_device_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_device_btt_2
	ui->screen_device_btt_2 = lv_img_create(ui->screen_device_2);
	lv_obj_add_flag(ui->screen_device_btt_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_device_btt_2, &_button_device_alpha_278x204);
	lv_img_set_pivot(ui->screen_device_btt_2, 50,50);
	lv_img_set_angle(ui->screen_device_btt_2, 0);
	lv_obj_set_pos(ui->screen_device_btt_2, 0, 0);
	lv_obj_set_size(ui->screen_device_btt_2, 278, 204);

	//Write style for screen_device_btt_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_device_btt_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_device_name_2
	ui->screen_device_name_2 = lv_label_create(ui->screen_device_2);
	lv_label_set_text(ui->screen_device_name_2, "Led 02\n");
	lv_label_set_long_mode(ui->screen_device_name_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_device_name_2, 25, 101);
	lv_obj_set_size(ui->screen_device_name_2, 183, 30);

	//Write style for screen_device_name_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_device_name_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_device_name_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_device_name_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_device_name_2, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_device_name_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_device_name_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_device_name_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_device_name_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_device_name_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_device_name_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_device_name_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_device_name_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_device_name_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_device_icon_2
	ui->screen_device_icon_2 = lv_img_create(ui->screen_device_2);
	lv_obj_add_flag(ui->screen_device_icon_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_device_icon_2, &_led_device_alpha_34x49);
	lv_img_set_pivot(ui->screen_device_icon_2, 50,50);
	lv_img_set_angle(ui->screen_device_icon_2, 0);
	lv_obj_set_pos(ui->screen_device_icon_2, 25, 25);
	lv_obj_set_size(ui->screen_device_icon_2, 34, 49);

	//Write style for screen_device_icon_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_device_icon_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_device_status_2
	ui->screen_device_status_2 = lv_label_create(ui->screen_device_2);
	lv_label_set_text(ui->screen_device_status_2, "OFF");
	lv_label_set_long_mode(ui->screen_device_status_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_device_status_2, 25, 141);
	lv_obj_set_size(ui->screen_device_status_2, 183, 30);

	//Write style for screen_device_status_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_device_status_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_device_status_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_device_status_2, lv_color_hex(0x6d6d6d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_device_status_2, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_device_status_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_device_status_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_device_status_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_device_status_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_device_status_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_device_status_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_device_status_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_device_status_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_device_status_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_device_1
	ui->screen_device_1 = lv_obj_create(ui->screen_info_tile_device);
	lv_obj_set_pos(ui->screen_device_1, 0, 0);
	lv_obj_set_size(ui->screen_device_1, 278, 204);
	lv_obj_set_scrollbar_mode(ui->screen_device_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_device_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_device_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_device_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_device_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_device_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_device_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_device_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_device_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_device_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_device_btt_1
	ui->screen_device_btt_1 = lv_img_create(ui->screen_device_1);
	lv_obj_add_flag(ui->screen_device_btt_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_device_btt_1, &_button_device_white_alpha_278x204);
	lv_img_set_pivot(ui->screen_device_btt_1, 50,50);
	lv_img_set_angle(ui->screen_device_btt_1, 0);
	lv_obj_set_pos(ui->screen_device_btt_1, 0, 0);
	lv_obj_set_size(ui->screen_device_btt_1, 278, 204);

	//Write style for screen_device_btt_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_device_btt_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_device_name_1
	ui->screen_device_name_1 = lv_label_create(ui->screen_device_1);
	lv_label_set_text(ui->screen_device_name_1, "Led 01");
	lv_label_set_long_mode(ui->screen_device_name_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_device_name_1, 25, 101);
	lv_obj_set_size(ui->screen_device_name_1, 183, 30);

	//Write style for screen_device_name_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_device_name_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_device_name_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_device_name_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_device_name_1, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_device_name_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_device_name_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_device_name_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_device_name_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_device_name_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_device_name_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_device_name_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_device_name_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_device_name_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_device_icon_1
	ui->screen_device_icon_1 = lv_img_create(ui->screen_device_1);
	lv_obj_add_flag(ui->screen_device_icon_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_device_icon_1, &_led_device_alpha_34x49);
	lv_img_set_pivot(ui->screen_device_icon_1, 50,50);
	lv_img_set_angle(ui->screen_device_icon_1, 0);
	lv_obj_set_pos(ui->screen_device_icon_1, 25, 25);
	lv_obj_set_size(ui->screen_device_icon_1, 34, 49);

	//Write style for screen_device_icon_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_device_icon_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_device_status_1
	ui->screen_device_status_1 = lv_label_create(ui->screen_device_1);
	lv_label_set_text(ui->screen_device_status_1, "ON");
	lv_label_set_long_mode(ui->screen_device_status_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_device_status_1, 25, 141);
	lv_obj_set_size(ui->screen_device_status_1, 183, 30);

	//Write style for screen_device_status_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_device_status_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_device_status_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_device_status_1, lv_color_hex(0x6d6d6d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_device_status_1, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_device_status_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_device_status_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_device_status_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_device_status_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_device_status_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_device_status_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_device_status_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_device_status_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_device_status_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_ac_device_fake
	ui->screen_ac_device_fake = lv_img_create(ui->screen_info_tile_ac_device);
	lv_obj_add_flag(ui->screen_ac_device_fake, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_ac_device_fake, &_fake_ac_device_alpha_600x600);
	lv_img_set_pivot(ui->screen_ac_device_fake, 50,50);
	lv_img_set_angle(ui->screen_ac_device_fake, 0);
	lv_obj_set_pos(ui->screen_ac_device_fake, 0, 0);
	lv_obj_set_size(ui->screen_ac_device_fake, 600, 600);

	//Write style for screen_ac_device_fake, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_ac_device_fake, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_curtain_fake
	ui->screen_curtain_fake = lv_img_create(ui->screen_info_tile_curtain);
	lv_obj_add_flag(ui->screen_curtain_fake, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_curtain_fake, &_curtain_fake_alpha_600x600);
	lv_img_set_pivot(ui->screen_curtain_fake, 50,50);
	lv_img_set_angle(ui->screen_curtain_fake, 0);
	lv_obj_set_pos(ui->screen_curtain_fake, 0, 0);
	lv_obj_set_size(ui->screen_curtain_fake, 600, 600);

	//Write style for screen_curtain_fake, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_curtain_fake, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_light_slider_set_bright
	ui->screen_light_slider_set_bright = lv_slider_create(ui->screen_info_tile_light);
	lv_slider_set_range(ui->screen_light_slider_set_bright, 0, 100);
	lv_slider_set_mode(ui->screen_light_slider_set_bright, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_light_slider_set_bright, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_light_slider_set_bright, 126, 57);
	lv_obj_set_size(ui->screen_light_slider_set_bright, 140, 450);

	//Write style for screen_light_slider_set_bright, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_light_slider_set_bright, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_light_slider_set_bright, lv_color_hex(0xddff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_light_slider_set_bright, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_light_slider_set_bright, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->screen_light_slider_set_bright, &_light_scroll_140x450, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->screen_light_slider_set_bright, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_light_slider_set_bright, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_light_slider_set_bright, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_light_slider_set_bright, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_light_slider_set_bright, lv_color_hex(0xffab00), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_light_slider_set_bright, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_light_slider_set_bright, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_light_slider_set_bright, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_light_slider_set_bright, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_light_image_set_color
	ui->screen_light_image_set_color = lv_img_create(ui->screen_info_tile_light);
	lv_obj_add_flag(ui->screen_light_image_set_color, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_light_image_set_color, &_mutiple_color_alpha_140x450);
	lv_img_set_pivot(ui->screen_light_image_set_color, 50,50);
	lv_img_set_angle(ui->screen_light_image_set_color, 0);
	lv_obj_set_pos(ui->screen_light_image_set_color, 331, 56);
	lv_obj_set_size(ui->screen_light_image_set_color, 140, 450);

	//Write style for screen_light_image_set_color, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_light_image_set_color, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_ligth_slider_set_color
	ui->screen_ligth_slider_set_color = lv_slider_create(ui->screen_info_tile_light);
	lv_slider_set_range(ui->screen_ligth_slider_set_color, 0, 100);
	lv_slider_set_mode(ui->screen_ligth_slider_set_color, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_ligth_slider_set_color, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_ligth_slider_set_color, 387, 95);
	lv_obj_set_size(ui->screen_ligth_slider_set_color, 30, 380);

	//Write style for screen_ligth_slider_set_color, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_ligth_slider_set_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_ligth_slider_set_color, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_ligth_slider_set_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_ligth_slider_set_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_ligth_slider_set_color, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_ligth_slider_set_color, 0, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_ligth_slider_set_color, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_ligth_slider_set_color, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_ligth_slider_set_color, 119, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_ligth_slider_set_color, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_ligth_slider_set_color, 50, LV_PART_KNOB|LV_STATE_DEFAULT);



	//Write codes screen_setting_cont
	ui->screen_setting_cont = lv_obj_create(ui->screen_main_setting);
	lv_obj_set_pos(ui->screen_setting_cont, 0, 0);
	lv_obj_set_size(ui->screen_setting_cont, 600, 600);
	lv_obj_set_scrollbar_mode(ui->screen_setting_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_setting_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_setting_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_setting_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_setting_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_setting_cont, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_setting_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_setting_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_setting_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_setting_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_setting_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_screen_config
	ui->screen_screen_config = lv_img_create(ui->screen_setting_cont);
	lv_obj_add_flag(ui->screen_screen_config, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_screen_config, &_screen_alpha_600x90);
	lv_img_set_pivot(ui->screen_screen_config, 50,50);
	lv_img_set_angle(ui->screen_screen_config, 0);
	lv_obj_set_pos(ui->screen_screen_config, 0, 500);
	lv_obj_set_size(ui->screen_screen_config, 600, 90);

	//Write style for screen_screen_config, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_screen_config, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_language
	ui->screen_language = lv_img_create(ui->screen_setting_cont);
	lv_obj_add_flag(ui->screen_language, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_language, &_language_alpha_600x90);
	lv_img_set_pivot(ui->screen_language, 50,50);
	lv_img_set_angle(ui->screen_language, 0);
	lv_obj_set_pos(ui->screen_language, 0, 400);
	lv_obj_set_size(ui->screen_language, 600, 90);

	//Write style for screen_language, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_language, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_timezone
	ui->screen_timezone = lv_img_create(ui->screen_setting_cont);
	lv_obj_add_flag(ui->screen_timezone, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_timezone, &_time_zone_alpha_600x90);
	lv_img_set_pivot(ui->screen_timezone, 50,50);
	lv_img_set_angle(ui->screen_timezone, 0);
	lv_obj_set_pos(ui->screen_timezone, 0, 300);
	lv_obj_set_size(ui->screen_timezone, 600, 90);

	//Write style for screen_timezone, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_timezone, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_auto_lock
	ui->screen_auto_lock = lv_img_create(ui->screen_setting_cont);
	lv_obj_add_flag(ui->screen_auto_lock, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_auto_lock, &_auto_lock_alpha_600x90);
	lv_img_set_pivot(ui->screen_auto_lock, 50,50);
	lv_img_set_angle(ui->screen_auto_lock, 0);
	lv_obj_set_pos(ui->screen_auto_lock, 0, 200);
	lv_obj_set_size(ui->screen_auto_lock, 600, 90);

	//Write style for screen_auto_lock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_auto_lock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_brightness
	ui->screen_brightness = lv_img_create(ui->screen_setting_cont);
	lv_obj_add_flag(ui->screen_brightness, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_brightness, &_bright_alpha_600x90);
	lv_img_set_pivot(ui->screen_brightness, 50,50);
	lv_img_set_angle(ui->screen_brightness, 0);
	lv_obj_set_pos(ui->screen_brightness, 0, 100);
	lv_obj_set_size(ui->screen_brightness, 600, 90);

	//Write style for screen_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_brightness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_network
	ui->screen_network = lv_img_create(ui->screen_setting_cont);
	lv_obj_add_flag(ui->screen_network, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_network, &_network_alpha_600x90);
	lv_img_set_pivot(ui->screen_network, 50,50);
	lv_img_set_angle(ui->screen_network, 0);
	lv_obj_set_pos(ui->screen_network, 0, 0);
	lv_obj_set_size(ui->screen_network, 600, 90);

	//Write style for screen_network, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_network, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen);

	
	//Init events for screen.
	events_init_screen(ui);
}
