# Celus Keyboard

*![Celus Keyboard](https://www.celus.io/hubfs/favicon.ico) Celus a custom split keyboard featuring a unique layout with 60 keys optimized for ergonomic typing.*

## Keyboard Info

- **Keyboard Maintainers**: Jonas and Rubens
- **Hardware Supported**: Celus PCB with RP2040 microcontroller
- **Hardware Availability**: Custom build

## Features

- **Split Design**: Ergonomic split layout with 60 keys
- **RP2040 Powered**: Uses the powerful and affordable RP2040 microcontroller
- **4-Layer Support**: Default keymap includes QWERTY, Lower, Raise, and Adjust layers
- **Hot-swappable**: Compatible with MX-style switches
- **OLED Support**: Displays typing stats and layer information
- **Rotary Encoder**: Media control and layer switching

## Layout

The Celus features a 60-key split layout with the following arrangement:
- **Top Row**: Numbers and function keys
- **Home Row**: QWERTY layout with modifiers
- **Bottom Row**: Space bars, layer switches, and navigation keys
- **Thumb Cluster**: Optimized for comfortable access to space, layer toggles, and modifiers

```
QWERTY Layer:
┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
│ESC│ 1 │ 2 │ 3 │ 4 │ 5 │   │ 6 │ 7 │ 8 │ 9 │ 0 │MUT│
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│TAB│ Q │ Y*│ E │ R │ T │   │ W │ U │ I │ O │ P |BSP│
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│L1 │ A │ S │ D │ F │ '*│   │ H │ J*│ K │ L │ ` │ L2│
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│SFT│ ; │ Z │ X │ C │ V │   │ B │ N │ M │ G │ / │SFT│
├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
│Mac│CTL│ = │OPT│  MCL  │SPC│ ENTER │ - │ , │ | │ . │
└───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
```

## Getting Started

### Prerequisites

- Python 3.7 or newer
- Git
- A compatible text editor (VS Code, Vim, etc.)

### Quick Setup

The easiest way to get started is following the [official QMK tutorial](https://docs.qmk.fm/newbs). However, if you prefer to keep QMK in an isolated environment, follow the steps below:

### Isolated Setup (Recommended)

```bash
# Create and navigate to a dedicated directory
mkdir ~/qmk-celus && cd ~/qmk-celus

# Create Python virtual environment
python3 -m venv venv
source venv/bin/activate

# Install QMK
pip install qmk

# Clone the firmware repository
git clone https://github.com/rubao13/qmk_firmware.git
cd qmk_firmware

# Setup QMK (follow prompts to configure)
qmk setup

# Test compilation
qmk compile -kb celus -km default
```

### Building and Flashing

#### Compile Firmware

```bash
# Navigate to QMK directory
cd qmk_firmware

# Compile with default keymap
qmk compile -kb celus -km default

# Compile with multiple cores for faster build
qmk compile -j0 -kb celus -km default
```

#### Flash the Keyboard

**First Time Flashing:**
1. Hold the "BOOT" button on the RP2040 while plugging in the USB cable
2. The keyboard will appear as a USB mass storage device
3. Copy the generated `.uf2` file to the mounted drive

```bash
# Example for macOS/Linux
cp celus_default.uf2 /Volumes/RPI-RP2/

# Example for Linux with manual mounting
sudo mount /dev/sda1 /mnt
sudo cp celus_default.uf2 /mnt
sudo umount /mnt
```

**Subsequent Flashing:**
- Press the reset button twice quickly while the keyboard is connected
- Or use the reset keycode if configured in your keymap

### Customization

#### Creating Your Own Keymap

```bash
# Copy the default keymap as a starting point
cp -r keyboards/celus/keymaps/default keyboards/celus/keymaps/yourusername

# Edit your keymap
$EDITOR keyboards/celus/keymaps/yourusername/keymap.c

# Compile your custom keymap
qmk compile -kb celus -km yourusername
```

#### Layer Customization

The default firmware includes four layers:
- **Layer 0**: QWERTY (base layer)
- **Layer 1**: Lower (symbols, arrows, logos and shortcuts)
- **Layer 2**: Raise (apps shortcuts, music, firmware update)
- **Layer 3**: Adjust (RGB, audio, keyboard settings)

#### Layers LOWER & RAISE Shortcuts table
| Layer | QWERTY |  Function |  Description |
|-------|--------------|-----------|--------------|
|LOWER |ESC|KC_LPAD| Mac Lauchpad|
|LOWER |1|KC_BRID| Lower Brigth|
|LOWER |2|KC_BRIU| Raise Brigth|
|LOWER |3|WIREVPN_OPEN| Open Wireguard VPN app|
|LOWER |4|CALCULATOR_OPEN| Open Calculator|
|LOWER |5|MONITOR_OPEN| Open System monitor|
|LOWER |6|ZOOM_OPEN| Open Zoom|
|LOWER |7|CODE_OPEN| Open VS Code|
|LOWER |8|NOTES_OPEN| Open Notes app |
|LOWER |Q|VIM_WQ_TYPE| Type ´:wq´|
|LOWER |T|TERMINAL_OPEN| Terminal |


| Layer | QWERTY |  Function |  Description |
|-------|--------------|-----------|--------------|
|RAISE |ESC|Lock| Lock computer |
|RAISE |1|SAFARI_OPEN| Open Safari browser |
|RAISE |2|EDGE_OPEN| Open Edge browser |
|RAISE |3|BRAVE_OPEN| Open Brave browser |
|RAISE |4|FIREFOX_OPEN| Open Firefox browser |
|RAISE |5|COMET_OPEN| Open COmet browser |
|RAISE |9|K9S_OPEN| Open K9S |
|RAISE |VOLUME|QK_BOOT| Reset Raspberry firmware |
|RAISE |T|TERRAFORM_TYPE| Type ´Terraform plan´ |
|RAISE |O|KC_MPRV| Music Control Previous Song |
|RAISE |P|KC_MPLY| Music Control Play Song |
|RAISE |Backspace|KC_MNXT| Music Control Next Song |
|RAISE |A|AWS_SSO|Type ´aws sso login´ |
|RAISE |S|SPOTIFY_OPEN| Open Spotify|
|RAISE |G|GIT_TYPE|Type ´git commit --amend´ |
|RAISE |B|BRAVE_OPEN| Open Brave browser |
|RAISE |F|FIREFOX_OPEN| Open Firefox browser |
|RAISE |K|KUBECTL_TYPE|Type ´kubectl ´ |
|RAISE |L|GIT_CLONE_TYPE|Type ´git clone https://$gusr:$tok@git.celus.co ´ |
|RAISE |C|K8SCNTX_TYPE|Type ´kubectl config use-context site-´ |
|RAISE |V|VIM_TYPE|Type ´vim ´ |
|RAISE |M|SPOTIFY_OPEN| Open Spotify|
|RAISE |= / + |KC_KB_VOLUME_UP| Volume UP|
|RAISE |OPT |KC_KB_VOLUME_DOWN| Volume DOWN|


### Adding a Custom OLED Logo / Bitmap

Use the helper script `jpg-converter.py` to turn any JPG/PNG into a monochrome byte array for the OLED.

1. (Optional) Install Pillow if not already available inside your environment:
	```bash
	pip install Pillow
	```
2. Run the converter (example):
	```bash
	python keyboards/celus/lib/jpg-converter.py my_logo.png keyboards/celus/lib/my_logo.inc -n my_logo_bitmap -w 128 -H 64 -t 128
	```
	Parameters:
	- `input`: source image path
	- `output`: destination file (e.g. `.inc`, `.h`)
	- `-n/--name`: C array symbol (wraps output in `const uint8_t name[] PROGMEM`)
	- `-w/--width`: resize width (default 128)
	- `-H/--height`: resize height (default 64, must be multiple of 8)
	- `-t/--threshold`: black/white cutoff 0–255 (default 128)

3. Include the generated file and add a render function in `keyboards/celus/lib/logos.c`:
	```c
	#include "my_logo.inc"  // after other includes

	void render_my_logo(void) {
		 oled_write_raw_P(my_logo_bitmap, sizeof(my_logo_bitmap));
	}
	```
4. Declare the function in `keyboards/celus/lib/logos.h`:
	```c
	void render_my_logo(void);
	```
5. Map it in your `keymap.c` logic (either in the base logo switch or layer logic). Example addition inside `oled_task_user()` base layer switch:
	```c
	case 8: render_my_logo(); break; // ensure current_logo cycling covers this index
	```
6. (Optional) Add a keycode so you can select it:
	```c
	enum custom_keycodes {
		 // ... existing ...
		 LOGO_MYLOGO,
	};

	case LOGO_MYLOGO:
		 if (record->event.pressed) { current_logo = 8; }
		 break;
	```
7. Rebuild and flash:
	```bash
	qmk compile -kb celus -km default
	```

Tips:
- Prefer high‑contrast images; simplify to solid shapes.
- Adjust `-t` if too dark (raise it) or too light (lower it).
- Keep height a multiple of 8 (OLED page requirement).
- You can collect several bitmaps in one `.inc` file.

Troubleshooting:
- Blank screen: Check size (128x64) and that you call the correct render function.
- Distorted image: Don’t edit the generated hex order; regenerate instead.
- Compile error: Ensure `render_my_logo` is declared in `logos.h` and referenced where used.

## Troubleshooting

### Common Issues

**Keyboard not detected:**
- Ensure the RP2040 is in bootloader mode (hold BOOT while connecting)
- Try a different USB cable
- Check that the USB port provides sufficient power

**Compilation errors:**
- Verify your QMK installation: `qmk doctor`
- Update QMK: `qmk update`
- Clear build cache: `qmk clean`

**Keys not registering:**
- Check your wiring against the pin configuration
- Verify switch connections
- Test with a multimeter if necessary

### Getting Help

- [QMK Documentation](https://docs.qmk.fm/)
- [QMK Discord](https://discord.gg/qmk)
- [GitHub Issues](https://github.com/rubao13/qmk_firmware/issues)

## Contributing

### Thank you [Natjo](https://gitlab.com/natjo)

Contributions to improve the Celus keyboard support are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is released under the [GPL v2 License](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
