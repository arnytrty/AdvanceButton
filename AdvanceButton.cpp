/**
 * Simple Button library that can detect if button was clicked, doubleclicked or hold.
 * Works on any sort of input (button, capacitive sensor, hall sensor) with two states.
 * 
 * written by: Arnošt Trtúšek
 * last edit: 2021.02.24
 * github: https://github.com/arnytrty/AdvanceButton
 */
#include "AdvanceButton.h"

/**
 * prepare button pin
 */
void AdvanceButton::init() {
    pinMode(btn_pin, pull_type);
}

/**
 * this is where magic happend
 */
void AdvanceButton::update() {
    if(!digitalRead(btn_pin)) {
        // start touching
        if(!hold_done) {
            if(!holding) {
                holding = true;
                start_hold = millis();

                // check for double touch
                if(millis() - last_click <= DOUBLE_TIME) {
                    two_in_row = true;
                }
            } else {
                // check for hold
                if(millis() - start_hold > LONGHOLD_TIME) {
                    holding = false;
                    two_in_row = false;
                    hold_done = true;

                    if(longhold != nullptr)
                        longhold();
                }
            }
        }
    } else {
        // stop touching
        if(holding) {
            holding = false;

            if(two_in_row) {
                two_in_row = false;
                click_wait = false;

                if(doubleclick != nullptr)
                    doubleclick();
            } else {
                // check for if is click or shorthold
                if(millis() - start_hold > SHORTHOLD_TIME) {
                    two_in_row = false;
                    click_wait = false;

                    if(shorthold != nullptr)
                        shorthold();
                } else {
                    click_wait = true;
                    last_click = millis();
                }
            }
        }

        // check for touch pending
        if(click_wait) {
            if(millis() - last_click > DOUBLE_TIME) {
                click_wait = false;

                if(click != nullptr)
                    click();
            }
        }

        hold_done = false;
    }
}

/**
 * setup callback whitch is called whenever button is clicked
 * 
 * @param onclickcallback function without parameters
 */
void AdvanceButton::onClick(void (*onclickcallback)()) {
    click = onclickcallback;
}

/**
 * setup callback whitch is called whenever button is clicked two times in fast interval (doubleclicked)
 * 
 * @param ondoubleclickcallback function without parameters
 */
void AdvanceButton::onDoubleClick(void (*ondoubleclickcallback)()) {
    doubleclick = ondoubleclickcallback;
}

/**
 * setup callback whitch is called whenever button is hold for some period of time
 * 
 * @param onshortholdcallback function without parameters
 */
void onShortHold(void (*onshortholdcallback)()) {
    shorthold = onshortholdcallback;
}

/**
 * setup callback whitch is called whenever button is hold for some longer period of time
 * 
 * @param onlongholdcallback function without parameters
 */
void onLongHold(void (*onlongholdcallback)()) {
    longhold = onlongholdcallback;
}
