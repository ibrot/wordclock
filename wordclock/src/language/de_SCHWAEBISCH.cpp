#include <Arduino.h>

#include "de_SCHWAEBISCH.h"

#include "../config.h"
#include "../dnd.h"
#include "../led.h"

void Grid_de_SCHWAEBISCH::setTime(int hour, int minute) {
  if(hour == -1 || minute == -1) {
    return;
  }

  if(DND::active(hour, minute)) {
    for(int i = 0; i < NUM_LEDS; i++) {
      Led::ids[i].setRGB(0, 0, 0);
    }

    FastLED.show();

    return;
  }

  int singleMinute = minute % 5;
  int hourLimit = 6;

  minute = (minute - (minute % 5));

  if(minute >= 25) {
    hour += 1;
  }

  minute = minute / 5;
  hour = hour % 12;

  for(int i = 0; i < NUM_LEDS; i++) {
    Led::ids[i].setRGB(Config::color_bg.r * 0.2, Config::color_bg.g * 0.2, Config::color_bg.b * 0.2);
  }

  for(int i = 0; i < 5; i++) {
    Led::ids[Led::getLedId(Grid_de_SCHWAEBISCH::time_it_is[i])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
  }

  for(int m = 0; m < 12; m++) {
    if(Grid_de_SCHWAEBISCH::time_minutes[minute][m] >= 0) {
      Led::ids[Led::getLedId(Grid_de_SCHWAEBISCH::time_minutes[minute][m])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    }
  }

  if(hour == 1 && minute == 0) {
    hourLimit = 3;
  }

  for(int h = 0; h < hourLimit; h++) {
    if(Grid_de_SCHWAEBISCH::time_hours[hour][h] >= 0) {
      Led::ids[Led::getLedId(Grid_de_SCHWAEBISCH::time_hours[hour][h])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    }
  }

  if(GRID_SINGLE_MINUTES == 1) {
    // single minutes
    for(int s = (NUM_LEDS - 4); s < (NUM_LEDS - 4 + singleMinute); s++) {
      Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    }
  } else {
    for(int s = 0; s < singleMinute; s++) {
      Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    }
  }

  FastLED.setBrightness(Config::brightness * 255);
  FastLED.show();
}

int Grid_de_SCHWAEBISCH::time_it_is[6] = {0, 1, 3, 4, 5, 6}; // es isch

int Grid_de_SCHWAEBISCH::time_minutes[12][18] = {
  { -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // "uhr" brauchs net im schaebischen
  { 13,  14,  15,  16,  27,  28,  29,  30,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // femf nach
  { 18,  19,  20,  21,  27,  28,  29,  30,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // zeah nach
  { 37,  38,  39,  40,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // viertel
  { 18,  19,  20,  21,  23,  24,  25,  48,  49,  50,  51,  52,  53,  -1,  -1,  -1,  -1,  -1}, // zeah vor halber
  { 13,  14,  15,  16,  23,  24,  25,  48,  49,  50,  51,  52,  53,  -1,  -1,  -1,  -1,  -1}, // femf vor halber
  { 48,  49,  50,  51,  52,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // halber
  { 13,  14,  15,  16,  27,  28,  29,  30,  48,  49,  50,  51,  52,  53,  -1,  -1,  -1,  -1}, // femf nach halber
  { 13,  14,  15,  16,  23,  24,  25,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43}, // femf vor dreiviertel
  { 33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // dreiviertel
  { 18,  19,  20,  21,  23,  24,  25,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // zeah vor
  { 13,  14,  15,  16,  23,  24,  25,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}  // femf vor
};

int Grid_de_SCHWAEBISCH::time_hours[12][7] = {
  { 60,  61,  62,  63,  64,  65,  -1}, // zwelfe
  {106, 107, 108,  -1,  -1,  -1,  -1}, // ois
  {104, 105, 106, 107,  -1,  -1,  -1}, // zwoi
  { 84,  85,  86,  -1,  -1,  -1,  -1}, // drei
  { 99, 100, 101, 102, 103,  -1,  -1}, // viere
  { 70,  71,  72,  73,  74,  -1,  -1}, // femfe
  { 90,  91,  92,  93,  94,  95,  -1}, // sechse
  { 77,  78,  79,  80,  81,  82,  83}, // siebene
  { 55,  56,  57,  58,  59,  -1,  -1}, // achde
  {115, 116, 117, 118, 119,  -1,  -1}, // neine
  {112, 113, 114, 115, 116,  -1,  -1}, // zehne
  { 62,  63,  64,  65,  -1,  -1,  -1}  // elfe
};
