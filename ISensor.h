// ISensor.h
#ifndef ISENSOR_H
#define ISENSOR_H

class ISensor {
public:
    // Sanal yıkıcı (Virtual Destructor): Bellek sızıntılarını önlemek için 
    // çok biçimlilik (polimorfizm) kullanılan her sınıfta olmalıdır.
    virtual ~ISensor() {}

    // Saf Sanal Fonksiyonlar (Pure Virtual Functions):
    // Sonundaki "= 0" ifadesi bu fonksiyonların içinin boş olduğunu 
    // ve bu sınıftan türeyen alt sınıfların bu fonksiyonları 
    // ZORUNLU OLARAK doldurması gerektiğini belirtir.
    
    virtual bool init() = 0;        // Sensörü başlatma/uyandırma fonksiyonu
    virtual void updateData() = 0;  // Sensörden yeni verileri çekme fonksiyonu
    virtual float getValue() = 0;   // Okunan işlenmiş veriyi döndürme fonksiyonu
    virtual const char* getUnit() =0;
};

#endif // ISENSOR_H