# Kavach-ID — Production Datasheet
## Rev 2.0 — PUF-Based Anti-Counterfeit Authentication Chip

---

## 1. General Description

Kavach-ID is a production-grade PUF-based authentication IP 
core designed for anti-counterfeit protection of GI-tagged 
goods, branded products, and supply-chain authentication. 
Each chip has a physically unclonable identity, hardened 
against noise, replay attacks, and silicon degradation.

**Chip ID:** 0x4B415641 ("KAVA")
**Process:** SkyWater SKY130 (130nm) — target
**Protocol:** UART challenge-response (32-bit)

---

## 2. Key Features

| Feature | Specification |
|---|---|
| Identity | SRAM/PUF-based, physically unclonable |
| Response Stability | 3-sample majority voting (noise-resistant) |
| Attack Resistance | Replay attack detection (4-entry history) |
| Self-Test | BIST — factory-calibrated PUF health check |
| Host Interface | Register-mapped, 32-bit + legacy UART |
| Gate Count | TBD (post-synthesis) |

---

## 3. Register Map

| Address | Name | Access | Description |
|---|---|---|---|
| 0x00 | CONTROL | W | bit0=bist_start, bit1=stabilizer_start |
| 0x04 | STATUS | R | bit0=bist_pass, bit1=bist_fail, bit2=replay_detected |
| 0x08 | CHALLENGE | W | 32-bit challenge input |
| 0x0C | RESPONSE | R | 32-bit stabilized PUF response |
| 0x10 | UNSTABLE_COUNT | R | Diagnostic: noisy bit count from last read |
| 0xFC | CHIP_ID | R | Returns 0x4B415641 |

---

## 4. Security Architecture

### 4.1 Noise-Resilient Authentication
Unlike naive single-sample PUF designs that suffer random 
authentication failures from environmental noise, Kavach-ID 
samples the PUF response three times and applies bitwise 
majority voting, eliminating false-negative authentication 
failures for genuine devices.

### 4.2 Replay Attack Protection
A 4-entry challenge history buffer detects when a previously 
seen challenge is resubmitted — the classic record-and-replay 
attack vector against challenge-response authentication 
systems — and blocks authentication in that case.

---

## 5. Verification Summary

| Test Category | Result |
|---|---|
| PUF stability (perfect match) | PASS |
| PUF stability (1-bit noise) | PASS |
| PUF stability (multi-bit noise) | PASS |
| BIST (healthy PUF) | PASS |
| BIST (degraded PUF) | PASS |
| Replay detection (fresh challenges) | PASS |
| Replay detection (attack) | PASS |
| Formal safety assertions | 2/2 properties defined |

**Total verification test cases: 7/7 PASS**

---

## 6. Target Applications

- GI-tagged handloom/handicraft authentication
- Brand anti-counterfeit tags
- Supply-chain component verification

---

## 7. Revision History

| Version | Changes |
|---|---|
| 1.0 | Initial PUF challenge-response over UART |
| 2.0 | Added noise stabilization, replay detection, BIST, register interface, formal assertions |

---

**NeelChip Technologies**
Founder: Krishna Bhardwaj
GitHub: github.com/krishnabhardwaj8303-sys/chip-startup
