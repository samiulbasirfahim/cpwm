#include "wm.h"
#include "utils.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <memory>

WindowManager::WindowManager(Display *dpy) {
    WindowManager::m_display = dpy;
    WindowManager::m_rootWindow = DefaultRootWindow(dpy);
};

Display *WindowManager::m_display;
Window WindowManager::m_rootWindow;

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

int WindowManager::XotherWmDetector(Display *dpy, XErrorEvent *e) {
    wm_detected = true;
    return -1;
}

int WindowManager::XerrorHandler(Display *dpy, XErrorEvent *e) {
    Log::Error("Fatal error.");
    return -1;
}

bool WindowManager::checkOtherWmRunning() {
    wm_detected = false;
    XSetErrorHandler(&WindowManager::XotherWmDetector);
    XSelectInput(m_display, m_rootWindow,
                 SubstructureRedirectMask | SubstructureNotifyMask);
    XSync(m_display, 0);
    return wm_detected;
}

void WindowManager::run() {
    initHandler();
    XEvent ev;
    XSync(m_display, 0);

    Log::Debug("Inside window manager class");
    while (!XNextEvent(m_display, &ev)) {
        if (handler[ev.type])
            handler[ev.type](ev);
        Log::Debug("Inside event loop");
    }
}

bool WindowManager::wm_detected;

void WindowManager::configureRequest(const XEvent &e) {
    XConfigureRequestEvent ev = e.xconfigurerequest;
    XWindowChanges newWindow;
    newWindow.x = ev.x;
    newWindow.y = ev.y;
    newWindow.height = ev.height;
    newWindow.width = ev.width;
    newWindow.border_width = ev.border_width;
    newWindow.sibling = ev.above;
    newWindow.stack_mode = ev.detail;

    XConfigureWindow(m_display, ev.window, ev.value_mask, &newWindow);
    Log::Debug("Succesfully handled configureRequest event");
}

void WindowManager::mapRequest(const XEvent &e) {
    XMapRequestEvent ev = e.xmaprequest;
    XMapWindow(m_display, ev.window);
};

void WindowManager::initHandler() {
    handler[ConfigureRequest] = &configureRequest;
    handler[MapRequest] = &mapRequest;
};
