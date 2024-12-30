#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <X11/X.h>
#include <memory>
#include <unordered_map>
extern "C" {
#include <X11/Xlib.h>
}

class WindowManager {
  private:
    Display *m_display;
    const Window m_rootWindow;
    std::unordered_map<Window, Window> m_clients;

    WindowManager(Display *display)
        : m_display(display), m_rootWindow(DefaultRootWindow(m_display)) {};

    static bool m_otherWmDetected;

    static int m_XOtherWmDetector(Display *, XErrorEvent *);
    static int m_XErrorHandler(Display *, XErrorEvent *);

    void (WindowManager::*handlers[LASTEvent])(XEvent &);
    void initHandler();

    void handleMapRequest(XEvent &);
    void handleResizeRequest(XEvent &);
    void handleConfigureRequest(XEvent &);

  public:
    using wmPtr = std::unique_ptr<WindowManager>;
    ~WindowManager();
    static wmPtr Init();
    bool checkOtherWmRunning();
    void run();
};

#endif
