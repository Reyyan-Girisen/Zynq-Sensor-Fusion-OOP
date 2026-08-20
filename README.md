# Zynq-Sensor-Fusion-OOP

Bu proje, Xilinx Zynq-7000 SoC (PYNQ-Z2) mimarisi üzerinde C++ ve Nesne Yönelimli Programlama (OOP) prensipleri kullanılarak geliştirilmiş bir donanım/yazılım ortak tasarım (co-design) projesidir. Sistem, ivme ve ağırlık/kuvvet verilerinin eşzamanlı olarak okunup filtrelendiği bir gömülü sistem prototiptir.

## Proje Mimarisi ve Özellikler
* **Donanım Soyutlama Katmanı (HAL):** Sistem ana programı (`main.cpp`), sensörlerin I2C veya GPIO ile haberleştiğini bilmez. `ISensor` arayüzü sayesinde yeni donanımlar sisteme tek satır kod değiştirmeden entegre edilebilir (Polimorfizm).
* **Gürültü Filtreleme (Bileşim):** Sensörlerden gelen ham ve gürültülü veriler, sınıfların içine gömülü matematiksel filtre sınıfları (Low-Pass Filter) ile yazılımsal olarak yumuşatılır.
* **Bare-Metal Geliştirme:** İşletim sistemi olmadan (standalone), doğrudan Xilinx API'leri (`xiicps`, `xgpiops`) kullanılarak ARM Cortex-A9 işlemcisi üzerinde koşturulmaktadır.

## Kullanılan Teknolojiler ve Donanımlar
* **SoC Kartı:** PYNQ-Z2 (Zynq-7020)
* **Hareket Sensörü:** MPU-6050 (I2C protokolü üzerinden, Vivado EMIO pinleri ile)
* **Kuvvet/Ağırlık Sensörü:** Load Cell & HX711 Amfi Modülü (GPIO üzerinden özel sinyal okuma ile)
* **Geliştirme Ortamı:** Xilinx Vitis (C++), Xilinx Vivado (Block Design & Constraints)

## Dosya Yapısı
* `src/` : C++ kaynak kodları, polimorfik arayüzler ve sensör okuma sınıfları.
* `pynq_z2_pins.xdc` : FPGA (PL) pinlerinin fiziksel Zynq donanımına haritalandığı dosya.

## Donanım Kurulumu
![Zynq Sensör Füzyonu Donanım Kurulumu](donanim_kurulumu.jpg)
