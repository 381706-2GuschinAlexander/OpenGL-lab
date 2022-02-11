file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${gl_module} STATIC ${srcs} ${hdrs})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(${gl_module} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
