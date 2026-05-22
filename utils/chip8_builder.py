import argparse

def create_chip8_rom(bytes_list, output_file):
    rom_bytes = bytearray()

    for b in bytes_list:
        b = b.lower().replace("0x", "")
        rom_bytes.append(int(b, 16))

    with open(output_file, "wb") as f:
        f.write(rom_bytes)

    print(f"[+] ROM criado: {output_file}")
    print(f"[+] Total de bytes: {len(rom_bytes)}")

def main():
    parser = argparse.ArgumentParser(
        description="Gerador simples de ROM CHIP-8"
    )

    parser.add_argument(
        "-o",
        "--output",
        default="program.ch8"
    )

    parser.add_argument(
        "bytes",
        nargs="+"
    )

    args = parser.parse_args()

    create_chip8_rom(args.bytes, args.output)


if __name__ == "__main__":
    main()
