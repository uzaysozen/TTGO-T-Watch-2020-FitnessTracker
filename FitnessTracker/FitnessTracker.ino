// FitnessTracker.ino
#include "config.h"

//initialize watch and bma sensor
TTGOClass *watch;
BMA *sensor;
AXP20X_Class *power;
PCF8563_Class *rtc;
TFT_eSPI *tft;


//initialize all screens
lv_obj_t *homeScreen;
lv_obj_t *exerciseScreen;
lv_obj_t *profileScreen;
lv_obj_t *profileInputScreen;
lv_obj_t *pastExercisesScreen;
lv_obj_t *screens[4];
lv_obj_t *batteryLabel;
lv_obj_t *wifiLabel;
lv_obj_t *menuBar;

//initialize styles
lv_style_t mainStyle;
lv_style_t batteryStyle;
lv_style_t menuBarStyle;

bool irq = false; // value to track bma sensor interrupt
int screenIndex = 1; // index of the current screen
int stepCount; // current step count
int lastStepCount = 0;
bool lenergy = false;
const char* userActivity;

static void swipeEventHandler(lv_obj_t *obj, lv_event_t event); // event handler for swipes

void setup()
{
    Serial.begin(115200);

    EEPROM.begin(EEPROM_SIZE);
    // Get TTGOClass instance
    watch = TTGOClass::getWatch();

    // Initialize the hardware, the BMA423 sensor has been initialized internally
    watch->begin();

    // Turn on the backlight
    watch->lvgl_begin();

    //Receive objects for easy writing
    sensor = watch->bma;
    rtc = watch->rtc;
    tft = watch->tft;

    power = watch->power;

    power->adc1Enable(
        AXP202_VBUS_VOL_ADC1 |
        AXP202_VBUS_CUR_ADC1 |
        AXP202_BATT_CUR_ADC1 |
        AXP202_BATT_VOL_ADC1,
        true);

    // Accel parameter structure
    Acfg cfg;
    cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
    cfg.range = BMA4_ACCEL_RANGE_2G;
    cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
    cfg.perf_mode = BMA4_CONTINUOUS_MODE;

    // Configure the BMA423 accelerometer
    sensor->accelConfig(cfg);

    // Enable BMA423 accelerometer
    // Warning : Need to use steps, you must first enable the accelerometer
    sensor->enableAccel();

    pinMode(BMA423_INT1, INPUT);
    attachInterrupt(BMA423_INT1, [] {
        // Set interrupt to set irq value to 1
        irq = 1;
    }, RISING); //It must be a rising edge

    // Enable BMA423 step count feature
    sensor->enableFeature(BMA423_STEP_CNTR, true);

    // Reset steps
    sensor->resetStepCounter();

    // Turn on step interrupt
    sensor->enableStepCountInterrupt();

    getUserInformation();

    // ----------HOME PAGE SETUP---------------------------------------------------
    
    lv_style_init(&mainStyle);
    lv_style_set_bg_color(&mainStyle, LV_STATE_DEFAULT, lv_color_hex(0x0F0129));
    lv_style_set_bg_opa(&mainStyle, LV_STATE_DEFAULT, LV_OPA_COVER);

    lv_style_init(&menuBarStyle);
    lv_style_set_bg_color(&menuBarStyle, LV_STATE_DEFAULT, lv_color_hex(0x000000));
    lv_style_set_bg_opa(&menuBarStyle, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_border_width(&menuBarStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_border_color(&menuBarStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_border_side(&menuBarStyle, LV_STATE_DEFAULT, LV_BORDER_SIDE_BOTTOM);

    homeScreen = lv_obj_create(NULL, NULL); //create home screen
    lv_obj_add_style(homeScreen, LV_OBJ_PART_MAIN, &mainStyle);  
    lv_obj_set_event_cb(homeScreen, swipeEventHandler); 
    lv_scr_load(homeScreen);
    setupScreen(homeScreen);

    // ----------EXERCISE PAGE SETUP---------------------------------------------------

    exerciseScreen = lv_obj_create(NULL, NULL); //create exercise screen
    lv_obj_add_style(exerciseScreen, LV_OBJ_PART_MAIN, &mainStyle);  
    lv_obj_set_event_cb(exerciseScreen, swipeEventHandler);

    // ----------PROFILE PAGE SETUP---------------------------------------------------

    profileScreen = lv_obj_create(NULL, NULL); //create profile screen
    lv_obj_add_style(profileScreen, LV_OBJ_PART_MAIN, &mainStyle);  
    lv_obj_set_event_cb(profileScreen, swipeEventHandler);

    // ----------PROFILE INPUT PAGE SETUP---------------------------------------------------

    profileInputScreen = lv_obj_create(NULL, NULL); //create profile input screen
    lv_obj_add_style(profileInputScreen, LV_OBJ_PART_MAIN, &mainStyle);  
    lv_obj_set_event_cb(profileInputScreen, swipeEventHandler);

    // ----------PAST EXERCISES PAGE SETUP---------------------------------------------------

    pastExercisesScreen = lv_obj_create(NULL, NULL); //create past exe screen
    lv_obj_add_style(pastExercisesScreen, LV_OBJ_PART_MAIN, &mainStyle);  
    lv_obj_set_event_cb(pastExercisesScreen, swipeEventHandler);

    // ordering main screens
    screens[0] = profileScreen;
    screens[1] = homeScreen;
    screens[2] = exerciseScreen;
    screens[3] = pastExercisesScreen;
    
    // adding style of the battery icon and percentage
    lv_style_init(&batteryStyle);
    lv_style_set_bg_opa(&batteryStyle, LV_STATE_DEFAULT, LV_OPA_0);
    lv_style_set_text_font(&batteryStyle, LV_STATE_DEFAULT, &lv_font_montserrat_12_subpx);
    lv_style_set_text_color(&batteryStyle, LV_STATE_DEFAULT, lv_color_hex(0x00FF00));

    //setting date and time manually
    //watch->rtc->setDateTime(2022,5,16,2,50,00);
    //Clear lvgl counter
    lv_disp_trig_activity(NULL);

    //When the initialization is complete, turn on the backlight
    watch->openBL();

    setupNetwork();
}

void loop()
{   
    power->readIRQ();
    //Serial.println(lv_disp_get_inactive_time(NULL));
    if (power->isPEKShortPressIRQ()) {
        power->clearIRQ();
        lenergy = !lenergy;
        low_energy(lenergy);
    }
    if (irq) {
      irq = 0;
      bool  rlst;
      do {
          // Read the BMA423 interrupt status,
          // need to wait for it to return to true before continuing
          rlst =  sensor->readInterrupt();
      } while (!rlst);

      // Check if it is a step interrupt
      if (sensor->isStepCounter()) {
          // Get step data from register
          updateStepCounter();
          
          if (lv_scr_act() == homeScreen) { // home screen modifications
            updateStepPercentage(); // update percentage value
          }
          else if (lv_scr_act() == exerciseScreen) { // exercise screen modifications
            lv_label_set_text_fmt(distanceLabel, "#ffffff Distance Covered: %.2f km#", (stepCount * stepLength)); // update distance
            lv_label_set_text_fmt(caloriesLabel, "#ffffff Calories Burned: %.1f Cal#", (stepCount * caloriesMultiplier)); // update calories
            lv_label_set_text_fmt(stepCountLabel, "#ffffff Step Count: %d#", stepCount); // update step count
          }
          Serial.println(stepCount);
        }
    }
  
    if (lv_scr_act() == homeScreen) { // home screen modifications
      displayTime(); // display current time
    }
        
    displayBattery();
    //Serial.println(wifiStatus);
    
    checkWifi();
      
    if (lv_disp_get_inactive_time(NULL) < DEFAULT_SCREEN_TIMEOUT) {
      lv_task_handler();// handle lvgl components
    } else {
      low_energy(true);
    }
    power->clearIRQ();
    delay(20);
}

void low_energy(bool activity)
{
    lenergy = activity; 
    if (activity) {
        watch->closeBL();
        watch->stopLvglTick();
        sensor->enableStepCountInterrupt(false);
        watch->displaySleep();
        if (!WiFi.isConnected()) {
            WiFi.mode(WIFI_OFF);
            Serial.println("ENTER IN LIGHT SLEEEP MODE");
            gpio_wakeup_enable ((gpio_num_t)AXP202_INT, GPIO_INTR_LOW_LEVEL);
            gpio_wakeup_enable ((gpio_num_t)BMA423_INT1, GPIO_INTR_HIGH_LEVEL);
            esp_sleep_enable_gpio_wakeup ();
            esp_light_sleep_start();
        }
    } else {
        Serial.println("Start tick!");
        watch->startLvglTick();
        watch->displayWakeup();
        watch->rtc->syncToSystem();
        lv_disp_trig_activity(NULL);
        watch->openBL();
        sensor->enableStepCountInterrupt();
    }
}

void updateStepCounter(void) {
  stepCount = sensor->getCounter();
  stepCount -= lastStepCount;
}

bool resetStepCounter(void) {
  lastStepCount += stepCount;
  updateStepCounter();
}

/* Function to display and update battery level*/
void displayBattery(void) {
  // Display Battery Level
  int per = power->getBattPercentage();
  //Serial.printf("Battery Level: %d%%\n", per); 
  if (power->isVBUSPlug()) {
    if (per < 100) {
      lv_label_set_text_fmt(batteryLabel, LV_SYMBOL_CHARGE " %d%%", per);
    }
    else {
      lv_label_set_text_fmt(batteryLabel, LV_SYMBOL_BATTERY_FULL " %d%%", per);
    }
  }
  else {
    if (per > 85) {
      lv_label_set_text_fmt(batteryLabel, LV_SYMBOL_BATTERY_FULL " %d%%", per);
    }
    else if (per > 65) {
       lv_label_set_text_fmt(batteryLabel, LV_SYMBOL_BATTERY_3 " %d%%", per);
    }
    else if (per > 45) {
       lv_label_set_text_fmt(batteryLabel, LV_SYMBOL_BATTERY_2 " %d%%", per);
    }
    else if (per > 25) {
       lv_label_set_text_fmt(batteryLabel, LV_SYMBOL_BATTERY_1 " %d%%", per);
    }
    else {
      lv_label_set_text_fmt(batteryLabel, LV_SYMBOL_BATTERY_EMPTY " %d%%", per);
    }
  }
}

void checkWifi(void){
  if (WiFi.status() == WL_CONNECTED) {
    lv_label_set_text(wifiLabel, LV_SYMBOL_WIFI);
  } else {
    lv_label_set_text(wifiLabel, "");
  }
}

void setupWifiIcon(lv_obj_t *screen) {
  wifiLabel = lv_label_create(screen, NULL);
  lv_obj_add_style(wifiLabel, LV_OBJ_PART_MAIN, &batteryStyle);
  lv_label_set_recolor(wifiLabel, true);
  lv_obj_align(wifiLabel, NULL, LV_ALIGN_CENTER, -70, -110);
  lv_label_set_text(wifiLabel, "");
}

/* Function to setup battery view on given screen */
void setupBattery(lv_obj_t *screen){
  batteryLabel = lv_label_create(screen, NULL);
  lv_obj_add_style(batteryLabel, LV_OBJ_PART_MAIN, &batteryStyle);
  lv_label_set_recolor(batteryLabel, true);
  lv_obj_align(batteryLabel, NULL, LV_ALIGN_CENTER, 70, -110);
}

void setupMenuBar(lv_obj_t *screen) {
  menuBar = lv_obj_create(screen, NULL);
  lv_obj_set_size(menuBar, 260, 25);
  lv_obj_align(menuBar, NULL, LV_ALIGN_CENTER, 0, -110);
  lv_obj_add_style(menuBar, LV_OBJ_PART_MAIN, &menuBarStyle); 
}

/* Function to setup given screen */
void setupScreen(lv_obj_t *screen) {
  if (screen == homeScreen) {
    setupHomePage();
  }
  else if (screen == exerciseScreen) {
    setupExercisePage();
  }
  else if (screen == profileScreen) {
    setupProfilePage();
  }
  else if (screen == pastExercisesScreen) {
    setupPastExercisesPage();
  }
}

/* Callback to handle swipe event */
static void swipeEventHandler(lv_obj_t *obj, lv_event_t event)
{
    
    if (event == LV_EVENT_GESTURE) {
      if ((lv_scr_act() == homeScreen) || (lv_scr_act() == profileScreen) || (lv_scr_act() == exerciseScreen)|| (lv_scr_act() == pastExercisesScreen)) {
        int swipeDir = (int)lv_indev_get_gesture_dir(lv_indev_get_act()); // get swipe direction, left = 3, right = 2, down = 1, up = 0
        int screenSize = sizeof(screens)/sizeof(screens[0]); // number of screens
        Serial.printf("dir=%d\n", swipeDir);
        // prevent going beyond the given screens
        
        Serial.println("Swipe detected");
        if (swipeDir == 3) { 
          screenIndex -= 1;
          if (screenIndex < 0) {
            screenIndex = 0;
          }
          lv_obj_t *scr = screens[screenIndex];// get swiped screen
          lv_obj_clean(scr); // clean current screen
          setupScreen(scr); // setup new screen
          lv_scr_load(scr); // load new screen
          if (lv_scr_act() == pastExercisesScreen) {
            getExerciseData(exerciseList);
          }
          
        }
        else if(swipeDir == 2) {
          screenIndex += 1;
          if (screenIndex >= screenSize) {
            screenIndex = screenSize - 1;
          }
          lv_obj_t *scr = screens[screenIndex];// get swiped screen
          lv_obj_clean(scr); // clean current screen
          setupScreen(scr); // setup new screen
          lv_scr_load(scr); // load new screen
          
          if (lv_scr_act() == pastExercisesScreen) {
            getExerciseData(exerciseList);
          }
        }
      } 
   }
}

void setupLabel(lv_obj_t *label, int x, int y, lv_style_t *style){
  if (style) {
    lv_obj_add_style(label, LV_OBJ_PART_MAIN, style);
  }
  lv_label_set_recolor(label, true);
  lv_obj_align(label, NULL, LV_ALIGN_CENTER, x, y);
}
