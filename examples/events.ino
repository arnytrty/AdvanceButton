/**
 * AdvanceButton example
 * how to use the library
 * 
 * written by: Arnošt Trtúšek
 * last edit: 2021.02.24
 * github: https://github.com/arnytrty/AdvanceButton
 */
#include <Arduino.h>
#include <AdvanceButton.h>

// this will setup the input with pullup and active state is low
//          |
// mcu    5 |-----. \.------ GND
//          |
AdvanceButton btn(5, INPUT_PULLUP, LOW);

/**
 * Button Events
 */
void onclick() {
    Serial.println("[AdvanceButton] click");
}

void ondoubleclick() {
    Serial.println("[AdvanceButton] double click");
}

void onshorthold() {
    Serial.println("[AdvanceButton] shorthold");
}

void onlonghold() {
	Serial.println("[AdvanceButton] longhold");
}

/**
 * Setup
 */
void setup() {
    // initialize serial
	Serial.begin(9600);
	Serial.println();
    Serial.println("[AdvanceButton] Simple Advance Button Example");

    // initialize advance_button
	btn.onClick(onclick);
	btn.onDoubleClick(ondoubleclick);
	btn.onShortHold(onshorthold);
	btn.onLongHold(onlonghold);
	btn.init();
}

/**
 * Main Loop
 */
void loop() {
    // check for button events
	btn.update();

	delay(2);
}
