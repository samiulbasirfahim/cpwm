#include "wm.h"
#include "utils.h"
#include <memory>

WindowManager::WindowManager(Display *dpy)
    : m_display(dpy), m_rootWindow(DefaultRootWindow(dpy)) {};

WindowManager::~WindowManager() {
    Log::Debug("Destroying WindowManager class.");
    XCloseDisplay(m_display);
}

std::unique_ptr<WindowManager> WindowManager::Init() {
    Display *dpy = XOpenDisplay(0);
    if (!dpy) {
        Log::Error("Failed to open display.");
        return 0;
    }

    return std::unique_ptr<WindowManager>(new WindowManager(dpy));
}

int WindowManager::XotherWmDetector(){

}
