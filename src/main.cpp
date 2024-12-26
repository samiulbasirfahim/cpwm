#include "utils.h"
#include "wm.h"
#include <cstdlib>
#include <memory>
int main(void) {
    std::unique_ptr<WindowManager> windowManager = WindowManager::Init();
    if (!windowManager) {
        Log::Error("Failed to initialize window manager.");
    }
    return 0;
}
