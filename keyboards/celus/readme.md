# Celus

# How to flash the keyboard
Generally you can follow the [official guide](https://docs.qmk.fm/newbs_getting_started). This is a bit more opinionated.
The official guide recommends to install qmk globally on the system. But I prefer to keep binaries and config in a separate directory.

## Steps
```
# Use dedicated directory
mkdir keyboard && cd keyboard

# Setup Python venv and install dependencies
python3 -m venv venv && source venv/bin/activate
pip3 install qmk

# Retrieve keyboard source code
git clone https://github.com/rubao13/qmk_firmware.git

# Initialize qmk (keep the qmk firmware)
qmk setup

# (Optional) Update keymap and keyboard behaviour
vim qmk_firmware/keyboards/celus/keymaps/default/keymap.c

# Compile keyboard firmware
cd qmk_firmware/
qmk compile -j0 -kb celus -km default

# Flash keyboard
# On first flash, hold "boot" on the microcontroller while connecting the cable
# Once the initial flash was done, simply press "reset" twice while plugin to reflash
sudo mount "/dev/microcontroller" /mnt
sudo cp celus_default.uf2 /mnt
```
