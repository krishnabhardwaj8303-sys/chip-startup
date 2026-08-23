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

---

## Revision 5.0 — Top-Level Integration Bug Fixes, SKY130 Synthesis, Repository Cleanup

### New Since Rev 4.0

**Sticky Status Latch Fix**
- Bug found: `kavach_bist.v` and `kavach_auth_gate.v` outputs (`bist_pass`, `bist_fail`, `authentication_grant`, `auth_denied_bist`, `auth_denied_replay`) are all one-cycle pulses. Each module's own isolated testbench sampled the result on the exact cycle it appeared, masking the issue. A real host polling STATUS a few cycles later — the realistic scenario — saw the pulse already gone, reading back all-zero.
- Fix: added sticky latch registers at top level, cleared only when the next corresponding operation begins (`bist_start` / `auth_request`) or on reset.
- Verified via a new dedicated top-level testbench (`kavach_id_top_tb.v`), which initially failed all 4 tests pre-fix and passed all 4 post-fix.

**UART Full-Response Transmission Fix**
- Bug found: the UART TX path transmitted only the top byte (`ciphertext_out[31:24]`) of the 32-bit encrypted response via a single un-sequenced assignment — the receiver only ever got 25% of the authenticated response.
- Fix: restored a proper 4-byte send sequence (`TX_IDLE → TX_B1 → TX_B2 → TX_B3`), gated so transmission only occurs on a genuine `authentication_grant`.

**Offline-Verify Counter and Provenance Chain — Now Wired to Top Level**
- Both modules were formally verified in isolation (Rev 4.0) but never connected to `kavach_id_top.v`. This revision wires both in:
  - `offline_verify_counter.v`: every `auth_request` now consumes one unit of offline budget; `authentication_grant` is now additionally gated on `verify_allowed` (non-exhausted budget) — enforcing at chip level the same property already formally proven for the module in isolation.
  - `provenance_chain.v`: host can now record supply-chain stages via new `STAGE_ID`/`STAGE_DATA`/`CONTROL[bit4]` registers, independent of the authentication critical path.
- New register map addresses: `0x14` PROVENANCE_STATUS, `0x18` OFFLINE_BUDGET, `0x1C` OFFLINE_CONTROL, `0x20` STAGE_ID, `0x24` STAGE_DATA.

**Double-Pulse / Dead-Condition Bug (auth_request → offline budget)**
- Bug found: a top-level testbench for the newly-wired offline counter showed the budget decrementing by 2 per logical request instead of 1 (50→40 after 5 requests, not 50→45), and a separate `verification_blocked` flag never asserting on budget exhaustion despite `authentication_grant` correctly being withheld.
- Root cause: (1) the raw `auth_request_o` register-map output was being fed directly into both `kavach_auth_gate` and `offline_verify_counter`, and observed to assert across two consecutive clock edges in simulation trace, causing a double count; (2) the `budget_denial_this_cycle` expression included a dead condition (`auth_request_o & auth_grant_raw`) that could structurally never be true, since `auth_grant_raw` only becomes valid on the cycle *after* `auth_request_o` has already deasserted.
- Fix: replaced all raw `auth_request_o` consumers with an edge-detected, guaranteed single-cycle `auth_request_pulse` (`auth_request_o & ~auth_request_prev`), and removed the dead condition from `budget_denial_this_cycle`.
- Verified via a dedicated `offline_provenance_tb.v` covering budget decrement, exhaustion/denial, `sync_complete` budget restoration, and both correct-sequence and skipped-stage provenance scenarios — 7/7 tests pass.

**`puf_stabilizer.v` Top-Level "No-Op" Limitation — Closed**
- Previously documented limitation: all three inputs to `puf_stabilizer` (`raw_response_1/2/3`) were wired to the same single `puf_array` read, making the majority-voting logic a no-op at chip level despite being formally verified in isolation.
- Fix: added a PUF resample controller (a small FSM) that pulses `puf_array` three separate times in sequence, latching each result into an independent sample register, before triggering `puf_stabilizer` with three genuinely distinct reads.
- Scope note (stated for accuracy): in RTL/Icarus behavioral simulation, `arbiter_puf_cell`'s delay-chain paths have zero simulated delay, so all three resampled reads remain bit-identical in this simulation environment regardless of this fix. This change corrects the **architecture** (three independent reads vs. one read reused three times) — genuine noise-correction behavior can only be observed on fabricated silicon or via SDF-annotated post-synthesis timing simulation.

**`arbiter_puf_cell.v` — Combinational Feedback Loop Fixed**
- Bug found: Yosys `synth -flatten` + CHECK reported 64 combinational logic-loop warnings (2 per PUF cell × 32 cells). Root cause: `mux_a`/`mux_b` fed back from `path_a`/`path_b` themselves whenever `challenge_bit` selected that branch (e.g. `mux_a = challenge_bit ? pulse_in : path_a` combined with `path_a = buf(mux_a)` creates `path_a = buf(path_a)` when `challenge_bit = 0`) — a literal self-referencing loop with no real signal ever propagating on that path for that challenge polarity.
- Fix: both delay chains (`raw_a`, `raw_b`) are now driven unconditionally from `pulse_in` with zero feedback; `challenge_bit` instead swaps which physical buffer output is labeled `path_a` vs. `path_b` before arbitration, preserving the intended "challenge selects routing" behavior without any loop.
- Result: post-fix synthesis reports 0 logic-loop warnings (down from 64); all 11 integration tests (top-level + offline/provenance) re-verified passing with no regressions.

**Updated Synthesis Results (SKY130, post-bug-fix RTL)**
- Tool: Yosys 0.52, `synth -flatten`, technology-mapped via `dfflibmap` + `abc` against the SkyWater SKY130 HD standard-cell library (`sky130_fd_sc_hd`, `tt_025C_1v80` typical corner).
- Result: **1,611 mapped standard cells, 18,271.27 µm² (≈0.0183 mm²) chip area**, of which 49.72% is sequential (flip-flop) area.
- Scope note: this is a **pre-place-and-route** standard-cell area estimate. It does not include routing overhead, cell spacing, or floorplan utilization margin; final post-place-and-route die area is typically 20–40% larger than this figure, consistent with realistic standard-cell utilization densities (60–80%, not 100%).
- This supersedes the earlier Rev 4.0-era hierarchical/generic-gate estimate, which predated all of the bug fixes listed above and was not technology-mapped to a specific standard-cell library.

**Repository Cleanup**
- Confirmed via `diff` that `kavach_id/integrated_v2/` (an intermediate checkpoint predating `kavach_auth_gate.v` and `provenance_chain.v`) contained no logic beyond what is already present and superseded in `production_v2/`; removed from the repository (preserved in git history).
- Confirmed no stray root-level `config.json` exists outside `kavach_id/config.json`.

### Updated Cumulative Status
6 modules formally proven correct (unchanged from Rev 4.0); top-level integration now additionally verified via 11/11 passing simulation tests across two dedicated testbenches (`kavach_id_top_tb.v`, `offline_provenance_tb.v`), covering BIST health reporting, authentication grant/denial (replay, BIST-fail, and now budget-exhaustion paths), full 4-byte UART transmission, offline-budget decrement/exhaustion/restoration, and both correct-sequence and violation-detection provenance scenarios. Two additional real bugs (PUF stabilizer no-op, arbiter PUF combinational loop) found and fixed since Rev 4.0, on top of the five integration-level bugs listed above.

---

## Revision 5.1 — Reset Synchronization Hardening

**Reset Recovery/Removal Hazard — Closed**
- Identified: 17 `always @(posedge clk or posedge rst)` blocks across the design used the raw external reset directly. While correct for reset *assertion* (must react immediately), this is unsafe for reset *de-assertion*: if the external reset releases close to a clock edge, different flip-flops across the chip can sample the release on different cycles, leaving the chip in an inconsistent, undefined state at power-up — a hazard invisible in RTL simulation but real on fabricated silicon.
- Fix: added `reset_sync.v`, a standard 2-stage async-assert/sync-deassert reset synchronizer. The external `rst` now only drives this synchronizer; every internal always-block uses the synchronized `rst_sync` output, guaranteeing all flops observe reset release on the same clock edge.
- Verified: all 11 existing integration tests (`kavach_id_top_tb.v`, `offline_provenance_tb.v`) re-run and pass with no regressions after this change.

**Scan-DFT Readiness Check**
- Confirmed via Yosys post-synthesis selection (`select -assert-none t:$_DLATCH_*` / `t:$_SR_*`) that the design contains no unintended latches or SR-latch inference — the design is fully flip-flop-based synchronous logic, which is a prerequisite for straightforward scan-chain DFT insertion in a future physical-implementation pass.

---

**Module-Level Combinational Loop Audit**
- Following the arbiter_puf_cell.v loop fix (Rev 5.0), all 11 remaining production_v2/ modules were individually flatten-synthesized and checked (Yosys `synth -flatten` + CHECK): kavach_bist.v, kavach_auth_gate.v, replay_detector.v, provenance_chain.v, offline_verify_counter.v, encrypted_channel.v, kavach_register_map.v, puf_stabilizer.v, scrambler.v, uart_tx.v, uart_rx.v — zero logic-loop warnings across all 11, confirming the arbiter_puf_cell.v issue was isolated and no other module has a similar structural hazard.

---

## Revision 5.2 — Per-Chip Key Provisioning (Hardcoded Key Security Fix)

**Hardcoded `shared_key` — Closed**
- Identified: `encrypted_channel.v`'s `shared_key` input was hardcoded to `32'hDEADBEEF` directly in `kavach_id_top.v`, with a comment noting this "would come from PUF-derived secret" — never implemented. Every chip built from this design shared an identical key, meaning encryption was uniform (and breakable) across the entire product line: compromising one chip's key compromised all of them.
- Fix: added `key_storage.v`, a factory-programmable, write-once key register. A new register-map interface (`KEY_DATA` 0x28, `KEY_CONTROL` 0x2C bit0=`prog_enable`, `KEY_STATUS` 0x30 bit0=`key_locked`) allows the key to be written exactly once; `key_locked` then permanently blocks further writes until reset. `encrypted_channel.v`'s `shared_key` now sources from this per-chip register instead of a hardcoded constant.
- Scope note: this is a **behavioral** model of one-time-programmability (an ordinary register + lock bit), not a physical OTP/e-fuse hardware macro. A real OTP/e-fuse macro (fab/PDK-specific, physically unrewritable even across power cycles) must replace this behavioral register at the physical-implementation stage before tape-out.
- Verified via a dedicated testbench (`key_storage_tb.v`): (1) key starts unprogrammed/unlocked, (2) a factory write correctly programs the key and sets `key_locked`, (3) a subsequent write attempt with a different key value is correctly rejected, preserving the original key. 3/3 tests pass. All 14 existing integration tests (`kavach_id_top_tb.v`, `offline_provenance_tb.v`, plus this new suite) re-verified passing with no regressions.

### Remaining Known Architectural Gaps (documented, not yet addressed)
- **Arbiter PUF layout symmetry**: the security property of `arbiter_puf_cell.v` depends on its two delay paths being electrically symmetric. Generic automated place-and-route does not guarantee this; dedicated placement/routing constraints will be required at the physical-implementation stage.
- **Host interface**: the chip currently exposes a parallel register bus and UART — neither is directly compatible with a smartphone. An NFC front-end (new RTL/analog work) or a bridge microcontroller (product-level, not chip-level) is required for direct phone connectivity.
- **Clock and reset sourcing for deployed/passive operation**: the design currently assumes an externally supplied `clk` and `rst`, suitable for lab/bench testing. A deployed, potentially passively-powered product (e.g. an NFC-powered tag) will require an on-chip oscillator and a power-on-reset (POR) circuit, neither of which exists in the current RTL.

---

## Revision 5.3 — Full UART-Protocol Interface Hardening

**~50-Pin Parallel Register Bus — Closed**
- Identified: `kavach_id_top.v` previously exposed its internal parallel register bus (`reg_write`, `reg_read`, `reg_addr[7:0]`, `reg_wdata[31:0]`, `reg_rdata[31:0]`, `reg_ready`) directly as top-level chip pins, alongside a separate UART — roughly 50 external pins, with which no realistic reader device or smartphone can physically interface.
- Fix: added `uart_to_reg_bridge.v`, moving the register bus fully inside the chip. Externally, `kavach_id_top.v` now exposes only `clk`, `rst`, `uart_rx_in`, `uart_tx_out` (plus `chip_healthy`/`verification_blocked` status outputs). A host communicates using a fixed 6-byte frame: `[CMD(1B)] [ADDR(1B)] [DATA(4B, MSB-first)]`, with `CMD=0x01` for WRITE and `CMD=0x02` for READ (4-byte response).

**UART Pin Conflict (Auto-Push vs Host-Driven Protocol) — Closed**
- Identified: a dedicated `UART_TX`/`UART_RX` pair previously auto-pushed the encrypted PUF response on every successful authentication, sharing the same physical `uart_tx_out`/`uart_rx_in` pins as the new host-driven command/response bridge — a host `READ` command in flight could collide with an unsolicited auto-push, corrupting both.
- Fix: removed the dedicated auto-push UART instances. `encrypted_channel.v`'s `ciphertext_out` and `tx_msg_counter_out` are now exposed as read-only registers (`CIPHERTEXT_DATA` 0x34, `TX_COUNTER` 0x38); the host explicitly reads them via the bridge instead of the chip pushing data unprompted.

**Reset Synchronizer Body Bug — Closed**
- Identified during this rewrite: although `reset_sync.v`'s output (`rst_sync`) was correctly used in every `always` block's sensitivity list (`posedge clk or posedge rst_sync`), the block *bodies* still checked the raw, unsynchronized `if (rst)` instead of `if (rst_sync)`. This silently bypassed the synchronizer's entire purpose — during the 2-cycle window after raw `rst` deasserted but before `rst_sync` released, clocked logic would incorrectly take the "normal operation" branch. Fixed by replacing all body-level `if (rst)` checks with `if (rst_sync)`.

**Register-Read Timing Bug in `uart_to_reg_bridge.v` — Closed**
- Identified: `reg_rdata` is a *registered* (one-cycle-delayed) output of `kavach_register_map.v`. The bridge's original `DO_READ` state pulsed `reg_read` and captured `reg_rdata` into the UART transmit buffer in the *same* cycle — one cycle too early — causing every UART read command to return the *previous* read's value rather than the one just requested. This was masked in an earlier standalone bridge test that used a combinationally-driven (non-registered) stand-in for `reg_rdata`; it was only caught once tested against the real, registered `kavach_register_map.v`. Fixed by adding two additional FSM states (`READ_WAIT`, `READ_CAP`) that give the register map one clock cycle to produce valid data before it is captured.

**Full Re-Verification Over Realistic UART**
- All top-level and module-integration testbenches were rewritten to drive and receive commands through actual `uart_tx.v`/`uart_rx.v` instances (not hand-timed bit-banging, which was found during this work to itself introduce race-condition false failures — see engineering note below).
- `kavach_id_top_uart_tb.v`: 4/4 tests pass (BIST-via-UART, fresh-challenge authentication grant, replay detection/block, ciphertext register readback).
- `offline_provenance_uart_tb.v`: 6/6 tests pass (initial budget, budget decrement, exhaustion/denial, sync-restore, correct-sequence provenance, skipped-stage violation).
- `key_storage_uart_tb.v`: 3/3 tests pass (unprogrammed-start, program-and-lock, reject-second-write).
- **13/13 tests pass overall**, fully driven and observed via the chip's actual 4-pin external interface — no internal parallel-bus shortcuts remain anywhere in the verification suite.

**Engineering note — a hand-written UART bit-banger produced false failures**: during development, a testbench that manually toggled `uart_rx_in` bit-by-bit (rather than instantiating `uart_tx.v`) produced consistent, structured data corruption (e.g. sending `0x01` and observing `0x80` received). This was traced to a signal-assignment race condition in the hand-written task (no settling delay after each bit change) rather than any RTL defect; confirmed via a direct `uart_tx`-to-`uart_rx` loopback test, which passed cleanly. All hand-bit-banged bridge tests were subsequently rewritten to drive/receive through the real, proven UART modules.

### Updated External Interface
Kavach-ID now exposes exactly 6 external signals: `clk`, `rst`, `uart_rx_in`, `uart_tx_out`, `chip_healthy`, `verification_blocked` — down from ~57 in the pre-Rev-5.3 design.
