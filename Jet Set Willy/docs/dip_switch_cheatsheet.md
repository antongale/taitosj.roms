# Jet Set Willy (Taito SJ) — DIP Switch Quick Reference

**Operator's Card**

---

## DIPSWITCH Bank 'A'

Eight-position rocker, located on the main PCB.

| Position | State |
|---|---|
| **OFF** (switch up) | Default for SW3, SW7, SW8 |
| **ON** (switch down) | Default for SW4, SW5, SW6 |

| SW1 | SW2 | SW3 | SW4 | SW5 | SW6 | SW7 | SW8 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| (reserved) | (reserved) | Collision | Infinite Lives | In-Game Warp | Willy Speed | Coin Lockout | Sound |

---

### SW1 + SW2 — Reserved

Leave OFF. Not wired to any game function.

### SW3 — Collision

| Position | Setting |
|:---:|---|
| OFF | Collision **On** — guardians, arrows and nasty tiles kill Willy (default) |
| ON  | Collision **Off** — Willy is immortal; useful for level tours and location test |

### SW4 — Infinite Lives

| Position | Setting |
|:---:|---|
| OFF | Infinite Lives **On** — a death plays the colour flash but doesn't decrement the lives counter |
| ON  | Infinite Lives **Off** — normal play, lives decrement (default) |

### SW5 — In-Game Warp

| Position | Setting |
|:---:|---|
| OFF | Warp **Enabled** — pressing SERVICE during play opens the room-warp menu |
| ON  | Warp **Disabled** — SERVICE only opens the attract diagnostics overlay (default) |

> The warp menu shows the room number + name. Use joystick LEFT/RIGHT to change rooms by 10, UP/DOWN by 1, BUTTON 1 to warp, SERVICE to exit without warping. Room 47 is skipped (unused in the original game).

### SW6 — Willy Speed

| Position | Setting |
|:---:|---|
| OFF | **Normal** — Willy moves at the original ZX Spectrum cadence (default) |
| ON  | **Turbo** — Willy moves at double speed |

### SW7 — Coin Lockout *(workshop / test use)*

| Position | Setting |
|:---:|---|
| OFF | Coin slot **released** — accepts coins (default) |
| ON  | Coin slot **engaged** — rejects coins |

> Must be OFF for coins to register in normal play.

### SW8 — Sound Output *(workshop / test use)*

| Position | Setting |
|:---:|---|
| OFF | Sound **on** — amplifier enabled (default) |
| ON  | Sound **muted** — amplifier disabled |

> Use for silent location-test or repair work.

---

## Recommended Factory Setting

| SW1 | SW2 | SW3 | SW4 | SW5 | SW6 | SW7 | SW8 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| OFF | OFF | **OFF** | **ON** | **ON** | **ON** | **OFF** | **OFF** |

> Collision on, lives decrement, warp disabled, normal Willy speed, coins accepted, sound on.

---

## Service Menu

Press the **SERVICE** button (test switch) during the attract screen to bring
up the on-screen DIP readout, plus the live state of the input ports. Useful
for verifying coin switches, joystick wiring, and button mappings without a
logic probe. Press SERVICE again to return to the attract title.

Pressing SERVICE **during gameplay** opens the in-game warp menu *if* SW5
(In-Game Warp) is OFF. Otherwise it's ignored.

---

*Jet Set Willy (Software Projects / Matthew Smith, 1984) — Taito System SJ port by Anton Gale, 2026.*
