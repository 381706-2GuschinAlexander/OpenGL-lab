file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${lib} STATIC ${srcs} ${hdrs})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
target_include_directories(${lib} PRIVATE ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(${lib} PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )