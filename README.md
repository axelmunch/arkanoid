# Arkanoid

By Maël EHRHARD & Axel MUNCH

## Requirements

- SDL2
- SDL2 Mixer

## Development

### Ubuntu

````shell
apt install libsdl2-dev libsdl2-mixer-dev
cmake -S . -B build
````

### Windows

- Install dependencies where you like

````shell
cmake -S . -B build -DSDL2_DIR="PATH_TO_SDL2" -DSDL2_MIXER_DIR="PATH_TO_SDL2_MIXER"
````

## Controls

Player 1:

- Move with left and right arrows
- Shoot with space

Player 2:

- Move with A/Q and D
- Shoot with left control

## Custom music

### URL

You can pass a custom music archive, with music files named this way: `musicX.ogg`, where 1 goes from 0 to the number of
levels.

Pass the URL to this archive to CMake with `-DMUSICS_ARCHIVE_URL="URL"`.

### Local files

Simply put the correctly named files (`musicX.ogg`) into the `assets` folder.

## Assets

- `bounce.ogg` under CC0 [URL](https://opengameart.org/content/3-ping-pong-sounds-8-bit-style)
- `break.ogg` under CC0 [URL](https://opengameart.org/content/power-up-level-up-beansjam)
- `death.ogg` under CC0 [URL](https://opengameart.org/content/8bit-death-whirl)
- `divide.ogg` under CC0 [URL](https://opengameart.org/content/8-bit-spellselection-effect)
- `victory.ogg` under CC-BY 3.0 [URL](https://opengameart.org/content/8-bit-sound-effects-library)
- `addition.ogg`, `expand.ogg`, `explo1.ogg`, `explo2.ogg`, `laser1.ogg`, `laser2.ogg`, `shoot_ball.ogg`, `slow_ball.ogg`
  under CC-BY 3.0 [URL](https://opengameart.org/content/8-bit-platformer-sfx)
- `Arkanoid_ascii.bmp`, `Arkanoid_ascii_red.bmp` Modified font under [OFL license](assets/OFL.txt)
