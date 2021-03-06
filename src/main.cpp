
#define ESP32_MRFAPTASTIC_PINOUT 99
#define GPIOPINOUT ESP32_MRFAPTASTIC_PINOUT

#include <SmartMatrix3.h>
#include "colorwheel.c"
#include "gimpbitmap.h"

#define COLOR_DEPTH                                                            \
  24 // known working: 24, 48 - If the sketch uses type `rgb24` directly,
     // COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 64;  // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 32; // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 36; // known working: 24, 36, 48
const uint8_t kDmaBufferRows =
    4; // known working: 2-4, use 2 to save memory, more to keep from dropping
       // frames and automatically lowering refresh rate
const uint8_t kPanelType =
    SMARTMATRIX_HUB75_32ROW_MOD16SCAN; // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN
                                       // for common 16x32 panels
const uint8_t kMatrixOptions =
    (SMARTMATRIX_OPTIONS_NONE); // see http://docs.pixelmatix.com/SmartMatrix
                                // for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);
const uint8_t kIndexedLayerOptions = (SM_INDEXED_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth,
                             kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth,
                                      kMatrixHeight, COLOR_DEPTH,
                                      kBackgroundLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth,
                                     kMatrixHeight, COLOR_DEPTH,
                                     kScrollingLayerOptions);
SMARTMATRIX_ALLOCATE_INDEXED_LAYER(indexedLayer, kMatrixWidth, kMatrixHeight,
                                   COLOR_DEPTH, kIndexedLayerOptions);

const int defaultBrightness = (100 * 255) / 100; // full (100%) brightness
// const int defaultBrightness = (15*255)/100;       // dim: 15% brightness
const int defaultScrollOffset = 6;
const rgb24 defaultBackgroundColor = {0x40, 0, 0};

// the setup() method runs once, when the sketch starts
void setup() {
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  matrix.addLayer(&backgroundLayer);
  matrix.addLayer(&scrollingLayer);
  matrix.addLayer(&indexedLayer);
  matrix.begin();

  matrix.setBrightness(defaultBrightness);

  scrollingLayer.setOffsetFromTop(defaultScrollOffset);

  backgroundLayer.enableColorCorrection(true);
}

char *TimeToString(unsigned long t) {
  t += 1601124992;
  static char str[12];
  long h = t / 3600;
  h = h % 24;
  t = t % 3600;
  int m = t / 60;
  int s = t % 60;
  sprintf(str, "%02ld:%02d:%02d", h, m, s);
  return str;
}

void loop() {
  scrollingLayer.setColor({0xff, 0xff, 0xff});
  scrollingLayer.setMode(stopped);
  scrollingLayer.setSpeed(5);

  scrollingLayer.start("Hola Migue", 3);
  backgroundLayer.swapBuffers();

  while (1) {
    scrollingLayer.update(TimeToString(millis() / 1000));
    delay(1000);
  }
}
