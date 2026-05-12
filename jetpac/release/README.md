# Jetpac (Taito SJ) — DIP Switch Quick Reference

**Operator's Card**

---

## DIPSWITCH Bank 'A'

Eight-position rocker, located on the main PCB.

| Position | Binary | State |
|---|---|---|
| **OFF** (switch up) | 1 | Factory default |
| **ON** (switch down) | 0 | Selected |

| SW1 | SW2 | SW3 | SW4 | SW5 | SW6 | SW7 | SW8 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Lives | Lives | Bonus | Bonus | Up Thrust | (reserved) | Coin Lockout | Sound |

---

### SW1 + SW2 — Number of Ships (Lives)

| SW1 | SW2 | Setting |
|:---:|:---:|---|
| OFF | OFF | 2 ships |
| ON  | OFF | 3 ships |
| OFF | ON  | 4 ships |
| ON  | ON  | **FREE PLAY** — no coin required, no life cap |

### SW3 + SW4 — Bonus Life Award

| SW3 | SW4 | Setting |
|:---:|:---:|---|
| OFF | OFF | Bonus on every rocket built |
| ON  | OFF | Bonus every 10,000 points |
| OFF | ON  | Bonus every 20,000 points |
| ON  | ON  | Bonus every 50,000 points |

### SW5 — Up Thrust

| Position | Setting |
|:---:|---|
| OFF | Thrust assigned to button only |
| ON  | Thrust also responds to UP on joystick |

### SW6 — Reserved

Leave OFF. Not currently wired to any game function.

### SW7 — Coin Lockout *(workshop / test use)*

| Position | Setting |
|:---:|---|
| OFF | Coin slot **released** — accepts coins (default) |
| ON  | Coin slot **engaged** — rejects coins; CPU sees no coins |

> **Note:** must be OFF for coins to register in normal play.

### SW8 — Sound Output *(workshop / test use)*

| Position | Setting |
|:---:|---|
| OFF | Sound **on** — amplifier enabled (default) |
| ON  | Sound **muted** — amplifier disabled at COIN_SET bit 1 |

> **Note:** use for silent location-test or repair work.

---

## Recommended Factory Setting

> **All switches OFF.**
> 3 ships, bonus every 10,000 points, thrust on button only, coins accepted, sound on.

---

## Service Menu

Press the **SERVICE** button (test switch) during attract to bring up an on-screen DIP readout *and* the live state of IN0..IN5 input ports. Useful for verifying coin switches, joystick wiring, and button mappings without needing a logic probe.

Press SERVICE again to return to the attract title.

---

*Jetpac (Ultimate Play The Game, 1983) — Taito System SJ port by Anton Gale, 2026.*
