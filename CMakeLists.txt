# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SD-project_3-hash_tables")

# Include sub-projects.
add_subdirectory ("SD-project_3-hash_tables")

add_library(hash_tables "include/hash_tables/hashTables_include.hpp")
target_include_directories(hash_tables PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/hash_tables/")

add_executable("SD-project_3-hash_tables" "SD-project_3-hash_tables.cpp")
target_link_libraries("SD-project_3-hash_tables" hash_tables)
target_link_libraries("SD-project_3-hash_tables" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/hash_tables/")