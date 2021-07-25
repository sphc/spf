/*
 * @Author       : sphc
 * @Description  : ---
 * @Email        : jinkai0916@outlook.com
 * @Date         : 2021-07-25 18:12:57
 * @LastEditors  : sphc
 * @LastEditTime : 2021-07-25 18:52:27
 */

#include "log.h"
#include <algorithm>

namespace spf {

    // LogEvent implementation

    LogEvent::LogEvent(
        std::string file_name,
        std::size_t line_no,
        std::int32_t thread_id,
        std::int32_t fiber_id,
        std::int64_t elapse,
        std::int64_t time
    ) :
        m_file_name(file_name),
        m_line_no(line_no),
        m_thread_id(thread_id),
        m_fiber_id(fiber_id),
        m_elapse(elapse),
        m_time(time)
    { }

    std::string LogEvent::get_file_name() const
    { return m_file_name; }

    std::size_t LogEvent::get_line_no() const
    { return m_line_no; }

    std::int32_t LogEvent::get_thread_id() const
    { return m_thread_id; }

    std::int32_t LogEvent::get_fiber_id() const
    { return m_fiber_id; }

    std::int64_t LogEvent::get_elapse() const
    { return m_elapse; }

    std::int64_t LogEvent::get_time() const
    { return m_time; }

    // Logger implementation

    void Logger::set_log_level(LogLevel level)
    { m_level = level; }

    LogLevel Logger::get_log_level() const
    { return m_level; }

    void Logger::add_appender(LogAppender::ptr appender)
    { m_appender_list.push_back(appender); }

    void Logger::delete_appender(LogAppender::ptr appender)
    {
        auto it = std::find(m_appender_list.begin(), m_appender_list.end(), appender);
        if (it != m_appender_list.end()) {
            m_appender_list.erase(it);
        }
    }

    void Logger::log(LogLevel level, LogEvent::ptr event)
    {
        // for (auto appender : m_appender_list) {
        //     appender->log(level, event);
        // }
        if (level < m_level) {
            return;
        }
        std::for_each(
            m_appender_list.begin(),
            m_appender_list.end(),
            [level, event] (LogAppender::ptr appender) {
                appender->log(level, event);
            }
        );
    }

    void Logger::debug(LogEvent::ptr event)
    { log(LogLevel::DEBUG, event); }

    void Logger::info(LogEvent::ptr event)
    { log(LogLevel::INFO, event); }

    void Logger::warn(LogEvent::ptr event)
    { log(LogLevel::WARN, event); }

    void Logger::error(LogEvent::ptr event)
    { log(LogLevel::ERROR, event); }

    void Logger::fatal(LogEvent::ptr event)
    { log(LogLevel::FATAL, event); }
}