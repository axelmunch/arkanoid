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
        score.h
        audio.c
        audio.h)
target_sources(${PROJECT_NAME} PRIVATE arkanoid.c)

target_link_libraries(${PROJECT_NAME} PRIVATE m)

set(MusicsArchiveFilename "musics.zip")
if (MUSICS_ARCHIVE_URL)
    message(STATUS "Downloading custom music archive")
    file(DOWNLOAD ${MUSICS_ARCHIVE_URL} ${MusicsArchiveFilename})
    file(ARCHIVE_EXTRACT INPUT ${MusicsArchiveFilename} DESTINATION assets)
    file(REMOVE ${MusicsArchiveFilename})
endif ()

if (TARGET SDL2::SDL2 AND TARGET SDL2::SDL2 AND TARGET SDL2_mixer::SDL2_mixer)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_mixer::SDL2_mixer)
else ()
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2 SDL2_mixer)
endif ()


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
