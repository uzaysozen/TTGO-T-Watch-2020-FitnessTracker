#include "config.h"

lv_obj_t *exerciseList;

void setupPastExercisesPage(void){

    /*Create a list*/
    exerciseList = lv_list_create(pastExercisesScreen, NULL);
    lv_obj_set_size(exerciseList, 220, 200);
    lv_obj_align(exerciseList, NULL, LV_ALIGN_CENTER, 0, 15);

    setupBattery(pastExercisesScreen);
    setupWifiIcon(pastExercisesScreen);
    setupMenuBar(pastExercisesScreen);
}
