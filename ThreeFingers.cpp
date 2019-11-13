#include "Fingers.cpp"
#include "linux/uinput.h"

class ThreeFingers : public Fingers {
public:

    ThreeFingers(unsigned short *x, unsigned short *y, VirtDevice &device) : Fingers(3, x, y, device) {
        this->device = device;
    }

    void _onClick() override {
        device.click(BTN_MIDDLE);
    }

    void _onX(int a) override {
        if (a > 0) device.click(KEY_LEFTCTRL, KEY_TAB);
        else device.click(KEY_LEFTCTRL, KEY_LEFTSHIFT, KEY_TAB);
    }

    void _onY(int a) override {
        if (a > 0) {
            device.click(KEY_LEFTCTRL, KEY_W);
        }
        else device.click(KEY_LEFTCTRL, KEY_T);
    }

    void _onPinch(float a) override {
        if (a > 0) device.click(KEY_LEFTMETA, KEY_A);
        else device.click(KEY_LEFTMETA);
    }



    int lastx = 0;

    void _onStartX(int a) override {
        device.press(KEY_LEFTCTRL);
        device.press(KEY_LEFTMETA);
        if (a > 0) device.click(KEY_TAB);
        else device.click(KEY_LEFTSHIFT, KEY_TAB);
    }

    void _onUpdateX(int a) override {
        if (abs(a - lastx) > 200) {
            if (a > lastx) device.click(KEY_TAB);
            else device.click(KEY_LEFTSHIFT, KEY_TAB);

            lastx = a;
        }
    }

    void _onStopX() override {
        device.release(KEY_LEFTCTRL);
        device.release(KEY_LEFTMETA);
        lastx = 0;
    }



    int lasty = 0;

    void _onStartY(int a) override {
        device.press(KEY_LEFTALT);
        if (a > 0) device.click(KEY_TAB);
        else device.click(KEY_LEFTSHIFT, KEY_TAB);
    }

    void _onUpdateY(int a) override {
        if (abs(a - lasty) > 200) {
            if (a > lasty) device.click(KEY_LEFTSHIFT, KEY_TAB);
            else device.click(KEY_TAB);

            lasty = a;
        }
    }

    void _onStopY() override {
        device.release(KEY_LEFTALT);
        lasty = 0;
    }
};