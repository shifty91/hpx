//  Copyright (c) 2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/util/lightweight_test.hpp>

///////////////////////////////////////////////////////////////////////////////
struct test_server
  : hpx::components::simple_component_base<test_server>
{
    void call_void()
    {
    }

     hpx::future<void> call_future_void()
     {
         return hpx::make_ready_future();
     }

    HPX_DEFINE_COMPONENT_ACTION(test_server, call_void, call_void_action);
    HPX_DEFINE_COMPONENT_ACTION(test_server, call_future_void, call_future_void_action);
};

typedef hpx::components::simple_component<test_server> server_type;
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(server_type, test_server);

typedef test_server::call_void_action call_void_action;
HPX_REGISTER_ACTION_DECLARATION(call_void_action);
HPX_REGISTER_ACTION(call_void_action);

typedef test_server::call_future_void_action call_future_void_action;
HPX_REGISTER_ACTION_DECLARATION(call_future_void_action);
HPX_REGISTER_ACTION(call_future_void_action);

///////////////////////////////////////////////////////////////////////////////
void test_component_call_void()
{
    hpx::id_type id = hpx::new_<test_server>(hpx::find_here()).get();

    // test apply
    for (std::size_t i = 0; i != 100; ++i)
    {
        hpx::apply<call_void_action>(id);
    }

    // test async
    std::vector<hpx::future<void> > calls;
    for (std::size_t i = 0; i != 100; ++i)
    {
        calls.push_back(hpx::async<call_void_action>(id));
    }
    hpx::wait_all(calls);
}

 void test_component_call_future_void()
 {
     hpx::id_type id = hpx::new_<test_server>(hpx::find_here()).get();
 
     // test apply
     for (std::size_t i = 0; i != 100; ++i)
     {
         hpx::apply<call_future_void_action>(id);
     }
 
     // test async
     std::vector<hpx::future<void> > calls;
     for (std::size_t i = 0; i != 100; ++i)
     {
         calls.push_back(hpx::async<call_future_void_action>(id));
     }
     hpx::wait_all(calls);
 }

///////////////////////////////////////////////////////////////////////////////
void plain_void()
{
}

HPX_DEFINE_PLAIN_ACTION(plain_void, plain_void_action);
HPX_REGISTER_PLAIN_ACTION_DECLARATION(plain_void_action);
HPX_REGISTER_PLAIN_ACTION(plain_void_action);

hpx::future<void> plain_future_void()
{
    return hpx::make_ready_future();
}

HPX_DEFINE_PLAIN_ACTION(plain_future_void, plain_future_void_action);
HPX_REGISTER_PLAIN_ACTION_DECLARATION(plain_future_void_action);
HPX_REGISTER_PLAIN_ACTION(plain_future_void_action);

void test_plain_call_void()
{
    hpx::id_type id = hpx::find_here();

    // test apply
    for (std::size_t i = 0; i != 100; ++i)
    {
        hpx::apply<plain_void_action>(id);
    }

    // test async
    std::vector<hpx::future<void> > calls;
    for (std::size_t i = 0; i != 100; ++i)
    {
        calls.push_back(hpx::async<plain_void_action>(id));
    }
    hpx::wait_all(calls);
}

void test_plain_call_future_void()
{
    hpx::id_type id = hpx::find_here();

    // test apply
    for (std::size_t i = 0; i != 100; ++i)
    {
        hpx::apply<plain_future_void_action>(id);
    }

    // test async
    std::vector<hpx::future<void> > calls;
    for (std::size_t i = 0; i != 100; ++i)
    {
        calls.push_back(hpx::async<plain_future_void_action>(id));
    }
    hpx::wait_all(calls);
}

///////////////////////////////////////////////////////////////////////////////
int main()
{
    test_component_call_void();
    test_component_call_future_void();

    test_plain_call_void();
    test_plain_call_future_void();

    return hpx::util::report_errors();
}
