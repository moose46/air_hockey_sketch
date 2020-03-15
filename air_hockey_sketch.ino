//#include <SoftwareSerial.h>
#include <SevSeg.h>
/* SevSeg Counter Example
  Edited by Haneef Puttur to match SMA420564 (www.haneefputtur.com)
  Copyright 2014 Dean Reading

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
  http://www.apache.org/licenses/LICENSE-2.0
l
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.


  This example demonstrates a very simple use of the SevSeg library with a 4
  digit display. It displays a counter that counts up, showing 10 deci-seconds.
*/
//#include <elapsedMillis.h>
#include <PrintEx.h> //allows printf-style printout syntax
// constants won't change. They're used here to set pin numbers:
const int buttonReset = A0;    // the number of the pushbutton pin
const int buttonPlayer1 = A1;    // the number of the pushbutton pin
const int buttonPlayer2 = A2;    // the number of the pushbutton pin
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int scoreBoard = 0;

SevSeg sevseg; //Instantiate a seven segment controller object

volatile bool Interrupt = false;     // indicates whether MPU interrupt pin has gone high
void BtnInterrupt()
{
    Interrupt = true;
    scoreBoard += 100;
}

void setup() {
    byte numDigits = 4;
    //byte digitPins[] = {10, 11, 12, 13};
    byte digitPins[] = { 13, 12, 11, 10 };
    byte segmentPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

    pinMode(buttonReset, INPUT);
    pinMode(buttonPlayer1, INPUT);
    pinMode(buttonPlayer2, INPUT);
    buttonState = digitalRead(buttonReset);

    Serial.println("Initial button state is ");
    attachInterrupt(digitalPinToInterrupt(buttonReset), BtnInterrupt, CHANGE);


    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
    // If your display is common anode type, please edit comment above line and uncomment below line
    // sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
    sevseg.setBrightness(90);
}

void loop() {
    static unsigned long timer = millis();
    static int deciSeconds = 0;

    ////////////////////////////////////////

    // read the state of the switch into a local variable:
    int reading = digitalRead(buttonReset);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
        Serial.println('Pressed');
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != buttonState) {
            buttonState = reading;

            // only toggle the LED if the new button state is HIGH
            if (buttonState == HIGH) {
                ledState = !ledState;
                //scoreBoard += 100;
                scoreBoard += 1;
                if (scoreBoard > 1600)
                    scoreBoard = 0;
                sevseg.setNumber(scoreBoard, 2);
            }
        }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;

    ///////////////////////////////////////



    //
    if (millis() >= timer) {
        deciSeconds++; // 1000 milliSeconds is equal to 10 deciSecond
        timer += 1000;
        if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
            deciSeconds = 0;
        }
        //    sevseg.setNumber(deciSeconds, 1);
        sevseg.setNumber(scoreBoard, 2);
    }
    //
    //  sevseg.refreshDisplay(); // Must run repeatedly
    sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///
