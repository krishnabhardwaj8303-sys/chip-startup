#!/usr/bin/env python3
"""
pramaan_uart.py — PC-side host driver for Pramaan-ID (Kavach-ID) secure element.

Implements the 6-byte UART frame protocol defined by uart_to_reg_bridge.v:

    [CMD (1 byte)] [ADDR (1 byte)] [DATA (4 bytes, MSB-first)]

    CMD = 0x01  ->  WRITE  : write DATA to register ADDR
    CMD = 0x02  ->  READ   : read register ADDR, chip replies with
                             4 bytes (MSB-first) over the same UART line

This script talks to REAL hardware (an FPGA dev board or a UART-capable
board running the synthesized/programmed chip) over a serial port. It
does NOT talk to the Verilog simulation directly - the simulation
testbenches (kavach_id_top_uart_tb.v etc.) already exercise this same
protocol inside Icarus Verilog. This script is the equivalent driver
for when real silicon/FPGA hardware is available on a COM/tty port.

Requires: pip install pyserial

Usage examples:
    python3 pramaan_uart.py --port COM5 bist
    python3 pramaan_uart.py --port /dev/ttyUSB0 verify --challenge 0x11111111
    python3 pramaan_uart.py --port COM5 status
    python3 pramaan_uart.py --port COM5 read-reg 0x34
    python3 pramaan_uart.py --port COM5 write-reg 0x08 0x11111111
    python3 pramaan_uart.py --port COM5 program-key 0xCAFEF00D
"""

import argparse
import sys
import time

try:
    import serial
except ImportError:
    print("Missing dependency. Install with:  pip install pyserial", file=sys.stderr)
    sys.exit(1)

# -- Register map (must match kavach_register_map.v / KAVACH_ID_DATASHEET.md) --
REG = {
    "CONTROL":          0x00,
    "STATUS":           0x04,
    "CHALLENGE":         0x08,
    "RESPONSE":          0x0C,
    "UNSTABLE_COUNT":    0x10,
    "STAGE_ID":          0x14,
    "STAGE_DATA":        0x18,
    "PROVENANCE_STATUS": 0x1C,
    "OFFLINE_STATUS":    0x20,
    "OFFLINE_USES":      0x24,
    "KEY_DATA":          0x28,
    "KEY_CONTROL":       0x2C,
    "KEY_STATUS":        0x30,
    "CIPHERTEXT_DATA":   0x34,
    "TX_COUNTER":        0x38,
    "CHIP_ID":           0xFC,
}

CMD_WRITE = 0x01
CMD_READ  = 0x02


class PramaanID:
    """Thin serial-port driver implementing the 6-byte frame protocol."""

    def __init__(self, port, baudrate=9600, timeout=1.0):
        self.ser = serial.Serial(port, baudrate=baudrate, timeout=timeout)
        time.sleep(0.2)

    def close(self):
        self.ser.close()

    def write_reg(self, addr, data):
        frame = bytes([
            CMD_WRITE,
            addr & 0xFF,
            (data >> 24) & 0xFF,
            (data >> 16) & 0xFF,
            (data >> 8) & 0xFF,
            data & 0xFF,
        ])
        self.ser.write(frame)
        self.ser.flush()

    def read_reg(self, addr):
        frame = bytes([CMD_READ, addr & 0xFF, 0x00, 0x00, 0x00, 0x00])
        self.ser.write(frame)
        self.ser.flush()

        resp = self.ser.read(4)
        if len(resp) != 4:
            raise TimeoutError(
                f"Expected 4 response bytes reading addr 0x{addr:02X}, "
                f"got {len(resp)}. Check wiring/baud rate/board power."
            )
        return int.from_bytes(resp, byteorder="big")

    def run_bist(self):
        self.write_reg(REG["CONTROL"], 1 << 0)
        time.sleep(0.05)
        status = self.read_reg(REG["STATUS"])
        return {
            "bist_pass": bool(status & (1 << 0)),
            "bist_fail": bool(status & (1 << 1)),
        }

    def verify(self, challenge):
        self.write_reg(REG["CHALLENGE"], challenge)
        self.write_reg(REG["CONTROL"], 1 << 1)
        time.sleep(0.05)
        self.write_reg(REG["CONTROL"], 1 << 2)
        time.sleep(0.05)
        status = self.read_reg(REG["STATUS"])
        return {
            "authentication_grant": bool(status & (1 << 3)),
            "auth_denied_bist":     bool(status & (1 << 4)),
            "auth_denied_replay":   bool(status & (1 << 5)),
            "replay_detected":      bool(status & (1 << 2)),
            "raw_status":           status,
        }

    def read_ciphertext(self):
        return self.read_reg(REG["CIPHERTEXT_DATA"])

    def offline_budget(self):
        val = self.read_reg(REG["OFFLINE_STATUS"])
        return {
            "budget":        val & 0xFF,
            "sync_required": bool(val & (1 << 8)),
        }

    def sync_complete(self):
        self.write_reg(REG["CONTROL"], 1 << 3)

    def program_key(self, key_value):
        self.write_reg(REG["KEY_DATA"], key_value)
        self.write_reg(REG["KEY_CONTROL"], 1)
        time.sleep(0.05)
        return self.key_status()

    def key_status(self):
        val = self.read_reg(REG["KEY_STATUS"])
        return {"key_locked": bool(val & 1)}

    def chip_id(self):
        return self.read_reg(REG["CHIP_ID"])

    def record_provenance_stage(self, stage_id, stage_data):
        self.write_reg(REG["STAGE_ID"], stage_id & 0x3)
        self.write_reg(REG["STAGE_DATA"], stage_data)
        self.write_reg(REG["CONTROL"], 1 << 4)
        time.sleep(0.05)
        return self.provenance_status()

    def provenance_status(self):
        val = self.read_reg(REG["PROVENANCE_STATUS"])
        return {
            "sequence_violation": bool(val & 1),
            "chain_complete":     bool(val & (1 << 1)),
            "stages_completed":   (val >> 2) & 0xF,
        }


def main():
    ap = argparse.ArgumentParser(description="Pramaan-ID (Kavach-ID) UART host driver")
    ap.add_argument("--port", required=True, help="Serial port, e.g. COM5 or /dev/ttyUSB0")
    ap.add_argument("--baud", type=int, default=9600, help="Baud rate (default 9600)")

    sub = ap.add_subparsers(dest="cmd", required=True)

    sub.add_parser("bist", help="Run BIST and report health")
    sub.add_parser("status", help="Read the STATUS register")
    sub.add_parser("chip-id", help="Read the CHIP_ID register")
    sub.add_parser("offline-budget", help="Read remaining offline-verification budget")
    sub.add_parser("sync-complete", help="Notify chip of a server sync (restores budget)")

    p_verify = sub.add_parser("verify", help="Run a full authentication attempt")
    p_verify.add_argument("--challenge", required=True, help="32-bit challenge, e.g. 0x11111111")

    p_key = sub.add_parser("program-key", help="Factory-provision the per-chip key (WRITE ONCE)")
    p_key.add_argument("key", help="32-bit key value, e.g. 0xCAFEF00D")

    p_wr = sub.add_parser("write-reg", help="Raw register write")
    p_wr.add_argument("addr", help="Register address, e.g. 0x08")
    p_wr.add_argument("data", help="32-bit value, e.g. 0x11111111")

    p_rd = sub.add_parser("read-reg", help="Raw register read")
    p_rd.add_argument("addr", help="Register address, e.g. 0x34")

    p_prov = sub.add_parser("record-stage", help="Record a supply-chain provenance stage")
    p_prov.add_argument("stage_id", type=int, choices=[0, 1, 2, 3],
                         help="0=Manufacturing 1=Distribution 2=Retail 3=Consumer")
    p_prov.add_argument("stage_data", help="32-bit stage data, e.g. 0xAAAA0000")

    args = ap.parse_args()

    chip = PramaanID(args.port, baudrate=args.baud)
    try:
        if args.cmd == "bist":
            print(chip.run_bist())
        elif args.cmd == "status":
            val = chip.read_reg(REG["STATUS"])
            print(f"STATUS = 0x{val:08X}")
        elif args.cmd == "chip-id":
            print(f"CHIP_ID = 0x{chip.chip_id():08X}")
        elif args.cmd == "offline-budget":
            print(chip.offline_budget())
        elif args.cmd == "sync-complete":
            chip.sync_complete()
            print("sync_complete sent.")
        elif args.cmd == "verify":
            result = chip.verify(int(args.challenge, 0))
            print(result)
            if result["authentication_grant"]:
                print(f"Ciphertext: 0x{chip.read_ciphertext():08X}")
        elif args.cmd == "program-key":
            print(chip.program_key(int(args.key, 0)))
        elif args.cmd == "write-reg":
            chip.write_reg(int(args.addr, 0), int(args.data, 0))
            print("Write sent.")
        elif args.cmd == "read-reg":
            addr_int = int(args.addr, 0)
            val = chip.read_reg(addr_int)
            print(f"0x{addr_int:02X} = 0x{val:08X}")
        elif args.cmd == "record-stage":
            result = chip.record_provenance_stage(args.stage_id, int(args.stage_data, 0))
            print(result)
    finally:
        chip.close()


if __name__ == "__main__":
    main()
