#include "liblwm2m.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LWM2M_TEMPERATURE_OBJECT_ID   3303
#define LWM2M_TEMPERATURE_SENSOR_UNITS  "Celsius"
#define LWM2M_TEMPERATURE_LOCATION      "Shenzhen,China" 


#define RES_SENSOR_MIN          5601
#define RES_SENSOR_MAX          5602
#define RES_SENSOR_MIN_RANGE    5603
#define RES_SENSOR_MAX_RANGE    5604
#define RES_SENSOR_RESET        5605
#define RES_SENSOR_VALUE        5700
#define RES_SENSOR_UNITS        5701
#define RES_SENSOR_LOCATION     5702

void get_temperature(float *temp);
                             
static uint8_t prv_set_value(lwm2m_data_t * dataP) 
{
    float temp =0;
    // a simple switch structure is used to respond at the specified resource asked
    switch (dataP->id) {
    case RES_SENSOR_VALUE:
        get_temperature(&temp);
        lwm2m_data_encode_float(temp, dataP);
        return COAP_205_CONTENT ;

    case RES_SENSOR_UNITS:
        lwm2m_data_encode_string(LWM2M_TEMPERATURE_SENSOR_UNITS, dataP);
        return COAP_205_CONTENT ;

    case RES_SENSOR_MIN:
    case RES_SENSOR_MAX:
    case RES_SENSOR_RESET:   
        lwm2m_data_encode_string("Not Support!", dataP);
        return COAP_205_CONTENT ;    
    case RES_SENSOR_MIN_RANGE:
        lwm2m_data_encode_float(-55, dataP);
        return COAP_205_CONTENT ;
    case RES_SENSOR_MAX_RANGE:
        lwm2m_data_encode_float(125, dataP);
        return COAP_205_CONTENT ;          
    //case RES_SENSOR_LOCATION:
    //    lwm2m_data_encode_string(LWM2M_TEMPERATURE_LOCATION, dataP);
    //    return COAP_205_CONTENT ;  
    default:
        return COAP_404_NOT_FOUND ;
    }
}

static uint8_t prv_temperature_read(uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP) {
    uint8_t result;
    int i;

    // this is a single instance object
    if (instanceId != 0) {
        return COAP_404_NOT_FOUND ;
    }

    // is the server asking for the full object ?
    if (*numDataP == 0) {

        uint16_t resList[] = { RES_SENSOR_VALUE, RES_SENSOR_UNITS, };
        
        int nbRes = sizeof(resList) / sizeof(uint16_t);

        *dataArrayP = lwm2m_data_new(nbRes);
        if (*dataArrayP == NULL)
            return COAP_500_INTERNAL_SERVER_ERROR ;
            
        *numDataP = nbRes;
        for (i = 0; i < nbRes; i++) {
            (*dataArrayP)[i].id = resList[i];
        }
    }

    i = 0;
    do {
        result = prv_set_value((*dataArrayP) + i);
        i++;
    } while (i < *numDataP && result == COAP_205_CONTENT );

    return result;
}


lwm2m_object_t * get_object_temperature() {
    /*
     * The get_object_tem function create the object itself and return a pointer to the structure that represent it.
     */
    lwm2m_object_t * temperatureObj = (lwm2m_object_t *) lwm2m_malloc(sizeof(lwm2m_object_t));

    if (NULL != temperatureObj) {
        memset(temperatureObj, 0, sizeof(lwm2m_object_t));

        /*
         * It assigns his unique ID
         * The 3313 is the standard ID for the mandatory object "IPSO Accelerometer".
         */
        temperatureObj->objID = LWM2M_TEMPERATURE_OBJECT_ID;

        /*
         * there is only one instance of accelerometer on the Application Board for mbed NXP LPC1768.
         *
         */
        temperatureObj->instanceList = (lwm2m_list_t *) lwm2m_malloc(sizeof(lwm2m_list_t));
        if (NULL != temperatureObj->instanceList) {
            memset(temperatureObj->instanceList, 0, sizeof(lwm2m_list_t));
        } else {
            lwm2m_free(temperatureObj);
            return NULL;
        }

        /*
         * And the private function that will access the object.
         * Those function will be called when a read/write/execute query is made by the server. In fact the library don't need to
         * know the resources of the object, only the server does.
         */
        temperatureObj->readFunc = prv_temperature_read;
        temperatureObj->writeFunc = NULL;
        temperatureObj->executeFunc = NULL;
        temperatureObj->userData = NULL;
        

    }

    return temperatureObj;
}
