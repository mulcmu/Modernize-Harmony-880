#include <stdint.h>
#ifndef EXTERN 
#define EXTERN extern
#endif

#include "buttons.h"


// struct button_state {
// 	uint8_t button;
// 	ButtonState state;
// };

// //precomputed array to return which MSB is set
// //only supports one button per column
// //TODO there might be an assembly instruction for this
const uint8_t bit_to_index[256] = {
0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
};

//array to define what button is at each row column combination
const uint8_t buttonMatrix[buttonRows][buttonCols] = {
  {  1,  5,  9, 13, 17, 21, 25},
  {  2,  6, 10, 14, 18, 22, 26},
  {  3,  7, 11, 15, 19, 23, 27},
  {  4,  8, 12, 16, 20, 24, 28},
  { 42, 46, 50, 29, 33, 37, 41},
  { 43, 47, 51, 30, 34, 38, 54},
  { 44, 48, 52, 31, 35, 39, 55},
  { 45, 49, 53, 32, 36, 40, 56}
};


//Called every 5ms from main() when matrix scanning is active
void process_buttons(void) {

        uint8_t button = 0;
        uint8_t column = 0;

        //Zero is no buttons pressed, but is a valid index
        //128 and greater is P2.7 for ball spring sensor
        column = P2IN & (~BIT7);
        if(column != 0 ) {
            button = buttonMatrix[ bit_to_index[P3OUT] ][ bit_to_index[column] ];
        }

 
        if(button != 0) {
          Serial.write(button);
          last_button_press=millis();
        }

        P3OUT = P3OUT << 1;

        if (P3OUT==0)
            P3OUT = BIT0;

}