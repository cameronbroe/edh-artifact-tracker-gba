# EDH Artifact Token Tracker

This repository is a GameBoy Advance homebrew app that tracks the 3 most common artifact token types in Commander: Food, Clues, and Treasures. The app will track both total count as well as tapped/untapped status of these tokens.

It is written using the Butano game engine. Tested with mGBA on macOS and on the Miyoo Mini+.

## Controls
| Button         | Description                                        |
| ------         | -------------------------------------------------- |
| ↑/↓            | Select token type                                  |
| ←/→            | Decrement/increment total of selected token        |
| Start + ←/→    | Decrement/increment total of selected tokten by 10 |
| A/B            | Tap/untap selected token by 1                      |
| Start + A/B    | Tap/untap selected token by 10                     |
| Select + A/B   | Tap/untap all of selected token                    |
| Select + Start | Reset tracker                                      |

## Building

1. Install the devkitARM toolchain for `gba-dev` from devkitPro: https://devkitpro.org/wiki/Getting_Started
2. Clone this repository with submodules
   ```bash
   git clone --recurse-submodules https://github.com/cameronbroe/edh-artifact-tracker-gba
   ```
3. Build the ROM file with `make`:
   ```bash
   make -j 4
   ```
4. Run the file `edh-artifact-tracker-gba.gba` in mGBA to verify the build works correct.

## License

This file is licensed under the MIT License and can be found in [LICENSE.md](LICENSE.md)