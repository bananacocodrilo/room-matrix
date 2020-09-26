
#define ESP32_MRFAPTASTIC_PINOUT 99
#define GPIOPINOUT ESP32_MRFAPTASTIC_PINOUT

#include <SmartMatrix3.h>
#include "colorwheel.c"
#include "gimpbitmap.h"

#define COLOR_DEPTH 24
// known working: 24, 48 - If the sketch uses type `rgb24` directly COLOR_DEPTH
// must be 24

const uint8_t kMatrixWidth = 64;  // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 32; // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 36; // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 4;
// known working: 2-4, use 2 to save memory, more to keep from dropping
// frames and automatically lowering refresh rate

const uint8_t kPanelType =
    SMARTMATRIX_HUB75_64ROW_MOD32SCAN; // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN
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

const int brightness = (100 * 255) / 100; // full (100%) brightness
const int defaultScrollOffset = 6;
const rgb24 backgroundColor = {0x40, 0, 0};
static bool showTime = false;