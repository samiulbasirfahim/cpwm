#include "window_manager.h"
#include <X11/Xlib.h>
#include <iostream>

void WindowManager::initHandler() {
    handlers[MapRequest] = &WindowManager::handleMapRequest;
    handlers[ResizeRequest] = &WindowManager::handleResizeRequest;
    handlers[ConfigureRequest] = &WindowManager::handleConfigureRequest;
}

void WindowManager::handleConfigureRequest(XEvent &e) {
    XConfigureRequestEvent *ev = &e.xconfigurerequest;
    XWindowChanges wc;
    wc.x = ev->x;
    wc.y = ev->y;
    wc.width = ev->width;
    wc.height = ev->height;
    wc.border_width = ev->border_width;
    wc.sibling = ev->above;
    wc.stack_mode = ev->detail;
    XConfigureWindow(m_display, ev->window, ev->value_mask, &wc);

    XSync(m_display, 0);
};

void WindowManager::handleMapRequest(XEvent &e) {
    XMapRequestEvent *ev = &e.xmaprequest;
    Window w = ev->window;
    XWindowAttributes wa;
    if (!XGetWindowAttributes(m_display, ev->window, &wa)) {
        return;
    }

    XMapWindow(m_display, w);
};

void WindowManager::handleResizeRequest(XEvent &e) {};
