#include <memory>
extern "C" {
#include <X11/Xlib.h>
}

class WindowManager {
  private:
    Display *m_display;
    const Window m_rootWindow;
    WindowManager(Display *dpy);

  public:
    ~WindowManager();
    static std::unique_ptr<WindowManager> Init();
    static int XotherWmDetector();
    static int XerrorHandler();
    void run();
};
