# HUB12 Connector Pinout Detail

## Overview HUB12 Standard

HUB12 adalah connector 16-pin standar untuk modul LED P10.
Connector ini menggunakan format 2 baris x 8 kolom.

## Pin Configuration

```
View dari depan (kabel masuk):

Baris 1 (Atas):    1   2   3   4   5   6   7   8
Baris 2 (Bawah):   9  10  11  12  13  14  15  16

Atau dalam bentuk tabel:

┌────────────────────────────────────────┐
│  1   2   3   4   5   6   7   8 │
│  9  10  11  12  13  14  15  16 │
└────────────────────────────────────────┘
```

## Pin Details

### Pin 1, 2, 11, 12 = GND (Ground)
- **Fungsi:** Ground/Negative
- **Jumlah:** 4 pin
- **Keterangan:** HARUS terhubung ke GND ESP32 DAN negatif PSU P10
- **Penting:** Jangan skip pin GND mana pun!

### Pin 3 = B (Row Select B)
- **Fungsi:** Pemilihan baris B
- **Tipe:** Digital Output (3.3V dari ESP32)
- **Koneksi:** GPIO 23
- **Catatan:** Untuk P10 16 baris, pin ini untuk row address bit 1

### Pin 4 = A (Row Select A)
- **Fungsi:** Pemilihan baris A
- **Tipe:** Digital Output (3.3V dari ESP32)
- **Koneksi:** GPIO 19
- **Catatan:** Row address bit 0

### Pin 7 = CLK (Clock)
- **Fungsi:** Clock signal untuk shift register
- **Tipe:** Digital Output (3.3V dari ESP32)
- **Koneksi:** GPIO 18
- **Catatan:** Merupakan sinyal SPI Clock
- **Kecepatan:** Biasanya 1-10 MHz

### Pin 8 = LAT/STB (Latch/Strobe)
- **Fungsi:** Latch signal untuk mengunci data
- **Tipe:** Digital Output (3.3V dari ESP32)
- **Koneksi:** GPIO 5
- **Catatan:** Pulse untuk lock data ke display
- **Durasi:** Minimal 1 microsecond

### Pin 9 = OE (Output Enable)
- **Fungsi:** Kontrol output/brightness
- **Tipe:** Digital Output (3.3V dari ESP32)
- **Koneksi:** GPIO 15
- **Catatan:** Aktif LOW (0 = ON, 1 = OFF)
- **PWM:** Bisa digunakan untuk kontrol brightness

### Pin 10 = DATA/R (Data Input - Red)
- **Fungsi:** Data input untuk warna merah
- **Tipe:** Digital Output (3.3V dari ESP32)
- **Koneksi:** GPIO 22
- **Catatan:** Merupakan sinyal SPI MOSI
- **Catatan2:** Untuk modul satu warna, ini adalah data input utama

### Pin 13, 14 = NC (Not Connected)
- **Fungsi:** Tidak digunakan
- **Status:** Biarkan kosong

### Pin 15, 16 = +5V (Power Supply)
- **Fungsi:** Power supply 5V
- **Jumlah:** 2 pin
- **Keterangan:** HARUS terhubung ke +5V dari PSU P10
- **Penting:** Jangan hubungkan ke ESP32 +5V pin (kapasitas terbatas)

## Tabel Lengkap

| Pin | Fungsi | Tipe | ESP32 GPIO | Catatan |
|-----|--------|------|-----------|----------|
| 1 | GND | Power | GND | Ground pin 1 |
| 2 | GND | Power | GND | Ground pin 2 |
| 3 | B | Signal | GPIO 23 | Row Select B |
| 4 | A | Signal | GPIO 19 | Row Select A |
| 7 | CLK | Signal | GPIO 18 | SPI Clock |
| 8 | LAT/STB | Signal | GPIO 5 | Latch/Strobe |
| 9 | OE | Signal | GPIO 15 | Output Enable (PWM) |
| 10 | DATA/R | Signal | GPIO 22 | Data Input |
| 11 | GND | Power | GND | Ground pin 3 |
| 12 | GND | Power | GND | Ground pin 4 |
| 13 | NC | - | - | Not Connected |
| 14 | NC | - | - | Not Connected |
| 15 | +5V | Power | +5V PSU | Power pin 1 |
| 16 | +5V | Power | +5V PSU | Power pin 2 |

## Testing Tips

1. **Gunakan multimeter** untuk test koneksi pin
2. **Jalankan test_pin_esp32.ino** untuk diagnosa
3. **Cek semua GND pin** (sering terabaikan)
4. **Gunakan kabel yang bagus** (tidak longgar)
5. **Test satu pin sekaligus** jika error

---

**Referensi:** HUB12 Standard LED Display Interface
