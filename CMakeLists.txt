cmake_minimum_required(VERSION 3.7)

project(Arkanoid LANGUAGES C)

find_package(SDL2 CONFIG REQUIRED)


add_executable(${PROJECT_NAME}
        config.h
        delta_time.c
        delta_time.h
        math/collisions.c
        math/collisions.h
        math/math.c
        math/math.h
        text.c
        text.h
        entities/entity.h
        entities/entity.c
        entities/entities_structures.h
        textures.c
        textures.h
        levels.c
        levels.h
        entities/entities_spawner.c
        entities/entities_spawner.h
        entities/capsule.c
        entities/capsule.h
        entities/ball.c
        entities/ball.h
        score.c
        score.h)
target_sources(${PROJECT_NAME} PRIVATE arkanoid.c)

target_link_libraries(${PROJECT_NAME} PRIVATE m)

if (TARGET SDL2::SDL2)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
else ()
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main)
endif ()


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Arkanoid_ascii.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Arkanoid_sprites.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
