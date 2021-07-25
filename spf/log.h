/*
 * @Author       : sphc
 * @Description  : ---
 * @Email        : jinkai0916@outlook.com
 * @Date         : 2021-07-24 21:53:08
 * @LastEditors  : sphc
 * @LastEditTime : 2021-07-25 20:00:38
 */

#ifndef SPF_LOG__H
#define SPF_LOG__H

#include <list>
#include <string>
#include <fstream>
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

    class LogFormatter {
    public:
        using ptr = std::shared_ptr<LogFormatter>;

        LogFormatter(const std::string &pattern);
        std::string format(LogEvent::ptr event);

    private:
        std::string m_pattern;
    };

    class LogAppender {
    public:
        using ptr = std::shared_ptr<LogAppender>;

        void set_level(LogLevel level);
        LogLevel get_level() const;
        void set_formatter(LogFormatter::ptr formatter);
        LogFormatter::ptr get_formatter() const;
        // TODO: 是否只读函数
        virtual void log(LogLevel level, LogEvent::ptr event) = 0;
        virtual ~LogAppender();

    protected:
        LogLevel m_level = LogLevel::DEBUG;
        LogFormatter::ptr m_formatter;
    };

    class StdoutAppender : public LogAppender {
    public:
        void log(LogLevel level, LogEvent::ptr event) override;
    };

    class FileAppender : public LogAppender {
    public:
        FileAppender(const std::string &file_name);

        void log(LogLevel level, LogEvent::ptr event) override;
        bool reopen();
    private:
        std::string m_file_name;
        std::fstream m_fstream;
    };

    class Logger {
    public:
        using ptr = std::shared_ptr<Logger>;

        void set_level(LogLevel level);
        LogLevel get_level() const;

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