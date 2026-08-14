
---

## Revision 3.0 — Full Integration + Dedicated TRNG

### New Since Rev 2.0

**Dedicated TRNG (True Random Number Generator)**
- Architecturally distinct from the PUF (identity) block — the PUF provides a reproducible device-unique key, while the TRNG provides genuinely non-deterministic randomness for session keys, masking, and nonces
- Ring-oscillator-modeled entropy source with Von Neumann de-biasing to remove statistical bias
- Built-in monobit statistical self-test (NIST SP 800-22 style), verified passing
- Status: RTL verified — consecutive outputs confirmed unique, self-test confirmed passing

**Full Chip Integration (NeelChip v3)**
- All 11 previously standalone sub-modules (AES core, PUF, TRNG, masked S-Box, BIST, watchdog, glitch detector, interrupt controller, UART, register map, security-mode controller) wired into a single top-level design
- 6/6 integration scenarios verified: boot-state health check, register-triggered BIST, LITE-mode transaction, high-value auto-escalation to FULL mode, tamper-triggered sticky lockdown, glitch-triggered UART blocking
- A sticky-lockdown bug was identified and fixed during integration: an interrupt-controller pulse was originally able to un-latch the tamper-response lockdown after a single clock cycle; the fix adds a dedicated sticky-lockdown register that only clears on chip reset, correcting a real security defect that only became visible once modules were wired together (not visible when each module was tested standalone)

### Updated Register Map Addition

| Address | Name | Access | Description |
|---|---|---|---|
| 0x40 | TRNG_OUT | R | Latest 32-bit TRNG output (updates on each valid pulse) |
| 0x44 | TRNG_SELFTEST | R | bit0 = statistical self-test pass/fail |

### Updated Verification Summary

| Test Category | Result |
|---|---|
| TRNG uniqueness + statistical self-test | 2/2 PASS |
| NeelChip v3 full integration (11 modules, 6 scenarios) | 6/6 PASS |

**Important Note:** The GDSII physical layout referenced in Revision 2.0 (95,980 gates) corresponds to the pre-integration design and does NOT yet include the TRNG or the full v3 integration wiring. A fresh OpenLane run against `neelchip_v3_top.v` is required before the physical layout reflects the current RTL — this is tracked as an open item, not yet completed.
