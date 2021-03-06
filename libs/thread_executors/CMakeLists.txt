# Copyright (c) 2020 The STE||AR-Group
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Default location is $HPX_ROOT/libs/thread_executors/include
set(thread_executors_headers
  hpx/execution/executors/default_executor.hpp
  hpx/execution/executors/thread_pool_executors.hpp
  hpx/execution/executors/this_thread_executors.hpp
  hpx/execution/executors/thread_pool_os_executors.hpp
  hpx/thread_executors/current_executor.hpp
  hpx/thread_executors/default_executor.hpp
  hpx/thread_executors/embedded_thread_pool_executors.hpp
  hpx/thread_executors/guided_pool_executor.hpp
  hpx/thread_executors/limiting_executor.hpp
  hpx/thread_executors/manage_thread_executor.hpp
  hpx/thread_executors/pool_executor.hpp
  hpx/thread_executors/service_executors.hpp
  hpx/thread_executors/this_thread_executors.hpp
  hpx/thread_executors/thread_executor.hpp
  hpx/thread_executors/thread_pool_attached_executors.hpp
  hpx/thread_executors/thread_pool_os_executors.hpp
  )

# Default location is $HPX_ROOT/libs/thread_executors/include_compatibility
set(thread_executors_compat_headers
  hpx/parallel/executors/default_executor.hpp
  hpx/parallel/executors/this_thread_executors.hpp
  hpx/parallel/executors/thread_pool_executors.hpp
  hpx/parallel/executors/thread_pool_os_executors.hpp
  hpx/runtime/threads/executors/current_executor.hpp
  hpx/runtime/threads/executors/default_executor.hpp
  hpx/runtime/threads/executors/embedded_thread_pool_executors.hpp
  hpx/runtime/threads/executors/guided_pool_executor.hpp
  hpx/runtime/threads/executors/limiting_executor.hpp
  hpx/runtime/threads/executors/manage_thread_executor.hpp
  hpx/runtime/threads/executors/pool_executor.hpp
  hpx/runtime/threads/executors/service_executors.hpp
  hpx/runtime/threads/executors/this_thread_executors.hpp
  hpx/runtime/threads/executors/thread_pool_attached_executors.hpp
  hpx/runtime/threads/executors/thread_pool_os_executors.hpp
  hpx/runtime/threads/thread_executor.hpp
  )

set(thread_executors_sources
  embedded_thread_pool_executors.cpp
  this_thread_executors.cpp
  thread_pool_os_executors.cpp
  )

include(HPX_AddModule)
add_hpx_module(thread_executors
  COMPATIBILITY_HEADERS OFF
  DEPRECATION_WARNINGS
  FORCE_LINKING_GEN
  GLOBAL_HEADER_GEN ON
  SOURCES ${thread_executors_sources}
  HEADERS ${thread_executors_headers}
  COMPAT_HEADERS ${thread_executors_compat_headers}
  DEPENDENCIES
    hpx_config
    hpx_affinity
    hpx_coroutines
    hpx_datastructures
    hpx_errors
    hpx_functional
    hpx_io_service
    hpx_threading_base
    hpx_timing
    hpx_resource_partitioner
    hpx_synchronization
    hpx_thread_pools
    hpx_thread_support
  CMAKE_SUBDIRS examples tests
)
