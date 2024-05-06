# CMakeList.txt: проект CMake для DIM_test; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (DIM_test "DIM_test.cpp" "DIM_test.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DIM_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
