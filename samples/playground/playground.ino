#include <Adafruit_NeoPixel.h>
#include <Flip4fun_NeoPixel.h>

Adafruit_NeoPixel* strip[4];

SingleColorEffect* ambilight = new Wave(4000, BLUE);
SingleColorEffect *flash = new Flash(12, CYAN);
SingleColorEffect *flashComplex = new FlashComplex(7, (uint16_t[7]) {
  32, 64, 32, 64, 128, 64, 32
}, MAGENTA);

Trigger *waveTick = new Tick(3000);
Trigger *tick = new Tick(1800);
Trigger *tickRandom = new TickRandom(3000, 6000);
Switcher *blink = new Blink(100, 200);

void setup() {

  unsigned long m = millis();

  strip[0] = new Adafruit_NeoPixel(58, 10, NEO_GRB + NEO_KHZ800); // undercab left
  strip[1] = new Adafruit_NeoPixel(58, 11, NEO_GRB + NEO_KHZ800); // undercab right
  strip[2] = new Adafruit_NeoPixel(38, 12, NEO_GRB + NEO_KHZ800); // backbox left
  strip[3] = new Adafruit_NeoPixel(38, 13, NEO_GRB + NEO_KHZ800); // backbox right

  pinMode(7, INPUT_PULLUP); // flasher upper pop bumpers

  for (int i = 0; i < 4; i++) {
    strip[i]->begin();
    strip[i]->show();
    strip[i]->setBrightness(50);
  }

  ambilight->start(m);

  waveTick->start(m);
  tick->start(m);
  tickRandom->start(m);
  blink->start(m);

  Serial.begin(9600);
}

void loop() {

  unsigned long m = millis();
  uint32_t color = 0;
  uint32_t flashColor = 0;
  char buf[64];

  if (waveTick->read(m)) {
    ambilight->setColor(ambilight->getColor() == BLUE ? RED : BLUE);
  }
  ambilight->update(m);
  if (ambilight->running()) {
    color = ambilight->getColor();
  }

  if (tick->read(m)) {
    flash->start(m);
  }
  flash->update(m);
  if (flash->running()) {
    flashColor = flash->getColor();
    if (flashColor != 0) {
      color = flashColor;
    }
  }

  if (tickRandom->read(m)) {
    flashComplex->start(m);
  }
  flashComplex->update(m);
  if (flashComplex->running()) {
    flashColor = flashComplex->getColor();
    if (flashColor != 0) {
      color = flashColor;
    }
  }

  uint16_t inFlash = digitalRead(7);
  if (blink->read(m, inFlash == LOW)) {
    //if (inFlash == LOW) {
    color = WHITE;
  }
  sprintf(buf, "%d", m);
  Serial.println(buf);

  for (int i = 0; i < 4; i++) {
    strip[i]->fill(color, 0, strip[i]->numPixels());
    strip[i]->show();
  }
}