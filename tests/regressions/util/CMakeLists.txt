# Copyright (c) 2007-2012 Hartmut Kaiser
# Copyright (c) 2011 Bryce Adelstein-Lelbach
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(tests
    configuration_1572
    iarchive_1237
    protect_with_nullary_pfo
    serialize_buffer_1069
    set_config_entry_deadlock
    use_all_cores_2262
   )

set(iarchive_1237_FLAGS DEPENDENCIES iostreams_component)
set(serialize_buffer_1069_FLAGS DEPENDENCIES iostreams_component)

if(HPX_WITH_NETWORKING)
    set(tests ${tests}
        zero_copy_parcels_1001
       )
  set(zero_copy_parcels_1001_PARAMETERS LOCALITIES 2)
endif()

foreach(test ${tests})
  set(sources
      ${test}.cpp)

  source_group("Source Files" FILES ${sources})

  # add example executable
  add_hpx_executable(${test}_test
    INTERNAL_FLAGS
    SOURCES ${sources}
    ${${test}_FLAGS}
    EXCLUDE_FROM_ALL
    HPX_PREFIX ${HPX_BUILD_PREFIX}
    FOLDER "Tests/Regressions/Util")

  add_hpx_regression_test("util" ${test} ${${test}_PARAMETERS})

endforeach()

if(HPX_WITH_NETWORKING)
  # run zero_copy_parcels_1001 with two additional configurations
  add_hpx_regression_test(
      "util" zero_copy_parcels_1001_no_array_optimization
      EXECUTABLE zero_copy_parcels_1001
      PSEUDO_DEPS_NAME zero_copy_parcels_1001
      ${zero_copy_parcels_1001_PARAMETERS}
      ARGS --hpx:ini=hpx.parcel.array_optimization=0)

  add_hpx_regression_test(
      "util" zero_copy_parcels_1001_no_zero_copy_optimization
      EXECUTABLE zero_copy_parcels_1001
      PSEUDO_DEPS_NAME zero_copy_parcels_1001
      ${zero_copy_parcels_1001_PARAMETERS}
      ARGS --hpx:ini=hpx.parcel.zero_copy_optimization=0)
endif()
