cmake_minimum_required(VERSION 3.7)

project(Arkanoid LANGUAGES C)

set(SDL2_DIR "" CACHE PATH "Path to SDL2 cmake files")
set(SDL2_MIXER_DIR "" CACHE PATH "Path to SDL2_mixer cmake files")

if (WIN32)
    set(FETCHCONTENT_BASE_DIR "C:/Users/$ENV{USERNAME}/AppData/Local/Temp")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
    list(APPEND CMAKE_PREFIX_PATH "${SDL2_DIR}")
    list(APPEND CMAKE_PREFIX_PATH "${SDL2_MIXER_DIR}")
    find_package(SDL2_MIXER CONFIG REQUIRED)
endif ()


find_package(SDL2 CONFIG REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES "src/*.c" "src/*.h")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_sources(${PROJECT_NAME} PRIVATE src/arkanoid.c)

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

if (WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2_mixer::SDL2_mixer>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            VERBATIM
    )
endif ()