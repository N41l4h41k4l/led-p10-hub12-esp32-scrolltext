/*
  LED P10 HUB12 - PIN TEST PROGRAM
  Target: ESP32 NodeMCU-32S
  
  Gunakan program ini untuk testing setiap pin jika LED tidak menyala.
  Program akan menampilkan pattern test pada display.
  
  Pin Configuration:
  GPIO 15 → OE (Pin 9 HUB12)
  GPIO 19 → A (Pin 4 HUB12)
  GPIO 23 → B (Pin 3 HUB12)
  GPIO 18 → CLK (Pin 7 HUB12)
  GPIO 5 → LAT (Pin 8 HUB12)
  GPIO 22 → DATA (Pin 10 HUB12)
*/

#include <SPI.h>
#include <DMD32.h>
#include "fonts/SystemFont5x7.h"

// ===== KONFIGURASI =====
#define DISPLAYS_WIDE 2
#define DISPLAYS_HIGH 1

// ===== PIN DEFINITIONS =====
#define PIN_OE    15   // Output Enable
#define PIN_A     19   // Row A
#define PIN_B     23   // Row B
#define PIN_CLK   18   // Clock
#define PIN_LAT   5    // Latch/Strobe
#define PIN_DATA  22   // Data

// ===== INISIALISASI =====
DMD dmd(DISPLAYS_WIDE, DISPLAYS_HIGH);
hw_timer_t * timer = NULL;

void IRAM_ATTR triggerScan() {
  dmd.scanDisplayBySPI();
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(500);
  
  Serial.println("\n\n========================================");
  Serial.println("  LED P10 HUB12 - PIN TEST PROGRAM");
  Serial.println("  ESP32 NodeMCU-32S");
  Serial.println("========================================\n");
  
  // Initialize pins
  Serial.println("[TEST] Initializing GPIO pins...");
  pinMode(PIN_OE, OUTPUT);
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_LAT, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  Serial.println("[TEST] GPIO pins initialized!\n");
  
  // Timer setup
  Serial.println("[TEST] Setting up timer interrupt...");
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &triggerScan);
  timerAlarm(timer, 1000, true, 0);
  Serial.println("[TEST] Timer interrupt ready!\n");
  
  // DMD setup
  Serial.println("[TEST] Initializing DMD display...");
  dmd.clearScreen(true);
  dmd.selectFont(SystemFont5x7);
  Serial.println("[TEST] DMD display ready!\n");
  
  // Display startup
  dmd.drawString(0, 0, "TEST MODE ON");
  delay(2000);
  dmd.clearScreen(true);
  
  Serial.println("========================================");
  Serial.println("\nStarting pin tests...\n");
}

// ===== MAIN LOOP =====
void loop() {
  // Test 1: Display all pixels ON
  Serial.println("[TEST 1] All pixels ON (fill display)");
  testAllPixelsOn();
  delay(2000);
  
  // Test 2: Display checkerboard pattern
  Serial.println("[TEST 2] Checkerboard pattern");
  testCheckerboard();
  delay(2000);
  
  // Test 3: Display lines
  Serial.println("[TEST 3] Horizontal lines");
  testHorizontalLines();
  delay(2000);
  
  // Test 4: Display columns
  Serial.println("[TEST 4] Vertical lines");
  testVerticalLines();
  delay(2000);
  
  // Test 5: Display text
  Serial.println("[TEST 5] Text display");
  testTextDisplay();
  delay(2000);
  
  // Test 6: Brightness test (PWM)
  Serial.println("[TEST 6] Brightness levels");
  testBrightness();
  delay(2000);
  
  // Test 7: Pixel test
  Serial.println("[TEST 7] Individual pixel test");
  testIndividualPixels();
  delay(2000);
  
  Serial.println("\n[CYCLE] All tests completed!\n\n");
}

// ===== TEST FUNCTIONS =====

void testAllPixelsOn() {
  dmd.clearScreen(true);
  
  // Draw filled rectangle (all pixels)
  int width = 32 * DISPLAYS_WIDE;
  int height = 16 * DISPLAYS_HIGH;
  
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      dmd.writePixel(x, y, GRAPHICS_ON);
    }
  }
  
  Serial.println("  → Display should be FULL WHITE\n");
}

void testCheckerboard() {
  dmd.clearScreen(true);
  
  int width = 32 * DISPLAYS_WIDE;
  int height = 16 * DISPLAYS_HIGH;
  
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if ((x + y) % 2 == 0) {
        dmd.writePixel(x, y, GRAPHICS_ON);
      }
    }
  }
  
  Serial.println("  → Display should show checkerboard pattern\n");
}

void testHorizontalLines() {
  dmd.clearScreen(true);
  
  int width = 32 * DISPLAYS_WIDE;
  int height = 16 * DISPLAYS_HIGH;
  
  for (int y = 0; y < height; y += 2) {
    for (int x = 0; x < width; x++) {
      dmd.writePixel(x, y, GRAPHICS_ON);
    }
  }
  
  Serial.println("  → Display should show horizontal stripes\n");
}

void testVerticalLines() {
  dmd.clearScreen(true);
  
  int width = 32 * DISPLAYS_WIDE;
  int height = 16 * DISPLAYS_HIGH;
  
  for (int x = 0; x < width; x += 2) {
    for (int y = 0; y < height; y++) {
      dmd.writePixel(x, y, GRAPHICS_ON);
    }
  }
  
  Serial.println("  → Display should show vertical stripes\n");
}

void testTextDisplay() {
  dmd.clearScreen(true);
  
  dmd.drawString(0, 0, "TEST");
  dmd.drawString(0, 8, "MODE");
  
  Serial.println("  → Display should show 'TEST' and 'MODE'\n");
}

void testBrightness() {
  // Brightness control via OE pin
  // Higher value = dimmer, lower value = brighter
  
  dmd.clearScreen(true);
  
  // Draw test pattern
  int width = 32 * DISPLAYS_WIDE;
  int height = 16 * DISPLAYS_HIGH;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      dmd.writePixel(x, y, GRAPHICS_ON);
    }
  }
  
  Serial.println("  → Brightness should change (PWM on GPIO 15)");
  Serial.println("  → If brightness doesn't change, check GPIO 15\n");
}

void testIndividualPixels() {
  dmd.clearScreen(true);
  
  // Draw corners
  dmd.writePixel(0, 0, GRAPHICS_ON);
  dmd.writePixel((32 * DISPLAYS_WIDE) - 1, 0, GRAPHICS_ON);
  dmd.writePixel(0, (16 * DISPLAYS_HIGH) - 1, GRAPHICS_ON);
  dmd.writePixel((32 * DISPLAYS_WIDE) - 1, (16 * DISPLAYS_HIGH) - 1, GRAPHICS_ON);
  
  // Draw center
  dmd.writePixel(16 * DISPLAYS_WIDE / 2, 8, GRAPHICS_ON);
  
  Serial.println("  → Display should show 4 corner pixels + center pixel\n");
}

/*
  ===== INTERPRETASI TEST RESULTS =====
  
  Jika test 1-5 JALAN:
  → Hardware OK, library OK
  → Problem ada di code atau konfigurasi
  
  Jika test 1-5 TIDAK JALAN:
  → Cek:
    1. Power supply +5V dan GND
    2. Koneksi kabel HUB12
    3. GND terhubung ke 2 tempat (ESP32 + PSU)
    4. Library DMD32 terinstal dengan benar
  
  Jika hanya test 6 (brightness) tidak jalan:
  → Problem di GPIO 15 (OE pin)
  
  Jika pattern bergeser/tidak akurat:
  → Problem di GPIO 18, 5, 22 (CLK, LAT, DATA)
  → Cek kecepatan SPI di library DMD32
*/
