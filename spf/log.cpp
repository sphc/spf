/*
 * @Author       : sphc
 * @Description  : ---
 * @Email        : jinkai0916@outlook.com
 * @Date         : 2021-07-25 18:12:57
 * @LastEditors  : sphc
 * @LastEditTime : 2021-07-25 18:18:10
 */

#include "log.h"

namespace spf {
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
}