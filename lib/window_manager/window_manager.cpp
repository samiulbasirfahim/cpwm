#include "window_manager.h"
#include "../utility/utility.h"
#include <iostream>

WindowManager::wmPtr WindowManager::Init() {
    Display *display = XOpenDisplay(0);
    if (!display)
        return 0;
    return wmPtr(new WindowManager(display));
};


WindowManager::~WindowManager(){
    XCloseDisplay(m_display);
    Log::Debug("Display closed & window manager destroyed");
};

bool WindowManager::m_otherWmDetected = false;

int WindowManager::m_XOtherWmDetector(Display *display, XErrorEvent *e) {
    WindowManager::m_otherWmDetected = true;
    return -1;
};

int WindowManager::m_XErrorHandler(Display *display, XErrorEvent *e) {
    if (e->type == BadWindow)
        return 0;
    return -1;
}

bool WindowManager::checkOtherWmRunning() {
    XSetErrorHandler(&WindowManager::m_XOtherWmDetector);

    XSelectInput(m_display, m_rootWindow,
                 SubstructureNotifyMask | SubstructureRedirectMask);
    XSync(m_display, 0);

    return WindowManager::m_otherWmDetected;
};

void WindowManager::run() {
    initHandler();
    XEvent ev;

    while (!XNextEvent(m_display, &ev)) {
        if (handlers[ev.type]) {
            (this->*handlers[ev.type])(ev);
        }
    }
}
