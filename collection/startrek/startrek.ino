/*
   Lightshow for Stern STAR TREK Pro Vault Edition
   -----------------------------------------------

   The ambilight, which is blue by default, changes to the color of the currently active mission.
   The active mission is detected by the corresponding insert which must be blinking:
     1 - Prime Directive: Blue
     2 - Klingon Battle: Red
     3 - Space Jump: Yellow
     4 - Destroy the Drill: Cyan
     5 - Nero: Purple
     6 - Save the Enterprise: Green

   White Flasher effects are triggered 1:1 by the flasher beneath the upper pop bumpers.
*/

#include <Adafruit_NeoPixel.h>
#include <Flip4fun_NeoPixel.h>

// Undercab and Backbos LED strips
Adafruit_NeoPixel* strip[4];

// Oscillating ambilight effect
SingleColorEffect* ambilight = new Wave(2500, BLUE);

// Ambilight color determined by the current mission
uint32_t ambilightColors[] = {BLUE, RED, YELLOW, CYAN, PURPLE, GREEN};

// Determines which of the 6 mission insert is blinking
Switcher *blink[6];

void setup() {

  unsigned long m = millis();

  strip[0] = new Adafruit_NeoPixel(58, 10, NEO_GRB + NEO_KHZ800); // undercab left
  strip[1] = new Adafruit_NeoPixel(58, 11, NEO_GRB + NEO_KHZ800); // undercab right
  strip[2] = new Adafruit_NeoPixel(38, 12, NEO_GRB + NEO_KHZ800); // backbox left
  strip[3] = new Adafruit_NeoPixel(38, 13, NEO_GRB + NEO_KHZ800); // backbox right

  // Light sensors of mission inserts
  for (int i = 1; i <= 6; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  // Light sensor of flasher below upper pop bumpers
  pinMode(7, INPUT_PULLUP);

  // Ambilight effect is running forever
  ambilight->start(m);

  for (int i = 0; i < 6; i++) {
    blink[i] = new Blink(100, 200);
    blink[i]->start(m);
  }

  for (int i = 0; i < 4; i++) {
    strip[i]->begin();
    strip[i]->show();
    strip[i]->setBrightness(255);
  }

  Serial.begin(9600);
}

void loop() {

  unsigned long m = millis();
  uint16_t in;
  uint32_t color = BLUE;

  // Determine the blinking mission insert and set corresponding color
  for (int i = 0; i < 6; i++) {
    in = digitalRead(i + 1);
    if (blink[i]->read(m, in == LOW)) {
      color = ambilightColors[i];
    }
  }
  // Set the appropriate ambilight color and determine the current intensity
  ambilight->setColor(color);
  ambilight->update(m);
  if (ambilight->running()) {
    color = ambilight->getColor();
  }

  // Determine whether the pop bumpers flasher is lit - if yes override ambilight color
  in = digitalRead(7);
  if (in == LOW) {
    color = WHITE;
  }

  // Set color of all strips
  for (int i = 0; i < 4; i++) {
    strip[i]->fill(color, 0, strip[i]->numPixels());
    strip[i]->show();
  }
}