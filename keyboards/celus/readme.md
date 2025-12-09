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
 │TAB│ Q │ W │ E │ R │ T │   │ Y │ U │ I │ O │ P |BSP│
 ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
 │ ; │ A │ S │ D │ F │ G │   │ H │ J │ K │ L │ , │ . │
 ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
 │SFT│ ' │ Z │ X │ C │ V │   │ B │ N │ M │ ` │ ↑ │ - │
 ├───┼───┼───┼───┼───┴───┼───┴───┴───┼───┼───┼───┼───┤
 │ / │CTL│OPT│L1 │  Mac  │   SPACE   │ L2│ ← │ ↓ │ → │
 └───┴───┴───┴───┴───────┴───────┴───┴───┴───┴───┴───┘
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

### Automated Builds

The Celus keyboard firmware is automatically built using GitHub Actions whenever changes are pushed to the repository. Tagged releases (e.g., `v1.0.0`) trigger automated builds that generate firmware artifacts (`.hex`, `.bin`, `.uf2` files) ready for flashing.

#### Downloading Pre-built Firmware

1. Navigate to the [Actions tab](https://github.com/rubao13/qmk_firmware/actions) in the repository
2. Select the latest successful build
3. Download the firmware artifact for your keyboard
4. Extract and flash the `.uf2` file to your keyboard

#### Local Firmware Build

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
|LOWER |ESC|LOCK_SCREEN| Lock computer|
|LOWER |1|LOGO_CELUS| Set Celus logo on display |
|LOWER |2|TYPE_EMAIL_WORK| Type work email |
|LOWER |3|TYPE_EMAIL_GMAIL| Type gmail email |
|LOWER |4|TYPE_EMAIL_DEUTSCH| Type gmx email|
|LOWER |5|SCREENSHOT| Type CMD + Shift + 5|
|LOWER |6|ZOOM_OPEN| Open Zoom|
|LOWER |7|CODE_OPEN| Open VS Code|
|LOWER |8|TXTEDIT_OPEN| Open TextEdit app |
|LOWER |TAB| KC_MCTL | Mac Mission Control|
|LOWER |Q|VIM_WQ_TYPE| Type ´:wq´|
|LOWER |T|TERMINAL_OPEN| Terminal |
|LOWER |G|GIT_TYPE|Type ´git commit --amend´ |
|LOWER |Z|CMD_TAB| CMD + TAB go previous app|
|LOWER |X|CMD_Q| Close app |
|LOWER |C|LOCK_SCREEN| Lock computer|
|LOWER |B|BITWARDEN_UNLOCK| Bitwarden unlock shortcut|

| Layer | QWERTY |  Function |  Description |
|-------|--------------|-----------|--------------|
|RAISE |ESC|LOCK_SCREEN| Lock computer |
|RAISE |1|SAFARI_OPEN| Open Safari browser |
|RAISE |2|COMET_OPEN| Open Comet browser  |
|RAISE |3|BRAVE_OPEN| Open Brave browser |
|RAISE |4|FIREFOX_OPEN| Open Firefox browser |
|RAISE |5|EDGE_OPEN| Open Edge browser |
|RAISE |8|PASSW_GEN_TYPE| Generates 23 char passwords|
|RAISE |9|K9S_OPEN| Open K9S |
|RAISE |VOLUME|QK_BOOT| Reset Raspberry firmware |
|RAISE |TAB| APPLE_AI | Apple Intelligence|
|RAISE |T|TERRAFORM_TYPE| Type ´Terraform plan´ |
|RAISE |O|KC_MPRV| Music Control Previous Song |
|RAISE |P|KC_MPLY| Music Control Play Song |
|RAISE |Backspace|KC_MNXT| Music Control Next Song |
|RAISE |A|AWS_SSO|Type ´aws sso login´ |
|RAISE |S|SPOTIFY_OPEN| Open Spotify|
|RAISE |F|FIREFOX_OPEN| Open Firefox browser |
|RAISE |G|GIT_CLONE_TYPE|Type ´git clone https://$gusr:$tok@git.celus.co ´ |
|RAISE |K|KUBECTL_TYPE|Type ´kubectl ´ |
|RAISE |L|LOCK_SCREEN| Lock computer |
|RAISE |C|K8SCNTX_TYPE|Type ´kubectl config use-context site-´ |
|RAISE |V|VIM_TYPE|Type ´vim ´ |
|RAISE |B|BITWARDEN_UNLOCK| Bitwarden unlock shortcut|

### Custom Macro Reference

The default keymap wires a set of custom keycodes inside `process_record_user()` so you can launch tools, paste text snippets, or pick OLED logos without leaving the home row. The tables below summarize every macro case that currently exists.

#### Logo Selection
| Keycode | Action |
|---------|--------|
|LOGO_SWITCH|Cycle through the 10 stored OLED logos in sequence|
|LOGO_TOMORROWLAND|Force the Tomorrowland logo|
|LOGO_LION|Force the Lion logo|
|LOGO_BAYERN|Force the Bayern logo|
|LOGO_FLAMENGO|Force the Flamengo logo|
|LOGO_CELUS|Force the Celus logo|
|LOGO_RIO|Force the Rio skyline logo|
|LOGO_LUNCH|Force the Lunch reminder logo|
|LOGO_THEOFFICE|Force The Office logo|
|LOGO_DJ|Force the DJ logo|

#### Application Launchers (Spotlight driven)
| Keycode | Action |
|---------|--------|
|BRAVE_OPEN|Open "Brave Brow" via Spotlight|
|COMET_OPEN|Open Comet browser|
|SAFARI_OPEN|Open Safari|
|FIREFOX_OPEN|Open Firefox|
|EDGE_OPEN|Open Microsoft Edge|
|K9S_OPEN|Type `k9s` and press Enter|
|ZOOM_OPEN|Open Zoom|
|CODE_OPEN|Open VS Code ("Code")|
|TXTEDIT_OPEN|Open TextEdit|
|WIREVPN_OPEN|Open WireGuard VPN|
|MATTERMOST_OPEN|Open Mattermost|
|SPOTIFY_OPEN|Open Spotify|
|TERMINAL_OPEN|Open the macOS Terminal app|
|MONITOR_OPEN|Open Monit|
|CALCULATOR_OPEN|Open Calculator|

#### Text, System, and Workflow Macros
| Keycode | Action |
|---------|--------|
|PASSW_GEN_TYPE|Generate a random 23-character password and switch the OLED to the password logo|
|AWS_SSO|Type `aws sso login` and press Enter|
|VIM_TYPE|Type `vim ` (with trailing space)|
|VIM_WQ_TYPE|Type `:wq`|
|KUBECTL_TYPE|Type `kubectl `|
|K8SCNTX_TYPE|Type `kubectl config use-context site-`|
|K9S_CTX_TYPE|Type `:ctx` inside k9s|
|K9S_NS_TYPE|Type `:ns` inside k9s|
|TERRAFORM_TYPE|Type `terraform plan `|
|GIT_TYPE|Type `git commit --amend`|
|GIT_CLONE_TYPE|Type `git clone https://$gusr:$tok@git.celus.co `|
|CMD_TAB|Hold Command, tap Tab, release (fast app switch)|
|CMD_Q|Send Command+Q (close app)|
|CMD_SAVE|Send Command+S|
|SCREENSHOT|Send Command+Shift+5|
|LOCK_SCREEN|Send Control+Command+Q|
|APPLE_AI|Double-tap Command to open Apple Intelligence|
|BITWARDEN_UNLOCK|Send Command+Shift+L (Bitwarden unlock)|
|TYPE_EMAIL_WORK|Type `<redacted>`|
|TYPE_EMAIL_GMAIL|Type `<redacted>`|
|TYPE_EMAIL_DEUTSCH|Type `<redacted>`|

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
