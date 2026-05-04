# Rover

A small WiFi-controlled robot. Long-term goal: magnetic-wheeled crawler that can drive on metal walls and (eventually) ceilings. Built in three phases, each adding exactly one new unknown.

## Mental model

A wheeled robot is four parts in a chain:

1. **Battery** — stores energy
2. **Brain** — a tiny computer (microcontroller)
3. **Driver** — translator chip that takes brain signals and switches motor power
4. **Motors** — turn electricity into motion

Two things flow through the chain. _Power_ flows battery → driver → motors (big current). _Signals_ flow brain → driver (tiny voltages saying "spin motor A forward at 60%"). The driver exists because the brain's pins can only supply ~20mA; motors want amps.

Control model: the robot is a tiny web server, the phone is a browser. The ESP32 hosts its own WiFi network (AP mode), serves an HTML page with directional buttons, and listens for HTTP requests like `/forward` or `/stop`. Latency on local WiFi is ~20–50ms.

## Phased plan

**Phase 1 — Floor rover (current).** No magnets, no climbing. Drive a wheeled robot around the floor from a phone. Teaches wiring, soldering, ESP32 programming, and debugging without gravity fighting back.

**Phase 2 — Wall climber.** Swap wheels for magnetic ones. Same robot, now climbs metal walls. Only new variable is magnetic adhesion.

**Phase 3 — Ceiling capability.** Hardest single thing the robot will do is the wall-to-ceiling transition. Decisions here depend on real measurements from phase 2.

## Phase 1 — Floor rover BOM

Approximate total: $45.

| #   | Part                             | Notes                                                                                                                                                                        | ~$  |
| --- | -------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --- |
| 1   | 2WD smart robot car chassis kit  | Acrylic deck, 2× TT yellow gearbox motors, 2 wheels, caster, hardware. Search "2WD smart robot car chassis kit". Get the version with motor wires pre-soldered if available. | 12  |
| 2   | ESP32 dev board                  | DOIT ESP32 DevKit V1 or any ESP32-WROOM-32 board. USB-C preferred.                                                                                                           | 10  |
| 3   | L298N motor driver module        | Bigger than alternatives but forgiving for beginners and matches every reference tutorial.                                                                                   | 5   |
| 4   | 4× AA battery holder with switch | Often included in chassis kit.                                                                                                                                               | 3   |
| 5   | AA batteries (×4)                | Alkaline or NiMH. Skipping LiPo for v1 — no charging circuit needed, safer to learn on.                                                                                      | 5   |
| 6   | Jumper wires                     | Mixed pack: male-to-male and male-to-female, ~40 of each.                                                                                                                    | 5   |
| 7   | Mini breadboard (half-size)      | Solderless prototyping for v1.                                                                                                                                               | 3   |
| 8   | USB cable for ESP32              | Match the board's connector (usually micro-USB or USB-C).                                                                                                                    | 3   |

## Reference build

Random Nerd Tutorials — ESP32 WiFi Car Robot: <https://randomnerdtutorials.com/esp32-wi-fi-car-robot-arduino/>

Free, complete, working tutorial with wiring diagram and code. Anchor the v1 build on this. Diverge later.

## Top-down layout

See `docs/rover-v1-plan.svg`.

Note: the diagram shows N20 micro-motors (~100×80mm chassis). The actual v1 kit uses larger TT yellow-gearbox motors, so the real chassis is closer to 200×150mm. Bigger is fine for v1 — more room to mount things, easier to debug. The smaller form factor returns in phase 2.

## Status

Phase 1 — planning. Parts not yet ordered.
