#include <iostream>
#include "math.h"
#include "Func.cpp"
#include "ThreeFingers.cpp"
#include "TwoFingers.cpp"
#include "FourFingers.cpp"
#include "VirtDevice.cpp"

using namespace std;

class EventBuster {
private:
    char slot = 0;
    char bl = 0;
    char b = 0;
    unsigned short x[5] = {0, 0, 0, 0, 0};
    unsigned short y[5] = {0, 0, 0, 0, 0};
    Func f = Func(x, y);


    timeval time;

    bool isStart(char n) {
        return b == n && bl < b;
    }

    bool isStop(char n) {
        return b != n && bl == n;
    }

public:
    ThreeFingers three;
    TwoFingers two;
    FourFingers four;

    EventBuster(VirtDevice &device): three(ThreeFingers(x, y, device)),
    two(TwoFingers(x, y, device)),
    four(FourFingers(x, y, device)){}

    void update(char *data) {
        input_event e = *((input_event *) data);

        if (e.type == EV_ABS) {
            if (e.code == ABS_MT_SLOT) {
                slot = e.value;
            }
            if (e.code == ABS_X) {
                x[0] = e.value;
            }
            if (e.code == ABS_Y) {
                y[0] = e.value;
            }
            if (e.code == ABS_MT_POSITION_X) {
                x[slot] = e.value;
            }
            if (e.code == ABS_MT_POSITION_Y) {
                y[slot] = e.value;
            }

            if (b == 2) {
                two.update(f.getLong(time));
            }else if (b == 4) {
                three.update(f.getLong(time));
            }else if (b == 8) {
                four.update(f.getLong(time));
            }
        }

        if (e.type == EV_KEY) {
            if (e.code == BTN_TOOL_FINGER) {
                b = b & 0b11110;
                b += 0b00001 * e.value;
            }
            if (e.code == BTN_TOOL_DOUBLETAP) {
                b = b & 0b11101;
                b += 0b00010 * e.value;
            }
            if (e.code == BTN_TOOL_TRIPLETAP) {
                b = b & 0b11011;
                b += 0b00100 * e.value;
            }
            if (e.code == BTN_TOOL_QUADTAP) {
                b = b & 0b10111;
                b += 0b01000 * e.value;
            }
            if (e.code == BTN_TOOL_QUINTTAP) {
                b = b & 0b01111;
                b += 0b10000 * e.value;
            }
        }

        if (e.type == 0 && e.code == 0 && e.value == 0) {
            if (isStop(2)) {
                two.onStop(f.getLong(time), b > bl);
            }else if (isStart(2)) {
                two.onStart(f.getLong(time));
            }

            if (isStop(4)) {
                three.onStop(f.getLong(time), b > bl);
            }else if (isStart(4)) {
                three.onStart(f.getLong(time));
            }

            if (isStop(8)) {
                four.onStop(f.getLong(time), b > bl);
            }else if (isStart(8)) {
                four.onStart(f.getLong(time));
            }
            bl = b;
        } else {
            time = e.time;
        }
    }
};
