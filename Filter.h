#ifndef FILTER_H
#define FILTER_H

class Filter {
    private:
         float alpha;
        float lastValue;
    public:
        Filter(float a = 0.5f) : alpha(a), lastValue(0.0f) {}
        
        float process(float newValue) {
                lastValue = (alpha * newValue) + ((1.0f - alpha) * lastValue);
                return lastValue;
        }
};
#endif