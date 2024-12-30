#ifndef UTILITY_H
#define UTILITY_H

class Log {
  public:
    enum LogLevel { levelDebug = 0, levelInfo, levelWarning, levelError };
    static void Error(const char *message);
    static void Warning(const char *message);
    static void Info(const char *message);
    static void Debug(const char *message);
    static void SetLevel(LogLevel level);

  private:
    static LogLevel m_logLevel;
    static void Message(const char *message);
};

#endif
