# CMakeList.txt : CMake project for SD-project_3-hash_tables, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (SD-project_3-hash_tables "SD-project_3-hash_tables.cpp" "SD-project_3-hash_tables.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SD-project_3-hash_tables PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
