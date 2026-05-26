# Panduan Troubleshooting LED P10 HUB12 ESP32

## Checklist Awal

Sebelum troubleshooting lebih lanjut, pastikan:

- [ ] Power supply +5V connected dan multimeter menunjukkan 5V
- [ ] Kabel GND connected ke 2 tempat: ESP32 dan PSU P10 negatif
- [ ] Semua pin sudah tersambung (tidak ada yang longgar)
- [ ] Library DMD32 v1.0 sudah install
- [ ] Board: NodeMCU-32S, Port: COM correct, Baud: 115200
- [ ] Code sudah di-upload tanpa error
- [ ] Tombol RESET di ESP32 sudah ditekan

---

## Problem 1: LED TIDAK MENYALA SAMA SEKALI

### Gejala:
- LED P10 gelap total, tidak ada cahaya sama sekali
- Serial monitor: "DMD display ready!" tapi tidak ada di display

### Diagnosis Step-by-Step:

#### Step 1: Cek Power Supply
```
1. Ambil multimeter (mode DC Voltage)
2. Test antara +5V dan GND pada PSU P10
   → Harus menunjukkan 5V (4.8V - 5.2V OK)
3. Jika tidak 5V:
   → Problem: PSU rusak atau kabel putus
   → Solusi: Ganti PSU atau perbaiki kabel

4. Jika sudah 5V, lanjut Step 2
```

#### Step 2: Cek Koneksi GND
```
1. Pastikan GND connected ke 2 tempat:
   a) GND dari ESP32 ke GND modul P10
   b) GND dari PSU ke GND modul P10
   
2. Test dengan multimeter:
   - Probe merah ke +5V PSU
   - Probe hitam ke GND modul P10
   - Harus menunjukkan 5V
   
3. Test setiap pin GND modul (pin 1, 2, 11, 12)
   - Semuanya harus terukur 5V
   
4. Jika ada yang tidak 5V:
   → Ada koneksi yang longgar
   → Cek dan kuatkan kabel GND
```

#### Step 3: Jalankan Test Program
```cpp
// Upload test_pin_esp32.ino
// Lihat di serial monitor:
// - Jika test berjalan: Hardware OK, problem di code
// - Jika tidak berjalan: Problem di hardware
```

#### Step 4: Cek Kabel Satu Per Satu
```
Gunakan multimeter untuk test kontinuitas:

Pin 1 (OE - GPIO 15):
  1. Set multimeter ke continuity/resistance
  2. Probe A ke pin 9 HUB12
  3. Probe B ke GPIO 15 ESP32
  4. Harus bersuara/resisrance 0 Ohm
  5. Jika tidak: Kabel putus, ganti kabel

Ulangi untuk semua pin:
- Pin 3 (B) → GPIO 23
- Pin 4 (A) → GPIO 19
- Pin 7 (CLK) → GPIO 18
- Pin 8 (LAT) → GPIO 5
- Pin 10 (DATA) → GPIO 22
- Pin 1,2,11,12 (GND) → GND
```

#### Step 5: Cek Board Configuration
```
1. Di Arduino IDE:
   Tools → Board → Pastikan "NodeMCU-32S" terpilih
   
2. Pastikan Board terpilih BENAR, bukan:
   - "ESP32 Dev Module"
   - "ESP32 Wrover Module"
   - Yang lain
   
3. Board yang salah → Pin mapping salah → LED tidak jalan
```

### Solusi Ringkas:
1. ✅ Pastikan +5V stabil
2. ✅ Pastikan GND connected 2x
3. ✅ Jalankan test_pin_esp32.ino
4. ✅ Cek kabel tidak longgar
5. ✅ Verifikasi board selection

---

## Problem 2: LED MENYALA TAPI TIDAK ADA TEKS

### Gejala:
- LED P10 nyala (ada cahaya) tapi hanya putih/random pattern
- Teks tidak muncul
- Atau menampilkan pattern aneh

### Penyebab & Solusi:

#### Masalah 1: DISPLAYS_WIDE/HEIGHT Salah
```cpp
// Cek di scroll_text_2modul.ino:

#define DISPLAYS_WIDE 2  // Pastikan sesuai jumlah modul Anda
#define DISPLAYS_HIGH 1

// Jika Anda punya 2 modul bersebelahan → DISPLAYS_WIDE = 2
// Jika Anda punya 2 modul bertumpuk → DISPLAYS_HIGH = 2

// Jika salah:
// 1. Ubah value
// 2. Save (Ctrl+S)
// 3. Upload ulang (Ctrl+U)
```

#### Masalah 2: Font Tidak Cocok
```cpp
// Jika teks muncul tapi weird:
// Coba ubah font di code:

// Baris:
// dmd.selectFont(SystemFont5x7);

// Jika error, coba:
// dmd.selectFont(Arial_Black_16);
// dmd.selectFont(Courier_New_16);
```

#### Masalah 3: Library DMD32 Tidak Terinstal
```
1. Sketch → Include Library → Manage Libraries
2. Search: "DMD32"
3. Install: "DMD32 by Khuddur Abdullaah Alfarhan" v1.0
4. Tunggu sampai selesai
5. Upload ulang code
```

#### Masalah 4: Serial Monitor Menunjukkan Error
```
1. Buka Serial Monitor (Tools → Serial Monitor)
2. Pastikan baud rate: 115200
3. Lihat output:
   - "DMD display ready!" → Library OK
   - "Error: ..." → Ada problem di code
   
4. Jika ada error, copy-paste error ke:
   - GitHub Issues
   - Forum Arduino
```

### Solusi Ringkas:
1. ✅ Cek DISPLAYS_WIDE dan DISPLAYS_HIGH
2. ✅ Install ulang library DMD32
3. ✅ Lihat serial monitor untuk error
4. ✅ Coba font berbeda jika ada pilihan

---

## Problem 3: TEKS BERKEDIP/FLICKER ATAU BERGESER SALAH

### Gejala:
- Teks bergerak-gerak tidak konsisten
- Flickering (berkedip-kedip)
- Pattern bergeser/tidak align

### Penyebab & Solusi:

#### Masalah 1: Power Supply Tidak Stabil
```
1. Cek dengan multimeter:
   - Harus tetap 5V saat display on
   - Jika turun ke 4.5V atau lebih rendah: Problem
   
2. Solusi:
   - Gunakan PSU yang lebih besar (minimum 2A)
   - Gunakan kabel PSU yang lebih tebal
   - Tambahkan kapasitor 1000µF di dekat modul
```

#### Masalah 2: Ground Connection Jelek
```
1. Periksa fisik kabel GND:
   - Ada solder yang longgar?
   - Ada kabel yang terputus?
   
2. Solusi:
   - Re-solder semua koneksi GND
   - Gunakan kabel yang lebih tebal untuk GND
   - Pastikan GND connected ke 2 tempat dengan kuat
```

#### Masalah 3: Kecepatan Scroll Terlalu Cepat
```cpp
// Di scroll_text_2modul.ino:

#define SCROLL_SPEED 30  // Satuan: milliseconds

// Coba naikkan value:
// 30 → 50 → 75 → 100

// Atau ubah BRIGHTNESS:
#define BRIGHTNESS 100   // Naikkan ke 150-200 jika masih flicker
```

#### Masalah 4: Cable Kualitas Rendah
```
1. Gunakan kabel berkualitas:
   - Tidak boleh kabel bekas/lusuh
   - Diameter minimal 0.5mm untuk signal
   - Diameter minimal 1mm untuk power
   
2. Solusi:
   - Ganti semua kabel dengan yang baru
   - Pastikan semua kabel terstrip dengan benar
   - Gunakan pin/header yang berkualitas
```

### Solusi Ringkas:
1. ✅ Cek power supply stabil 5V
2. ✅ Cek dan kuatkan semua koneksi GND
3. ✅ Naikkan SCROLL_SPEED di code
4. ✅ Gunakan kabel berkualitas
5. ✅ Tambahkan kapasitor di power supply

---

## Advanced: Pin Mapping Alternatif

Jika GPIO standard tidak cocok, bisa ganti:

```cpp
// Di scroll_text_2modul.ino, ubah PIN definitions:

#define PIN_OE    15   // Coba: 13, 14, 12
#define PIN_A     19   // Coba: 32, 33, 34
#define PIN_B     23   // Coba: 25, 26, 27
#define PIN_CLK   18   // Coba: 17, 9, 10 (jarang)
#define PIN_LAT   5    // Coba: 4, 21, 35
#define PIN_DATA  22   // Coba: 21, 23, 25

// Pastikan GPIO yang dipilih tidak digunakan komponen lain
```

---

## Diagram Alur Troubleshooting

```
LED Tidak Menyala?
    ↓
[YA] → Cek Power Supply 5V
    ↓
    [OK] → Cek GND Connection (2x)
    ↓
    [OK] → Run test_pin_esp32.ino
    ↓
    [OK] → Problem di code/configuration
    [ERROR] → Problem di GPIO/Hardware

LED Menyala Tapi Tidak Ada Teks?
    ↓
Cek DISPLAYS_WIDE/HEIGHT
    ↓
[OK] → Cek Library DMD32
    ↓
[OK] → Cek Serial Monitor untuk error

Teks Berkedip/Flickering?
    ↓
Cek Power Supply Stabil 5V
    ↓
[OK] → Cek GND Connection
    ↓
[OK] → Naikkan SCROLL_SPEED
```

---

## Kontak Support

Jika sudah follow semua langkah tapi masih error:

1. Screenshot error message
2. Catat:
   - Apa yang sudah dicoba
   - Hasil test_pin_esp32.ino
   - Foto wiring/koneksi
3. Post di GitHub Issues dengan detail lengkap

---

**Last Updated:** 2026
**Tested On:** ESP32 NodeMCU-32S + P10 HUB12 SMD
