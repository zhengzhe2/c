#include "convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TouchConvert.h"
#include "KeyConvert.h"

static void initData(struct ST_FIXATION_KEY_CODE* data) 
{  
    if (data) {
        data->freq_push = 0;
        data->fix_key_code = 0;
        data->key_type = 0;
        data->operate_info = 0;
        data->touch_coord.curr_state = 0;
        data->touch_coord.touch_id  = 0;
        data->touch_coord.x = 0;
        data->touch_coord.y = 0;
        data->touch_status.gesture_type = 0;
        data->touch_status.touch_info = 0;
        data->touch_status.touch_numb = 0;
        data->touch_status.pos_1.curr_state = 0;
        data->touch_status.pos_1.touch_id = 0;
        data->touch_status.pos_1.x = 0;
        data->touch_status.pos_1.y = 0;
        data->touch_status.pos_2.curr_state = 0;
        data->touch_status.pos_2.touch_id = 0;
        data->touch_status.pos_2.x = 0;
        data->touch_status.pos_2.y = 0;
        data->touch_status.pos_3.curr_state = 0;
        data->touch_status.pos_3.touch_id = 0;
        data->touch_status.pos_3.x = 0;
        data->touch_status.pos_3.y = 0;
        data->touch_status.pos_4.curr_state = 0;
        data->touch_status.pos_4.touch_id = 0;
        data->touch_status.pos_4.x = 0;
        data->touch_status.pos_4.y = 0;
        data->touch_status.pos_5.curr_state = 0;
        data->touch_status.pos_5.touch_id = 0;
        data->touch_status.pos_5.x = 0;
        data->touch_status.pos_5.y = 0;
    }
}

static void convertByDevice(struct ST_FIXATION_KEY_CODE* data, const char* device, cJSON* json)
{
    if (strcmp("\"touch\"", device) == 0) { 
        printf("convertByDevice device %s-----------\n", device);
        data->touch_status.pos_1.curr_state = TouchConvert::instance()->getType(json);
        data->touch_status.pos_1.x = TouchConvert::instance()->getCoordinateX(json);
        data->touch_status.pos_1.y = TouchConvert::instance()->getCoordinateY(json);  
    }
    else {           
        data->key_type = KeyConvert::instance()->findKeyDevice(device);
        data->fix_key_code = KeyConvert::instance()->getValueKey(json);   
    }   
}

static void packageData(struct ST_FIXATION_KEY_CODE* data)
{

}

void convert(struct ST_FIXATION_KEY_CODE* data, const char* buf)
{
    cJSON* json, *subJson;
    char* out;

    initData(data);
    json = cJSON_Parse(buf);
    if (!json) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }
    else {
        subJson = cJSON_GetObjectItem(json, "device");
        out = cJSON_Print(subJson);
        convertByDevice(data, out, json);
    }

    cJSON_Delete(json);
    free(out);

    printf("kt:%d fk:%d state:%d x:%d y:%d\n",data->key_type, data->fix_key_code,
        data->touch_status.pos_1.curr_state, data->touch_status.pos_1.x, data->touch_status.pos_1.y);
        
    // packageData(data);
}