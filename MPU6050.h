// MPU6050.h
#ifndef MPU6050_H
#define MPU6050_H

#include "ISensor.h"
#include "Filter.h"
#include "xiicps.h"

class MPU6050 : public ISensor {
    private:
        int i2cAddress;
        float accelX;
        Filter xFilter;
        XIicPs iicInstance;
    
    public:
        MPU6050(int address = 0x68);
        bool init() override;
        void updateData() override;
        float getValue() override;
        const char* getUnit() override;
        
};
#endif