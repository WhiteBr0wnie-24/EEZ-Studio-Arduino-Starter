#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include "TouchScreen.h"

// TODO: Re-Define according to actual wiring of touch display
#define YP A1
#define XM A0
#define YM 4
#define XP 5

// TODO: Replace with your screen resolution
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

bool touched = false;
bool coordinatesSet = false;

// TODO: Replace with your screen's touch controller
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
  // TODO: Replace with your custom touch-screen handling logic!

  TSPoint p = ts.getPoint();
  touched = (p.z > 375 && p.z < 415);

  float x = 1.0f * p.x - 200.0f;
  float y = 1.0f * p.y - 135.0f;
  x = (x / 685.0f) * 240.0f;
  y = (y / 735.0f) * 320.0f;

  x = (x - 480.0f) * -1.0f - 240;
  y = (y - 640.0f) * -1.0f - 320;

  if(touched && !coordinatesSet)
  {
    data->state = LV_INDEV_STATE_PR;

    
    data->point.x = x;
    data->point.y = y;

    coordinatesSet = true; 
  }
  
  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
    coordinatesSet = false;
  }
}

void setup()
{
  lv_init();

  tft.begin();
  tft.setRotation(2);

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);

  // Register the custom display function
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  // Register the custom touch-input handler
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );

  // Init EEZ-Studio UI
  ui_init();
}

void loop() {
  lv_timer_handler();
  // Update EEZ-Studio UI
  ui_tick();
}
