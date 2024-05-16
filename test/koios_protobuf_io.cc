#include "gtest/gtest.h"

#include "dummy_pb_example.pb.h"

#include "koios/iouring_protobuf.h"
#include "koios/tcp_server.h"

using namespace koios;
using namespace ::std::chrono_literals;
using namespace ::std::string_view_literals;
using namespace toolpex::ip_address_literals;

namespace 
{
    bool ret{};
    eager_task<> server_app(toolpex::unique_posix_fd client)
    {
        [[maybe_unused]] dummy_pb_example::SearchRequest sr;
        ret = co_await uring::recv_pb_message(client, sr);
        co_return;
    }

    eager_task<> client_app()
    {
        dummy_pb_example::SearchRequest sr;
        sr.set_query("fuck");
        sr.set_page_number(32);
        sr.set_results_per_page(32);

        auto sock = co_await uring::connect_get_sock("::1"_ip, 8890);
        co_await uring::send_pb_message(sock, sr);
        
        co_return;
    }

    eager_task<bool> server_example()
    {
        tcp_server s{ "::1"_ip, 8890 };
        co_await s.start(server_app);
        co_await client_app();
        s.stop();
        co_await s.until_done_async();

        co_return true;
    }
} // annoymous namespace

TEST(koios_protobuf_io, basic)
{
    ASSERT_TRUE(server_example().result());
    ASSERT_TRUE(ret);
}
