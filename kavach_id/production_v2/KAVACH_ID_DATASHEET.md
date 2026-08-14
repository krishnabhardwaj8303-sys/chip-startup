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

---

## Revision 3.0 — Encrypted Channel, Offline Verification, Supply-Chain Provenance, Full Integration

### New Since Rev 2.0

**Session-Nonce Encrypted UART Channel**
- Replaces the original plaintext challenge-response link with a stream cipher keyed by a session nonce that increments on every new reader connection
- Verified: encrypted wire data differs from plaintext (not snoopable), symmetric decryption correctly recovers original data, and identical challenges produce different ciphertext across sessions (replay-resistant even at the transport layer, independent of the replay-detector's challenge-history mechanism)

**Offline-First Verification Budget**
- A factory-provisioned counter (default: 50 uses) permits fully offline field authentication, critical for low-connectivity rural markets (the exact deployment context for GI-tagged agricultural/handloom goods)
- Verification is correctly BLOCKED once the budget is exhausted, forcing mandatory server sync before further offline use — bounding the security exposure of extended offline operation
- Verified: budget exhaustion correctly blocks the 50th+1 verification attempt; server sync correctly restores the full budget

**Supply-Chain Provenance Chaining**
- A 4-stage cryptographic chain (Manufacturing \u2192 Distribution \u2192 Retail \u2192 Consumer) where each stage adds a hash-linked record; out-of-sequence recording (e.g. Manufacturing directly to Consumer, skipping Distribution/Retail) is detected as a sequence violation
- This directly targets grey-market diversion and relabeling/re-manufacturing attempts \u2014 attack patterns distinct from simple counterfeit-identity spoofing that a single static-ID check does not address
- Verified: legitimate full-sequence chain completes without false alarm; skipped-stage diversion correctly flagged; duplicate-stage (relabeling) attempt correctly flagged

**Full Chip Integration (Kavach-ID v2)**
- PUF array, response stabilizer, replay detector, scrambler, encrypted channel, BIST, register map, and UART wired into a single top-level chip
- Verified: BIST-via-register produces correct chip-healthy status; replay-attack detection correctly blocks a repeated challenge end-to-end through the integrated chip

### Updated Register Map Addition

| Address | Name | Access | Description |
|---|---|---|---|
| 0x14 | PROVENANCE_STATUS | R | bit0 = sequence_violation, bit[5:1] = stages_completed |
| 0x18 | OFFLINE_BUDGET | R | Remaining offline-verification count |
| 0x1C | OFFLINE_CONTROL | W | bit0 = sync_complete trigger |

### Updated Verification Summary

| Test Category | Result |
|---|---|
| Encrypted channel | 3/3 PASS |
| Offline verification budget | 5/5 PASS |
| Supply-chain provenance | 3/3 PASS |
| Full v2 integration | Core scenarios PASS |

**Known Limitation Update (unchanged, restated for emphasis):** PUF uniqueness and randomness fundamentally cannot be validated in RTL simulation. This is the single most important open item for this chip \u2014 it requires fabricated silicon and inter-chip Hamming-distance characterization to actually confirm the security property the entire chip depends on. GDSII physical design has also not yet been started.
