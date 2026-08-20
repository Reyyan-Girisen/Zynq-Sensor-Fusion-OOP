#include "HX711.h"
#include "xparameters.h"
#include "sleep.h"
#include <cstdio>

HX711::HX711(int dataPin, int clockPin) {
    this->dataPin = dataPin;
    this->clockPin = clockPin;
    this->currentForce = 0.0f;
}

bool HX711::init() {
    XGpioPs_Config *Config;
    
    // Zynq içindeki GPIO donanımını bul ve başlat
    Config = XGpioPs_LookupConfig(0);
    if (XGpioPs_CfgInitialize(&gpioInstance, Config, Config->BaseAddr) != XST_SUCCESS) {
        printf("[HATA] GPIO Baslatilamadi!\n");
        return false;
    }
    
    // Pin yönlerini ayarla (Data = Giriş(0), Clock = Çıkış(1))
    XGpioPs_SetDirectionPin(&gpioInstance, dataPin, 0); 
    XGpioPs_SetDirectionPin(&gpioInstance, clockPin, 1);
    
    // Output Enable ayarı
    XGpioPs_SetOutputEnablePin(&gpioInstance, clockPin, 1);
    XGpioPs_WritePin(&gpioInstance, clockPin, 0); // Başlangıçta clock LOW olsun

    printf("[HX711] Gercek Load Cell GPIO uzerinden baslatildi.\n");
    return true; 
}

void HX711::updateData() {
    long count = 0;
    
    // Sensörün veriyi hazırlamasını bekle (Data pini 0 olana kadar)
    XGpioPs_WritePin(&gpioInstance, clockPin, 0);
    while(XGpioPs_ReadPin(&gpioInstance, dataPin) == 1) {
        usleep(1); // Sensörü kitlememek için 1 mikrosaniye bekle
    }
    
    // 24 bitlik veriyi saat (clock) sinyali vererek çek
    for(int i = 0; i < 24; i++) {
        XGpioPs_WritePin(&gpioInstance, clockPin, 1);
        count = count << 1;
        XGpioPs_WritePin(&gpioInstance, clockPin, 0);
        
        if(XGpioPs_ReadPin(&gpioInstance, dataPin)) {
            count++;
        }
    }
    
    // 25. clock sinyali (Gain ayarını 128'de tutmak için gerekli)
    XGpioPs_WritePin(&gpioInstance, clockPin, 1);
    count = count ^ 0x800000; // Negatif değerler için formül (Two's complement)
    XGpioPs_WritePin(&gpioInstance, clockPin, 0);
    
    // Ham değeri kalibrasyon katsayısına bölerek ağırlığa (kg/gr) çeviririz.
    // Şimdilik sadece değer değişiyor mu diye görmek için rastgele bir değere bölüyoruz. 
    // Daha sonra bunu kendi kalibrasyon ağırlığınla (örn 100gr) güncelleyeceğiz.
    this->currentForce = (float)count / 100000.0f; 
}

float HX711::getValue() {
    return forceFilter.process(this->currentForce);
}

const char* HX711::getUnit() {
    return "Birim"; // Kalibrasyon yapana kadar ham birim
}