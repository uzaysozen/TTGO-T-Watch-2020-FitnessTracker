#include "config.h"

static lv_obj_t *kb;

lv_obj_t *nameTextArea;
lv_obj_t *ageTextArea;
lv_obj_t *heightTextArea;
lv_obj_t *weightTextArea;
lv_obj_t *targetTextArea;
lv_obj_t *genderRoller;

lv_style_t buttonLabelStyle;

static void textAreaEventHandler(lv_obj_t *ta, lv_event_t event);
static void saveBtnEventHandler(lv_obj_t *obj, lv_event_t event);
static void keyboardEventHandler(lv_obj_t *keyboard, lv_event_t event);
static void genderRollerEventHandler(lv_obj_t *obj, lv_event_t event);
void setupTextArea(lv_obj_t *text_area, int x, int y, int w, int h);

void setupProfileInputPage(void){
  // Name text area
  nameTextArea = lv_textarea_create(profileInputScreen, NULL);
  setupTextArea(nameTextArea, 25, -80, LV_HOR_RES / 2, LV_VER_RES / 6 - 10);
  lv_textarea_set_text(nameTextArea, userName.c_str());

  // Name Label
  lv_obj_t * nameLabel = lv_label_create(profileInputScreen, NULL);
  lv_label_set_recolor(nameLabel, true);
  lv_label_set_text(nameLabel, "#ffffff Name:#");
  lv_obj_align(nameLabel, nameTextArea, LV_ALIGN_CENTER, -115, 0);

  // Age text area
  ageTextArea = lv_textarea_create(profileInputScreen, NULL);
  setupTextArea(ageTextArea, 25, -50, LV_HOR_RES / 4, LV_VER_RES / 6 - 10);
  char ageText[30];
  itoa(userAge, ageText, 10);
  lv_textarea_set_text(ageTextArea, ageText);

  // Age Label
  lv_obj_t * ageLabel = lv_label_create(profileInputScreen, NULL);
  lv_label_set_recolor(ageLabel, true);
  lv_label_set_text(ageLabel, "#ffffff Age:#");
  lv_obj_align(ageLabel, ageTextArea, LV_ALIGN_CENTER, -120, 0);

  // Height text area
  heightTextArea = lv_textarea_create(profileInputScreen, NULL);
  setupTextArea(heightTextArea, 25, -20, LV_HOR_RES / 4, LV_VER_RES / 6 - 10);
  char heightText[30];
  itoa(userHeight, heightText, 10);
  lv_textarea_set_text(heightTextArea, heightText);

  // Height Label
  lv_obj_t * heightLabel = lv_label_create(profileInputScreen, NULL);
  lv_label_set_recolor(heightLabel, true);
  lv_label_set_text(heightLabel, "#ffffff Height:#");
  lv_obj_align(heightLabel, heightTextArea, LV_ALIGN_CENTER, -110, 0);

  // Weight text area
  weightTextArea = lv_textarea_create(profileInputScreen, NULL);
  setupTextArea(weightTextArea, 25, 10, LV_HOR_RES / 4, LV_VER_RES / 6 - 10);
  char weightText[30];
  itoa(userWeight, weightText, 10);
  lv_textarea_set_text(weightTextArea, weightText);

  // Weight Label
  lv_obj_t * weightLabel = lv_label_create(profileInputScreen, NULL);
  lv_label_set_recolor(weightLabel, true);
  lv_label_set_text(weightLabel, "#ffffff Weight:#");
  lv_obj_align(weightLabel, weightTextArea, LV_ALIGN_CENTER, -110, 0);

  // Target Steps text area
  targetTextArea = lv_textarea_create(profileInputScreen, NULL);
  setupTextArea(targetTextArea, 25, 40, LV_HOR_RES / 4, LV_VER_RES / 6 - 10);
  char targetText[30];
  itoa(userTargetSteps, targetText, 10);
  lv_textarea_set_text(targetTextArea, targetText);

  // Target Steps Label
  lv_obj_t * targetLabel = lv_label_create(profileInputScreen, NULL);
  lv_label_set_recolor(targetLabel, true);
  lv_label_set_text(targetLabel, "#ffffff Target Steps:#");
  lv_obj_align(targetLabel, targetTextArea, LV_ALIGN_CENTER, -90, 0);

  // Gender Roller
  genderRoller = lv_roller_create(profileInputScreen, NULL);
  lv_roller_set_options(genderRoller,
                      "Male\n"
                      "Female",
                      LV_ROLLER_MODE_INIFINITE);

  lv_roller_set_visible_row_count(genderRoller, 1);
  lv_obj_align(genderRoller, NULL, LV_ALIGN_CENTER, 0, 80);
  lv_obj_set_event_cb(genderRoller, genderRollerEventHandler);
  if (userGender == "Male") {
    lv_roller_set_selected(genderRoller, 0, LV_ANIM_ON);
  }
  else {
    lv_roller_set_selected(genderRoller, 1, LV_ANIM_ON);
  }

  // Gender Label
  lv_obj_t *genderLabel = lv_label_create(profileInputScreen, NULL);
  lv_label_set_recolor(genderLabel, true);
  lv_label_set_text(genderLabel, "#ffffff Gender:#");
  lv_obj_align(genderLabel, genderRoller, LV_ALIGN_CENTER, -80, 0);

  lv_style_init(&buttonLabelStyle);
  lv_style_set_bg_opa(&buttonLabelStyle, LV_STATE_DEFAULT, LV_OPA_0);
  lv_style_set_text_font(&buttonLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_12);

  //Save Button
  lv_obj_t *saveButton = lv_btn_create(profileInputScreen, NULL);
  lv_obj_set_event_cb(saveButton, saveBtnEventHandler);
  lv_obj_align(saveButton, NULL, LV_ALIGN_CENTER, 120, 90);
  //lv_btn_set_fit2(saveButton, LV_FIT_TIGHT, LV_FIT_TIGHT);
  lv_obj_set_size(saveButton, 45, 30);

  lv_obj_t *saveButtonLabel = lv_label_create(saveButton, NULL);
  lv_obj_add_style(saveButtonLabel, LV_OBJ_PART_MAIN, &buttonLabelStyle);
  lv_label_set_text(saveButtonLabel, "Save");
    
  //Battery
  setupBattery(profileInputScreen);
  setupWifiIcon(profileInputScreen);
  setupMenuBar(profileInputScreen);
}

static void saveBtnEventHandler(lv_obj_t *obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
      
      char genderValue[6];
      lv_roller_get_selected_str(genderRoller, genderValue, sizeof(genderValue));
      // storing user info to flash memory
      struct UserInfo user;
      strcpy(user.userName, lv_textarea_get_text(nameTextArea));
      user.userAge = atoi(lv_textarea_get_text(ageTextArea));
      user.userHeight = atoi(lv_textarea_get_text(heightTextArea));
      user.userWeight = atoi(lv_textarea_get_text(weightTextArea));
      user.targetSteps = atoi(lv_textarea_get_text(targetTextArea));
      strcpy(user.userGender, genderValue);
      EEPROM.put(0, user); 
      EEPROM.commit();
      
      lv_obj_clean(profileInputScreen);
      setupProfilePage();
      lv_scr_load(profileScreen);
      getUserInformation();
  }
}

static void textAreaEventHandler(lv_obj_t * ta, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
      if (kb != NULL) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_del(kb);
        kb = NULL;
      }
      /* Create a keyboard */
      kb = lv_keyboard_create(profileInputScreen, NULL);
      if (ta != nameTextArea) {
        lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUM);
      } else {
        lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_TEXT_UPPER);
      }
      lv_obj_set_size(kb,  LV_HOR_RES, LV_VER_RES / 2);
    
      //lv_keyboard_set_textarea(kb, oneline_ta); /* Focus it on one of the text areas to start */
      lv_keyboard_set_cursor_manage(kb, true); /* Automatically show/hide cursors on text areas */
      lv_obj_set_event_cb(kb, keyboardEventHandler);
      /* Focus on the clicked text area */
      lv_keyboard_set_textarea(kb, ta);
    }

    else if(event == LV_EVENT_INSERT) {
      const char * str = lv_textarea_get_text(ta);
      if(str[0] == '\n') {
          printf("Ready\n");
      }
    }
}

static void keyboardEventHandler(lv_obj_t * keyboard, lv_event_t event)
{
    lv_keyboard_def_event_cb(kb, event);
    if(event == LV_EVENT_CANCEL) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_del(kb);
        kb = NULL;
    } else if (event == LV_EVENT_APPLY){
      lv_keyboard_set_textarea(kb, NULL);
      lv_obj_del(kb);
      kb = NULL;
    }
}

static void genderRollerEventHandler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        printf("Selected gender: %s\n", buf);
    }
}

void setupTextArea(lv_obj_t *text_area, int x, int y, int w, int h) {
  lv_textarea_set_text(text_area, "");
  lv_textarea_set_pwd_mode(text_area, false);
  lv_textarea_set_cursor_hidden(text_area, true);
  lv_textarea_set_one_line(text_area, true);
  lv_obj_set_width(text_area, w);
  lv_obj_set_height(text_area, h);
  lv_obj_align(text_area, NULL, LV_ALIGN_CENTER, x, y);
  lv_obj_set_event_cb(text_area, textAreaEventHandler);
}
