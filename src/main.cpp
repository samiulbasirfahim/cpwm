#include "../lib/utility/utility.h"
#include "../lib/window_manager/window_manager.h"

typedef WindowManager::wmPtr wmPtr;

int main(void) {
    Log::SetLevel(Log::levelDebug);

    wmPtr windowManager = WindowManager::Init();

    if (!windowManager) {
        Log::Error("Failed to initialize window manager");
        return 1;
    }

    if (windowManager->checkOtherWmRunning()) {
        Log::Error("Another window manager is already running.");
        return 1;
    }

    windowManager->run();

    return 0;
}
