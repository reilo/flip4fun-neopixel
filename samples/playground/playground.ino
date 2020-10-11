#include <Adafruit_NeoPixel.h>
#include <Flip4fun_NeoPixel.h>

Adafruit_NeoPixel* strip[4];

Wave* ambilight;
FlashComplex *flash;
//Flash *flash;

TickRandom *tick1;
TickRandom *tick2;

void setup() {

  unsigned long m = millis();

  strip[0] = new Adafruit_NeoPixel(72, 10, NEO_GRB + NEO_KHZ800); // undercab left
  strip[1] = new Adafruit_NeoPixel(72, 11, NEO_GRB + NEO_KHZ800); // undercab right
  strip[2] = new Adafruit_NeoPixel(38, 12, NEO_GRB + NEO_KHZ800); // backbox left
  strip[3] = new Adafruit_NeoPixel(38, 13, NEO_GRB + NEO_KHZ800); // backbox right

  ambilight = new Wave(4000, BLUE);
  uint16_t intervals[7] = {32, 64, 32, 64, 128, 64, 32};
  flash = new FlashComplex(7, intervals, MAGENTA);
  //flash = new Flash(128, GREEN);

  tick1 = new TickRandom(2000, 6000);
  tick2 = new TickRandom(3000, 8000);

  pinMode(7, INPUT_PULLUP); // flasher upper pop bumpers

  for (int i = 0; i < 4; i++) {
    strip[i]->begin();
    strip[i]->show();
    strip[i]->setBrightness(50);
  }

  ambilight->start(m);

  tick1->start(m);
  tick2->start(m);
}

void loop() {

  unsigned long m = millis();
  uint32_t color = 0;

  if (tick1->read(m)) {
    ambilight->setColor(ambilight->getColor() == BLUE ? RED : BLUE);
  }
  if (ambilight->running()) {
    color = ambilight->update(m);
  }

  if (tick2->read(m)) {
    flash->start(m);
  }
  uint32_t flashColor = 0;
  if (flash->running()) {
    flashColor = flash->update(m);
    if (flashColor != 0) {
      color = flashColor;
    }
  }

  uint16_t inFlash = digitalRead(7);
  if (inFlash == HIGH) {
    color = WHITE;
  }

  for (int i = 0; i < 4; i++) {
    strip[i]->fill(color, 0, strip[i]->numPixels());
    strip[i]->show();
  }
}
