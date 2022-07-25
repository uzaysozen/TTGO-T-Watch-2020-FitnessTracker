#include "config.h"

lv_obj_t *progress;
lv_obj_t *timeLabel;
lv_obj_t *perLabel;
lv_obj_t *dateLabel;

lv_style_t timeStyle;
lv_style_t styleProgress;
lv_style_t styleArc;
lv_style_t perStyle;

int dday;
int mmonth;
int yyear;

void setupProgressWheel(void);

void setupHomePage(void){
  //Display Time
  lv_style_init(&timeStyle);
  lv_style_set_bg_opa(&timeStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_text_font(&timeStyle, LV_STATE_DEFAULT, &lv_font_montserrat_48);

  timeLabel = lv_label_create(homeScreen, NULL);
  setupLabel(timeLabel, -10, -50, &timeStyle);

  //Display Progress Percentage
  lv_style_init(&perStyle);
  lv_style_set_bg_opa(&perStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_text_font(&perStyle, LV_STATE_DEFAULT, &lv_font_montserrat_22);

  perLabel = lv_label_create(homeScreen, NULL);
  setupLabel(perLabel, 6, 60, &perStyle);

  //Date
  static lv_style_t dateStyle;
  lv_style_init(&dateStyle);
  lv_style_set_bg_opa(&dateStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_text_font(&dateStyle, LV_STATE_DEFAULT, &lv_font_montserrat_18);

  dateLabel = lv_label_create(homeScreen, NULL);
  setupLabel(dateLabel, -25, 0, &dateStyle);

  //Progress Wheel
  setupProgressWheel();

  //Battery
  setupBattery(homeScreen);
  setupWifiIcon(homeScreen);
  setupMenuBar(homeScreen);
  updateStepPercentage();
}

void updateStepPercentage(){
  int percent;
  if (userTargetSteps == 0) {
    percent = 0;
  } else {
    percent = (stepCount * 100)/userTargetSteps;
  }
  
  if (percent >= 1000) {
    lv_style_set_text_font(&perStyle, LV_STATE_DEFAULT, &lv_font_montserrat_14);
    lv_obj_add_style(perLabel, LV_OBJ_PART_MAIN, &perStyle);
    lv_obj_align(perLabel, NULL, LV_ALIGN_CENTER, 0, 60);
    lv_style_set_line_color(&styleArc,LV_STATE_DEFAULT, lv_color_hex(0xFADE07));
    lv_style_set_line_color(&styleProgress,LV_STATE_DEFAULT, lv_color_hex(0x0000FF));
    lv_obj_add_style(progress, LV_ARC_PART_BG, &styleProgress);
    lv_obj_add_style(progress, LV_ARC_PART_INDIC, &styleArc);
    lv_arc_set_range(progress, userTargetSteps*10, userTargetSteps*100);
  }
  else if (percent >= 100){
    lv_style_set_text_font(&perStyle, LV_STATE_DEFAULT, &lv_font_montserrat_18);
    lv_obj_add_style(perLabel, LV_OBJ_PART_MAIN, &perStyle);
    lv_obj_align(perLabel, NULL, LV_ALIGN_CENTER, 0, 60);
    lv_style_set_line_color(&styleArc,LV_STATE_DEFAULT, lv_color_hex(0x0000FF));
    lv_style_set_line_color(&styleProgress,LV_STATE_DEFAULT, lv_color_hex(0x00FF00));
    lv_obj_add_style(progress, LV_ARC_PART_BG, &styleProgress);
    lv_obj_add_style(progress, LV_ARC_PART_INDIC, &styleArc);
    lv_arc_set_range(progress, userTargetSteps, userTargetSteps*10);
  }
  else if (percent >= 10 && percent < 100){
    lv_obj_align(perLabel, NULL, LV_ALIGN_CENTER, 3, 60);
  }
  else if (percent < 10){
    lv_obj_align(perLabel, NULL, LV_ALIGN_CENTER, 6, 60);
  }
  lv_label_set_text_fmt(perLabel, "#ffffff %d%%#", percent);
  lv_arc_set_value(progress, stepCount); // update progress wheel
}

void displayTime(void) {
  // Get the current data
  rtc->syncToRtc();
  RTC_Date tnow = watch->rtc->getDateTime();

  int hh = tnow.hour;
  int mm = tnow.minute;
  int ss = tnow.second;
  dday = tnow.day;
  mmonth = tnow.month;
  yyear = tnow.year;

  // Display Time
  if (hh < 10 && mm < 10) {
    lv_label_set_text_fmt(timeLabel, "#ffffff 0%d:0%d#", hh, mm);
  }
  else if (hh < 10){
    lv_label_set_text_fmt(timeLabel, "#ffffff 0%d:%d#", hh, mm);
  }
  else if (mm < 10){
    lv_label_set_text_fmt(timeLabel, "#ffffff %d:0%d#", hh, mm);
  }
  else {
    lv_label_set_text_fmt(timeLabel, "#ffffff %d:%d#", hh, mm);
  }

  lv_label_set_text_fmt(dateLabel, "#ffffff %02d/%02d/%4d#", dday, mmonth, yyear);
}

void setupProgressWheel(void) {
  // Progress Wheel
  static lv_style_t mainArcStyle;
  lv_style_init(&styleProgress);
  lv_style_init(&styleArc);
  lv_style_init(&mainArcStyle);
  lv_style_set_bg_opa(&mainArcStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_border_opa(&mainArcStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_line_width(&styleArc,LV_STATE_DEFAULT, 5);
  lv_style_set_line_color(&styleArc,LV_STATE_DEFAULT, lv_color_hex(0x00FF00));
  lv_style_set_line_width(&styleProgress,LV_STATE_DEFAULT, 5);
  lv_style_set_line_color(&styleProgress,LV_STATE_DEFAULT, lv_color_hex(0xFF0000));
  
  /*Create a Preloader object*/
  progress = lv_arc_create(homeScreen, NULL);
  lv_obj_align(progress, NULL, LV_ALIGN_CENTER, 15, 75);
  lv_obj_add_style(progress, LV_ARC_PART_BG, &styleProgress);
  lv_obj_add_style(progress, LV_OBJ_PART_MAIN, &mainArcStyle);
  lv_obj_add_style(progress, LV_ARC_PART_INDIC, &styleArc);
  lv_arc_set_range(progress, 0, userTargetSteps);
  lv_arc_set_bg_angles(progress, 0, 360);
  lv_arc_set_rotation(progress, 270);
  lv_obj_set_size(progress, 100, 100);
}
