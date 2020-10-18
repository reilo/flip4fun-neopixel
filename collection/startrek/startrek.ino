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

   Additional effects are triggered by the
     7 - Captain's Chair insert
   which lights the front part of the undercab LEDs whitish,
   and the
     8 - Flasher beneath the left spinner
   which lights the upper part of the left backbox LEDs whitish.

   Whitish blinking effects are triggered 1:1 by the
     9 - Flasher beneath the upper pop bumpers
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

// Captain's chair flashing effect
uint16_t chairPeriods[21] = {232, 216, 158, 192, 96, 168, 84, 144, 72, 120, 60, 96, 48, 72, 36, 60, 30, 48, 24, 36, 18 };
SingleColorEffect* chairFlash = new FlashComplex(21, chairPeriods, 0x003f3f3f);

// Spinner wave effect
uint16_t spinnerPeriods[5] = {18, 18, 18, 18, 18};
SingleColorEffect* spinnerFlash = new FlashComplex(5, spinnerPeriods, WHITE);

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

  // Light sensor of Captain's Chair insert
  pinMode(7, INPUT_PULLUP);

  // Light sensor of left spinner
  pinMode(8, INPUT_PULLUP);

  // Light sensor of flasher below upper pop bumpers
  pinMode(9, INPUT_PULLUP);

  // Ambilight effect is running forever
  ambilight->start(m);

  for (int i = 0; i < 6; i++) {
    blink[i] = new Blink(50, 200);
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
  uint32_t ambilightColor = BLUE;
  uint32_t color;
  uint32_t overlayColor;

  // Determine the blinking mission insert and set corresponding color
  for (int i = 0; i < 6; i++) {
    in = digitalRead(i + 1);
    if (blink[i]->read(m, in == LOW)) {
      ambilightColor = ambilightColors[i];
      break;
    }
  }
  // Set the appropriate ambilight color and determine the current intensity
  ambilight->setColor(ambilightColor);
  ambilight->update(m);
  if (ambilight->running()) {
    color = ambilight->getColor();
  }

  // Determine whether the pop bumpers flasher is lit - if yes override ambilight color
  in = digitalRead(9);
  if (in == LOW) {
    color = ambilightColor | 0x007f7f7f;
  }

  // Set color of all strips
  for (int i = 0; i < 4; i++) {
    strip[i]->fill(color, 0, strip[i]->numPixels());
  }

  // Determine whether the left spinner insert is lit - if yes set partial effect
  in = digitalRead(8);
  if (in == LOW) {
    if (!spinnerFlash->running()) {
      spinnerFlash->start(m);
    }
  }
  if (spinnerFlash->running()) {
    spinnerFlash->update(m);
    overlayColor = spinnerFlash->getColor();
    strip[2]->fill(overlayColor, 20, strip[2]->numPixels() - 20);
  }

  // Determine whether the Captain's Chair insert is lit - if yes set partial effect
  in = digitalRead(7);
  if (in == LOW) {
    if (!chairFlash->running()) {
      chairFlash->start(m);
    }
  }
  if (chairFlash->running()) {
    chairFlash->update(m);
    overlayColor = chairFlash->getColor();
    for (int i = 0; i < 2; i++) {
      strip[i]->fill(overlayColor, 0, 10);
    }
  }

  // Update all strips
  for (int i = 0; i < 4; i++) {
    strip[i]->show();
  }
}