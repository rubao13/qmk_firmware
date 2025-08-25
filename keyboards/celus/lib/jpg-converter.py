from __future__ import annotations
import argparse
import os
import sys
from PIL import Image


def image_to_c_array(image_path: str, output_path: str, width: int = 128, height: int = 64,
                     array_name: str | None = None, threshold: int = 128) -> None:
    """Convert an image into a C-style monochrome byte array (SSD1306 page order).

    Args:
        image_path: Source image path (any Pillow-readable format).
        output_path: Destination file path (.h/.inc/.txt etc.).
        width: Output width in pixels (OLED width = 128).
        height: Output height in pixels (OLED height = 64).
        array_name: Optional C symbol to wrap the bytes in an array definition.
        threshold: Grayscale threshold (0-255) for black/white conversion.
    """
    if not os.path.isfile(image_path):
        raise FileNotFoundError(f"Input image not found: {image_path}")
    if height % 8 != 0:
        raise ValueError("Height must be a multiple of 8 for page-based OLED format.")

    # Open, convert and resize
    img = Image.open(image_path).convert("L")
    img = img.resize((width, height), Image.Resampling.LANCZOS)

    # Binarize
    img = img.point(lambda x: 0 if x < threshold else 1, '1')

    pixels = img.load()
    byte_array = []
    for page in range(height // 8):  # each page = 8 vertical pixels
        for x in range(width):
            byte = 0
            for bit in range(8):
                y = page * 8 + bit
                if pixels[x, y] == 0:  # black pixel treated as "on"
                    byte |= (1 << bit)
            byte_array.append(byte)

    # Ensure directory exists
    os.makedirs(os.path.dirname(os.path.abspath(output_path)), exist_ok=True)

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(f"// Source: {os.path.basename(image_path)} | Size: {width}x{height}\n")
        f.write(f"// Bytes: {len(byte_array)}\n")
        if array_name:
            f.write(f"const uint8_t {array_name}[{len(byte_array)}] PROGMEM = {{\n")
        line = []
        for i, val in enumerate(byte_array, 1):
            line.append(f"0x{val:02x}")
            if i % 16 == 0:
                f.write(", ".join(line) + ",\n")
                line = []
        if line:
            f.write(", ".join(line) + (",\n" if array_name else "\n"))
        if array_name:
            f.write("};\n")

    print(f"Wrote {len(byte_array)} bytes -> {output_path}")


def parse_args(argv: list[str]) -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Convert an image to a QMK-friendly monochrome byte array.")
    p.add_argument("input", help="Input image path (jpg/png/etc.)")
    p.add_argument("output", help="Output file path (e.g. logo.h or logo.inc)")
    p.add_argument("-w", "--width", type=int, default=128, help="Output width (default: 128)")
    p.add_argument("-H", "--height", type=int, default=64, help="Output height (default: 64)")
    p.add_argument("-n", "--name", dest="array_name", help="Optional C array name to wrap bytes")
    p.add_argument("-t", "--threshold", type=int, default=128, help="B/W threshold 0-255 (default: 128)")
    return p.parse_args(argv)


if __name__ == "__main__":
    args = parse_args(sys.argv[1:])
    try:
        image_to_c_array(args.input, args.output, width=args.width, height=args.height,
                         array_name=args.array_name, threshold=args.threshold)
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)
