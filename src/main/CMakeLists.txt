add_executable(${main} main.cpp)

include_directories( ${gl_include})
target_link_libraries(${main}  PRIVATE ${gl_module})
