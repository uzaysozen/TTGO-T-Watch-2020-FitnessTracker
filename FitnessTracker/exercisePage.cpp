#include "config.h"

lv_obj_t *stepCountLabel;
lv_obj_t *distanceLabel;
lv_obj_t *caloriesLabel;

lv_style_t exerciseLabelStyle;

static void resetBtnEventHandler(lv_obj_t *obj, lv_event_t event);
static void saveExerciseBtnEventHandler(lv_obj_t *obj, lv_event_t event);

void setupExercisePage(void){
  // initialize exercise label style
  lv_style_init(&exerciseLabelStyle);
  lv_style_set_bg_opa(&exerciseLabelStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_text_font(&exerciseLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_14);
  
  //Title
  lv_obj_t *exerciseTitleLabel = lv_label_create(exerciseScreen, NULL);
  setupLabel(exerciseTitleLabel, -50, -70, &timeStyle);
  lv_label_set_text(exerciseTitleLabel, "#ffffff Exercise#");

  //Step Count
  stepCountLabel = lv_label_create(exerciseScreen, NULL);
  setupLabel(stepCountLabel, -80, -30, &exerciseLabelStyle);
  lv_label_set_text_fmt(stepCountLabel, "#ffffff Step Count: %d#", stepCount); // update step count

  //Distance
  distanceLabel = lv_label_create(exerciseScreen, NULL);
  setupLabel(distanceLabel, -80, 0, &exerciseLabelStyle);
  lv_label_set_text_fmt(distanceLabel, "#ffffff Distance Covered: %.2f km#", (stepCount * stepLength)); // update distance

  //Calories
  caloriesLabel = lv_label_create(exerciseScreen, NULL);
  setupLabel(caloriesLabel, -80, 30, &exerciseLabelStyle);
  lv_label_set_text_fmt(caloriesLabel, "#ffffff Calories Burned: %.2f Cal#", (stepCount * caloriesMultiplier)); // update calories

  //Target Steps
  lv_obj_t *targetLabel = lv_label_create(exerciseScreen, NULL);
  setupLabel(targetLabel, -80, 60, &exerciseLabelStyle);
  lv_label_set_text_fmt(targetLabel, "#ffffff Target Steps: %d#", userTargetSteps);

  //Reset Button
  lv_obj_t *resetButton = lv_btn_create(exerciseScreen, NULL);
  lv_obj_set_event_cb(resetButton, resetBtnEventHandler);
  lv_obj_align(resetButton, NULL, LV_ALIGN_CENTER, -30, 95);
  lv_obj_set_size(resetButton, 70, 30);

  lv_obj_t *resetButtonLabel = lv_label_create(resetButton, NULL);
  lv_obj_add_style(resetButtonLabel, LV_OBJ_PART_MAIN, &buttonLabelStyle);
  lv_label_set_text(resetButtonLabel, "Reset");

  //Save Exercise Button
  lv_obj_t *saveExerciseButton = lv_btn_create(exerciseScreen, NULL);
  lv_obj_set_event_cb(saveExerciseButton, saveExerciseBtnEventHandler);
  lv_obj_align(saveExerciseButton, NULL, LV_ALIGN_CENTER, 60, 95);
  lv_obj_set_size(saveExerciseButton, 110, 30);

  lv_obj_t *saveExerciseButtonLabel = lv_label_create(saveExerciseButton, NULL);
  lv_obj_add_style(saveExerciseButtonLabel, LV_OBJ_PART_MAIN, &buttonLabelStyle);
  lv_label_set_text(saveExerciseButtonLabel, "Save Exercise");
  
  //Battery
  setupBattery(exerciseScreen);
  setupWifiIcon(exerciseScreen);
  setupMenuBar(exerciseScreen);
}

static void resetBtnEventHandler(lv_obj_t *obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    resetStepCounter();
    lv_obj_clean(exerciseScreen); // clean current screen
    setupExercisePage(); // setup new screen
    lv_scr_load(exerciseScreen);
  }
}

static void saveExerciseBtnEventHandler(lv_obj_t *obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    sendExerciseData();
  }
}
