set(INC_DIR ${display_SOURCE_DIR}/inc/display)
include_directories(${INC_DIR})
set(display_SRC
    main.cpp
    Explosion.cpp
)

set(display_INC
    ${INC_DIR}/Explosion.hpp
)

add_executable(${DISPLAY} ${display_SRC} ${display_INC})

find_package(SFML 2 REQUIRED system window graphics)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${DISPLAY} ${SFML_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${DISPLAY} ${OPENGL_LIBRARIES})
