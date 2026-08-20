
#include <cstdio> 
#include "ISensor.h"
#include "MPU6050.h"
#include "HX711.h"
#include <unistd.h>

void sensordanVeriAlVeIsle(ISensor* sensor) {
    sensor->updateData();
    printf("Okunan Deger: %.2f %s\n", sensor->getValue(), sensor->getUnit());
    printf("----------------------------------------\n");
}

int main() {
    printf("=== Zynq Sensor Fuzyonu Sistemi Baslatiliyor ===\n");

    ISensor* ivmeSensoru = new MPU6050(0x68);
    ISensor* kuvvetSensoru = new HX711(54, 55);
    
    ISensor* sistemSensorleri[2] = {ivmeSensoru, kuvvetSensoru};

    for(int i=0; i<2; i++) {
        sistemSensorleri[i]->init();   
    }
    
    printf("\nSistem hazir. Veri okumasi basliyor...\n\n");
    
   int tur = 1;
    // Sonsuz döngü: Sistem kapatılana kadar okuma yapmaya devam eder
    while(1) {
        printf("---OKUMA TURU %d---\n", tur);
        for(int i=0; i<2; i++) {
            sensordanVeriAlVeIsle(sistemSensorleri[i]);
        }
        tur++;
        sleep(1); // Terminal yazılarının su gibi akmasını önlemek için her tur 1 saniye bekler
    }
    delete ivmeSensoru;
    delete kuvvetSensoru;

    return 0;
}