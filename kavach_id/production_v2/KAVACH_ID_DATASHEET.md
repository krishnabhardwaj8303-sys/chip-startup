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

---

## Revision 4.0 — Full Integration, Register Map Extension, Formal Verification Closure

### New Since Rev 3.0

**Full Top-Level Integration (`kavach_id_top.v`)**
- Rev 3.0's integration existed only as a separate `kavach_id_v2_top.v` snapshot that predated `kavach_auth_gate.v` and `provenance_chain.v`. This revision replaces it with a single `production_v2/kavach_id_top.v` that instantiates all 8 security modules plus the PUF array, PUF stabilizer, scrambler, and UART blocks in one design.
- `kavach_auth_gate.v` is now the sole authority for gating the UART transmit path — a message is only sent when `encrypt_done` AND `authentication_grant` are both true, replacing the earlier weaker "not replayed" check.
- Elaborates cleanly under Icarus Verilog (`iverilog`), confirming all inter-module port connections are correct.

**Register Map Extension**
- `kavach_register_map.v` previously had no way to actually reach `provenance_chain.v` or `offline_verify_counter.v` — the addresses referenced in Rev 3.0's documentation (0x14, 0x18, 0x1C) did not yet exist in the RTL. This revision adds the real wiring:

| Address | Name | Access | Description |
|---|---|---|---|
| 0x14 | PROVENANCE_STATUS | R | bit0=sequence_violation, bit1=chain_complete, bits[5:2]=stages_completed |
| 0x18 | OFFLINE_BUDGET | R | bits[7:0]=offline_budget, bit8=verify_allowed, bit9=sync_required |
| 0x1C | OFFLINE_CONTROL | W | bit0=sync_complete |
| 0x20 | STAGE_ID | W | [1:0] — held until next provenance record |
| 0x24 | STAGE_DATA | W | [31:0] — held until next provenance record |
| 0x28 | CHAIN_HASH | R | Current cumulative provenance chain hash |
| 0x2C | TOTAL_OFFLINE_USES | R | Lifetime offline-verification audit counter |

- `CONTROL` (0x00) gains bit3=`record_stage` (triggers provenance recording) and bit4=`verify_request` (triggers offline-budget check).

**Formal Verification Closure**
- 6 modules now formally proven correct via SymbiYosys + Yosys + Z3 (Bounded Model Checking): `kavach_auth_gate.v`, `kavach_bist.v`, `offline_verify_counter.v`, `replay_detector.v`, `provenance_chain.v`, `puf_stabilizer.v` — zero counterexamples across all bound depths tested.
- `kavach_register_map.v` brought from zero testbench coverage to 13/13 passing tests, including end-to-end verification that a register-issued `auth_request` correctly reaches `kavach_auth_gate.v` and its grant/deny result is correctly visible back through STATUS.

**Build Configuration Fix**
- `config.json`'s `VERILOG_FILES` previously pointed at the legacy `src/` prototype (pre-hardening, no BIST/auth-gate/register-map/encryption). It now explicitly lists all 14 `production_v2/` RTL files needed for `kavach_id_top`, so an OpenLane run will synthesize the actual verified/hardened design.

### Known Limitations (carried forward)
- PUF uniqueness and randomness still cannot be validated in RTL simulation — requires fabricated silicon and inter-chip Hamming-distance characterization.
- GDSII physical design has not yet been started.
- `src/` and `integrated_v2/` remain in the repo as legacy/intermediate snapshots, superseded by `production_v2/`.
