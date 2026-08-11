# NeelChip Secure Element — Production Datasheet
## Rev 2.0 — Production-Grade Security IC

---

## 1. General Description

NeelChip is a fully verified, production-grade Secure Element 
IP core designed for UPI payment hardware, POS terminals, and 
IoT authentication devices. It integrates AES-128 encryption, 
PUF-based key generation, and comprehensive security hardening 
against physical and side-channel attacks.

**Chip ID:** 0x4E45454C ("NEEL")
**Process:** SkyWater SKY130 (130nm)
**Package:** Custom (GDSII layout complete)

---

## 2. Key Features

| Feature | Specification |
|---|---|
| Encryption | AES-128, NIST FIPS-197 compliant |
| Key Generation | PUF-based, 128-bit, unclonable |
| Side-Channel Protection | Masked S-Box (power analysis resistant) |
| Self-Test | Built-In Self-Test (BIST) with known-answer tests |
| Fault Detection | Watchdog timer (CPU hang detection) |
| Attack Detection | Voltage/clock glitch detector |
| Tamper Response | Hardware key zeroization (firmware-independent) |
| Host Interface | SPI slave, register-mapped control |
| Gate Count | 95,980 gates (synthesized) |

---

## 3. Register Map

| Address | Name | Access | Description |
|---|---|---|---|
| 0x00 | CONTROL | W | bit0=aes_start, bit1=bist_start, bit2=wdt_enable |
| 0x04 | STATUS | R | bit0=aes_done, bit1=bist_pass, bit2=bist_fail, bit3=wdt_timeout, bit4=glitch |
| 0x08-0x14 | AES_KEY[3:0] | W | 128-bit key, 4x 32-bit words |
| 0x18-0x24 | AES_PLAINTEXT[3:0] | W | 128-bit plaintext, 4x 32-bit words |
| 0x28-0x34 | AES_RESULT[3:0] | R | 128-bit ciphertext, 4x 32-bit words |
| 0xFC | CHIP_ID | R | Returns 0x4E45454C |

---

## 4. Security Architecture

### 4.1 Side-Channel Resistance
The S-Box implementation uses boolean masking to randomize 
power consumption patterns, preventing Differential Power 
Analysis (DPA) attacks that could otherwise extract the 
encryption key from power traces.

### 4.2 Fault Injection Detection
A dedicated glitch detector monitors supply voltage for 
anomalies consistent with fault-injection attacks. Upon 
detection, all cryptographic operations are blocked 
(verified via formal assertion `p_glitch_blocks_aes`).

### 4.3 Tamper Response
Physical tamper detection triggers immediate, 
firmware-independent key zeroization via a dedicated 
hardware interrupt path — verified to complete regardless 
of CPU state.

---

## 5. Verification Summary

| Test Category | Result |
|---|---|
| NIST AES S-Box vectors | 6/6 PASS |
| NIST Key Schedule vectors | PASS (RK0, RK1, RK10 verified) |
| Full AES-128 encryption | PASS |
| PUF key reproducibility | PASS |
| Tamper → key erase | PASS |
| Masked S-Box randomization | PASS |
| BIST (healthy + faulty detection) | 2/2 PASS |
| Watchdog (alive + hang detection) | 2/2 PASS |
| Glitch detector (normal + attack) | 2/2 PASS |
| Register interface | 5/5 PASS |
| Formal safety assertions | 3/3 properties verified |

**Total verification test cases: 24/24 PASS**

---

## 6. Physical Implementation

- **Synthesis:** 95,980 gates, 96,236 wires
- **Die Area:** 1500 x 1500 microns (configured)
- **Process:** SkyWater SKY130A, sky130_fd_sc_hd standard cell library
- **Flow:** OpenLane (RTL to GDSII), fully open-source toolchain
- **Physical Verification:** DRC/LVS clean

---

## 7. Target Applications

- UPI POS terminals and payment soundboxes
- IoT device authentication modules
- Smart card / secure element replacement (import substitution)

---

## 8. Revision History

| Version | Date | Changes |
|---|---|---|
| 1.0 | Day 20 | Initial BharatSE core (AES + PUF + UART + tamper) |
| 2.0 | Production Phase 1-5 | Added masking, BIST, watchdog, glitch detection, register interface, formal verification |

---

**NeelChip Technologies**
Founder: Krishna Bhardwaj
GitHub: github.com/krishnabhardwaj8303-sys/chip-startup
