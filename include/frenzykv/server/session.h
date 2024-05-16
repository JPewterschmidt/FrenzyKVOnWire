#ifndef FRENZYKV_SERVER_SESSION_H
#define FRENZYKV_SERVER_SESSION_H

#include <string>
#include <unordered_map>

#include "frenzykv/server/session_impl.h"

namespace frenzykv::server
{

class session
{
public:
    session()
        : m_pimpl{ make_default_session_pimpl() }
    {
    }

    session(session_id_t session_id)
        : m_pimpl{ make_default_session_pimpl(::std::move(session_id)) }
    {
    }

    koios::task<> update_conn(toolpex::unique_posix_fd fd);
    const session_id_t& session_id() const noexcept;
    const toolpex::uuid native_session_id() const;
    
private:
    ::std::unique_ptr<session_impl> m_pimpl;
};

class session_layer
{
public:
    koios::task<> new_connection(toolpex::unique_posix_fd fd);

private:
    ::std::unordered_map<::std::string, session> m_sessions;
};

} // namespace frenzykv::server

#endif
