# Pin Configuration Penjelasan Detail

## Diagram Koneksi Fisik

```
ESP32 NodeMCU-32S ─────────────────────── LED P10 (HUB12)

┌──────────────────────────────────────┐               ┌──────────────────────┐
│   ESP32 NodeMCU      │               │  P10 HUB12      │
│       -32S           │               │   Connector     │
│                      │               │                 │
│ GPIO 15 (OE)    ─────┼───────────────┼──────────→ Pin 9 (OE)   │
│ GPIO 19 (A)     ─────┼───────────────┼──────────→ Pin 4 (A)    │
│ GPIO 23 (B)     ─────┼───────────────┼──────────→ Pin 3 (B)    │
│ GPIO 18 (CLK)   ─────┼───────────────┼──────────→ Pin 7 (CLK)  │
│ GPIO 5 (LAT)    ─────┼───────────────┼──────────→ Pin 8 (LAT)  │
│ GPIO 22 (DATA)  ─────┼───────────────┼──────────→ Pin 10 (R)   │
│ GND             ─────┼───────────────┼──────────→ Pin 1,2,11,12│
│                      │               │  (GND)         │
└──────────────────────────────────────┘               └──────────────────────┘

+5V PSU ──────────────────────────────────────────────→ Pin 15, 16 (+5V)
GND PSU ──────────────────────────────────────────────→ Pin 1,2,11,12 (GND)
```

## Penjelasan Setiap Signal

### 1. GPIO 15 → Pin 9 (OE - Output Enable)

**Fungsi:** Mengontrol on/off LED display

**Logika:**
- OE = LOW (0V) → LED ON (menyala)
- OE = HIGH (3.3V) → LED OFF (mati)

**Penggunaan untuk Brightness:**
```cpp
// PWM untuk kontrol brightness
ledcSetup(0, 5000, 8);              // Channel 0, 5kHz, 8-bit
ledcAttachPin(15, 0);               // Attach GPIO 15
ledcWrite(0, brightness_value);     // 0-255
```

**Catatan:** Aktif LOW, jangan lupa!

### 2. GPIO 19 → Pin 4 (A - Row Address Bit 0)

**Fungsi:** Pemilihan baris (row) di display

**Logika Row Selection (2-bit):**
```
A (GPIO 19) | B (GPIO 23) | Baris yang dipilih
────────────┼─────────────┼──────────────────
     0      |      0      | Baris 0-3
     1      |      0      | Baris 4-7
     0      |      1      | Baris 8-11
     1      |      1      | Baris 12-15
```

**Catatan:** Untuk P10 standar 16 baris, hanya perlu 2 bit (A, B)

### 3. GPIO 23 → Pin 3 (B - Row Address Bit 1)

**Fungsi:** Pemilihan baris (row) di display

**Catatan:** Lihat tabel di atas (A & B bersamaan)

### 4. GPIO 18 → Pin 7 (CLK - Clock)

**Fungsi:** Sinyal clock untuk shift register

**Karakteristik:**
- Tipe: Digital Output (3.3V)
- Frekuensi: 1-10 MHz (tergantung library)
- Pulsa untuk menggeser data 1 bit per pulsa

**Timing (contoh 1 MHz):**
```
─┬  ┬─┬  ┬─┬  ┬─┬  ┬─┬
 ┴──┘ ┴──┘ ┴��─┘ ┴──┘ ┴──┘  (1 microsecond per bit)

  1   2   3   4     (bit shifted in)
```

**Catatan:** Standar SPI Clock dari ESP32

### 5. GPIO 5 → Pin 8 (LAT/STB - Latch/Strobe)

**Fungsi:** Mengunci data yang sudah di-shift ke output

**Operasi:**
```
1. Shift data masuk via GPIO 22 & CLK
2. Data tersimpan di shift register
3. Pulse LAT (Pin 8) untuk "lock" data
4. Output berubah sesuai data yang di-lock
```

**Timing:**
```
Data & CLK: ─────┬      ┬─────
               └──────┘
              (data in)

LAT:        ─────────────┬  ┬─
                       └──┘
                     (pulse)

Output:     ─────────────────●  (berubah saat LAT pulse)
                          └─────
```

**Durasi:** Minimal 1 microsecond pulse

### 6. GPIO 22 → Pin 10 (R/DATA - Red Data Input)

**Fungsi:** Data input untuk LED pixel

**Karakteristik:**
- Tipe: Serial data input (SPI MOSI)
- Format: MSB first
- 1 baris = 32 pixel (untuk modul 32 wide)

**Data Format (Per Baris):**
```
Bit 31-0: RGB data untuk 32 pixel

Pixel 0: Bit 31-24 (RGB)
Pixel 1: Bit 23-16 (RGB)
...
Pixel 31: Bit 7-0 (RGB)
```

**Catatan:** Untuk modul satu warna, hanya "RED" data digunakan

### 7. GND (Multiple Pins)

**Fungsi:** Ground/Negative reference

**Pins:** 1, 2, 11, 12 (semua adalah GND)

**PENTING:**
- ⚠️ SEMUA pin GND harus connected
- ⚠️ HARUS connected ke 2 tempat:
  1. GND dari ESP32
  2. GND dari PSU P10 (negatif)

**Alasan:**
- Untuk distribusi current yang baik
- Menghindari ground bounce
- Menjamin voltage reference yang stabil

### 8. +5V Power Supply

**Pins:** 15, 16 (semua adalah +5V)

**Sumber:** Dari PSU P10 (bukan dari ESP32)

**Alasan:** 
- ESP32 GPIO pin tidak bisa supply arus besar
- P10 LED membutuhkan arus 1-3A
- Harus dari dedicated power supply

**Spesifikasi PSU:**
- Voltage: 5V (±5%)
- Current: Minimum 2A untuk 2 modul
- Quality: Regulated power supply

---

## Voltage Levels

### ESP32 Output (GPIO)
- Low (0): < 0.5V
- High (1): > 2.0V (nominal 3.3V)
- Output current: ~40mA per pin (total ~100mA)

### P10 Module Input (HUB12)
- Logic compatible: TTL/CMOS 5V tolerant
- Input threshold: ~2.0V (untuk HIGH)
- Input current: <10mA per pin

### Conclusion:
✅ ESP32 3.3V output → P10 5V tolerant input = **OK**

---

## Checklist Final

- [ ] Semua 7 GPIO sudah dihubungkan ke pin HUB12 yang benar
- [ ] GND connected ke ESP32 AND PSU
- [ ] +5V connected ke PSU (bukan ESP32 power pin)
- [ ] Power supply stabil 5V
- [ ] Semua kabel tersambung kuat (tidak longgar)
- [ ] Menggunakan GPIO pin yang tidak berkonflik
- [ ] Library DMD32 sudah install dengan benar

---

**Reference:** ESP32 Technical Reference Manual & HUB12 Standard
