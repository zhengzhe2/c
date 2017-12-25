#ifndef TOUCHCONVERT
#define TOUCHCONVERT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "jType.h"

class TouchConvert
{
public:
    TouchConvert();
    ~TouchConvert();
    int getType(cJSON* json);
    int getCoordinateX(cJSON* json);
    int getCoordinateY(cJSON* json);
    static TouchConvert* instance();
};



#endif