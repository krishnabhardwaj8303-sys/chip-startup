# NeelChip — India's First Student-Designed Secure Element
## by Krishna Bhardwaj | ECE 2nd Year | Fabless Semiconductor Startup

---

## What is NeelChip?
India's first open-source Secure Element IP Core —
designed to replace imported NXP/Infineon chips in
UPI payment terminals, POS devices, and soundboxes.

## The Problem
- India processes 18 BILLION UPI transactions/month
- Every POS/Soundbox uses IMPORTED secure elements
- NXP, Infineon, STMicro — all foreign chips
- Zero Indian secure element in production today

## The Solution — NeelChip v1.0
A fully verified, NIST-compliant Secure Element IP Core
designed from scratch in 21 days using free tools.

---

## Architecture

NeelChip
├── PUF Block          → 128-bit unclonable device key
├── AES-128 Core       → NIST FIPS-197 compliant encryption
│   ├── S-Box          → NIST verified
│   ├── Key Scheduler  → 11 round keys verified
│   ├── Round Function → SubBytes+ShiftRows+MixCols+ARK
│   └── Final Round    → 10-round complete pipeline
├── UART Interface     → External communication
└── Interrupt + Tamper → Hardware key zeroization

---

## Verification Results

| Block | Test | Result |
|-------|------|--------|
| AES S-Box | NIST vectors | 6/6 PASS |
| Key Scheduler | NIST FIPS-197 | PASS |
| AES Core | Encryption | PASS |
| PUF Key | Reproducibility | PASS |
| Tamper Detection | Key Erase | PASS |
| Full System | Integration | PASS |

---

## 21-Day Build Journey

| Week | What I Built |
|------|-------------|
| Week 1 | CPU: ALU + Register File + Pipeline |
| Week 2 | Protocols: UART + SPI + I2C + PWM |
| Week 3 | NeelChip: AES + PUF + Tamper |

---

## Tools Used (100% Free)
- Icarus Verilog — Simulation
- Verilator — Fast simulation + coverage
- GTKWave — Waveform analysis
- Git + GitHub — Version control
- OpenLane (next) — RTL to GDSII

## Target Funding
- MeitY DLI Scheme — Chip Design Infrastructure Support
- Smart India Hackathon 2025
- Startup India Recognition (DPIIT)

## Market Opportunity
- 18B+ UPI transactions/month
- 10M+ POS terminals in India
- Zero Indian secure element chips today
- Target: Rs 5/chip royalty x 1M chips = Rs 5 Cr/year

## Contact
- GitHub: krishnabhardwaj8303-sys
- Email: krishnabhardwaj8303@gmail.com

---

## Chip 2: Laghu-NPU — Edge AI Matrix-Multiply Accelerator

A compact 4x4 systolic-array AI inference engine — the core compute building block used in edge AI accelerators (similar in principle to Google TPU / Apple Neural Engine, at student scale).

### What It Does
Performs output = ReLU(Weight_Matrix x Input_Vector) — the fundamental operation repeated billions of times in every neural network.

### Architecture

    Laghu-NPU
    |-- 4x4 Systolic MAC Array    -> 16 parallel Multiply-Accumulate units
    |-- Weight/Activation Buffers -> On-chip register storage
    |-- ReLU Activation Unit      -> Non-linearity for neural net layers
    +-- Control FSM               -> Load -> Compute -> Output sequencing

### Verification
8-bit signed INT MAC operations, 32-bit accumulation. Test case: diagonal weight matrix x input vector — TEST PASSED (matched expected output exactly).

### Status
Complete, simulation verified. OpenLane flow pending.

---

## Chip 3: Kavach-ID — PUF-Based Anti-Counterfeit Authentication Chip

An unclonable hardware identity chip designed to combat India's ₹1 lakh crore+/year counterfeit parts and agrochemical crisis — using silicon manufacturing variation as an uncopiable fingerprint.

### The Problem
Fake spare parts, bearings, and pesticides cause equipment failure, crop loss, and safety incidents. Existing anti-counterfeiting (holograms, QR codes) is trivially cloned.

### Architecture

    Kavach-ID
    |-- Arbiter PUF Array (32-bit)  -> Silicon-variation-based unique fingerprint
    |-- Challenge-Response Engine   -> Cryptographic authentication protocol
    |-- Scrambler                   -> Obfuscates raw PUF output from leakage
    |-- UART Interface              -> Host verification communication
    +-- Control FSM                 -> Challenge -> PUF -> Scramble -> Respond

### Status
Complete, simulation verified. OpenLane flow pending.

## 🔐 NeelChip — Now Production-Grade!
- Side-channel resistant (masked AES S-Box)
- BIST + Watchdog + Glitch Detection
- Register-mapped host interface
- Formal safety assertions verified
- Complete datasheet available
- 24/24 verification test cases PASS

See: day20/production_v2/NEELCHIP_DATASHEET.md

---

## 🆕 Production Hardening Update (Post-Proposal Gap Closure)

Following the technical roadmap outlined in the University R&D 
Cell proposal, the following gaps have been actively closed with 
verified RTL and passing testbenches:

### NeelChip — Dedicated TRNG
- Ring-oscillator-modeled True Random Number Generator, 
  architecturally distinct from the PUF (identity) block
- Von Neumann de-biasing to remove statistical bias
- Built-in monobit statistical self-test (NIST SP 800-22 style)
- **Status: RTL verified, consecutive outputs confirmed unique**

### Laghu-NPU — Multi-Layer Chaining
- Layer-to-layer chaining controller: Layer 1 (INT32 accumulator) 
  output is saturated and requantized to INT8, then fed as Layer 
  2 input — the core mechanism of real neural network inference
- Addresses the proposal's primary limitation: *"cannot chain 
  multiple layers... not a competitive AI accelerator"*
- **Status: 2-layer chain verified, inter-layer overflow 
  correctly saturated**

### Kavach-ID — Encrypted Communication Channel
- Session-nonce-based stream cipher replacing plaintext UART link
- Fresh keystream per reader connection — same challenge produces 
  different ciphertext across sessions (replay-resistant)
- Symmetric encrypt/decrypt verified round-trip correct
- **Status: 3/3 tests pass — wire-snoop and replay resistance 
  both verified**

### TropicBMS-RV — CAN-Lite Vehicle Bus Interface
- Priority-based CAN frame controller for vehicle-level 
  integration (motor controller, dashboard, charger)
- Emergency thermal-trip frames use highest-priority CAN ID 
  (0x001), preempting routine status broadcasts
- **Status: Priority preemption verified — emergency frames 
  never delayed by normal traffic**

---

## Verification Test Count (Cumulative)

| Chip | Core Tests | Production Tests | Gap-Closure Tests | Total |
|---|---|---|---|---|
| NeelChip | 6 (NIST) | 24 | 2 (TRNG) | 32 |
| Laghu-NPU | 1 | 14 | 3 (chaining) | 18 |
| Kavach-ID | - | 7 | 3 (encryption) | 10 |
| TropicBMS-RV | 6 | 10 | 3 (CAN) | 19 |
| **Total** | | | | **79 passing test cases** |

This update directly reflects Phase 1-2 of the roadmap proposed 
to the R&D Cell: closing production-readiness gaps with verified 
RTL, ahead of the OpenLane physical-design and Efabless 
tape-out phases.

---

## 💡 Unique Differentiators (Beyond Standard Production Hardening)

Each chip in this portfolio includes one hardware feature 
specifically designed for an Indian deployment context that 
generic/imported chips do not address:

| Chip | Unique Feature | Problem Addressed |
|---|---|---|
| NeelChip | Dual-mode security (LITE/FULL) with auto-escalation | Single-SKU imports force all-or-nothing pricing; this enables one silicon to serve both budget and premium POS markets |
| TropicBMS-RV | Rate-of-change thermal detection | Absolute-threshold-only imports react too late; this catches the accelerating pattern of thermal runaway before the danger threshold |
| Laghu-NPU | Multi-channel saturation confidence estimator | Generic AI accelerators silently mispredict on dust/fog-corrupted camera input; this flags low-confidence results instead |
| Kavach-ID | Offline verification budget with mandatory sync | Server-dependent anti-counterfeit systems fail in low-connectivity rural markets; this enables secure offline operation with a bounded trust window |

All four have been verified in simulation (5/5, 4/4, 4/4, and 
5/5 test cases respectively).

---

## 🆕 Round 2 Innovation — Additional Differentiators

- **Kavach-ID:** Supply-chain provenance chaining — a 4-stage (Manufacturing → Distribution → Retail → Consumer) cryptographic chain that detects grey-market diversion (skipped stages) and relabeling attempts (duplicate stage recording). Verified: 3/3 tests pass.
- **Laghu-NPU:** Sparsity-aware MAC skipping — clock-gates zero-weight processing elements, verified to save 50-75% estimated power on pruned model weights (a standard AI optimization technique) without affecting dense-matrix correctness. Verified: 4/4 tests pass.
- **TropicBMS-RV:** State-of-Health (SOH) degradation tracking — cycle-counting with a realistic capacity-fade model, providing battery lifespan data (not just current charge) for warranty, resale, and predictive-maintenance use cases. Verified: 4/4 tests pass.
