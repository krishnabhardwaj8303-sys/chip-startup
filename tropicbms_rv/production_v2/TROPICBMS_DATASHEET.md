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
