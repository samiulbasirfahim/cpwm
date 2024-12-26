#include <X11/X.h>
#include <array>
#include <memory>
extern "C" {
#include <X11/Xlib.h>
}

class WindowManager {
  private:
    static Display *m_display;
    static Window m_rootWindow;
    WindowManager(Display *dpy);
    std::array<void (*)(const XEvent &), LASTEvent> handler;
    void initHandler();
    static bool wm_detected;
    static int XotherWmDetector(Display *dpy, XErrorEvent *e);
    static int XerrorHandler(Display *dpy, XErrorEvent *e);

    static void configureRequest(const XEvent &e);
    static void mapRequest(const XEvent &e);

  public:
    ~WindowManager();
    static std::unique_ptr<WindowManager> Init();
    bool checkOtherWmRunning();
    void run();
};
