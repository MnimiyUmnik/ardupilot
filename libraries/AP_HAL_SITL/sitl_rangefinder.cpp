/*
  SITL handling

  This simulates a rangefinder

 */

#include <AP_HAL/AP_HAL.h>
#if CONFIG_HAL_BOARD == HAL_BOARD_SITL && !defined(HAL_BUILD_AP_PERIPH)

#include "AP_HAL_SITL.h"
#include "AP_HAL_SITL_Namespace.h"
#include "HAL_SITL_Class.h"
#include "SITL_State.h"
#include <SITL/SITL.h>
#include <AP_Math/AP_Math.h>

extern const AP_HAL::HAL& hal;
float last_voltage = 0;
float last_time = 0;
float last_time_range = 0;
float random_pause = 0;
float rand_offset_range = 10;
float real_pause = 0;
using namespace HALSITL;
struct TableEntry {
    int outcome;
    float probability;
};

struct TableEntry prob_table[] = {
    
    {40, 0.163},
    {60, 0.235},
    {80, 0.17},
    {100, 0.133},
    {120, 0.096},
    {140, 0.083},
    {160, 0.054},
    {180, 0.040},
    {200, 0.026}
    
    
    /*
    {20, 0.016},
    {40, 0.17},
    {60, 0.17},
    {80, 0.17},
    {100, 0.263},
    {120, 0.066},
    {140, 0.066},
    {160, 0.04},
    {180, 0.026},
    {200, 0.013}
    */
};

// returns a voltage between 0V to 5V which should appear as the
// voltage from the sensor
float SITL_State::_sonar_pin_voltage() const
{


    
    // Use glitch defines as the probablility between 0-1 that any
    // given sonar sample will read as max distance
    /*
    if (!is_zero(_sitl->sonar_glitch) &&
        _sitl->sonar_glitch >= (rand_float() + 1.0f) / 2.0f) {
        // glitched
        return 5.0f;
    }    
    */

    
    if (AP_HAL::millis() - last_time_range > 20000) {
        last_time_range = AP_HAL::millis();
        rand_offset_range = ((rand_float() + 1) / 2) *10;
    }


    const float altitude = sitl_model->rangefinder_range() + rand_offset_range;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
    if (altitude == INFINITY) {
        return last_voltage;
        //return 5.0f;
    }
#pragma GCC diagnostic pop

    // Altitude in in m, scaler in meters/volt
    float voltage = altitude / _sitl->sonar_scale;
    //dead noise when radar
    if (constrain_float(voltage, 0.0f, 5.0f) >= 4.5f){
        voltage = 0.01;

    }

     


    /*if (constrain_float(voltage, 0.0f, 5.0f) >= 4.5f){
        if (!is_zero(_sitl->sonar_glitch) &&
        _sitl->sonar_glitch*10 >= (rand_float() + 1.0f) / 2.0f) {
        // glitched
            float max_min = rand_float();
            if (max_min <= 0.33f) {
                return last_voltage;

            }
           
            

            //return 4.0f;
        }




    }*/

    float random_value = 0;
    float cumulativeProbability = 0.0;
    //AP_HAL::millis() - last_pwm_input
    real_pause = AP_HAL::millis() - last_time;
    if (AP_HAL::millis() - last_time > random_pause) {
        
        random_value = (rand_float() + 1) / 2; // Generate a random number between 0 and 1
        float random_offset = (rand_float()*6);
        

        for (int i = 0; i < 9; i++) {
            cumulativeProbability += prob_table[i].probability;
            if (random_value <= cumulativeProbability) {
                random_pause =  prob_table[i].outcome;
                random_pause = random_pause + random_offset;
                break;
        }
    }



        last_time = AP_HAL::millis();
        
        
        float voltage_with_noise = voltage + rand_float()*0.005;
        last_voltage = constrain_float(voltage_with_noise, 0.0f, 5.0f);
        //printf("random_pause: %.1f , random_value: %.3f \n", random_pause, random_value);
        //printf("real_pause: %.1f \n", real_pause);

        
        


    }

    
    
    return last_voltage;
}

/*
  setup the rangefinder with new input
 */
void SITL_State::_update_rangefinder()
{
    sonar_pin_value = 1023 * (_sonar_pin_voltage() / 5.0f);
}

#endif
