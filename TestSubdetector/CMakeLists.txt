# Добавьте источник в исполняемый файл этого проекта.
add_executable (TestSubdetector "SubdetectorMain.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TestSubdetector PROPERTY CXX_STANDARD 20)
endif()

# include path
target_include_directories(TestSubdetector PUBLIC "${CMAKE_SOURCE_DIR}/include")

#link libs
target_link_libraries(TestSubdetector dim)

#copy dll next to the executable
if(WIN32)
	file(COPY ${CMAKE_SOURCE_DIR}/lib/dim.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
