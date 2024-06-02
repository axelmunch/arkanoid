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

### URL

You can pass a custom music archive, with music files named this way: `musicX.ogg`, where 1 goes from 0 to the number of
levels.
Pass the URL to this archive to CMake with `-DMUSICS_ARCHIVE_URL="URL"`

### Local files

Just put the correctly named files into the `assets` folder

## Assets

- `bounce.ogg` under CC0 [URL](https://opengameart.org/content/3-ping-pong-sounds-8-bit-style)
- `break.ogg` under CC0 [URL](https://opengameart.org/content/power-up-level-up-beansjam)
- `divide.ogg` under CC0 [URL](https://opengameart.org/content/8-bit-spellselection-effect)
- `addition.ogg`, `expand.ogg`, `explo1.ogg`, `explo2.ogg`, `laser1.ogg`, `laser2.ogg`, `shoot_ball.ogg`, `slow_ball.ogg` under CC-BY 3.0 [URL](https://opengameart.org/content/8-bit-platformer-sfx)
- `Arkanoid_ascii.bmp`, `Arkanoid_ascii_red.bmp` Modified font under [OFL license](assets/OFL.txt)
