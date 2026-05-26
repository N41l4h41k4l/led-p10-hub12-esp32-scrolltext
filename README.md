# LED P10 HUB12 dengan ESP32 NodeMCU - Scroll Text

Program untuk menampilkan scroll text pada 2 modul LED P10 SMD menggunakan ESP32 NodeMCU dengan connector HUB12.

## 📋 Spesifikasi Hardware

### Komponen yang Digunakan
- **Mikrokontroler:** ESP32 NodeMCU-32S
- **Display:** 2x Modul LED P10 SMD (HUB12 Connector)
- **Power Supply:** 5V (untuk LED P10)
- **IC Driver:** ULN2003 (Darlington Array Driver)
- **IC Logic:** 74HC04 (Inverter)

### Wiring Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                      ESP32 NodeMCU-32S                          │
│                                                                 │
│  GPIO 15 ─────────────────��────┐                              │
│  GPIO 19 ──────────────────────┼──→ HUB12 Connector           │
│  GPIO 23 ──────────────────────┼──→ (Modul P10 1 & 2)         │
│  GPIO 18 ──────────────────────┼──→                            │
│  GPIO 5  ──────────────────────┼──→                            │
│  GPIO 22 ──────────────────────┼──→                            │
│  GND ──────────────────────────┴──→                            │
│                                                                 │
│  +5V ────────────────────────────────→ PSU P10 Positif        │
│  GND ────────────────────────────────→ PSU P10 Negatif        │
└─────────────────────────────────────────────────────────────────┘
```

### Pin Configuration HUB12

| Fungsi P10 | Pin ESP32 | Pin HUB12 | Keterangan |
|-----------|----------|----------|----------|
| OE (Output Enable) | GPIO 15 | 9 | Kontrol brightness |
| A (Row Select A) | GPIO 19 | 4 | Pemilihan baris A |
| B (Row Select B) | GPIO 23 | 3 | Pemilihan baris B |
| CLK (Clock) | GPIO 18 | 7 | SPI Clock |
| LAT/STB (Latch) | GPIO 5 | 8 | Strobe/Latch signal |
| R/DATA (Red Data) | GPIO 22 | 10 | Data input |
| GND | GND | 1, 2, 11, 12 | Ground |
| +5V | +5V PSU | 15, 16 | Power supply |

## 🔧 Setup Arduino IDE

### Board & Library
- **IDE:** Arduino IDE 2.3.8
- **Board:** NodeMCU-32S (ESP32)
- **Library:** DMD32 v1.0 by Khuddur Abdullaah Alfarhan

## 🚀 Quick Start

1. **Clone repository:**
   ```bash
   git clone https://github.com/N41l4h41k4l/led-p10-hub12-esp32-scrolltext.git
   cd led-p10-hub12-esp32-scrolltext
   ```

2. **Buka scroll_text_2modul.ino di Arduino IDE**

3. **Setup:**
   - Tools → Board → NodeMCU-32S
   - Tools → Port → [Pilih COM port ESP32]
   - Sketch → Include Library → Manage Libraries → Install DMD32

4. **Upload & Run**
   - Sketch → Upload (Ctrl+U)
   - Tools → Serial Monitor (115200 baud)

## 📁 File Project

- `scroll_text_2modul.ino` - Program utama (scroll text untuk 2 modul)
- `test_pin_esp32.ino` - Program test pin (untuk debug/diagnosis)
- `README.md` - Dokumentasi ini
- `docs/` - Folder dokumentasi lengkap
  - `hub12_pinout.md` - Detail pin HUB12
  - `troubleshooting.md` - Panduan troubleshooting lengkap
  - `pin_configuration.md` - Penjelasan detail setiap pin

## 🎯 Fitur Program

### scroll_text_2modul.ino
- ✅ Scroll text berjalan untuk 2 modul P10 (64x16 pixel)
- ✅ Customizable text (ubah string `scrollText`)
- ✅ Kecepatan scroll dapat diatur (`SCROLL_SPEED`)
- ✅ Brightness control (`BRIGHTNESS`)
- ✅ Serial monitor untuk debug
- ✅ Timer interrupt untuk refresh smooth
- ✅ Comments lengkap untuk dipelajari

### test_pin_esp32.ino
- ✅ Test 7 pattern berbeda
- ✅ Diagnosis pin yang error
- ✅ Checklist manual debugging
- ✅ Sangat berguna jika LED tidak menyala

## 🐛 Troubleshooting

### LED Tidak Menyala Sama Sekali
1. Cek power supply +5V dengan multimeter (harus 5V)
2. Cek GND connected ke 2 tempat (ESP32 dan PSU)
3. Jalankan `test_pin_esp32.ino`
4. Baca `docs/troubleshooting.md` untuk langkah detail

### LED Menyala Tapi Tidak Ada Teks
1. Cek `DISPLAYS_WIDE` dan `DISPLAYS_HIGH` di code
2. Install ulang library DMD32
3. Cek serial monitor untuk error messages

### Teks Berkedip/Flickering
1. Cek power supply stabil 5V
2. Kuatkan koneksi GND
3. Naikkan `SCROLL_SPEED` value
4. Gunakan kabel berkualitas yang lebih tebal

### Hanya Sebagian LED Nyala
1. Test dengan `test_pin_esp32.ino`
2. Cek pin A, B, CLK, DATA
3. Baca `docs/troubleshooting.md` untuk detail

## 📚 Dokumentasi Lengkap

- **hub12_pinout.md** - Penjelasan semua 16 pin HUB12
- **pin_configuration.md** - Diagram koneksi, timing, voltage levels
- **troubleshooting.md** - 5 masalah umum dengan solusi step-by-step

## 💡 Cara Menggunakan

### Mengubah Teks yang Ditampilkan
```cpp
// Di scroll_text_2modul.ino, cari baris:
String scrollText = "SMK BISA - IOT ESP32 P10";

// Ubah teks sesuai keinginan:
String scrollText = "TEKS ANDA DI SINI";

// Save (Ctrl+S) dan Upload (Ctrl+U)
```

### Mengubah Kecepatan Scroll
```cpp
// Di bagian atas:
#define SCROLL_SPEED 30  // Satuan: milliseconds

// Naikkan nilai untuk scroll lebih lambat:
#define SCROLL_SPEED 50  // Lebih lambat
#define SCROLL_SPEED 100 // Paling lambat

// Turunkan nilai untuk scroll lebih cepat:
#define SCROLL_SPEED 20  // Lebih cepat
#define SCROLL_SPEED 10  // Paling cepat
```

### Mengubah Brightness
```cpp
#define BRIGHTNESS 100  // 0-255 (0=gelap, 255=terang)

// Contoh:
#define BRIGHTNESS 50   // Lebih redup
#define BRIGHTNESS 200  // Lebih terang
```

## ⚠️ Penting!

- **GND HARUS connected ke 2 tempat:** ESP32 dan PSU P10
- **Power supply minimum 2A** untuk 2 modul P10
- **Gunakan kabel berkualitas** untuk menghindari voltage drop
- **Jangan ubah pin configuration** kecuali Anda tahu apa yang dilakukan

## 📧 Support

Jika ada masalah:
1. Baca file `docs/troubleshooting.md`
2. Jalankan `test_pin_esp32.ino`
3. Cek serial monitor untuk error messages
4. Post di GitHub Issues dengan detail lengkap

## 📖 Referensi

- [ESP32 Documentation](https://docs.espressif.com/projects/esp32-arduino/en/latest/)
- [DMD32 Library GitHub](https://github.com/khuddur/DMD32)
- [HUB12 Connector Standard](http://www.lclark.net/~chb/hub12.txt)

---

**Version:** 1.0  
**Target:** ESP32 NodeMCU-32S + LED P10 HUB12 SMD  
**Created:** 2026  
**License:** MIT
