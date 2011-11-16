#ifndef LOG_H
#define LOG_H

extern int loglvl;

enum {
    MSG_NORM,
    MSG_ADD,
    MSG_DEBUG,
    MSG_ERR = -1
};

#define l(fmt, ...) \
    log(MSG_NORM, fmt, ##__VA_ARGS__)

#define log(msgloglvl, fmt, ...) \
    log_whine(msgloglvl, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define assert(condition, fmt, ...) \
    if (!condition) \
        log_whine(MSG_ERR, __FILE__, __LINE__, fmt, ##__VA_ARGS__); \

#define assert_fatal(condition, fmt, ...) \
    if (!condition) { \
        log_whine(MSG_ERR, __FILE__, __LINE__, fmt, ##__VA_ARGS__); \
        exit(128); \
    }

#define assert_fatal_ret(condition, fmt, ...) \
    if (!condition) { \
        log_whine(MSG_ERR, __FILE__, __LINE__, fmt, ##__VA_ARGS__); \
        return -1; \
    }

void log_whine(int msgloglvl, const char* file, int line, const char *fmt, ...);

#endif /* LOG_H */
