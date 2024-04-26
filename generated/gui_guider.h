/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_brightless_cont;
	lv_obj_t *screen_br_save;
	lv_obj_t *screen_br_name;
	lv_obj_t *screen_br_back;
	lv_obj_t *screen_br_slider;
	lv_obj_t *screen_br_value;
	lv_obj_t *screen_br_close;
	lv_obj_t *screen_auto_lock_cont;
	lv_obj_t *screen_img_3;
	lv_obj_t *screen_label_2;
	lv_obj_t *screen_img_2;
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_timezone_cont;
	lv_obj_t *screen_img_6;
	lv_obj_t *screen_label_3;
	lv_obj_t *screen_img_5;
	lv_obj_t *screen_img_4;
	lv_obj_t *screen_language_cont;
	lv_obj_t *screen_img_9;
	lv_obj_t *screen_label_4;
	lv_obj_t *screen_img_8;
	lv_obj_t *screen_img_7;
	lv_obj_t *screen_main;
	lv_obj_t *screen_main_background;
	lv_obj_t *screen_main_info;
	lv_obj_t *screen_main_setting;
	lv_obj_t *screen_back_cont;
	lv_obj_t *screen_back_img;
	lv_obj_t *screen_back_clock;
	lv_obj_t *screen_back_datetime;
	lv_obj_t *screen_back_temp;
	lv_obj_t *screen_back_air;
	lv_obj_t *screen_back_icon_temp;
	lv_obj_t *screen_back_icon_air;
	lv_obj_t *screen_info_tile;
	lv_obj_t *screen_info_tile_ethernet;
	lv_obj_t *screen_info_tile_scene;
	lv_obj_t *screen_info_tile_device;
	lv_obj_t *screen_info_tile_ac_device;
	lv_obj_t *screen_info_tile_curtain;
	lv_obj_t *screen_info_tile_light;
	lv_obj_t *screen_ether_cont;
	lv_obj_t *screen_ether_icon_lan;
	lv_obj_t *screen_ether_icon_qr;
	lv_obj_t *screen_ether_icon_or;
	lv_obj_t *screen_ether_text_info;
	lv_obj_t *screen_ether_text_scan;
	lv_obj_t *screen_scene_2;
	lv_obj_t *screen_sce_butt2;
	lv_obj_t *screen_sce_text2;
	lv_obj_t *screen_sce_icon_2;
	lv_obj_t *screen_scene_1;
	lv_obj_t *screen_sce_butt1;
	lv_obj_t *screen_sce_icon_1;
	lv_obj_t *screen_sce_text1;
	lv_obj_t *screen_scene_3;
	lv_obj_t *screen_sce_butt3;
	lv_obj_t *screen_sce_text3;
	lv_obj_t *screen_sce_icon_3;
	lv_obj_t *screen_device_2;
	lv_obj_t *screen_device_btt_2;
	lv_obj_t *screen_device_name_2;
	lv_obj_t *screen_device_icon_2;
	lv_obj_t *screen_device_status_2;
	lv_obj_t *screen_device_1;
	lv_obj_t *screen_device_btt_1;
	lv_obj_t *screen_device_name_1;
	lv_obj_t *screen_device_icon_1;
	lv_obj_t *screen_device_status_1;
	lv_obj_t *screen_ac_device_fake;
	lv_obj_t *screen_curtain_fake;
	lv_obj_t *screen_light_slider_set_bright;
	lv_obj_t *screen_light_image_set_color;
	lv_obj_t *screen_ligth_slider_set_color;
	lv_obj_t *screen_setting_cont;
	lv_obj_t *screen_screen_config;
	lv_obj_t *screen_language;
	lv_obj_t *screen_timezone;
	lv_obj_t *screen_auto_lock;
	lv_obj_t *screen_brightness;
	lv_obj_t *screen_network;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_screen(lv_ui *ui);
LV_IMG_DECLARE(_save_alpha_141x72);
LV_IMG_DECLARE(_button_scene_alpha_600x200);
LV_IMG_DECLARE(_icon_close_alpha_56x56);
LV_IMG_DECLARE(_save_alpha_141x72);
LV_IMG_DECLARE(_fake_autolock_alpha_600x495);
LV_IMG_DECLARE(_icon_close_alpha_56x56);
LV_IMG_DECLARE(_save_alpha_141x72);
LV_IMG_DECLARE(_fake_timezone_alpha_600x495);
LV_IMG_DECLARE(_icon_close_alpha_56x56);
LV_IMG_DECLARE(_save_alpha_141x72);
LV_IMG_DECLARE(_fake_langugae_alpha_600x495);
LV_IMG_DECLARE(_icon_close_alpha_56x56);
LV_IMG_DECLARE(_back_1_alpha_600x600);
LV_IMG_DECLARE(_sun_alpha_30x30);
LV_IMG_DECLARE(_smile_alpha_30x30);
LV_IMG_DECLARE(_lan_alpha_80x80);
LV_IMG_DECLARE(_qr_alpha_100x100);
LV_IMG_DECLARE(_or_alpha_500x40);
LV_IMG_DECLARE(_info_alpha_500x80);
LV_IMG_DECLARE(_scan_alpha_200x60);
LV_IMG_DECLARE(_button_scene_alpha_278x142);
LV_IMG_DECLARE(_Plant_alpha_58x58);
LV_IMG_DECLARE(_button_scene_alpha_278x142);
LV_IMG_DECLARE(_Welcome_alpha_58x58);
LV_IMG_DECLARE(_button_scene_alpha_278x142);
LV_IMG_DECLARE(_Plant_alpha_58x58);
LV_IMG_DECLARE(_button_device_alpha_278x204);
LV_IMG_DECLARE(_led_device_alpha_34x49);
LV_IMG_DECLARE(_button_device_white_alpha_278x204);
LV_IMG_DECLARE(_led_device_alpha_34x49);
LV_IMG_DECLARE(_fake_ac_device_alpha_600x600);
LV_IMG_DECLARE(_curtain_fake_alpha_600x600);

LV_IMG_DECLARE(_light_scroll_140x450);
LV_IMG_DECLARE(_mutiple_color_alpha_140x450);
LV_IMG_DECLARE(_screen_alpha_600x90);
LV_IMG_DECLARE(_language_alpha_600x90);
LV_IMG_DECLARE(_time_zone_alpha_600x90);
LV_IMG_DECLARE(_auto_lock_alpha_600x90);
LV_IMG_DECLARE(_bright_alpha_600x90);
LV_IMG_DECLARE(_network_alpha_600x90);

LV_FONT_DECLARE(lv_font_arial_40)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_60)
LV_FONT_DECLARE(lv_font_montserratMedium_40)
LV_FONT_DECLARE(lv_font_montserratMedium_30)


#ifdef __cplusplus
}
#endif
#endif
