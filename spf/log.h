/*
 * @Author       : sphc
 * @Description  : ---
 * @Email        : jinkai0916@outlook.com
 * @Date         : 2021-07-24 21:53:08
 * @LastEditors  : sphc
 * @LastEditTime : 2021-07-25 18:51:30
 */

#ifndef SPF_LOG__H
#define SPF_LOG__H

#include <list>
#include <string>
#include <cstddef>
#include <memory>

namespace spf {
    enum class LogLevel {
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    class LogEvent {
    public:
        using ptr = std::shared_ptr<LogEvent>;

        LogEvent(
            std::string file_name,
            std::size_t line_no,
            std::int32_t thread_id,
            std::int32_t fiber_id,
            std::int64_t elapse,
            std::int64_t time
        );

        std::string get_file_name() const;
        std::size_t get_line_no() const;
        std::int32_t get_thread_id() const;
        std::int32_t get_fiber_id() const;
        std::int64_t get_elapse() const;
        std::int64_t get_time() const;

    private:
        std::string m_file_name;
        std::size_t m_line_no;
        std::int32_t m_thread_id;
        std::int32_t m_fiber_id;    // 协程id
        std::int64_t m_elapse;      // 程序启动到现在的时间差
        std::int64_t m_time;        // 时间戳
    };

    class Formatter {};

    class LogAppender {
    public:
        using ptr = std::shared_ptr<LogAppender>;

        virtual log(LogLevel level, const LogEvent &event) = 0;
        virtual ~LogAppender() { }
    };

    class Logger {
    public:
        using ptr = std::shared_ptr<Logger>;

        void set_log_level(LogLevel level);
        LogLevel get_log_level() const;

        void add_appender(LogAppender::ptr appender);
        void delete_appender(LogAppender::ptr appender);

        // TODO: 这些是否为只读函数
        void log(LogLevel level, LogEvent::ptr event);
        void debug(LogEvent::ptr event);
        void info(LogEvent::ptr event);
        void warn(LogEvent::ptr event);
        void error(LogEvent::ptr event);
        void fatal(LogEvent::ptr event);
    private:
        LogLevel m_level = LogLevel::DEBUG;         // 日志级别高于或等于m_level才会被输出
        std::list<LogAppender::ptr> m_appender_list;
    };
}

#endif