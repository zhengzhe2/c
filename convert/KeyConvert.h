#ifndef KEYCONVERT
#define KEYCONVERT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include <map>  
using namespace std;

class KeyConvert
{
public:
    KeyConvert();
    ~KeyConvert();
    int getValueKey(cJSON* json);
    int findKeyDevice(const char* device);
    static KeyConvert* instance();
private:
    std::map<const char*, int> m_keyDevice;
};

#endif