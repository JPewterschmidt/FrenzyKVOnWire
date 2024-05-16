#ifndef FRENZYKV_SERVER_SESSION_IMPL_H
#define FRENZYKV_SERVER_SESSION_IMPL_H

#include <memory>

#include "toolpex/uuid.h"
#include "toolpex/unique_posix_fd.h"

#include "koios/task.h"

#include "frenzykv/server/types.h"

namespace frenzykv::server
{

class session_impl
{
public:
    virtual ~session_impl() noexcept {}
    virtual koios::task<> update_conn(toolpex::unique_posix_fd fd) = 0;
    virtual const session_id_t& session_id() const = 0;
    virtual const toolpex::uuid native_session_id() const = 0;
};

::std::unique_ptr<session_impl> make_default_session_pimpl();
::std::unique_ptr<session_impl> make_default_session_pimpl(session_id_t session_id);

} // namespace frenzykv::server

#endif
