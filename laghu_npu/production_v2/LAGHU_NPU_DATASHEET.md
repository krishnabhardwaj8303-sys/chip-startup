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

---

## Revision 3.0 — Multi-Layer Chaining, Confidence Estimation, Sparsity Gating, Full Integration

### New Since Rev 2.0

**Multi-Layer Chaining**
- Layer-to-layer chaining controller: Layer 1's INT32 accumulator output is saturated and requantized to INT8, then correctly fed as Layer 2's activation input — demonstrating true multi-layer network inference rather than a single-layer demonstration
- Verified: 2-layer chain data flow correct; inter-layer overflow correctly saturated at the layer boundary

**Multi-Channel Saturation Confidence Estimator**
- Detects the specific signature of dust/fog camera-sensor corruption: multiple simultaneously saturated activation channels
- A single saturated channel (normal bright object in frame) is correctly NOT flagged; 3-4 simultaneously saturated channels ARE flagged as low-confidence
- Verified: 4/4 test cases pass, including correct non-triggering on a normal bright-spot scenario

**Sparsity-Aware MAC Skipping**
- Clock-gates zero-weight Processing Elements, exploiting the fact that pruned neural-network models (a standard AI deployment optimization) contain 30-70% zero weights
- Verified power-saving estimate: 50% at 8/16 zero weights, 75% at 12/16 zero weights, with correct per-PE targeting (verified that only the PE corresponding to a specific zero weight is gated, not others)

**Full Chip Integration (Laghu-NPU v2)**
- Core systolic array, hazard detector, confidence estimator, requantizer, BIST, and register map wired into a single top-level chip
- Verified: BIST-via-register, clean-data compute producing correct MAC results, hazard-path wiring, and confidence-gated output (low-confidence inputs correctly zero the reported result rather than reporting a silently-wrong prediction)

### Updated Register Map Addition

| Address | Name | Access | Description |
|---|---|---|---|
| 0x28 | SPARSITY_STATUS | R | bit[4:0] = zero-weight count, bit[15:8] = estimated power-saved % |
| 0x2C | CONFIDENCE_STATUS | R | bit0 = low-confidence flag, bit[3:1] = saturated-channel count |

### Updated Verification Summary

| Test Category | Result |
|---|---|
| Multi-layer chaining | 3/3 PASS |
| Confidence estimator | 4/4 PASS |
| Sparsity-aware gating | 4/4 PASS |
| Full v2 integration | Core scenarios PASS |

**Known Limitation Update:** GDSII physical design has not yet been started for this chip (unchanged from Rev 2.0) — this remains the largest gap toward production readiness alongside a real trained-model (e.g. MNIST) benchmark, which has also not yet been run.
