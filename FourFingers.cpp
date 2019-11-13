#include "Fingers.cpp"
#include "linux/uinput.h"

class FourFingers : public Fingers {
public:

    FourFingers(unsigned short *x, unsigned short *y, VirtDevice &device) : Fingers(4, x, y, device) {
        this->device = device;
    }

    void _onClick() override {
        device.click(KEY_LEFTCTRL, KEY_LEFTALT, KEY_ESC);
    }

    void _onPinch(float a) override {
        if (a < 0) device.click(KEY_LEFTALT, KEY_F4);
    }

    void _onX(int a) override {
        if (a < 0) device.click(KEY_LEFTALT, KEY_LEFT);
        else device.click(KEY_LEFTALT, KEY_RIGHT);
    }

    void _onY(int a) override {
        if (a < 0) device.click(KEY_LEFTCTRL, KEY_LEFTALT, KEY_DOWN);
        else device.click(KEY_LEFTCTRL, KEY_LEFTALT, KEY_UP);
    }

    int lasty = 0;

    void _onStartY(int a) override {
        if (a < 0) device.click(KEY_LEFTMETA, KEY_LEFTSHIFT, KEY_PAGEUP);
        else device.click(KEY_LEFTMETA, KEY_LEFTSHIFT, KEY_PAGEDOWN);
    }

    void _onStopY() override {
        lasty = 0;
    }

    void _onUpdateY(int a) override {
        if (abs(a - lasty) > 200) {
            if (a < lasty) device.click(KEY_LEFTMETA, KEY_LEFTSHIFT, KEY_PAGEUP);
            else device.click(KEY_LEFTMETA, KEY_LEFTSHIFT, KEY_PAGEDOWN);

            lasty = a;
        }
    }

    int lastx = 0;

    void _onStopX() override {
        lastx = 0;
    }

    void _onUpdateX(int a) override {
        if (abs(a - lastx) > 170) {
            if (a > lastx) device.click(KEY_LEFTCTRL, KEY_TAB);
            else device.click(KEY_LEFTCTRL, KEY_LEFTSHIFT, KEY_TAB);

            lastx = a;
        }
    }
};

