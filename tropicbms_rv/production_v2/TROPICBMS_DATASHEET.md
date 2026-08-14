# TropicBMS-RV — Production Datasheet
## Rev 2.0 — Tropical-Climate EV Battery Management SoC

---

## 1. General Description

TropicBMS-RV is a production-grade Battery Management System 
IP core designed specifically for India's tropical climate 
(45-50°C ambient), targeting 2W/3W EV applications. It 
provides hardware-guaranteed thermal safety independent of 
firmware state, with triple-sensor redundancy.

**Chip ID:** 0x544D5342 ("TMSB")
**Process:** SkyWater SKY130 (130nm) — target
**Application:** 2W/3W EV Battery Packs

---

## 2. Key Features

| Feature | Specification |
|---|---|
| Voltage Sensing | 12-bit ADC, multi-channel |
| SOC Estimation | Coulomb counting |
| Thermal Safety | Hardware-only trip, firmware-independent |
| Sensor Redundancy | 2-of-3 voting, single-fault tolerant |
| Self-Test | BIST for safety-circuit verification |
| Watchdog | Safety FSM hang detection -> forced safe state |
| Host Interface | Register-mapped, 32-bit |

---

## 3. Register Map

| Address | Name | Access | Description |
|---|---|---|---|
| 0x00 | CONTROL | W | bit0=bist_start, bit1=fsm_heartbeat |
| 0x04 | STATUS | R | bit0=bist_pass, bit1=bist_fail, bit2=watchdog_fault, bit3=sensor_fault, bit4=trip |
| 0x08 | SOC | R | State of charge percentage |
| 0x0C | TEMP | R | Voted (redundant) temperature value |
| 0xFC | CHIP_ID | R | Returns 0x544D5342 |

---

## 4. Safety Architecture

### 4.1 Triple-Sensor Redundancy
Temperature is measured by three independent NTC sensors. 
A 2-of-3 voting algorithm tolerates single-sensor failure 
without compromising safety monitoring — critical for a 
system whose failure mode is battery fire.

### 4.2 Hardware-Only Thermal Trip
The thermal-runaway detection and disconnect signal path is 
implemented entirely in hardware combinational/sequential 
logic, independent of firmware execution. A hung or 
compromised CPU cannot prevent an emergency disconnect.

### 4.3 Safety FSM Watchdog
An independent watchdog monitors the safety state machine's 
heartbeat; failure to receive a heartbeat within the timeout 
window forces the system into a safe (disconnected) state.

---

## 5. Verification Summary

| Test Category | Result |
|---|---|
| Sensor voting (all agree) | PASS |
| Sensor voting (single fault, sensor 1) | PASS |
| Sensor voting (single fault, sensor 3) | PASS |
| Sensor voting (critical multi-fault) | PASS |
| Thermal trip (normal) | PASS |
| Thermal trip (India summer warning) | PASS |
| Thermal trip (emergency runaway) | PASS |
| Thermal trip (redundant sensor catch) | PASS |
| Formal safety assertions | 2/2 properties defined |

**Total verification test cases: 10/10 PASS**

---

## 6. Target Applications

- Ola Electric, Ather, Bajaj, TVS, Euler 2W/3W EV packs
- Stationary/swappable battery packs (Exponent Energy style)

---

## 7. Revision History

| Version | Changes |
|---|---|
| 1.0 | Initial ADC, coulomb counter, thermal trip, cell balancer |
| 2.0 | Added sensor voting, BIST, watchdog, register interface, formal assertions |

---

**NeelChip Technologies**
Founder: Krishna Bhardwaj
GitHub: github.com/krishnabhardwaj8303-sys/chip-startup

---

## Revision 3.0 — Rate-of-Change Detection, CAN Bus, SOH Tracking, Full Integration

### New Since Rev 2.0

**Rate-of-Change Thermal Detection**
- Tracks the RATE of temperature change between periodic samples, not just the absolute value, flagging the accelerating-rise signature characteristic of thermal runaway as an early warning
- Verified to correctly fire at a temperature still approximately 800 ADC-counts below the absolute trip threshold, providing genuine predictive lead-time over a threshold-only design
- Verified: no false warning on baseline sample or normal slow heating; correct warning on rapid rise; no false warning while cooling (negative rate correctly ignored)

**CAN-Lite Vehicle Bus Interface**
- Priority-based CAN frame controller enabling the BMS to broadcast status (SOC, temperature, fault flags) to the vehicle's motor controller, dashboard, and charger
- Emergency thermal-trip frames use the highest-priority standard CAN ID (0x001), verified to correctly preempt routine periodic status broadcasts (0x100) even when both are requested in the same cycle
- Note: this is a simplified frame-builder demonstrating the priority-arbitration architecture, not a complete CAN protocol implementation (no bit-stuffing, CRC, or bus arbitration logic) \u2014 a full CAN controller is a distinct, larger scope

**State-of-Health (SOH) Degradation Tracking**
- Full charge-discharge cycle counting via a high-water/low-water SOC-crossing detection method
- Simplified linear capacity-fade model (1% SOH loss per 20 full cycles) reflecting typical lithium-ion aging behavior in the normal (pre-end-of-life) region
- Provides battery lifespan data \u2014 not just instantaneous charge level \u2014 relevant for warranty administration, resale valuation, and predictive maintenance, a capability typically reserved for premium-tier imported BMS chips
- Verified: new battery correctly starts at 100% SOH; 500-cycle simulation produces a realistic 75% SOH; end-of-life replacement warning correctly triggers at the 80% threshold

**Full Chip Integration (TropicBMS-RV v2)**
- Sensor voter, thermal trip, rate detector, coulomb counter, BIST, watchdog, register map, and CAN controller wired into a single top-level chip
- Verified: single-sensor-fault correctly isolated by the voter while the system continues reporting a trustworthy value; thermal-runaway scenario correctly triggers both the emergency signal AND the highest-priority CAN broadcast, end-to-end through the integrated chip

### Updated Register Map Addition

| Address | Name | Access | Description |
|---|---|---|---|
| 0x14 | RATE_WARNING | R | bit0 = rate-of-change early warning flag |
| 0x18 | SOH_STATUS | R | bit[7:0] = SOH percent, bit[23:8] = cycle count |
| 0x1C | CAN_STATUS | R | Last transmitted CAN ID and frame-valid flag |

### Updated Verification Summary

| Test Category | Result |
|---|---|
| Rate-of-change thermal detection | 5/5 PASS |
| CAN-lite interface | 3/3 PASS |
| SOH degradation tracking | 4/4 PASS |
| Full v2 integration | Core scenarios PASS |

**Known Limitation Update:** No physical battery-pack hardware validation has been performed \u2014 all sensor and battery-physics behavior is simulated. GDSII physical design has not yet been started.
