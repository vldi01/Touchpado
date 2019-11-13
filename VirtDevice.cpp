#include <linux/uinput.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/stat.h>
#include <cstdlib>
#include <iostream>

#ifndef VIRTDEV
#define VIRTDEV

using  namespace std;

class VirtDevice {
private:
    int fd;
public:
    void emit(int type, int code, int val) {
        input_event ie;

        ie.type = type;
        ie.code = code;
        ie.value = val;
        /* timestamp values below are ignored */
        ie.time.tv_sec = 0;
        ie.time.tv_usec = 0;

        write(fd, &ie, sizeof(ie));
    }

    void press(int key) {
        emit(EV_KEY, key, 1);
        emit(EV_SYN, SYN_REPORT, 0);
        usleep(4000);
    }

    void release(int key) {
        emit(EV_KEY, key, 0);
        emit(EV_SYN, SYN_REPORT, 0);
        usleep(3000);
    }

    void click(int a, int b, int c) {
        press(a);
        press(b);
        press(c);
        release(a);
        release(b);
        release(c);
    }

    void click(int a, int b) {
        press(a);
        press(b);
        release(a);
        release(b);
    }

    void click(int key) {
        press(key);
        release(key);
    }

    int createDevice() {
        struct uinput_setup usetup;

        fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

        ioctl(fd, UI_SET_EVBIT, EV_KEY);
        ioctl(fd, UI_SET_KEYBIT, BTN_MIDDLE);
        ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT);

        ioctl(fd, UI_SET_KEYBIT, KEY_LEFTMETA);
        ioctl(fd, UI_SET_KEYBIT, KEY_LEFTCTRL);
        ioctl(fd, UI_SET_KEYBIT, KEY_TAB);
        ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT);
        ioctl(fd, UI_SET_KEYBIT, KEY_LEFTALT);
        ioctl(fd, UI_SET_KEYBIT, KEY_KPPLUS);
        ioctl(fd, UI_SET_KEYBIT, KEY_KPMINUS);
        ioctl(fd, UI_SET_KEYBIT, KEY_DOWN);
        ioctl(fd, UI_SET_KEYBIT, KEY_UP);
        ioctl(fd, UI_SET_KEYBIT, KEY_LEFT);
        ioctl(fd, UI_SET_KEYBIT, KEY_RIGHT);
        ioctl(fd, UI_SET_KEYBIT, KEY_PAGEDOWN);
        ioctl(fd, UI_SET_KEYBIT, KEY_PAGEUP);
        ioctl(fd, UI_SET_KEYBIT, KEY_ENTER);
        ioctl(fd, UI_SET_KEYBIT, KEY_F4);
        ioctl(fd, UI_SET_KEYBIT, KEY_ESC);

        ioctl(fd, UI_SET_KEYBIT, KEY_W);
        ioctl(fd, UI_SET_KEYBIT, KEY_T);
        ioctl(fd, UI_SET_KEYBIT, KEY_A);
        ioctl(fd, UI_SET_KEYBIT, KEY_SPACE);


        memset(&usetup, 0, sizeof(usetup));
        usetup.id.bustype = BUS_USB;
        usetup.id.vendor = 0x1a23; /* sample vendor */
        usetup.id.product = 0xaac1; /* sample product */
        strcpy(usetup.name, "MultitouchGestures");

        ioctl(fd, UI_DEV_SETUP, &usetup);
        ioctl(fd, UI_DEV_CREATE);
        return 0;
    }

    void closeDev() {
        ioctl(fd, UI_DEV_DESTROY);
        close(fd);
    }
};

#endif