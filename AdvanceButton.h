/**
 * Simple Button library that can detect if button was clicked, doubleclicked or hold.
 * Works on any sort of input (button, capacitive sensor, hall sensor) with two states.
 * 
 * written by: Arnošt Trtúšek
 * last edit: 2021.02.24
 * github: https://github.com/arnytrty/AdvanceButton
 */
#ifndef AdvanceButton_h
#define AdvanceButton_h

#include <Arduino.h>

#define DOUBLE_TIME 100
#define HOLD_TIME 1000

class AdvanceButton {
    public:
        /**
         * initalize advance_button class and define pin, pull resistor & down state
         * 
         * @param pin where button is connected
         * @param pulltype setup internal resistors, use [INPUT, INPUT_PULLUP, INPUT_PULLDOWN]
         * @param dowstate pin state when button is down, use [HIGH, LOW]
         */
        advance_button(int pin, int pulltype, int downstate) : btn_pin(pin), pull_type(pulltype), down_state(downstate) {}

        /**
         * prepare button pin
         */
        void init();

        /**
         * this is where magic happend
         */
        void update();

        /**
         * setup callback whitch is called whenever button is clicked
         * 
         * @param onclickcallback function without parameters
         */
        void onClick(void (*onclickcallback)());

        /**
         * setup callback whitch is called whenever button is clicked two times in fast interval (doubleclicked)
         * 
         * @param ondoubleclickcallback function without parameters
         */
        void onDoubleClick(void (*ondoubleclickcallback)());

        /**
         * setup callback whitch is called whenever button is hold for some period of time
         * 
         * @param onholdcallback function without parameters
         */
        void onHold(void (*onholdcallback)());

    private:
        int btn_pin, pull_type, down_state;
        void (*click)() = nullptr, (*doubleclick)() = nullptr, (*hold)() = nullptr;

        unsigned long start_hold, last_click;
        bool holding = false, two_in_row = false, click_wait, hold_done = false;
};

#endif