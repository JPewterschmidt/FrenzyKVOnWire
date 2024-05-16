#include "toolpex/exceptions.h"

#include "frenzykv/server/session.h"

namespace frenzykv::server
{

koios::task<> session_layer::new_connection(toolpex::unique_posix_fd fd)
{
    toolpex::not_implemented();
    co_return;
}

} // namespace frenzykv::server
