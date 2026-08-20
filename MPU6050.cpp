#include "MPU6050.h"
#include "xparameters.h"
#include "cstdio"

MPU6050::MPU6050(int address) {
    this->i2cAddress = address;
    this->accelX = 0.0f;
}

bool MPU6050::init() {
    XIicPs_Config *Config;
    
    // I2C0 kanalını bulur (Eğer Vivado'da I2C1 seçtiysen burayı 1 yapmalısın)
    Config = XIicPs_LookupConfig(0); 
    if (Config == NULL) {
        printf("[MPU6050 HATA] I2C yapilandirmasi bulunamadi!\n");
        return false;
    }

    if (XIicPs_CfgInitialize(&iicInstance, Config, Config->BaseAddress) != XST_SUCCESS) {
        printf("[MPU6050 HATA] I2C baslatilamadi!\n");
        return false;
    }
    
    // Breadboard ve jumper kablolar için en güvenilir hız: 100kHz
    XIicPs_SetSClk(&iicInstance, 100000); 
    
    // Uyandırma Komutu
    u8 wakeUpCmd[2] = {0x6B, 0x00};
    int status = XIicPs_MasterSendPolled(&iicInstance, wakeUpCmd, 2, i2cAddress);
    
    if (status != XST_SUCCESS) {
        // Eğer bu hatayı alırsan sorun %100 kablolardadır (SDA/SCL ters veya temassız)
        printf("[MPU6050 HATA] Uyandirma komutu gitmedi! I2C baglantisi kopuk.\n");
        return false; 
    }

    printf("[MPU6050] Gercek sensor I2C uzerinden basariyla uyarildi.\n");
    return true;
}

void MPU6050::updateData() {
    u8 regAddr = 0x3B;
    int statusSend = XIicPs_MasterSendPolled(&iicInstance, &regAddr, 1, i2cAddress);

    u8 data[2] = {0, 0}; // Okuma başarısız olursa diye içini sıfırlarla dolduruyoruz
    int statusRecv = XIicPs_MasterRecvPolled(&iicInstance, data, 2, i2cAddress);
    
    if (statusSend != XST_SUCCESS || statusRecv != XST_SUCCESS) {
        printf("[MPU6050 UYARI] I2C veri okuma hatasi! Kablolar sallaniyor olabilir.\n");
    }
    
    short rawX = (data[0] << 8) | data[1];
    
    this->accelX = (float)rawX / 16384.0f;
}

float MPU6050::getValue() {
    return xFilter.process(this->accelX);
}

const char* MPU6050::getUnit() {
    return "G";
}