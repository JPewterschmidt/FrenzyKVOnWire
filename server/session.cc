#include <cassert>

#include "toolpex/exceptions.h"

#include "frenzykv/server/session.h"

namespace frenzykv::server
{

koios::task<> session_layer::new_connection(toolpex::unique_posix_fd fd)
{
    toolpex::not_implemented();
    co_return;
}

koios::task<> session::update_conn(toolpex::unique_posix_fd fd)
{
    assert(m_pimpl);
    return m_pimpl->update_conn(::std::move(fd));   
}

const session_id_t& session::session_id() const noexcept
{
    assert(m_pimpl);
    return m_pimpl->session_id();   
}

const toolpex::uuid session::native_session_id() const
{
    assert(m_pimpl);
    return m_pimpl->native_session_id();   
}

} // namespace frenzykv::server
