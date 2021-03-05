file(GLOB_RECURSE SRCS *.cc)

list(APPEND ${PROJECT_NAME}_LIBS "glfw" "GLEW::GLEW" "OpenGL::GL")
#NIKOS if(OpenMP_CXX_FOUND)
#NIKOS  list(APPEND ${PROJECT_NAME}_LIBS "OpenMP::OpenMP_CXX")
#NIKOS endif()

add_executable(${PROJECT_NAME} ${SRCS})

if (LTOAvailable)
    message(STATUS "Link-time optimization enabled")
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()

target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIBS})
