# Lorcana Lore Counter

This repository is a GameBoy Advance homebrew app that tracks your Lore count in a game of Disney's Lorcana.

It is written using the Butano game engine. Tested with mGBA on macOS and on the Miyoo Mini+.

## Controls
| Button | Description       |
| ------ | ----------------- |
| A      | Increment counter |
| B      | Decrement counter |
| Select | Reset counter     |

## Building

1. Install the devkitARM toolchain for `gba-dev` from devkitPro: https://devkitpro.org/wiki/Getting_Started
2. Clone this repository with submodules
   ```bash
   git clone --recurse-submodules https://github.com/cameronbroe/lorcana-lore-counter-gba
   ```
3. Build the ROM file with `make`:
   ```bash
   make -j 4
   ```
4. Run the file `lorcana-lore-counter-gba.gba` in mGBA to verify the build works correct.

## License

This file is licensed under the MIT License and can be found in [LICENSE.md](LICENSE.md)