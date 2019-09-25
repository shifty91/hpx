//  Copyright (c) 2016 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/datapar.hpp>
#include <hpx/include/parallel_for_each.hpp>
#include <hpx/testing.hpp>

#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include <hpx/program_options.hpp>

#include "../algorithms/test_utils.hpp"

///////////////////////////////////////////////////////////////////////////////
struct set_42
{
    template <typename Tuple>
    void operator()(Tuple&& t)
    {
        hpx::util::get<0>(t) = 42;
        hpx::util::get<1>(t) = 42;
    }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ExPolicy, typename IteratorTag>
void for_each_zipiter_test(ExPolicy&& policy, IteratorTag)
{
    static_assert(
        hpx::parallel::execution::is_execution_policy<ExPolicy>::value,
        "hpx::parallel::execution::is_execution_policy<ExPolicy>::value");

    typedef std::vector<int>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    std::vector<int> c(10007), d(10007);
    std::iota(std::begin(c), std::end(c), std::rand());
    std::iota(std::begin(d), std::end(d), std::rand());

    auto begin = hpx::util::make_zip_iterator(
        iterator(std::begin(c)), iterator(std::begin(d)));
    auto end = hpx::util::make_zip_iterator(
        iterator(std::end(c)), iterator(std::end(d)));

    auto result = hpx::parallel::for_each(
        std::forward<ExPolicy>(policy), begin, end, set_42());

    HPX_TEST(result == end);

    // verify values
    std::size_t count = 0;
    std::for_each(std::begin(c), std::end(c), [&count](int v) -> void {
        HPX_TEST_EQ(v, int(42));
        ++count;
    });
    HPX_TEST_EQ(count, c.size());
    /*
    auto begin = hpx::util::make_zip_iterator(
        iterator(std::begin(c)), iterator(std::begin(d)));

    static_assert(
//        hpx::parallel::traits::is_indirect_callable<
//            set_42, hpx::parallel::traits::projected<
//                hpx::parallel::util::projection_identity,
//                decltype(begin)>
//        >::value,
        hpx::traits::is_callable<
            set_42(
                typename std::iterator_traits<decltype(begin)>::value_type&
            )
//            typename hpx::parallel::traits::detail::projected_result_of_indirect<
//            hpx::parallel::traits::projected<
//                hpx::parallel::util::projection_identity,
//                decltype(begin)
//            >
//            >::type)
        >::value,
        "foo");*/
}

template <typename IteratorTag>
void for_each_zipiter_test()
{
    using namespace hpx::parallel;

    for_each_zipiter_test(execution::datapar, IteratorTag());
    //     test_for_each_async(execution::datapar(execution::task), IteratorTag());
}

void for_each_zipiter_test()
{
    for_each_zipiter_test<std::random_access_iterator_tag>();
    //    for_each_zipiter_test<std::forward_iterator_tag>();
    //    for_each_zipiter_test<std::input_iterator_tag>();
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(hpx::program_options::variables_map& vm)
{
    unsigned int seed = (unsigned int) std::time(nullptr);
    if (vm.count("seed"))
        seed = vm["seed"].as<unsigned int>();

    std::cout << "using seed: " << seed << std::endl;
    std::srand(seed);

    for_each_zipiter_test();

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    // add command line option which controls the random number generator seed
    using namespace hpx::program_options;
    options_description desc_commandline(
        "Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()("seed,s", value<unsigned int>(),
        "the random number generator seed to use for this run");

    // By default this test should run on all available cores
    std::vector<std::string> const cfg = {"hpx.os_threads=all"};

    // Initialize and run HPX
    HPX_TEST_EQ_MSG(hpx::init(desc_commandline, argc, argv, cfg), 0,
        "HPX main exited with non-zero status");

    return hpx::util::report_errors();
}
