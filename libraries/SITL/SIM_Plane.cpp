/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
  very simple plane simulator class. Not aerodynamically accurate,
  just enough to be able to debug control logic for new frame types
*/

#define ALLOW_DOUBLE_MATH_FUNCTIONS

#include "SIM_Plane.h"

#include <stdio.h>

using namespace SITL;

Plane::Prop prop0[30] = {
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 },
    { 000, 0.0001 }};

    Plane::Prop prop1[30] = {
    { 0.0, 0.293 },
    { 0.4, 0.290 },
    { 0.9, 0.287 },
    { 1.3, 0.284 },
    { 1.8, 0.280 },
    { 2.2, 0.275 },
    { 2.6, 0.270 },
    { 3.1, 0.264 },
    { 3.5, 0.257 },
    { 4.0, 0.250 },
    { 4.4, 0.242 },
    { 4.8, 0.234 },
    { 5.3, 0.225 },
    { 5.7, 0.215 },
    { 6.2, 0.203 },
    { 6.6, 0.192 },
    { 7.0, 0.180 },
    { 7.5, 0.168 },
    { 7.9, 0.155 },
    { 8.4, 0.143 },
    { 8.8, 0.130 },
    { 9.2, 0.116 },
    { 9.7, 0.103 },
    { 10.1, 0.089 },
    { 10.6, 0.075 },
    { 11.0, 0.060 },
    { 11.4, 0.045 },
    { 11.9, 0.031 },
    { 12.3, 0.015 },
    { 12.7, 0.000 }};

    Plane::Prop prop2[30] = {
    { 0.0, 1.171 },
    { 0.9, 1.162 },
    { 1.8, 1.151 },
    { 2.6, 1.138 },
    { 3.5, 1.121 },
    { 4.4, 1.102 },
    { 5.3, 1.081 },
    { 6.2, 1.057 },
    { 7.0, 1.030 },
    { 7.9, 1.001 },
    { 8.8, 0.970 },
    { 9.7, 0.936 },
    { 10.5, 0.900 },
    { 11.4, 0.861 },
    { 12.3, 0.816 },
    { 13.2, 0.769 },
    { 14.1, 0.722 },
    { 14.9, 0.673 },
    { 15.8, 0.623 },
    { 16.7, 0.572 },
    { 17.6, 0.520 },
    { 18.5, 0.467 },
    { 19.3, 0.412 },
    { 20.2, 0.356 },
    { 21.1, 0.299 },
    { 22.0, 0.241 },
    { 22.9, 0.182 },
    { 23.7, 0.122 },
    { 24.6, 0.061 },
    { 25.5, 0.000 }};

    Plane::Prop prop3[30] = {
    { 0.0, 2.630 },
    { 1.3, 2.611 },
    { 2.6, 2.587 },
    { 4.0, 2.557 },
    { 5.3, 2.520 },
    { 6.6, 2.478 },
    { 7.9, 2.430 },
    { 9.2, 2.376 },
    { 10.5, 2.317 },
    { 11.9, 2.253 },
    { 13.2, 2.183 },
    { 14.5, 2.107 },
    { 15.8, 2.026 },
    { 17.1, 1.937 },
    { 18.5, 1.836 },
    { 19.8, 1.731 },
    { 21.1, 1.624 },
    { 22.4, 1.514 },
    { 23.7, 1.402 },
    { 25.0, 1.287 },
    { 26.4, 1.169 },
    { 27.7, 1.049 },
    { 29.0, 0.926 },
    { 30.3, 0.801 },
    { 31.6, 0.673 },
    { 33.0, 0.543 },
    { 34.3, 0.410 },
    { 35.6, 0.275 },
    { 36.9, 0.138 },
    { 38.2, -0.001 }};

    Plane::Prop prop4[30] = {
    { 0.0, 4.775 },
    { 1.8, 4.739 },
    { 3.5, 4.693 },
    { 5.3, 4.635 },
    { 7.0, 4.566 },
    { 8.8, 4.485 },
    { 10.5, 4.393 },
    { 12.3, 4.291 },
    { 14.1, 4.179 },
    { 15.8, 4.057 },
    { 17.6, 3.925 },
    { 19.3, 3.783 },
    { 21.1, 3.632 },
    { 22.8, 3.468 },
    { 24.6, 3.284 },
    { 26.3, 3.097 },
    { 28.1, 2.905 },
    { 29.9, 2.708 },
    { 31.6, 2.507 },
    { 33.4, 2.301 },
    { 35.1, 2.091 },
    { 36.9, 1.876 },
    { 38.6, 1.656 },
    { 40.4, 1.432 },
    { 42.2, 1.204 },
    { 43.9, 0.972 },
    { 45.7, 0.735 },
    { 47.4, 0.493 },
    { 49.2, 0.247 },
    { 50.9, -0.001 }};

    Plane::Prop prop5[30] = {
    { 0.0, 7.618 },
    { 2.2, 7.561 },
    { 4.4, 7.485 },
    { 6.6, 7.389 },
    { 8.8, 7.272 },
    { 11.0, 7.137 },
    { 13.2, 6.985 },
    { 15.4, 6.815 },
    { 17.6, 6.630 },
    { 19.8, 6.430 },
    { 21.9, 6.213 },
    { 24.1, 5.981 },
    { 26.3, 5.734 },
    { 28.5, 5.468 },
    { 30.7, 5.175 },
    { 32.9, 4.879 },
    { 35.1, 4.578 },
    { 37.3, 4.268 },
    { 39.5, 3.950 },
    { 41.7, 3.625 },
    { 43.9, 3.292 },
    { 46.1, 2.954 },
    { 48.3, 2.608 },
    { 50.5, 2.256 },
    { 52.7, 1.897 },
    { 54.9, 1.531 },
    { 57.1, 1.158 },
    { 59.3, 0.776 },
    { 61.4, 0.390 },
    { 63.6, -0.002 }};

    Plane::Prop prop6[30] = {
    { 0.0, 11.184 },
    { 2.6, 11.109 },
    { 5.3, 11.004 },
    { 7.9, 10.865 },
    { 10.5, 10.690 },
    { 13.2, 10.484 },
    { 15.8, 10.252 },
    { 18.4, 9.993 },
    { 21.1, 9.712 },
    { 23.7, 9.409 },
    { 26.3, 9.084 },
    { 29.0, 8.735 },
    { 31.6, 8.364 },
    { 34.2, 7.968 },
    { 36.9, 7.536 },
    { 39.5, 7.102 },
    { 42.1, 6.664 },
    { 44.8, 6.213 },
    { 47.4, 5.750 },
    { 50.0, 5.277 },
    { 52.7, 4.793 },
    { 55.3, 4.301 },
    { 57.9, 3.798 },
    { 60.6, 3.286 },
    { 63.2, 2.763 },
    { 65.8, 2.229 },
    { 68.5, 1.684 },
    { 71.1, 1.130 },
    { 73.7, 0.568 },
    { 76.4, -0.002 }};

    Plane::Prop prop7[30] = {
    { 0.0, 15.076 },
    { 3.1, 15.010 },
    { 6.1, 14.907 },
    { 9.2, 14.755 },
    { 12.3, 14.551 },
    { 15.4, 14.293 },
    { 18.4, 13.996 },
    { 21.5, 13.660 },
    { 24.6, 13.291 },
    { 27.6, 12.893 },
    { 30.7, 12.464 },
    { 33.8, 12.003 },
    { 36.9, 11.510 },
    { 39.9, 10.983 },
    { 43.0, 10.400 },
    { 46.1, 9.804 },
    { 49.1, 9.199 },
    { 52.2, 8.578 },
    { 55.3, 7.941 },
    { 58.4, 7.289 },
    { 61.4, 6.621 },
    { 64.5, 5.941 },
    { 67.6, 5.247 },
    { 70.6, 4.540 },
    { 73.7, 3.820 },
    { 76.8, 3.082 },
    { 79.9, 2.330 },
    { 82.9, 1.567 },
    { 86.0, 0.786 },
    { 89.1, -0.003 }};

    Plane::Prop prop8[30] = {
    { 0.0, 19.417 },
    { 3.5, 19.376 },
    { 7.0, 19.312 },
    { 10.5, 19.203 },
    { 14.0, 19.005 },
    { 17.5, 18.719 },
    { 21.1, 18.366 },
    { 24.6, 17.956 },
    { 28.1, 17.499 },
    { 31.6, 17.001 },
    { 35.1, 16.461 },
    { 38.6, 15.877 },
    { 42.1, 15.250 },
    { 45.6, 14.577 },
    { 49.1, 13.819 },
    { 52.6, 13.027 },
    { 56.2, 12.222 },
    { 59.7, 11.397 },
    { 63.2, 10.552 },
    { 66.7, 9.687 },
    { 70.2, 8.804 },
    { 73.7, 7.899 },
    { 77.2, 6.978 },
    { 80.7, 6.033 },
    { 84.2, 5.077 },
    { 87.7, 4.097 },
    { 91.3, 3.099 },
    { 94.8, 2.079 },
    { 98.3, 1.047 },
    { 101.8, -0.005 }};


    Plane::Prop prop9[30] = {
    { 0.0, 24.216 },
    { 3.9, 24.196 },
    { 7.9, 24.172 },
    { 11.8, 24.136 },
    { 15.8, 24.060 },
    { 19.7, 23.834 },
    { 23.7, 23.450 },
    { 27.6, 22.977 },
    { 31.6, 22.424 },
    { 35.5, 21.819 },
    { 39.5, 21.165 },
    { 43.4, 20.444 },
    { 47.4, 19.665 },
    { 51.3, 18.822 },
    { 55.3, 17.864 },
    { 59.2, 16.849 },
    { 63.2, 15.808 },
    { 67.1, 14.742 },
    { 71.1, 13.651 },
    { 75.0, 12.535 },
    { 79.0, 11.391 },
    { 82.9, 10.225 },
    { 86.9, 9.031 },
    { 90.8, 7.813 },
    { 94.8, 6.571 },
    { 98.7, 5.298 },
    { 102.7, 4.010 },
    { 106.6, 2.697 },
    { 110.6, 1.354 },
    { 114.5, -0.012 }};

    static  Plane::Prop prop10[30] = {
    { 0.0, 29.983 },
    { 4.4, 29.976 },
    { 8.8, 29.963 },
    { 13.2, 29.944 },
    { 17.6, 29.920 },
    { 21.9, 29.888 },
    { 26.3, 29.682 },
    { 30.7, 29.133 },
    { 35.1, 28.462 },
    { 39.5, 27.701 },
    { 43.9, 26.866 },
    { 48.3, 25.950 },
    { 52.7, 24.963 },
    { 57.0, 23.893 },
    { 61.4, 22.686 },
    { 65.8, 21.401 },
    { 70.2, 20.085 },
    { 74.6, 18.734 },
    { 79.0, 17.352 },
    { 83.4, 15.937 },
    { 87.8, 14.489 },
    { 92.2, 13.012 },
    { 96.5, 11.506 },
    { 100.9, 9.962 },
    { 105.3, 8.388 },
    { 109.7, 6.784 },
    { 114.1, 5.136 },
    { 118.5, 3.455 },
    { 122.9, 1.739 },
    { 127.3, -0.011 }};

    //table of prop - rpm
    static const struct  PropRpm{
    double rpm;
    } prop_rpm[11]  = {
     10000.0,
     9000.0,
     8000.0,
     7000.0,
     6000.0,
     5000.0,
     4000.0,
     3000.0,
     2000.0,
     1000.0,
     0}; 



Plane::Plane(const char *frame_str) :
    Aircraft(frame_str)
{

    
    
    battery.setup(24.5, 0.04, 25.2);
    battery.init_voltage(25.2);
    mass = 11.0f;

    /*
       scaling from motor power to Newtons. Allows the plane to hold
       vertically against gravity when the motor is at hover_throttle
    */
    thrust_scale = (mass * GRAVITY_MSS) / hover_throttle;
    frame_height = 0.1f;

    ground_behavior = GROUND_BEHAVIOR_FWD_ONLY;
    lock_step_scheduled = true;

    if (strstr(frame_str, "-heavy")) {
        mass = 8;
    }
    if (strstr(frame_str, "-jet")) {
        // a 22kg "jet", level top speed is 102m/s
        mass = 22;
        thrust_scale = (mass * GRAVITY_MSS) / hover_throttle;
    }
    if (strstr(frame_str, "-revthrust")) {
        reverse_thrust = true;
    }
    if (strstr(frame_str, "-elevon")) {
        elevons = true;
    } else if (strstr(frame_str, "-vtail")) {
        vtail = true;
    } else if (strstr(frame_str, "-dspoilers")) {
        dspoilers = true;
    }
    if (strstr(frame_str, "-elevrev")) {
        reverse_elevator_rudder = true;
    }
    if (strstr(frame_str, "-catapult")) {
        have_launcher = true;
        launch_accel = 40;
        launch_time = 2;
    }
    if (strstr(frame_str, "-bungee")) {
        have_launcher = true;
        launch_accel = 7;
        launch_time = 4;
    }
    if (strstr(frame_str, "-throw")) {
        have_launcher = true;
        launch_accel = 25;
        launch_time = 0.4;
    }
    if (strstr(frame_str, "-tailsitter")) {
        tailsitter = true;
        ground_behavior = GROUND_BEHAVIOR_TAILSITTER;
        thrust_scale *= 1.5;
    }

    if (strstr(frame_str, "-3d")) {
        aerobatic = true;
        thrust_scale *= 1.5;
        // setup parameters for plane-3d
        AP_Param::load_defaults_file("@ROMFS/models/plane.parm", false);
        AP_Param::load_defaults_file("@ROMFS/models/plane-3d.parm", false);
    }
    
    if (strstr(frame_str, "-ice")) {
        ice_engine = true;
    }

    if (strstr(frame_str, "-soaring")) {
        mass = 2.0;
        coefficient.c_drag_p = 0.05;
    }
}



/*
  state of charge table for a single cell battery.
 */
static const struct {
    float thrust;
    float throttle;
    float RPM;
    float current;
} rpm_table[] = {
    { 7017, 100, 7201, 72.70},
    { 6417, 90, 6905, 63.11 },
    { 5409, 80, 6360, 47.54 },
    { 4908, 75, 6048, 40.51 },
    { 4355, 70, 5719, 33.66 },
    { 3824, 65, 5403, 28.09 },
    { 3374, 60, 5082, 23.22 },
    { 2830, 55, 4684, 18.30 },
    { 2356, 50, 4283, 14.17 },
    { 2016, 45, 3953,11.36 },
    { 1778, 40, 3696, 9.57 },
    { 1450, 35, 3210, 7.87 },
    { 1200, 30, 2760, 7.12 },
    { 700, 25, 2250, 5.52 },
    { 350, 20, 1840, 4.77 },
    { 200, 15, 1350, 3.1 },
    { 100, 10, 920, 2.35 },
    { 0.001, 0, 0, 0.2 }};


    


//prop characteristic  
// speed mph
// thrust lbf



    



/*
  use table to get resting voltage from remaining capacity
 */
float Plane::get_thrust(float throttle) const
{
    //const float max_cell_voltage = rpm_table[0].thrust;
    for (uint8_t i=1; i<ARRAY_SIZE(rpm_table); i++) {
        if (throttle >= rpm_table[i].throttle) {
            // linear interpolation between table rows
            float dv1 = throttle - rpm_table[i].throttle;
            float dv2 = rpm_table[i-1].throttle - rpm_table[i].throttle;
            float vpc1 = rpm_table[i].thrust;
            float vpc2 = rpm_table[i-1].thrust;
            float thrust = vpc1 + (dv1 / dv2) * (vpc2 - vpc1);
            return thrust;
        }
    }
    // off the bottom of the table, return a small non-zero to prevent math errors
    return 0.001;
}

float Plane::get_rpm(float throttle) const
{
    //const float max_cell_voltage = rpm_table[0].thrust;
    for (uint8_t i=1; i<ARRAY_SIZE(rpm_table); i++) {
        if (throttle >= rpm_table[i].throttle) {
            // linear interpolation between table rows
            float dv1 = throttle - rpm_table[i].throttle;
            float dv2 = rpm_table[i-1].throttle - rpm_table[i].throttle;
            float vpc1 = rpm_table[i].RPM;
            float vpc2 = rpm_table[i-1].RPM;
            float RPM = vpc1 + (dv1 / dv2) * (vpc2 - vpc1);
            return RPM;
        }
    }
    // off the bottom of the table, return a small non-zero to prevent math errors
    return 0.001;
}

float Plane::get_current(float throttle) const
{
    //const float max_cell_voltage = rpm_table[0].thrust;
    for (uint8_t i=1; i<ARRAY_SIZE(rpm_table); i++) {
        if (throttle >= rpm_table[i].throttle) {
            // linear interpolation between table rows
            float dv1 = throttle - rpm_table[i].throttle;
            float dv2 = rpm_table[i-1].throttle - rpm_table[i].throttle;
            float vpc1 = rpm_table[i].current;
            float vpc2 = rpm_table[i-1].current;
            float CURRENT = vpc1 + (dv1 / dv2) * (vpc2 - vpc1);
            return CURRENT;
        }
    }
    // off the bottom of the table, return a small non-zero to prevent math errors
    return 0.001;
}


float Plane::get_thrust_prop(float RPM, float airspeed_rpm) const
{
    //const float max_cell_voltage = rpm_table[0].thrust;
    for (uint8_t i=1; i<ARRAY_SIZE(prop_rpm); i++) {
        if (RPM >= prop_rpm[i].rpm) {
            
            // linear interpolation between table rows
            float dv1 = RPM - prop_rpm[i].rpm;
            float dv2 = prop_rpm[i-1].rpm - prop_rpm[i].rpm;
            
            float vpc1 = 0;
            float vpc2 = 0;
            if (RPM > 9000) {
                 vpc1 = linear_from_rpm(prop10,airspeed_rpm);
                 vpc2 = linear_from_rpm(prop9,airspeed_rpm);

            } else if (RPM > 8000){
                 vpc1 = linear_from_rpm(prop9,airspeed_rpm);
                 vpc2 = linear_from_rpm(prop8,airspeed_rpm);
            } else if (RPM > 7000){
                 vpc1 = linear_from_rpm(prop8,airspeed_rpm);
                 vpc2 = linear_from_rpm(prop7,airspeed_rpm);
            } else if (RPM > 6000){
                 vpc1 = linear_from_rpm(prop7,airspeed_rpm);
                 vpc2 = linear_from_rpm(prop6,airspeed_rpm);
            } else if (RPM > 5000){
                 vpc1 = linear_from_rpm(prop6,airspeed_rpm);
                 vpc2 = linear_from_rpm(prop5,airspeed_rpm);
            } else if (RPM > 4000){
                 vpc1 = linear_from_rpm(prop5,airspeed_rpm);
                 vpc2 = linear_from_rpm(prop4,airspeed_rpm);
            } else if (RPM > 3000){
                 vpc1 = linear_from_rpm(prop4,airspeed_rpm);
                 vpc2 = linear_from_rpm(prop3,airspeed_rpm);
            } else if (RPM > 2000){
                 vpc1 = linear_from_rpm(prop3,airspeed_rpm);
                 vpc2 = linear_from_rpm(prop2,airspeed_rpm);
            } else if (RPM > 1000){
                 vpc1 = linear_from_rpm(prop2,airspeed_rpm);
                 vpc2 = linear_from_rpm(prop1,airspeed_rpm);
            } else if (RPM > 0){
                vpc1 = linear_from_rpm(prop1,airspeed_rpm);
                vpc2 = 0;
            }
            
            float thrust = vpc2 + (dv1 / dv2) * (vpc1 - vpc2);
            
            return thrust;
        }
    }
    return 0.001;

}

float Plane::linear_from_rpm(Plane::Prop prop[30], float airspeed_rpm) const
{
    
    for (uint8_t i=1; i<30; i++) {
        
        if (airspeed_rpm <= prop[i].airspeed) {
            
            
            // linear interpolation between table rows
            float dv1 = prop[i].airspeed - airspeed_rpm;
            float dv2 = prop[i].airspeed - prop[i-1].airspeed;
            float vpc1 = prop[i-1].thrust;
            float vpc2 = prop[i].thrust;
            float thrust = vpc1 + (dv1 / dv2) * (vpc2 - vpc1);
            
            return thrust;
        }
    }
    return 0.001;


}



/*
  the following functions are from last_letter
  https://github.com/Georacer/last_letter/blob/master/last_letter/src/aerodynamicsLib.cpp
  many thanks to Georacer!
 */
float Plane::liftCoeff(float alpha) const
{
    const float alpha0 = coefficient.alpha_stall;
    const float M = coefficient.mcoeff;
    const float c_lift_0 = coefficient.c_lift_0;
    const float c_lift_a0 = coefficient.c_lift_a;

    // clamp the value of alpha to avoid exp(90) in calculation of sigmoid
    const float max_alpha_delta = 0.8f;
    if (alpha-alpha0 > max_alpha_delta) {
        alpha = alpha0 + max_alpha_delta;
    } else if (alpha0-alpha > max_alpha_delta) {
        alpha = alpha0 - max_alpha_delta;
    }
	double sigmoid = ( 1+exp(-M*(alpha-alpha0))+exp(M*(alpha+alpha0)) ) / (1+exp(-M*(alpha-alpha0))) / (1+exp(M*(alpha+alpha0)));
	double linear = (1.0-sigmoid) * (c_lift_0 + c_lift_a0*alpha); //Lift at small AoA
	double flatPlate = sigmoid*(2*copysign(1,alpha)*pow(sin(alpha),2)*cos(alpha)); //Lift beyond stall

	float result  = linear+flatPlate;
	return result;
}

float Plane::dragCoeff(float alpha) const
{
    const float b = coefficient.b;
    const float s = coefficient.s;
    const float c_drag_p = coefficient.c_drag_p;
    const float c_lift_0 = coefficient.c_lift_0;
    const float c_lift_a0 = coefficient.c_lift_a;
    const float oswald = coefficient.oswald;
    
	double AR = pow(b,2)/s;
	double c_drag_a = c_drag_p + pow(c_lift_0+c_lift_a0*alpha,2)/(M_PI*oswald*AR);

	return c_drag_a;
}

// Torque calculation function
Vector3f Plane::getTorque(float inputAileron, float inputElevator, float inputRudder, float inputThrust, const Vector3f &force) const
{
    float alpha = angle_of_attack;

	//calculate aerodynamic torque
    float effective_airspeed = airspeed;

    if (tailsitter || aerobatic) {
        /*
          tailsitters get airspeed from prop-wash
         */
        effective_airspeed += inputThrust * 20;

        // reduce effective angle of attack as thrust increases
        alpha *= constrain_float(1 - inputThrust, 0, 1);
    }
    
    const float s = coefficient.s;
    const float c = coefficient.c;
    const float b = coefficient.b;
    const float c_l_0 = coefficient.c_l_0;
    const float c_l_b = coefficient.c_l_b;
    const float c_l_p = coefficient.c_l_p;
    const float c_l_r = coefficient.c_l_r;
    const float c_l_deltaa = coefficient.c_l_deltaa;
    const float c_l_deltar = coefficient.c_l_deltar;
    const float c_m_0 = coefficient.c_m_0;
    const float c_m_a = coefficient.c_m_a;
    const float c_m_q = coefficient.c_m_q;
    const float c_m_deltae = coefficient.c_m_deltae;
    const float c_n_0 = coefficient.c_n_0;
    const float c_n_b = coefficient.c_n_b;
    const float c_n_p = coefficient.c_n_p;
    const float c_n_r = coefficient.c_n_r;
    const float c_n_deltaa = coefficient.c_n_deltaa;
    const float c_n_deltar = coefficient.c_n_deltar;
    const Vector3f &CGOffset = coefficient.CGOffset;
    
    float rho = air_density;

	//read angular rates
	double p = gyro.x;
	double q = gyro.y;
	double r = gyro.z;

	double qbar = 1.0/2.0*rho*pow(effective_airspeed,2)*s; //Calculate dynamic pressure
	double la, na, ma;
	if (is_zero(effective_airspeed))
	{
		la = 0;
		ma = 0;
		na = 0;
	}
	else
	{
		la = qbar*b*(c_l_0 + c_l_b*beta + c_l_p*b*p/(2*effective_airspeed) + c_l_r*b*r/(2*effective_airspeed) + c_l_deltaa*inputAileron + c_l_deltar*inputRudder);
		ma = qbar*c*(c_m_0 + c_m_a*alpha + c_m_q*c*q/(2*effective_airspeed) + c_m_deltae*inputElevator);
		na = qbar*b*(c_n_0 + c_n_b*beta + c_n_p*b*p/(2*effective_airspeed) + c_n_r*b*r/(2*effective_airspeed) + c_n_deltaa*inputAileron + c_n_deltar*inputRudder);
	}


	// Add torque to force misalignment with CG
	// r x F, where r is the distance from CoG to CoL
	la +=  CGOffset.y * force.z - CGOffset.z * force.y;
	ma += -CGOffset.x * force.z + CGOffset.z * force.x;
	na += -CGOffset.y * force.x + CGOffset.x * force.y;

	return Vector3f(la, ma, na);
}

// Force calculation function from last_letter
Vector3f Plane::getForce(float inputAileron, float inputElevator, float inputRudder) const
{
    const float alpha = angle_of_attack;
    const float c_drag_q = coefficient.c_drag_q;
    const float c_lift_q = coefficient.c_lift_q;
    const float s = coefficient.s;
    const float c = coefficient.c;
    const float b = coefficient.b;
    const float c_drag_deltae = coefficient.c_drag_deltae;
    const float c_lift_deltae = coefficient.c_lift_deltae;
    const float c_y_0 = coefficient.c_y_0;
    const float c_y_b = coefficient.c_y_b;
    const float c_y_p = coefficient.c_y_p;
    const float c_y_r = coefficient.c_y_r;
    const float c_y_deltaa = coefficient.c_y_deltaa;
    const float c_y_deltar = coefficient.c_y_deltar;
    
    float rho = air_density;

	//request lift and drag alpha-coefficients from the corresponding functions
	double c_lift_a = liftCoeff(alpha);
	double c_drag_a = dragCoeff(alpha);

	//convert coefficients to the body frame
	double c_x_a = -c_drag_a*cos(alpha)+c_lift_a*sin(alpha);
	double c_x_q = -c_drag_q*cos(alpha)+c_lift_q*sin(alpha);
	double c_z_a = -c_drag_a*sin(alpha)-c_lift_a*cos(alpha);
	double c_z_q = -c_drag_q*sin(alpha)-c_lift_q*cos(alpha);

	//read angular rates
	double p = gyro.x;
	double q = gyro.y;
	double r = gyro.z;

	//calculate aerodynamic force
	double qbar = 1.0/2.0*rho*pow(airspeed,2)*s; //Calculate dynamic pressure
	double ax, ay, az;
	if (is_zero(airspeed))
	{
		ax = 0;
		ay = 0;
		az = 0;
	}
	else
	{
		ax = qbar*(c_x_a + c_x_q*c*q/(2*airspeed) - c_drag_deltae*cos(alpha)*fabs(inputElevator) + c_lift_deltae*sin(alpha)*inputElevator);
		// split c_x_deltae to include "abs" term
		ay = qbar*(c_y_0 + c_y_b*beta + c_y_p*b*p/(2*airspeed) + c_y_r*b*r/(2*airspeed) + c_y_deltaa*inputAileron + c_y_deltar*inputRudder);
		az = qbar*(c_z_a + c_z_q*c*q/(2*airspeed) - c_drag_deltae*sin(alpha)*fabs(inputElevator) - c_lift_deltae*cos(alpha)*inputElevator);
		// split c_z_deltae to include "abs" term
	}
    return Vector3f(ax, ay, az);
}

void Plane::calculate_forces(const struct sitl_input &input, Vector3f &rot_accel)
{
    float aileron  = filtered_servo_angle(input, 0);
    float elevator = filtered_servo_angle(input, 3);
    float rudder   = filtered_servo_angle(input, 4);
    bool launch_triggered = input.servos[6] > 1700;
    float throttle;
    if (reverse_elevator_rudder) {
        elevator = -elevator;
        rudder = -rudder;
    }
    if (elevons) {
        // fake an elevon plane
        float ch1 = aileron;
        float ch2 = elevator;
        aileron  = (ch2-ch1)/2.0f;
        // the minus does away with the need for RC2_REVERSED=-1
        elevator = -(ch2+ch1)/2.0f;

        // assume no rudder
        rudder = 0;
    } else if (vtail) {
        // fake a vtail plane
        float ch1 = elevator;
        float ch2 = rudder;
        // this matches VTAIL_OUTPUT==2
        elevator = (ch2-ch1)/2.0f;
        rudder   = (ch2+ch1)/2.0f;
    } else if (dspoilers) {
        // fake a differential spoiler plane. Use outputs 1, 2, 4 and 5
        float dspoiler1_left = filtered_servo_angle(input, 0);
        float dspoiler1_right = filtered_servo_angle(input, 1);
        float dspoiler2_left = filtered_servo_angle(input, 3);
        float dspoiler2_right = filtered_servo_angle(input, 4);
        float elevon_left  = (dspoiler1_left + dspoiler2_left)/2;
        float elevon_right = (dspoiler1_right + dspoiler2_right)/2;
        aileron  = (elevon_right-elevon_left)/2;
        elevator = (elevon_left+elevon_right)/2;
        rudder = fabsf(dspoiler1_right - dspoiler2_right)/2 - fabsf(dspoiler1_left - dspoiler2_left)/2;
    }
    //printf("Aileron: %.1f elevator: %.1f rudder: %.1f\n", aileron, elevator, rudder);

    if (reverse_thrust) {
        throttle = filtered_servo_angle(input, 2);
    } else {
        throttle = filtered_servo_range(input, 2);
    }
    
    float thrust     = throttle;
    
    if (battery_voltage < 16) {
        thrust = 0;
    }
    

    //sitl->batt_voltage - 0.7*throttle;
    battery_current = get_current(throttle*100);
    if (battery.resting_voltage > 17){
        battery_current *= (1 + ((battery.resting_voltage-21.5) * 1.5) / 100);

    }
    battery.set_current(battery_current);
    battery_voltage = battery.get_voltage();




    /* if (battery_voltage < 16) {
        battery_current = 0.2;
    }
    else{
        battery_current = 38.0f*throttle;

    } */
    

    if (battery_voltage < 16) {
        thrust = 0;
    }
    
    if (ice_engine) {
        thrust = icengine.update(input);
    }

    // calculate angle of attack
    angle_of_attack = atan2f(velocity_air_bf.z, velocity_air_bf.x);
    beta = atan2f(velocity_air_bf.y,velocity_air_bf.x);

    if (tailsitter || aerobatic) {
        /*
          tailsitters get 4x the control surfaces
         */
        aileron *= 4;
        elevator *= 4;
        rudder *= 4;
    }
    
    Vector3f force = getForce(aileron, elevator, rudder);
    rot_accel = getTorque(aileron, elevator, rudder, thrust, force);

    if (true) {
        /*
          simple simulation of a launcher
         */
        launch_accel = 80;
        launch_time = 0.8;
        if (launch_triggered) {
            uint64_t now = AP_HAL::millis64();
            if (launch_start_ms == 0) {
                launch_start_ms = now;
            }
            if (now - launch_start_ms < launch_time*1000) {
                force.x += mass * launch_accel;
                force.z += mass * launch_accel/3;
            }
        } else {
            // allow reset of catapult
            launch_start_ms = 0;
        }
    }
    
    // simulate engine RPM
    motor_mask |= (1U<<2);
    rpm[2] = thrust * 7000;
    
    // scale thrust to newtons
    //thrust *= thrust_scale;
    float RPM = get_rpm(throttle*100);
    RPM *= (1 + ((battery.resting_voltage-21.5) * 1.5) / 100);
    //thrust = get_thrust(thrust*100)*GRAVITY_MSS/1000;
    thrust = get_thrust_prop(RPM,airspeed*2.237)*GRAVITY_MSS*0.45359237;
    /* ::printf("thr: %f \n",
             thrust);
    ::printf("RPM: %f \n",
             RPM); */

    //voltage scale
    //thrust *= (1 + ((battery.resting_voltage-21.5) * 2.75) / 100);


    accel_body = Vector3f(thrust, 0, 0) + force;
    accel_body /= mass;

    // add some noise
    if (thrust_scale > 0) {
        add_noise(fabsf(thrust) / thrust_scale);
    }

    if (on_ground() && !tailsitter) {
        // add some ground friction
        Vector3f vel_body = dcm.transposed() * velocity_ef;
        accel_body.x -= vel_body.x * 0.3f;
    }
}
    
/*
  update the plane simulation by one time step
 */
void Plane::update(const struct sitl_input &input)
{
    Vector3f rot_accel;

    update_wind(input);
    
    calculate_forces(input, rot_accel);
    
    update_dynamics(rot_accel);
    update_external_payload(input);

    // update lat/lon/altitude
    update_position();
    time_advance();

    // update magnetic field
    update_mag_field_bf();
}
