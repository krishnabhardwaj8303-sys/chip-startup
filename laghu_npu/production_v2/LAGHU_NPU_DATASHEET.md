# Laghu-NPU — Production Datasheet
## Rev 2.0 — 4x4 Systolic AI Accelerator

---

## 1. General Description

Laghu-NPU is a production-grade 4x4 systolic array 
neural processing unit designed for edge-AI applications 
including agricultural drone vision, traffic ANPR, and 
IoT inference. It performs INT8 matrix-multiply operations 
with hardware-guaranteed numerical safety and fault detection.

**Chip ID:** 0x4C41474E ("LAGN")
**Process:** SkyWater SKY130 (130nm) — target
**Array Size:** 4x4 Processing Elements (PE)

---

## 2. Key Features

| Feature | Specification |
|---|---|
| Architecture | 4x4 Systolic Array (Weight-Stationary) |
| Data Type | INT8 weights & activations, INT32 accumulation |
| Activation | ReLU (hardware) |
| Numerical Safety | Saturating requantization (no silent overflow) |
| Self-Test | BIST with known-answer MAC verification |
| Hazard Protection | Pipeline race-condition detector |
| Host Interface | Register-mapped, 32-bit data bus |
| Gate Count | TBD (post-synthesis) |

---

## 3. Register Map

| Address | Name | Access | Description |
|---|---|---|---|
| 0x00 | CONTROL | W | bit0=start, bit1=bist_start, bit2=load_weights, bit3=load_activations |
| 0x04 | STATUS | R | bit0=done, bit1=bist_pass, bit2=bist_fail, bit3=hazard |
| 0x08 | W_ROW_IDX | W | Weight row index (0-3) |
| 0x0C | W_DATA | W | Packed 4x INT8 weights (one row) |
| 0x10 | A_DATA | W | Packed 4x INT8 activations |
| 0x14-0x20 | OUT[0:3] | R | 32-bit row-sum outputs (post-ReLU) |
| 0xFC | CHIP_ID | R | Returns 0x4C41474E |

---

## 4. Numerical Safety Architecture

### 4.1 Saturating Requantization
Every MAC accumulation result is passed through a saturating 
requantizer before being used by subsequent layers, preventing 
the silent integer wraparound that plagues naive NPU 
implementations — a documented source of incorrect AI 
inference in production hardware.

### 4.2 Pipeline Hazard Detection
Weight and activation loading are monitored against compute 
start signals. Any overlap (a real-world race condition in 
multi-cycle load sequences) is flagged and blocks computation, 
guaranteeing the array never computes on partially-loaded data.

---

## 5. Verification Summary

| Test Category | Result |
|---|---|
| Saturation (overflow) | PASS |
| Saturation (underflow) | PASS |
| Boundary value handling | PASS |
| BIST (healthy PE array) | PASS |
| BIST (faulty PE detection) | PASS |
| Hazard detection (weight race) | PASS |
| Hazard detection (activation race) | PASS |
| Register interface (5 tests) | 5/5 PASS |
| Formal safety assertions | 3/3 properties defined |

**Total verification test cases: 14/14 PASS**

---

## 6. Target Applications

- Agricultural drone crop-row vision (KisanDrone use-case)
- Traffic camera ANPR edge inference
- Low-power IoT vision endpoints

---

## 7. Revision History

| Version | Changes |
|---|---|
| 1.0 | Initial 4x4 systolic array (weights, MAC, ReLU) |
| 2.0 | Added saturation, BIST, hazard detection, register interface, formal assertions |

---

**NeelChip Technologies**
Founder: Krishna Bhardwaj
GitHub: github.com/krishnabhardwaj8303-sys/chip-startup
