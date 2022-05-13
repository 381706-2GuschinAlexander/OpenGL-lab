add_executable(main main.cpp)

include_directories( ${include_dir})
target_link_libraries(main  PRIVATE ${lib})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
target_include_directories(main PRIVATE ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(main PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )