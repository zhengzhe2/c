#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "jType.h"
#include "convert.h"

int main()
{
    // char buf[]="{\"device\":\"touch\",\n\"type\":\"down\",\n\"value\":[\n    [100,200]\n]}";
    // char buf[]="{\"device\":\"panel\"}";
    char buf[]="{\"device\":\"panel\",\n\"type\":\"none\",\n\"value\":[\n    45\n]}";
    struct ST_FIXATION_KEY_CODE* data = (struct ST_FIXATION_KEY_CODE*)malloc(sizeof(struct ST_FIXATION_KEY_CODE)) ;
    if (data) {
        convert(data, buf);
    }
   
    free(data);
    data = NULL;
    return 0;
}




