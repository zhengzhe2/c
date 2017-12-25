#include "TouchConvert.h"

static TouchConvert* tc = NULL;

TouchConvert* TouchConvert::instance()
{
    if (tc == NULL) {
        tc = new TouchConvert();
    }
    return tc;
}

static int convertByStrType(const char* strType)
{
    int type = KEYDCD_TOUCH_INVALID;
    if (!strType) {
        return type;
    }
    if (strcmp(TOUCH_TYPE_DOWN, strType) == 0) {
        type = KEYDCD_TOUCH_DOWN;
    }
    else if (strcmp(TOUCH_TYPE_UP, strType) == 0) {
        type = KEYDCD_TOUCH_UP;
    }
    else if (strcmp(TOUCH_TYPE_MOVE, strType) == 0) {
        type = KEYDCD_TOUCH_MOVE;
    }
    else {
        type = KEYDCD_TOUCH_INVALID;
    } 

    return type;
}

static int getValueIntx(char* str)
{
    if (!str) {
        return 0;
    }
    char* pch = str;
    bool flag = false;
    char* substr = (char*)malloc(sizeof(char)*strlen(str));
    if (!substr) {
        return 0;
    }
    unsigned int i;
    int x;
    for (i = 0; i < strlen(str); ++i) {
        if ('[' == *pch) {
            pch++;
            flag = true;
            continue;
        }
        else if (',' == *pch) {
            substr[i-1] = '\0';
            break;
        }
        else {
            if (true == flag) {
                printf("pch = %c\n", *pch);
                substr[i-1] = *pch;
            }
        }
        pch++;
    }

    x = atoi(substr);
    free(substr);
    substr = NULL;
    return x;
}

static int getValueInty(char* str)
{
    if (!str) {
        return 0;
    }
    char* pch = str;
    char* substr = (char*)malloc(sizeof(char)*strlen(str));
    if (!substr) {
        return 0;
    }
    unsigned int i, l = 0;
    int y;
    bool flag = false;
    for (i = 0; i < strlen(str); ++i) {
        if ('[' == *pch) {
            pch++;
            ++l;
            continue;
        }
        else if (',' == *pch) {
            flag = true;
            pch++;
            ++l;
            continue;
        }
        else if (']' == *pch) {
            substr[i-l] = '\0';
            break;
        }
        else {
            if (flag == true) {
                substr[i-l] = *pch;
            }
            else {
                ++l;
            }
        }
        pch++;
    }

    y = atoi(substr);
    free(substr);
    substr = NULL;
    return y;
}



TouchConvert::TouchConvert()
{

}

TouchConvert::~TouchConvert()
{
    delete(tc);
    tc = NULL;
}

int TouchConvert::getType(cJSON* json)
{
    if (!json) {
        return 0;
    }
    cJSON* subJson;
    char* strType;
    int type;

    subJson = cJSON_GetObjectItem(json, "type");
    if (!subJson) {
        return 0;
    }
    strType = cJSON_Print(subJson);
    type = convertByStrType(strType);  
    free(strType);  
    return type;
}

int TouchConvert::getCoordinateX(cJSON* json)
{
    if (!json) {
        return 0;
    }
    cJSON* subJson, *iJson;
    char* point;
    int size, coordinateX;

    subJson = cJSON_GetObjectItem(json, "value");
    if (!subJson) {
        return 0;
    }
    size = cJSON_GetArraySize(subJson);

    if (size != 1) {
        return 0;
    }
    else {
        iJson = cJSON_GetArrayItem(subJson, 0);
        if (!iJson) {
            return 0;
        }
        point = cJSON_Print(iJson);  
        printf("point = %s\n", point);
        coordinateX = getValueIntx(point);
        free(point);
        return coordinateX;
    }
}

int TouchConvert::getCoordinateY(cJSON* json)
{
    if (json) {
        return 0;
    }
    cJSON* subJson, *iJson;
    char* point;
    int size, coordinateY;

    subJson = cJSON_GetObjectItem(json, "value");
    if (!subJson) {
        return 0;
    }
    size = cJSON_GetArraySize(subJson);

    if (size != 1) {
        return 0;
    }
    else {
        iJson = cJSON_GetArrayItem(subJson, 0);
        if (!iJson) {
            return 0;
        }
        point = cJSON_Print(iJson);  
        coordinateY = getValueInty(point); 
        free(point);
        return coordinateY; 
    }
}   



