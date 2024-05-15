#ifndef FRENZYKV_ON_WIRE_CLIENT_DB_REMOTE_H
#define FRENZYKV_ON_WIRE_CLIENT_DB_REMOTE_H

#include "frenzykv/db.h"

namespace frenzykv
{

class db_remote : public db_interface
{
public:
    virtual koios::task<bool> init() override;

    virtual koios::task<::std::error_code> 
    insert(write_batch batch, write_options opt = {}) override;

    virtual koios::task<::std::optional<kv_entry>> 
    get(const_bspan key, ::std::error_code& ec_out, read_options opt = {}) noexcept override;

    // Not support yet
    virtual koios::task<snapshot> get_snapshot() override;

    virtual koios::task<> close() override;
};

} // namespace frenzykv

#endif
