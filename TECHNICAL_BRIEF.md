# BharatSE — Technical Brief

## One Line
India's first open-source Secure Element IP Core
for UPI payment hardware — replacing NXP/Infineon.

## Problem
Rs 2000+ Cr worth of secure element chips imported
annually for India's payment infrastructure.
Zero Indian alternatives exist today.

## Solution
BharatSE IP Core:
- AES-128 encryption (NIST FIPS-197 verified)
- PUF-based unclonable device key
- Hardware tamper detection + key zeroization
- UART/SPI/I2C interfaces
- Designed for UPI/POS/Soundbox use cases

## Verification
- 6/6 NIST AES S-Box vectors: PASS
- NIST Key Schedule RK0-RK10: PASS
- PUF reproducibility: PASS
- Tamper → Key erase: PASS

## Business Model
- IP licensing: Rs 5-10/chip royalty
- Target: Pine Labs, BharatPe, Paytm devices
- TAM: 10M+ POS terminals in India
- Revenue Year 1: Rs 50L-1Cr (IP license fees)
- Revenue Year 3: Rs 5Cr+ (volume royalties)

## Current Status
- RTL design: COMPLETE
- Simulation verified: COMPLETE
- FPGA prototype: IN PROGRESS
- DLI application: READY TO SUBMIT

## Founder
Krishna Bhardwaj
ECE 2nd Year Student
GitHub: krishnabhardwaj8303-sys
