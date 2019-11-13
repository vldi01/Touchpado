#include "Fingers.cpp"
#include "linux/uinput.h"

class TwoFingers : public Fingers {
public:

    TwoFingers(unsigned short *x, unsigned short *y, VirtDevice &device) : Fingers(2, x, y, device) {
        this->device = device;
    }

    float pinch = 0;

    void _onStartPinch(float a) override {
        f.enableTouchpad(false);
    }

    void _onStopPinch() override {
        f.enableTouchpad(true);
        pinch = 0;
    }

    void _onUpdatePinch(float a) override {
        if (abs(a - pinch) > 40) {
            if (a < pinch) device.click(KEY_LEFTCTRL, KEY_KPMINUS);
            else device.click(KEY_LEFTCTRL, KEY_KPPLUS);
            pinch = a;
        }
    }
};

