#include <iostream>
#include <fstream>
#include <csignal>
#include "EventBuster.cpp"
#include "VirtDevice.cpp"

using namespace std;

bool run = true;
ifstream is;
char data[24];

VirtDevice virtDevice = VirtDevice();

string exec(const char* cmd) {
    char buffer[128];
    std::string result;
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != nullptr) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

void prepare() {
    string event = exec("/home/vlad/Programs/2works/CLion/TouchpadoC++/cmake-build-debug/getEvent");

    event[event.size()-1] = '\0';
    is = ifstream("/dev/input/"+event);

    system(string("xinput -set-button-map 'ELAN1010:00 04F3:3012 Touchpad' 1 0 3 4 5 6 7 8 9 10 11 12").c_str());
}

void signalHandler(int signum) {
    run = false;
    is.close();
    virtDevice.closeDev();
}

int main() {
    signal(SIGINT, signalHandler);
    signal(SIGILL, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGSEGV, signalHandler);
    signal(SIGTERM, signalHandler);

    virtDevice.createDevice();
    EventBuster eventBuster = EventBuster(virtDevice);

    prepare();

    sleep(1);

    while (run) {
        is.read(data, 24);
        eventBuster.update(data);
    }
    return 0;
}