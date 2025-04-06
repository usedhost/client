#include "logger.hpp"

constexpr int MAX_LOG_COUNT = 30;
constexpr int MIN_MESSAGE_LENGTH = 28;
constexpr int MAX_MESSAGE_LENGTH = 90;
static int biggest = MIN_MESSAGE_LENGTH;
static int logCount = 1;

namespace logger {


    static std::ofstream logs;
    static std::filesystem::path path = (std::filesystem::path)(winrt::Windows::Storage::ApplicationData::Current().RoamingFolder().Path().c_str()) / "selaura" / "logs.txt";

    void clear() {
        logs.open(path);
        logs << "";
        logs.close();
    }

    void init() {
        if (!std::filesystem::exists(path.parent_path())) {
            std::filesystem::create_directories(path.parent_path());
        }
#ifdef _WIN32
#ifdef BUILD_TYPE_DEBUG
        console::open();
#endif
#endif
        clear();
    }

    void updateDimensions(const std::string& string) {
        if (string.length() > biggest && string.length() < MAX_MESSAGE_LENGTH) biggest = string.length();
        else if (string.length() > biggest) biggest = MAX_MESSAGE_LENGTH;
        if (logCount < MAX_LOG_COUNT) logCount++;
    }

    void out(const std::string& prefix, const std::string& string) {
        logs.open(path, std::ios::app);
        logs << "[" << prefix << "] " << string << std::endl;
        logs.close();
        std::cout << "[" << prefix << "] " << string << std::endl;
        updateDimensions(string);
        console::resize();
    }

    void info(const std::string& string) {
        out("INFO", string);
    }

    void error(const std::string& string) {
        out("ERROR", string);
    }
}

namespace console {
    static HWND window = nullptr;
    static FILE* f = nullptr;
    static RECT rect;

    void open() {
        window = GetConsoleWindow();
        if (!window) {
            AllocConsole();
            SetConsoleTitleA("selaura debugger");
            freopen_s(&f, "CONOUT$", "w", stdout);
            freopen_s(&f, "CONIN$", "r", stdin);
            window = GetConsoleWindow();
            ShowWindow(window, SW_SHOW);
        }
        SetWindowPos(
            window, 
            HWND_TOPMOST,
            0, 0, 0, 0,
            SWP_DRAWFRAME |  SWP_NOMOVE | SWP_NOSIZE
        );
        resize();
    }

    void scrollToTop() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            SMALL_RECT top = {
                .Left = 0,
                .Top = 0,
                .Right = static_cast<SHORT>(csbi.srWindow.Right - csbi.srWindow.Left),
                .Bottom = static_cast<SHORT>(csbi.srWindow.Bottom - csbi.srWindow.Top)
            };
            SetConsoleWindowInfo(hConsole, TRUE, &top);
        }
    }

    void resize() {
        GetWindowRect(window, &rect);
        MoveWindow(
            window, 
            rect.left, rect.top,
            11 * biggest, 
            40 + logCount * 15, 
            TRUE
        );
        if (logCount != MAX_LOG_COUNT) scrollToTop();
    }
}