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
 │ / │Mac│OPT│L1 │  CTRL │   SPACE   │ L2│ ← │ ↓ │ → │
 └───┴───┴───┴───┴───────┴───────┴───┴───┴───┴───┴───┘
```

### Rotary Encoder

| Layer | Counter-clockwise | Clockwise |
|-------|-------------------|-----------|
| QWERTY | Volume up | Volume down |
| LOWER | Brightness up | Brightness down |
| RAISE | Arrow Down | Arrow Up |
| ADJUST | — | — |

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
- **Layer 3**: Adjust (reserved — currently empty and not reachable)

#### LOWER Layer

```
 ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
 │LOK│CEL│EMW│EMG│EMD│SHT│   │   │ / │   │ [ │ ] │F12│
 ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
 │MCL│:wq│   │   │RIO│   │   │   │   │   │ { │ } │DEL│
 ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
 │   │ALL│SAV│   │   │GIT│   │   │   │   │LIO│   │   │
 ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
 │SFT│   │MTb│ + │LOK│PST│   │BWU│ ~ │   │   │DEL│ = │
 ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
 │ \ │CAP│LUN│   │  Mac  │LGO│ ENTER │   │   │ | │   │
 └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
```

| QWERTY key | Function | Description |
|------------|----------|-------------|
|ESC|LOCK_SCREEN|Lock computer|
|1|LOGO_CELUS|Set Celus logo on display|
|2|TYPE_EMAIL_WORK|Type work email|
|3|TYPE_EMAIL_GMAIL|Type gmail email|
|4|TYPE_EMAIL_DEUTSCH|Type gmx email|
|5|SCREENSHOT|Cmd + Shift + 5|
|7|KC_SLSH|`/`|
|9|KC_LBRC|`[`|
|0|KC_RBRC|`]`|
|MUTE|KC_F12|F12|
|TAB|KC_MCTL|Mac Mission Control|
|Q|VIM_WQ_TYPE|Type `:wq`|
|R|LOGO_RIO|Set Rio logo on display|
|O|KC_LCBR|`{`|
|P|KC_RCBR|`}`|
|Backspace|KC_DEL|DEL key|
|A|CMD_ALL|Select all + copy|
|S|CMD_SAVE|Save file (Cmd + S)|
|G|GIT_TYPE|Type `git commit --amend`|
|L|LOGO_LION|Set Lion logo on display|
|Shift|KC_LSFT|Shift|
|Z|CMD_TAB|Cmd + Tab, go to previous app|
|X|KC_KP_PLUS|Keypad `+`|
|C|LOCK_SCREEN|Lock computer|
|V|CMD_V|Paste clipboard|
|B|BITWARDEN_UNLOCK|Bitwarden unlock shortcut|
|N|KC_TILDE|`~`|
|↑|KC_DEL|DEL key|
|-|KC_EQL|`=`|
|/|KC_BSLS|`\`|
|Mac|KC_CAPS|Caps Lock|
|OPT|LOGO_LUNCH|Set Lunch logo on display|
|CTRL|KC_LGUI|Left Command|
|SPACE (left)|LOGO_SWITCH|Cycle to the next OLED logo|
|SPACE (right)|KC_ENT|Enter|
|↓|KC_PIPE|`\|`|

Unassigned on LOWER (`KC_NO`): `6`, `8`, `W`, `E`, `T`, `Y`, `U`, `I`, `;`, `D`, `F`, `H`, `J`, `K`, `,`, `.`, `'`, `M`, `` ` ``, `L1`, `L2`, `←`, `→`.

#### RAISE Layer

```
 ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
 │LOK│SAF│CMT│BRV│FRX│EDG│   │   │   │PWD│K9S│SPO│BOO│
 ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
 │AAI│   │   │EXS│   │KXT│   │   │   │IGS│   │POD│DEL│
 ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
 │   │AWS│SVC│DPL│STS│GCL│   │   │CRJ│KCT│LOK│   │   │
 ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
 │SFT│   │   │   │CTX│MDL│   │BWU│ NS│SPO│   │DEL│ = │
 ├───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┤
 │   │   │OPT│   │  Mac  │LGO│ ENTER │   │PRV│PLY│NXT│
 └───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┘
```

| QWERTY key | Function | Description |
|------------|----------|-------------|
|ESC|LOCK_SCREEN|Lock computer|
|1|SAFARI_OPEN|Open Safari browser|
|2|COMET_OPEN|Open Comet browser|
|3|BRAVE_OPEN|Open Brave browser|
|4|FIREFOX_OPEN|Open Firefox browser|
|5|EDGE_OPEN|Open Edge browser|
|8|PASSW_GEN_TYPE|Generate a 23-character password|
|9|K9S_OPEN|Type `k9s` + Enter|
|0|SPOTIFY_OPEN|Open Spotify|
|MUTE|QK_BOOT|Reboot into bootloader (firmware flash)|
|TAB|APPLE_AI|Apple Intelligence|
|E|K9S_EXTERNALSECRET_TYPE|Type `:externalsecrets`|
|T|K8SCNTX_TYPE|Type `kubectl config use-context site-`|
|I|K9S_INGRESS_TYPE|Type `:ingressroute`|
|P|K9S_PODS_TYPE|Type `:pods`|
|Backspace|KC_DEL|DEL key|
|A|AWS_SSO|Type `aws sso login` + Enter|
|S|K9S_SVC_TYPE|Type `:services`|
|D|K9S_DEPLOY_TYPE|Type `:deployments`|
|F|K9S_STATEFULSET_TYPE|Type `:statefulsets`|
|G|GIT_CLONE_TYPE|Special paste: `git clone https://$gusr:$tok@$gitsite/<CLIPBOARD>.git`|
|J|K9S_CRONJOB_TYPE|Type `:cronjobs`|
|K|KUBECTL_TYPE|Type `kubectl `|
|L|LOCK_SCREEN|Lock computer|
|Shift|KC_LSFT|Shift|
|C|K9S_CTX_TYPE|Type `:ctx`|
|V|CMD_V_URL|Special paste in markdown link format `[link here](<CLIPBOARD>)`|
|B|BITWARDEN_UNLOCK|Bitwarden unlock shortcut|
|N|K9S_NS_TYPE|Type `:ns`|
|M|SPOTIFY_OPEN|Open Spotify|
|↑|KC_DEL|DEL key|
|-|KC_EQL|`=`|
|OPT|KC_LOPT|Left Option|
|CTRL|KC_LGUI|Left Command|
|SPACE (left)|LOGO_SWITCH|Cycle to the next OLED logo|
|SPACE (right)|KC_ENT|Enter|
|←|KC_MPRV|Previous track|
|↓|KC_MPLY|Play / pause|
|→|KC_MNXT|Next track|

Unassigned on RAISE (`KC_NO`): `6`, `7`, `Q`, `W`, `R`, `Y`, `U`, `O`, `;`, `H`, `,`, `.`, `'`, `Z`, `X`, `` ` ``, `/`, `Mac`, `L1`, `L2`.

#### ADJUST Layer

Currently entirely `KC_NO` — there is no key combination that activates it either (only `MO(1)` and `MO(2)` are bound).

### Custom Macro Reference

The default keymap wires a set of custom keycodes inside `process_record_user()` so you can launch tools, paste text snippets, or pick OLED logos without leaving the home row. The tables below summarize every macro case that currently exists.

#### Logo Selection
| Keycode | Index | Action |
|---------|-------|--------|
|LOGO_SWITCH|—|Cycle through the 10 stored OLED logos in sequence|
|LOGO_CELUS|4|Force the Celus logo|
|LOGO_RIO|5|Force the Rio skyline logo|
|LOGO_LION|1|Force the Lion logo|
|LOGO_LUNCH|6|Force the Lunch reminder logo|
|LOGO_TOMORROWLAND|0|Force the Tomorrowland logo *(no key bound)*|
|LOGO_BAYERN|2|Force the Bayern logo *(no key bound)*|
|LOGO_FLAMENGO|3|Force the Flamengo logo *(no key bound)*|
|LOGO_THEOFFICE|7|Force The Office logo *(no key bound)*|
|LOGO_DJ|8|Force the DJ logo *(no key bound)*|

Index 9 is the password-generator logo, set automatically by `PASSW_GEN_TYPE`.

#### Application Launchers (Spotlight driven)
| Keycode | Action |
|---------|--------|
|BRAVE_OPEN|Open "Brave Brow" via Spotlight|
|COMET_OPEN|Open Comet browser|
|SAFARI_OPEN|Open Safari|
|FIREFOX_OPEN|Open Firefox|
|EDGE_OPEN|Open Microsoft Edge|
|K9S_OPEN|Type `k9s` and press Enter|
|SPOTIFY_OPEN|Open Spotify|
|ZOOM_OPEN|Open Zoom *(no key bound)*|
|CODE_OPEN|Open VS Code ("Code") *(no key bound)*|
|TXTEDIT_OPEN|Open TextEdit *(no key bound)*|
|WIREVPN_OPEN|Open WireGuard VPN *(no key bound)*|
|MATTERMOST_OPEN|Open Mattermost *(no key bound)*|
|TERMINAL_OPEN|Open the macOS Terminal app *(no key bound)*|
|MONITOR_OPEN|Open Monit *(no key bound)*|
|CALCULATOR_OPEN|Open Calculator *(no key bound)*|

#### Text, System, and Workflow Macros
| Keycode | Action |
|---------|--------|
|PASSW_GEN_TYPE|Generate a random 23-character password, copy it to the clipboard, type it, and switch the OLED to the password logo|
|AWS_SSO|Type `aws sso login` and press Enter|
|VIM_WQ_TYPE|Type `:wq`|
|KUBECTL_TYPE|Type `kubectl `|
|K8SCNTX_TYPE|Type `kubectl config use-context site-`|
|GIT_TYPE|Type `git commit --amend`|
|GIT_CLONE_TYPE|Type `git clone https://$gusr:$tok@$gitsite/`, paste the clipboard, then append `.git`|
|CMD_TAB|Hold Command, tap Tab, release (fast app switch)|
|CMD_SAVE|Send Command+S|
|CMD_V|Send Command+V (paste)|
|CMD_ALL|Send Command+A then Command+C (select all + copy)|
|CMD_V_URL|Type `[link here](`, paste the clipboard, then `)` — markdown link|
|SCREENSHOT|Send Command+Shift+5|
|LOCK_SCREEN|Send Control+Command+Q|
|APPLE_AI|Double-tap Command to open Apple Intelligence|
|BITWARDEN_UNLOCK|Send Command+Shift+L (Bitwarden unlock)|
|TYPE_EMAIL_WORK|Type `<redacted>`|
|TYPE_EMAIL_GMAIL|Type `<redacted>`|
|TYPE_EMAIL_DEUTSCH|Type `<redacted>`|
|VIM_TYPE|Type `vim ` (with trailing space) *(no key bound)*|
|TERRAFORM_TYPE|Type `terraform plan ` *(no key bound)*|
|CMD_Q|Send Command+Q (close app) *(no key bound)*|

#### k9s Command Macros
| Keycode | Action |
|---------|--------|
|K9S_CTX_TYPE|Type `:ctx` + Enter|
|K9S_NS_TYPE|Type `:ns` + Enter|
|K9S_PODS_TYPE|Type `:pods` + Enter|
|K9S_DEPLOY_TYPE|Type `:deployments` + Enter|
|K9S_SVC_TYPE|Type `:services` + Enter|
|K9S_STATEFULSET_TYPE|Type `:statefulsets` + Enter|
|K9S_CRONJOB_TYPE|Type `:cronjobs` + Enter|
|K9S_INGRESS_TYPE|Type `:ingressroute` + Enter|
|K9S_EXTERNALSECRET_TYPE|Type `:externalsecrets` + Enter|

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
