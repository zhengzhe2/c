#include "KeyConvert.h"

static KeyConvert* kc = NULL;

KeyConvert* KeyConvert::instance()
{
    if (kc == NULL) {
        kc = new KeyConvert();
    }
    return kc;
}

KeyConvert::KeyConvert()
{
    m_keyDevice["\"none\""] = 0;
    m_keyDevice["\"hard\""] = 1;
    m_keyDevice["\"rotary\""] = 2;
    m_keyDevice["\"wired\""] = 4;
    m_keyDevice["\"remote\""] = 7;
    m_keyDevice["\"panel\""] = 8;
    m_keyDevice["\"infrared\""] = 9;    
}

KeyConvert::~KeyConvert()
{
    delete(kc);
    kc = NULL;
}

int KeyConvert::getValueKey(cJSON* json)
{
    if (!json) {
        return 0;
    }
    cJSON* subJson, *iJson;
    char* key;
    int size, iKey;

    subJson = cJSON_GetObjectItem(json, "value");
    if (!subJson) {
        return 0;
    }
    size = cJSON_GetArraySize(subJson);

    if (size != 1) {
        return -1;
    }
    else {
        iJson = cJSON_GetArrayItem(subJson, 0);
        if (!iJson) {
            return 0;
        }
        key = cJSON_Print(iJson);  
        iKey = atoi(key);
        free(key);
        return iKey;
    }
}

int KeyConvert::findKeyDevice(const char* device)
{
    if (!device) {
        return 0;
    }
    int keyType = 0;
    for (std::map<const char*, int>::iterator it = m_keyDevice.begin();
        it != m_keyDevice.end(); ++it) {
            if (strcmp(device, it->first) == 0) {
                keyType = it->second;
                break;
            }
    }
    return keyType; 
}


