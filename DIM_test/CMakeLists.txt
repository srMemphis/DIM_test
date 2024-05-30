# CMakeList.txt: проект CMake для DIM_test; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (DIM_test "DIM_test.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DIM_test PROPERTY CXX_STANDARD 20)
endif()

# include path
target_include_directories(DIM_test PUBLIC "${CMAKE_SOURCE_DIR}/include")

#link libs
target_link_libraries(DIM_test ${CMAKE_SOURCE_DIR}/lib/dim64.lib)
