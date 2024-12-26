#include "utils.h"
#include "wm.h"

int main(void) {
    std::unique_ptr<WindowManager> windowManager = WindowManager::Init();
    if (!windowManager) {
        Log::Error("Failed to initialize window manager.");
        return 1;
    }
    if (windowManager->checkOtherWmRunning()) {
        Log::Error("Another window manager is already running.");
        return 1;
    };
    Log::Info("Running!");
    windowManager->run();
    return 0;
}
