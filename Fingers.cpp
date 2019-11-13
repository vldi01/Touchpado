#include "Func.cpp"
#include <iostream>
#include "VirtDevice.cpp"

#ifndef FINGERS
#define FINGERS

using namespace std;

class Fingers {
protected:
    short N;

    Func f = Func(nullptr, nullptr);
    VirtDevice device;

    float startP = 0;
    int startX = 0;
    int startY = 0;
    long startTime = 0;

    bool isP = false;
    bool isX = false;
    bool isY = false;

    float pD = 0;
    int xD = 0;
    int yD = 0;

    virtual void _onStart() {}

    virtual void _onClick() {}

    virtual void _onPinch(float a) {}

    virtual void _onX(int a) {}

    virtual void _onY(int a) {}

    virtual void _onStartPinch(float a) {}

    virtual void _onUpdatePinch(float a) {}

    virtual void _onStopPinch() {}

    virtual void _onStartX(int a) {}

    virtual void _onUpdateX(int a) {}

    virtual void _onStopX() {}

    virtual void _onStartY(int a) {}

    virtual void _onUpdateY(int a) {}

    virtual void _onStopY() {}


public:
    Fingers(char n, unsigned short *x, unsigned short *y, VirtDevice& d): device(d) {
        f = Func(x, y);
        N = n;
    }

    void onStart(long time) {
        startP = f.avDist(N);
        startX = f.avX(N);
        startY = f.avY(N);
        startTime = time;

        _onStart();
    }

    void onStop(long time, bool missClick) {
        if (startTime == 0 || missClick)
            goto end;

        if (isP) _onStopPinch();
        else if (isX) _onStopX();
        else if (isY) _onStopY();
        else if (abs(pD) > 100 && f.absLar(pD, pD, xD, yD)) _onPinch(pD);
        else if (abs(xD) > 100 && f.absLar(xD, pD, xD, yD)) _onX(xD);
        else if (abs(yD) > 100 && f.absLar(yD, pD, xD, yD)) _onY(yD);
        else if (time - startTime < 250) _onClick();

        end:
        isP = false;
        isX = false;
        isY = false;

        startTime = 0;
    }

    void update(long time) {
        pD = f.avDist(N) - startP;
        xD = f.avX(N) - startX;
        yD = f.avY(N) - startY;

        if (startTime != 0 && (time - startTime > 250 || (N == 2))) {
            labelUpdate:
            if (isP) _onUpdatePinch(pD);
            else if (isX) _onUpdateX(xD);
            else if (isY) _onUpdateY(yD);
            else {
                if (abs(pD) > 50 && f.absLar(pD, pD, xD, yD)) {
                    isP = true;
                    _onStartPinch(pD);
                } else if (abs(xD) > 50 && f.absLar(xD, pD, xD, yD)) {
                    isX = true;
                    _onStartX(xD);
                } else if (abs(yD) > 50 && f.absLar(yD, pD, xD, yD)) {
                    isY = true;
                    _onStartY(yD);
                }

                if (isP || isX || isY) {
                    startP = f.avDist(N);
                    startX = f.avX(N);
                    startY = f.avY(N);
                    pD = 0;
                    xD = 0;
                    yD = 0;
                    goto labelUpdate;
                }
            }
        }
    }
};

#endif