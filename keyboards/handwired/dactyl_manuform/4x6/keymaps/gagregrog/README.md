# Helpful Commands

## First Time Flash

First time Flashing you need to set the handedness of the board.

### Pro Micro

Use the following to set in EEPROM:

```bash
make handwired/dactyl_manuform/4x6:default:avrdude-split-right

# or

make handwired/dactyl_manuform/4x6:default:avrdude-split-left
```
### Elite-C

Use the following to set in EEPROM:

```bash
make handwired/dactyl_manuform/4x6:trackpoint:dfu-split-right

# or

make handwired/dactyl_manuform/4x6:trackpoint:dfu-split-left
```

After the first time, to flash in the future use:

```bash
qmk flash -kb handwired/dactyl_manuform/4x6 -km default
```
