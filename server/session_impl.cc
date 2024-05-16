#include "toolpex/ref_count.h"

#include "frenzykv/server/session_impl.h"

#include "koios/coroutine_mutex.h"

namespace frenzykv::server
{

namespace
{

class session_impl_1 : public session_impl
{
public:
    session_impl_1(session_id_t session_id = {})
        : m_session_id{ session_id.empty() ? toolpex::uuid{}.to_string() : ::std::move(session_id) }
    {
    }

    virtual koios::task<> update_conn(toolpex::unique_posix_fd fd) override
    {
        auto lk = co_await m_mutex.acquire();
        m_connection_fd = ::std::move(fd);
    }

    virtual const session_id_t& session_id() const override
    {
        return m_session_id;
    }

    virtual const toolpex::uuid native_session_id() const override
    {
        return { m_session_id };
    }

private:
    mutable koios::mutex m_mutex;
    toolpex::unique_posix_fd m_connection_fd;
    session_id_t m_session_id;
};
    
} // annoymous namespace

::std::unique_ptr<session_impl> make_default_session_pimpl()
{
    return ::std::make_unique<session_impl_1>();
}

::std::unique_ptr<session_impl> make_default_session_pimpl(session_id_t session_id)
{
    return ::std::make_unique<session_impl_1>(::std::move(session_id));
}

} // namespace frenzykv::server
