#define LILYGO_WATCH_2020_V1
#define LILYGO_WATCH_LVGL 
#include <Arduino.h>
#include <LilyGoWatch.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "esp_wifi.h"
#include "esp_sleep.h"


#define EEPROM_SIZE 128
#define DEFAULT_SCREEN_TIMEOUT  180*1000

extern TTGOClass *watch;
extern BMA *sensor;
extern PCF8563_Class *rtc;
extern TFT_eSPI *tft;

extern lv_obj_t *homeScreen;
extern lv_obj_t *exerciseScreen;
extern lv_obj_t *profileScreen;
extern lv_obj_t *profileInputScreen;
extern lv_obj_t *pastExercisesScreen;

extern lv_obj_t *batteryLabel;
extern lv_obj_t *stepCountLabel;
extern lv_obj_t *distanceLabel;
extern lv_obj_t *caloriesLabel;
extern lv_obj_t *progress;
extern lv_obj_t *exerciseList;

extern lv_style_t perStyle;
extern lv_style_t styleProgress;
extern lv_style_t styleArc;
extern lv_style_t mainStyle;
extern lv_style_t timeStyle;
extern lv_style_t batteryStyle;
extern lv_style_t buttonLabelStyle;

extern int stepCount;
extern String userName;
extern int userAge; 
extern int userHeight;
extern int userWeight;
extern int userTargetSteps;
extern String userGender;

extern float stepLength;
extern float caloriesMultiplier;

extern int dday;
extern int mmonth;
extern int yyear;

void setupHomePage(void);
void setupExercisePage(void);
void setupProfilePage(void);
void setupProfileInputPage(void);
void setupPastExercisesPage(void);
void updateStepPercentage(void);
void setupScreen(lv_obj_t *screen);
void setupBattery(lv_obj_t *screen);
void setupWifiIcon(lv_obj_t *screen);
void setupMenuBar(lv_obj_t *screen);
void displayTime(void);
void setupLabel(lv_obj_t *label, int x, int y, lv_style_t *style);
void getUserInformation(void);
void updateStepCounter(void);
bool resetStepCounter(void);
void setupNetwork(void);
void getExerciseData(lv_obj_t *list);
void sendExerciseData(void);


struct UserInfo{
  char userName[30];
  int userAge;
  int userHeight;
  int userWeight;
  int targetSteps;
  char userGender[6];
};
