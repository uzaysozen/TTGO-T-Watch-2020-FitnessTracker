#include "config.h"

String userName;
int userAge; 
int userHeight;
int userWeight;
int userTargetSteps;
double userBmi;
String userGender;

float stepLength;
float caloriesMultiplier;

static void editBtnEventHandler(lv_obj_t *obj, lv_event_t event);
void getUserInformation(void);
void setCaloriesBurned(void);
void setDistanceCovered(void);

void setupProfilePage(void){
  getUserInformation();
  // Profile Label Style
  static lv_style_t profileLabelStyle;
  lv_style_init(&profileLabelStyle);
  lv_style_set_bg_opa(&profileLabelStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_text_font(&profileLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_14);

  // Profile Title Style
  static lv_style_t profileTitleStyle;
  lv_style_init(&profileTitleStyle);
  lv_style_set_bg_opa(&profileTitleStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_text_font(&profileTitleStyle, LV_STATE_DEFAULT, &lv_font_montserrat_20);

  //Title
  lv_obj_t *profileTitleLabel = lv_label_create(profileScreen, NULL);
  setupLabel(profileTitleLabel, -75, -80, &profileTitleStyle);
  lv_label_set_text(profileTitleLabel, "#ffffff Personal Info#");
  
  //User Name
  lv_obj_t *nameLabel = lv_label_create(profileScreen, NULL); 
  String nameString = "#ffffff " + userName + "#";
  setupLabel(nameLabel, -80, -40, &profileLabelStyle);
  lv_label_set_text(nameLabel, nameString.c_str());
  

  //User Age
  lv_obj_t *ageLabel = lv_label_create(profileScreen, NULL);
  setupLabel(ageLabel, -80, -20, &profileLabelStyle);
  lv_label_set_text_fmt(ageLabel, "#ffffff Age: %d#", userAge);

  //User Height
  lv_obj_t *heightLabel = lv_label_create(profileScreen, NULL);
  setupLabel(heightLabel, -80, 0, &profileLabelStyle);
  lv_label_set_text_fmt(heightLabel, "#ffffff Height: %d cm#", userHeight);

  //User Weight
  lv_obj_t *weightLabel = lv_label_create(profileScreen, NULL);
  setupLabel(weightLabel, -80, 20, &profileLabelStyle);
  lv_label_set_text_fmt(weightLabel, "#ffffff Weight: %d kg#", userWeight);

  //User BMI
  lv_obj_t *bmiLabel = lv_label_create(profileScreen, NULL);
  setupLabel(bmiLabel, -80, 40, &profileLabelStyle);
  lv_label_set_text_fmt(bmiLabel, "#ffffff BMI: %.1f#", userBmi);

  //User Gender
  lv_obj_t *genderLabel = lv_label_create(profileScreen, NULL);
  setupLabel(genderLabel, -80, 60, &profileLabelStyle);
  if (userGender == "Male") {
    String genderText = "#ffffff Gender: Male#";
    lv_label_set_text(genderLabel, genderText.c_str());
  }
  else {
    String genderText = "#ffffff Gender: Female#";
    lv_label_set_text(genderLabel, genderText.c_str());
  }

  //Edit Button
  lv_obj_t *editButton = lv_btn_create(profileScreen, NULL);
  lv_obj_set_event_cb(editButton, editBtnEventHandler);
  lv_obj_align(editButton, NULL, LV_ALIGN_CENTER, 60, 100);
  lv_obj_set_size(editButton, 110, 35);

  lv_obj_t *editButtonLabel = lv_label_create(editButton, NULL);
  lv_label_set_text(editButtonLabel, "Edit User Info");

  //Battery
  setupBattery(profileScreen);
  setupWifiIcon(profileScreen);
  setupMenuBar(profileScreen);
}

void getUserInformation(void) {
  struct UserInfo info;
  EEPROM.get(0, info);
  
  userName = info.userName;
  userAge = info.userAge; 
  userHeight = info.userHeight;
  userWeight = info.userWeight; 
  userTargetSteps = info.targetSteps;
  userBmi = userWeight / pow((userHeight * 0.01), 2);
  userGender = info.userGender;
  setDistanceCovered();
  setCaloriesBurned();
  Serial.printf("Calories: %.8f", caloriesMultiplier);
  Serial.printf("Step length: %.8f", stepLength);
}

static void editBtnEventHandler(lv_obj_t *obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
      lv_obj_clean(profileScreen);
      setupProfileInputPage();
      lv_scr_load(profileInputScreen);
  }
}

void setDistanceCovered(void){
  if (userGender == "Male") {
    stepLength = ((userHeight * 0.01) * 0.415) * 0.001; 
  }
  else {
    stepLength = ((userHeight * 0.01) * 0.413)* 0.001;
  }
}

void setCaloriesBurned(void){
  float BMR;
  if (userGender == "Male") {
    BMR = (13.75 * userWeight) + (5 * userHeight) - (6.76 * userAge) + 66; 
    caloriesMultiplier = BMR * 0.0000245;
  }
  else {
    BMR = (9.56 * userWeight) + (1.85 * userHeight) - (4.68 * userAge) + 655; 
    caloriesMultiplier = BMR * 0.0000269;
  }
  
}
