# Arkanoid

## Requirements

- SDL2
- SDL2 Mixer

## Development

### Ubuntu

````shell
apt install libsdl2-dev libsdl2-mixer-dev
````

## Custom music

You can pass a custom music archive, with music files named this way: `musicX.ogg`, where 1 goes from 0 to the number of
levels.
Pass the URL to this archive to CMake with -DMUSICS_ARCHIVE_URL="URL"