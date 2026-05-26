/*
  LED P10 HUB12 Scroll Text - 2 Modul
  Target: ESP32 NodeMCU-32S
  Library: DMD32 v1.0
  
  Fitur:
  - Scroll text untuk 2 modul P10 (64x16 pixel)
  - Customizable text & speed
  - Brightness control
  - Serial monitor debug
  
  Pin Configuration:
  GPIO 15 → OE (Pin 9 HUB12)
  GPIO 19 → A (Pin 4 HUB12)
  GPIO 23 → B (Pin 3 HUB12)
  GPIO 18 → CLK (Pin 7 HUB12)
  GPIO 5 → LAT (Pin 8 HUB12)
  GPIO 22 → DATA (Pin 10 HUB12)
  GND → Pin 1,2,11,12 HUB12 + PSU Ground
  +5V PSU → Pin 15,16 HUB12
*/

#include <SPI.h>
#include <DMD32.h>
#include "fonts/SystemFont5x7.h"

// ===== KONFIGURASI DISPLAY =====
#define DISPLAYS_WIDE 2      // 2 modul horizontal
#define DISPLAYS_HIGH 1      // 1 modul vertikal
#define BRIGHTNESS 100       // Brightness 0-255
#define SCROLL_SPEED 30      // Kecepatan scroll (ms)

// ===== INISIALISASI DMD =====
DMD dmd(DISPLAYS_WIDE, DISPLAYS_HIGH);

// ===== TIMER INTERRUPT =====
hw_timer_t * timer = NULL;

void IRAM_ATTR triggerScan() {
  dmd.scanDisplayBySPI();
}

// ===== SETUP =====
void setup() {
  // Serial communication untuk debug
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n\n");
  Serial.println("=====================================");
  Serial.println("  LED P10 HUB12 - Scroll Text");
  Serial.println("  ESP32 NodeMCU-32S");
  Serial.println("=====================================");
  Serial.println();
  
  // Timer setup untuk ESP32
  Serial.println("[SETUP] Initializing timer...");
  timer = timerBegin(1000000);              // 1 MHz
  timerAttachInterrupt(timer, &triggerScan);
  timerAlarm(timer, 1000, true, 0);         // Refresh setiap 1ms
  Serial.println("[SETUP] Timer initialized!");
  
  // DMD setup
  Serial.println("[SETUP] Initializing DMD display...");
  dmd.clearScreen(true);
  dmd.selectFont(SystemFont5x7);
  Serial.println("[SETUP] DMD display ready!");
  
  Serial.println();
  Serial.println("Configuration:");
  Serial.print("  - Display Size: ");
  Serial.print(DISPLAYS_WIDE * 32);
  Serial.print(" x ");
  Serial.println(DISPLAYS_HIGH * 16);
  Serial.print("  - Brightness: ");
  Serial.println(BRIGHTNESS);
  Serial.print("  - Scroll Speed: ");
  Serial.println(SCROLL_SPEED);
  Serial.println();
  Serial.println("=====================================");
  Serial.println();
  
  // Display startup message
  dmd.drawString(0, 0, "STARTING...");
  delay(2000);
  dmd.clearScreen(true);
}

// ===== MAIN LOOP =====
void loop() {
  // Text yang akan ditampilkan
  String scrollText = "SMK BISA - IOT ESP32 P10";
  
  // Print ke serial monitor
  Serial.print("[SCROLL] ");
  Serial.println(scrollText);
  
  // Setup marquee (scrolling text)
  int textWidth = scrollText.length() * 6; // Approximate width
  int displayWidth = (32 * DISPLAYS_WIDE) - 1;
  
  dmd.drawMarquee(
    scrollText.c_str(),
    scrollText.length(),
    displayWidth,
    0
  );
  
  // Animate scroll
  long startTime = millis();
  long lastUpdate = startTime;
  bool finished = false;
  
  while (!finished) {
    long currentTime = millis();
    
    // Update scroll setiap SCROLL_SPEED milliseconds
    if ((currentTime - lastUpdate) >= SCROLL_SPEED) {
      finished = dmd.stepMarquee(-1, 0);
      lastUpdate = currentTime;
    }
  }
  
  long endTime = millis();
  Serial.print("[SCROLL] Duration: ");
  Serial.print(endTime - startTime);
  Serial.println(" ms");
  
  // Pause sebelum repeat
  dmd.clearScreen(true);
  delay(1000);
}

/*
  ===== PIN CONFIGURATION =====
  
  Koneksi P10 HUB12 ke ESP32:
  
  P10 Pin | Function | ESP32 Pin | Notes
  --------|----------|-----------|--------
  1,2,11,12 | GND    | GND       | HARUS konek 2 tempat (ESP32 + PSU)
  3       | B        | GPIO 23   | Row Select B
  4       | A        | GPIO 19   | Row Select A
  7       | CLK      | GPIO 18   | Clock signal
  8       | LAT/STB  | GPIO 5    | Latch/Strobe
  9       | OE       | GPIO 15   | Output Enable
  10      | DATA/R   | GPIO 22   | Data input
  15,16   | +5V      | +5V PSU   | Power supply
  
  ===== TROUBLESHOOTING =====
  
  1. LED tidak menyala:
     - Cek power supply +5V dan GND
     - Cek koneksi GND ke 2 tempat
     - Run test_pin_esp32.ino
  
  2. LED nyala tapi tidak ada teks:
     - Check DISPLAYS_WIDE dan DISPLAYS_HIGH
     - Verify baud rate di serial monitor
     - Install ulang library DMD32
  
  3. Teks flicker/berkedip:
     - Cek power supply stabil 5V
     - Increase SCROLL_SPEED value
     - Use thicker/better quality cables
*/
