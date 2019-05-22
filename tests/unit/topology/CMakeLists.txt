# Copyright (c) 2019 John Biddiscombe
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if (HPX_WITH_SHARED_PRIORITY_SCHEDULER AND HPX_WITH_CXX14_RETURN_TYPE_DEDUCTION)
  set(tests ${tests}
    numa_allocator
  )

  # NB. threads = -2 = threads = 'cores'
  # NB. threads = -1 = threads = 'all'
  set(numa_allocator_PARAMETERS
    THREADS_PER_LOCALITY -2
    ARGS --size=128 --nb=512 --tiles-per-domain=2 --col-proc=1 --row-proc=1)
endif()

###############################################################################
foreach(test ${tests})
  set(sources
      ${test}.cpp)

  source_group("Source Files" FILES ${sources})

  # add example executable
  add_hpx_executable(${test}_test
                     SOURCES ${sources}
                     ${${test}_FLAGS}
                     EXCLUDE_FROM_ALL
                     HPX_PREFIX ${HPX_BUILD_PREFIX}
                     FOLDER "Tests/Unit/Topology/")

  add_hpx_unit_test("topology" ${test} ${${test}_PARAMETERS})

  # add a custom target for this example
  add_hpx_pseudo_target(tests.unit.topology.${test})

  # make pseudo-targets depend on master pseudo-target
  add_hpx_pseudo_dependencies(tests.unit.topology
                              tests.unit.topology.${test})

  # add dependencies to pseudo-target
  add_hpx_pseudo_dependencies(tests.unit.topology.${test}
                              ${test}_test)
endforeach()