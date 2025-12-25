# SimPad_1x3

## Flash

On the first flash, hold the bootloader button while plugging in the device.

On subsequent flashes, double press the reset button, or hold BTN1 while plugging it in.

```bash
qmk flash -kb handwired/sim_pad_1x3 -km default
```

## Keymap

Edit [keymap.c](./keymaps/default/keymap.c) to change button behaviors.

As implemented, the three keys are mapped, in order, to `Escape`, `Return`, and `Left Click`.

Each key is implemented as a tap dance with the following behavior:

-   Tap once for a regular tap/release
-   Hold for a regular hold
-   Double tap to auto-hold the key for X seconds (default is 6 seconds)

Note: If you double tap and hold the third key then the board will enter bootloader mode for flashing.

## Parts

MCU: [Seeed Xiao RP2040](https://wiki.seeedstudio.com/XIAO-RP2040/#hardware-overview)
Trackpad: [Cirque Pinnacle](https://github.com/2bndy5/CirquePinnacle?tab=readme-ov-file#pinout)
FPC Breakout: [12P 0.5mm](https://www.amazon.com/dp/B09VPKK7QR)
FPC Cable: [12 pin 0.5mm pitch FPC cable](amazon.com/uxcell-Flexible-Ribbon-Player-Laptop/dp/B0F4JD7TZT)

## Wiring

![Xiao Pinout](https://files.seeedstudio.com/wiki/XIAO-RP2040/img/xinpin.jpg)

### Cirque -> Xiao RP2040

FPC B/O # -> Pin Name -> RP2040 Digital Pin (GPIO)

1 -> SCK -> D8 (GP2)

2 -> MISO -> D9 (GP4)

3 -> CS -> D7 (GP1)

5 -> MOSI -> D10 (GP3)

11 -> GND -> GND

12 -> VCC -> 3.3v

### Buttons

All buttons are direct wired, meaning one leg goes to GND and the other goes to the expected GPIO pin.

There is no matrix, and no diodes are needed

BTN1 -> D4 (GP6)

BTN2 -> D5 (GP7)

BTN3 -> D6 (GP0)
