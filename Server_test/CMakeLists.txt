# CMakeList.txt: проект CMake для DIM_test; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Server_test "ServerMain.cpp" "TestServer.h" "TestServer.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Server_test PROPERTY CXX_STANDARD 20)
endif()

# include path
target_include_directories(Server_test PUBLIC "${CMAKE_SOURCE_DIR}/include")

#link libs
target_link_libraries(Server_test dim)

#copy dll next to the executable
if(WIN32)
file(COPY ${CMAKE_SOURCE_DIR}/lib/dim.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
