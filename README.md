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
