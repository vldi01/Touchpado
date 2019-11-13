#include <math.h>
#include <bits/types/struct_timeval.h>
#include <fstream>
#include <sys/time.h>

#ifndef FUNC
#define FUNC

class Func{
private:
    unsigned short* x;
    unsigned short* y;
public:
    Func(unsigned short* x, unsigned short* y) {
        this->x = x;
        this->y = y;
    }

    bool absLar(float& x, float& a, int& b, int& c)
    {
        double max = abs(a);

        if (abs(b) > max) max = abs(b);
        if (abs(c) > max) max = abs(c);

        return abs(x) == max;
    }

    bool absLar(int& x, float& a, int& b, int& c)
    {
        double max = abs(a);

        if (abs(b) > max) max = abs(b);
        if (abs(c) > max) max = abs(c);

        return abs(x) == max;
    }

    long getLong(timeval time){
        return time.tv_sec*1000+time.tv_usec/1000;
    }

    void enableTouchpad(bool k) {
        if (k) {
            system("xinput set-prop 'ELAN1010:00 04F3:3012 Touchpad' \"Device Enabled\" 1");
        } else {
            system("xinput set-prop 'ELAN1010:00 04F3:3012 Touchpad' \"Device Enabled\" 0");
        }
    }

    double dist(char a, char b) {
        return sqrt(pow(x[a] - x[b], 2) + pow(y[a] - y[b], 2));
    }

    float avDist(char n) {
        float d = 0;
        for (int i = 0; i < n - 1; ++i) {
            d += dist(i, i + 1);
        }
        if (n > 2) d += dist(0, n - 1);
        return d / n;
    }

    int avX(char n) {
        int r = 0;
        for (int i = 0; i < n; ++i) {
            r += x[i];
        }
        return r / n;
    }

    int avY(char n) {
        int r = 0;
        for (int i = 0; i < n; ++i) {
            r += y[i];
        }
        return r / n;
    }
};

#endif