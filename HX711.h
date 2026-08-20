#ifndef HX711_H
#define HX711_H
#include "Filter.h"
#include "ISensor.h"
#include "xgpiops.h"

class HX711 : public ISensor {
 private:
    int dataPin;
    int clockPin;
    float currentForce;
    Filter forceFilter;
    XGpioPs gpioInstance;
public:
    HX711(int dataPin, int clockPin);
    
    bool init() override;
    void updateData() override;
    float getValue() override;
    const char* getUnit() override;
};

#endif