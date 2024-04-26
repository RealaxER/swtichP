# Copyright 2024 NXP
# NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct
import fs_driver

lv.init()
SDL.init(w=1280,h=720)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(1280*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 1280
disp_drv.ver_res = 720
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init()
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_zoom(v)

def anim_img_rotate_cb(obj, v):
    obj.set_angle(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.font_load(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.img_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = e.get_current_target()
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RES.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    target = e.get_target()
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = target.get_screen()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = target.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, target), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    target = e.get_current_target()
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if target.get_pressed_date(date) == lv.RES.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.clear_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            target.delete()

# Create screen
screen = lv.obj()
screen.set_size(1280, 720)
# Set style for screen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main
screen_main = lv.tileview(screen)
screen_main_background = screen_main.add_tile(0, 0, lv.DIR.BOTTOM)
screen_main_info = screen_main.add_tile(0, 1, lv.DIR.TOP | lv.DIR.BOTTOM)
screen_main_setting = screen_main.add_tile(0, 2, lv.DIR.TOP)
screen_main.set_pos(0, 0)
screen_main.set_size(600, 600)
screen_main.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_main, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_main.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_main.set_style_bg_color(lv.color_hex(0xeaeff3), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_main.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create screen_back_cont
screen_back_cont = lv.obj(screen_main_background)
screen_back_cont.set_pos(0, 0)
screen_back_cont.set_size(600, 600)
screen_back_cont.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_back_cont, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_back_cont.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_cont.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_cont.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_cont.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_cont.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_cont.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_cont.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_cont.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_cont.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_back_img
screen_back_img = lv.img(screen_back_cont)
screen_back_img.set_src("B:MicroPython/_back_1_alpha_600x600.bin")
screen_back_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_back_img.set_pivot(50,50)
screen_back_img.set_angle(0)
screen_back_img.set_pos(0, 0)
screen_back_img.set_size(600, 600)
# Set style for screen_back_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_back_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_back_clock
screen_back_clock = lv.label(screen_back_cont)
screen_back_clock.set_text("08\n53")
screen_back_clock.set_long_mode(lv.label.LONG.WRAP)
screen_back_clock.set_pos(0, 450)
screen_back_clock.set_size(138, 126)
# Set style for screen_back_clock, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_back_clock.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_text_font(test_font("montserratMedium", 60), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_clock.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_back_datetime
screen_back_datetime = lv.label(screen_back_cont)
screen_back_datetime.set_text("20/04\n2024")
screen_back_datetime.set_long_mode(lv.label.LONG.WRAP)
screen_back_datetime.set_pos(400, 500)
screen_back_datetime.set_size(191, 92)
# Set style for screen_back_datetime, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_back_datetime.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_text_font(test_font("montserratMedium", 40), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_datetime.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_back_temp
screen_back_temp = lv.label(screen_back_cont)
screen_back_temp.set_text("30 °C")
screen_back_temp.set_long_mode(lv.label.LONG.WRAP)
screen_back_temp.set_pos(61, 14)
screen_back_temp.set_size(111, 28)
# Set style for screen_back_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_back_temp.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_temp.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_back_air
screen_back_air = lv.label(screen_back_cont)
screen_back_air.set_text("125 AQI")
screen_back_air.set_long_mode(lv.label.LONG.WRAP)
screen_back_air.set_pos(61, 56)
screen_back_air.set_size(140, 28)
# Set style for screen_back_air, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_back_air.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_back_air.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_back_icon_temp
screen_back_icon_temp = lv.img(screen_back_cont)
screen_back_icon_temp.set_src("B:MicroPython/_sun_alpha_30x30.bin")
screen_back_icon_temp.add_flag(lv.obj.FLAG.CLICKABLE)
screen_back_icon_temp.set_pivot(50,50)
screen_back_icon_temp.set_angle(0)
screen_back_icon_temp.set_pos(25, 13)
screen_back_icon_temp.set_size(30, 30)
# Set style for screen_back_icon_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_back_icon_temp.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_back_icon_air
screen_back_icon_air = lv.img(screen_back_cont)
screen_back_icon_air.set_src("B:MicroPython/_smile_alpha_30x30.bin")
screen_back_icon_air.add_flag(lv.obj.FLAG.CLICKABLE)
screen_back_icon_air.set_pivot(50,50)
screen_back_icon_air.set_angle(0)
screen_back_icon_air.set_pos(25, 54)
screen_back_icon_air.set_size(30, 30)
# Set style for screen_back_icon_air, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_back_icon_air.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_info_tile
screen_info_tile = lv.tileview(screen_main_info)
screen_info_tile_ethernet = screen_info_tile.add_tile(0, 0, lv.DIR.RIGHT)
screen_info_tile_scene = screen_info_tile.add_tile(1, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
screen_info_tile_device = screen_info_tile.add_tile(2, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
screen_info_tile_ac_device = screen_info_tile.add_tile(3, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
screen_info_tile_curtain = screen_info_tile.add_tile(4, 0, lv.DIR.LEFT | lv.DIR.RIGHT)
screen_info_tile_light = screen_info_tile.add_tile(5, 0, lv.DIR.LEFT)
screen_info_tile.set_pos(0, 0)
screen_info_tile.set_size(600, 600)
screen_info_tile.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_info_tile, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_info_tile.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_info_tile.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_info_tile.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_info_tile.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_info_tile, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_info_tile.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_info_tile.set_style_bg_color(lv.color_hex(0xeaeff3), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_info_tile.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create screen_ether_cont
screen_ether_cont = lv.obj(screen_info_tile_ethernet)
screen_ether_cont.set_pos(0, 0)
screen_ether_cont.set_size(600, 600)
screen_ether_cont.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_ether_cont, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ether_cont.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ether_cont.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ether_cont.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ether_cont.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ether_cont.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ether_cont.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ether_cont.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ether_cont.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ether_cont.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_ether_icon_lan
screen_ether_icon_lan = lv.img(screen_ether_cont)
screen_ether_icon_lan.set_src("B:MicroPython/_lan_alpha_80x80.bin")
screen_ether_icon_lan.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ether_icon_lan.set_pivot(50,50)
screen_ether_icon_lan.set_angle(0)
screen_ether_icon_lan.set_pos(260, 40)
screen_ether_icon_lan.set_size(80, 80)
# Set style for screen_ether_icon_lan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ether_icon_lan.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ether_icon_qr
screen_ether_icon_qr = lv.img(screen_ether_cont)
screen_ether_icon_qr.set_src("B:MicroPython/_qr_alpha_100x100.bin")
screen_ether_icon_qr.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ether_icon_qr.set_pivot(50,50)
screen_ether_icon_qr.set_angle(0)
screen_ether_icon_qr.set_pos(250, 320)
screen_ether_icon_qr.set_size(100, 100)
# Set style for screen_ether_icon_qr, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ether_icon_qr.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ether_icon_or
screen_ether_icon_or = lv.img(screen_ether_cont)
screen_ether_icon_or.set_src("B:MicroPython/_or_alpha_500x40.bin")
screen_ether_icon_or.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ether_icon_or.set_pivot(50,50)
screen_ether_icon_or.set_angle(0)
screen_ether_icon_or.set_pos(50, 253)
screen_ether_icon_or.set_size(500, 40)
# Set style for screen_ether_icon_or, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ether_icon_or.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ether_text_info
screen_ether_text_info = lv.img(screen_ether_cont)
screen_ether_text_info.set_src("B:MicroPython/_info_alpha_500x80.bin")
screen_ether_text_info.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ether_text_info.set_pivot(50,50)
screen_ether_text_info.set_angle(0)
screen_ether_text_info.set_pos(50, 158)
screen_ether_text_info.set_size(500, 80)
# Set style for screen_ether_text_info, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ether_text_info.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ether_text_scan
screen_ether_text_scan = lv.img(screen_ether_cont)
screen_ether_text_scan.set_src("B:MicroPython/_scan_alpha_200x60.bin")
screen_ether_text_scan.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ether_text_scan.set_pivot(50,50)
screen_ether_text_scan.set_angle(0)
screen_ether_text_scan.set_pos(200, 451)
screen_ether_text_scan.set_size(200, 60)
# Set style for screen_ether_text_scan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ether_text_scan.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_scene_2
screen_scene_2 = lv.obj(screen_info_tile_scene)
screen_scene_2.set_pos(320, 0)
screen_scene_2.set_size(278, 142)
screen_scene_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_scene_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_scene_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_sce_butt2
screen_sce_butt2 = lv.img(screen_scene_2)
screen_sce_butt2.set_src("B:MicroPython/_button_scene_alpha_278x142.bin")
screen_sce_butt2.add_flag(lv.obj.FLAG.CLICKABLE)
screen_sce_butt2.set_pivot(50,50)
screen_sce_butt2.set_angle(0)
screen_sce_butt2.set_pos(0, 0)
screen_sce_butt2.set_size(278, 142)
# Set style for screen_sce_butt2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_sce_butt2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_sce_text2
screen_sce_text2 = lv.label(screen_scene_2)
screen_sce_text2.set_text("Cảnh 2")
screen_sce_text2.set_long_mode(lv.label.LONG.WRAP)
screen_sce_text2.set_pos(86, 53)
screen_sce_text2.set_size(183, 30)
# Set style for screen_sce_text2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_sce_text2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_sce_icon_2
screen_sce_icon_2 = lv.img(screen_scene_2)
screen_sce_icon_2.set_src("B:MicroPython/_Plant_alpha_58x58.bin")
screen_sce_icon_2.add_flag(lv.obj.FLAG.CLICKABLE)
screen_sce_icon_2.set_pivot(50,50)
screen_sce_icon_2.set_angle(0)
screen_sce_icon_2.set_pos(18, 40)
screen_sce_icon_2.set_size(58, 58)
# Set style for screen_sce_icon_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_sce_icon_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_scene_1
screen_scene_1 = lv.obj(screen_info_tile_scene)
screen_scene_1.set_pos(0, 0)
screen_scene_1.set_size(278, 142)
screen_scene_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_scene_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_scene_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_sce_butt1
screen_sce_butt1 = lv.img(screen_scene_1)
screen_sce_butt1.set_src("B:MicroPython/_button_scene_alpha_278x142.bin")
screen_sce_butt1.add_flag(lv.obj.FLAG.CLICKABLE)
screen_sce_butt1.set_pivot(50,50)
screen_sce_butt1.set_angle(0)
screen_sce_butt1.set_pos(0, 0)
screen_sce_butt1.set_size(278, 142)
# Set style for screen_sce_butt1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_sce_butt1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_sce_icon_1
screen_sce_icon_1 = lv.img(screen_scene_1)
screen_sce_icon_1.set_src("B:MicroPython/_Welcome_alpha_58x58.bin")
screen_sce_icon_1.add_flag(lv.obj.FLAG.CLICKABLE)
screen_sce_icon_1.set_pivot(50,50)
screen_sce_icon_1.set_angle(0)
screen_sce_icon_1.set_pos(18, 40)
screen_sce_icon_1.set_size(58, 58)
# Set style for screen_sce_icon_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_sce_icon_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_sce_text1
screen_sce_text1 = lv.label(screen_scene_1)
screen_sce_text1.set_text("Cảnh 1")
screen_sce_text1.set_long_mode(lv.label.LONG.WRAP)
screen_sce_text1.set_pos(86, 53)
screen_sce_text1.set_size(183, 30)
# Set style for screen_sce_text1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_sce_text1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_scene_3
screen_scene_3 = lv.obj(screen_info_tile_scene)
screen_scene_3.set_pos(0, 162)
screen_scene_3.set_size(278, 142)
screen_scene_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_scene_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_scene_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_scene_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_sce_butt3
screen_sce_butt3 = lv.img(screen_scene_3)
screen_sce_butt3.set_src("B:MicroPython/_button_scene_alpha_278x142.bin")
screen_sce_butt3.add_flag(lv.obj.FLAG.CLICKABLE)
screen_sce_butt3.set_pivot(50,50)
screen_sce_butt3.set_angle(0)
screen_sce_butt3.set_pos(0, 0)
screen_sce_butt3.set_size(278, 142)
# Set style for screen_sce_butt3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_sce_butt3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_sce_text3
screen_sce_text3 = lv.label(screen_scene_3)
screen_sce_text3.set_text("Cảnh 3\n")
screen_sce_text3.set_long_mode(lv.label.LONG.WRAP)
screen_sce_text3.set_pos(86, 53)
screen_sce_text3.set_size(183, 30)
# Set style for screen_sce_text3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_sce_text3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_sce_text3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_sce_icon_3
screen_sce_icon_3 = lv.img(screen_scene_3)
screen_sce_icon_3.set_src("B:MicroPython/_Plant_alpha_58x58.bin")
screen_sce_icon_3.add_flag(lv.obj.FLAG.CLICKABLE)
screen_sce_icon_3.set_pivot(50,50)
screen_sce_icon_3.set_angle(0)
screen_sce_icon_3.set_pos(18, 40)
screen_sce_icon_3.set_size(58, 58)
# Set style for screen_sce_icon_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_sce_icon_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_device_2
screen_device_2 = lv.obj(screen_info_tile_device)
screen_device_2.set_pos(320, 0)
screen_device_2.set_size(278, 204)
screen_device_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_device_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_device_btt_2
screen_device_btt_2 = lv.img(screen_device_2)
screen_device_btt_2.set_src("B:MicroPython/_button_device_alpha_278x204.bin")
screen_device_btt_2.add_flag(lv.obj.FLAG.CLICKABLE)
screen_device_btt_2.set_pivot(50,50)
screen_device_btt_2.set_angle(0)
screen_device_btt_2.set_pos(0, 0)
screen_device_btt_2.set_size(278, 204)
# Set style for screen_device_btt_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_btt_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_device_name_2
screen_device_name_2 = lv.label(screen_device_2)
screen_device_name_2.set_text("Led 02\n")
screen_device_name_2.set_long_mode(lv.label.LONG.WRAP)
screen_device_name_2.set_pos(25, 101)
screen_device_name_2.set_size(183, 30)
# Set style for screen_device_name_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_name_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_device_icon_2
screen_device_icon_2 = lv.img(screen_device_2)
screen_device_icon_2.set_src("B:MicroPython/_led_device_alpha_34x49.bin")
screen_device_icon_2.add_flag(lv.obj.FLAG.CLICKABLE)
screen_device_icon_2.set_pivot(50,50)
screen_device_icon_2.set_angle(0)
screen_device_icon_2.set_pos(25, 25)
screen_device_icon_2.set_size(34, 49)
# Set style for screen_device_icon_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_icon_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_device_status_2
screen_device_status_2 = lv.label(screen_device_2)
screen_device_status_2.set_text("OFF")
screen_device_status_2.set_long_mode(lv.label.LONG.WRAP)
screen_device_status_2.set_pos(25, 141)
screen_device_status_2.set_size(183, 30)
# Set style for screen_device_status_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_status_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_text_color(lv.color_hex(0x6d6d6d), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_device_1
screen_device_1 = lv.obj(screen_info_tile_device)
screen_device_1.set_pos(0, 0)
screen_device_1.set_size(278, 204)
screen_device_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_device_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_device_btt_1
screen_device_btt_1 = lv.img(screen_device_1)
screen_device_btt_1.set_src("B:MicroPython/_button_device_white_alpha_278x204.bin")
screen_device_btt_1.add_flag(lv.obj.FLAG.CLICKABLE)
screen_device_btt_1.set_pivot(50,50)
screen_device_btt_1.set_angle(0)
screen_device_btt_1.set_pos(0, 0)
screen_device_btt_1.set_size(278, 204)
# Set style for screen_device_btt_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_btt_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_device_name_1
screen_device_name_1 = lv.label(screen_device_1)
screen_device_name_1.set_text("Led 01")
screen_device_name_1.set_long_mode(lv.label.LONG.WRAP)
screen_device_name_1.set_pos(25, 101)
screen_device_name_1.set_size(183, 30)
# Set style for screen_device_name_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_name_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_name_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_device_icon_1
screen_device_icon_1 = lv.img(screen_device_1)
screen_device_icon_1.set_src("B:MicroPython/_led_device_alpha_34x49.bin")
screen_device_icon_1.add_flag(lv.obj.FLAG.CLICKABLE)
screen_device_icon_1.set_pivot(50,50)
screen_device_icon_1.set_angle(0)
screen_device_icon_1.set_pos(25, 25)
screen_device_icon_1.set_size(34, 49)
# Set style for screen_device_icon_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_icon_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_device_status_1
screen_device_status_1 = lv.label(screen_device_1)
screen_device_status_1.set_text("ON")
screen_device_status_1.set_long_mode(lv.label.LONG.WRAP)
screen_device_status_1.set_pos(25, 141)
screen_device_status_1.set_size(183, 30)
# Set style for screen_device_status_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_device_status_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_text_color(lv.color_hex(0x6d6d6d), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_device_status_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ac_device_fake
screen_ac_device_fake = lv.img(screen_info_tile_ac_device)
screen_ac_device_fake.set_src("B:MicroPython/_fake_ac_device_alpha_600x600.bin")
screen_ac_device_fake.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ac_device_fake.set_pivot(50,50)
screen_ac_device_fake.set_angle(0)
screen_ac_device_fake.set_pos(0, 0)
screen_ac_device_fake.set_size(600, 600)
# Set style for screen_ac_device_fake, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ac_device_fake.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_curtain_fake
screen_curtain_fake = lv.img(screen_info_tile_curtain)
screen_curtain_fake.set_src("B:MicroPython/_curtain_fake_alpha_600x600.bin")
screen_curtain_fake.add_flag(lv.obj.FLAG.CLICKABLE)
screen_curtain_fake.set_pivot(50,50)
screen_curtain_fake.set_angle(0)
screen_curtain_fake.set_pos(0, 0)
screen_curtain_fake.set_size(600, 600)
# Set style for screen_curtain_fake, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_curtain_fake.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_light_slider_set_bright
screen_light_slider_set_bright = lv.slider(screen_info_tile_light)
screen_light_slider_set_bright.set_range(0, 100)
screen_light_slider_set_bright.set_mode(lv.slider.MODE.NORMAL)
screen_light_slider_set_bright.set_value(50, lv.ANIM.OFF)
screen_light_slider_set_bright.set_pos(126, 57)
screen_light_slider_set_bright.set_size(140, 450)
# Set style for screen_light_slider_set_bright, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_light_slider_set_bright.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_light_slider_set_bright.set_style_bg_color(lv.color_hex(0xddff00), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_light_slider_set_bright.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_light_slider_set_bright.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_light_slider_set_bright.set_style_bg_img_src("B:MicroPython/_light_scroll_140x450.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
screen_light_slider_set_bright.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_light_slider_set_bright.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_light_slider_set_bright, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
screen_light_slider_set_bright.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_light_slider_set_bright.set_style_bg_color(lv.color_hex(0xffab00), lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_light_slider_set_bright.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for screen_light_slider_set_bright, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
screen_light_slider_set_bright.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_light_slider_set_bright.set_style_radius(50, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create screen_light_image_set_color
screen_light_image_set_color = lv.img(screen_info_tile_light)
screen_light_image_set_color.set_src("B:MicroPython/_mutiple_color_alpha_140x450.bin")
screen_light_image_set_color.add_flag(lv.obj.FLAG.CLICKABLE)
screen_light_image_set_color.set_pivot(50,50)
screen_light_image_set_color.set_angle(0)
screen_light_image_set_color.set_pos(331, 56)
screen_light_image_set_color.set_size(140, 450)
# Set style for screen_light_image_set_color, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_light_image_set_color.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ligth_slider_set_color
screen_ligth_slider_set_color = lv.slider(screen_info_tile_light)
screen_ligth_slider_set_color.set_range(0, 100)
screen_ligth_slider_set_color.set_mode(lv.slider.MODE.NORMAL)
screen_ligth_slider_set_color.set_value(50, lv.ANIM.OFF)
screen_ligth_slider_set_color.set_pos(387, 95)
screen_ligth_slider_set_color.set_size(30, 380)
# Set style for screen_ligth_slider_set_color, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ligth_slider_set_color.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ligth_slider_set_color.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ligth_slider_set_color.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ligth_slider_set_color.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_ligth_slider_set_color, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
screen_ligth_slider_set_color.set_style_bg_opa(0, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_ligth_slider_set_color.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for screen_ligth_slider_set_color, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
screen_ligth_slider_set_color.set_style_bg_opa(119, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_ligth_slider_set_color.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.KNOB|lv.STATE.DEFAULT)
screen_ligth_slider_set_color.set_style_radius(50, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create screen_setting_cont
screen_setting_cont = lv.obj(screen_main_setting)
screen_setting_cont.set_pos(0, 0)
screen_setting_cont.set_size(600, 600)
screen_setting_cont.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_setting_cont, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_setting_cont.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_cont.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_screen_config
screen_screen_config = lv.img(screen_setting_cont)
screen_screen_config.set_src("B:MicroPython/_screen_alpha_600x90.bin")
screen_screen_config.add_flag(lv.obj.FLAG.CLICKABLE)
screen_screen_config.set_pivot(50,50)
screen_screen_config.set_angle(0)
screen_screen_config.set_pos(0, 500)
screen_screen_config.set_size(600, 90)
# Set style for screen_screen_config, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_screen_config.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_language
screen_language = lv.img(screen_setting_cont)
screen_language.set_src("B:MicroPython/_language_alpha_600x90.bin")
screen_language.add_flag(lv.obj.FLAG.CLICKABLE)
screen_language.set_pivot(50,50)
screen_language.set_angle(0)
screen_language.set_pos(0, 400)
screen_language.set_size(600, 90)
# Set style for screen_language, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_language.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_timezone
screen_timezone = lv.img(screen_setting_cont)
screen_timezone.set_src("B:MicroPython/_time_zone_alpha_600x90.bin")
screen_timezone.add_flag(lv.obj.FLAG.CLICKABLE)
screen_timezone.set_pivot(50,50)
screen_timezone.set_angle(0)
screen_timezone.set_pos(0, 300)
screen_timezone.set_size(600, 90)
# Set style for screen_timezone, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_timezone.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_auto_lock
screen_auto_lock = lv.img(screen_setting_cont)
screen_auto_lock.set_src("B:MicroPython/_auto_lock_alpha_600x90.bin")
screen_auto_lock.add_flag(lv.obj.FLAG.CLICKABLE)
screen_auto_lock.set_pivot(50,50)
screen_auto_lock.set_angle(0)
screen_auto_lock.set_pos(0, 200)
screen_auto_lock.set_size(600, 90)
# Set style for screen_auto_lock, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_auto_lock.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_brightness
screen_brightness = lv.img(screen_setting_cont)
screen_brightness.set_src("B:MicroPython/_bright_alpha_600x90.bin")
screen_brightness.add_flag(lv.obj.FLAG.CLICKABLE)
screen_brightness.set_pivot(50,50)
screen_brightness.set_angle(0)
screen_brightness.set_pos(0, 100)
screen_brightness.set_size(600, 90)
# Set style for screen_brightness, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_brightness.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_network
screen_network = lv.img(screen_setting_cont)
screen_network.set_src("B:MicroPython/_network_alpha_600x90.bin")
screen_network.add_flag(lv.obj.FLAG.CLICKABLE)
screen_network.set_pivot(50,50)
screen_network.set_angle(0)
screen_network.set_pos(0, 0)
screen_network.set_size(600, 90)
# Set style for screen_network, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_network.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen.update_layout()

# content from custom.py

# Load the default screen
lv.scr_load(screen)

while SDL.check():
    time.sleep_ms(5)

