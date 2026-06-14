# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project status

Hardware/embedded project. **Phase 1 — planning, parts on order, no firmware written yet.** Repo is scaffolded as a PlatformIO project so structure is tracked from day one.

## Toolchain & build

- **PlatformIO** (CLI). Project config: `platformio.ini`. Board: `esp32doit-devkit-v1` (standard 30-pin ESP32-WROOM-32, micro-USB).
- **Framework:** Arduino (matches the Random Nerd reference tutorial; easier library ecosystem for v1).
- **Source layout:** `src/main.cpp`, headers in `include/`. Don't fight PlatformIO's conventions.

Common commands (run from repo root):

```
pio run                    # build
pio run -t upload          # flash to connected ESP32
pio device monitor         # open serial at 115200
pio run -t clean           # clear build artifacts
pio run -t upload -t monitor  # flash and immediately tail serial
```

PlatformIO build output lives in `.pio/` (gitignored).

## Architecture (planned)

Read `readme.md` for the mental model and phased plan. Invariants future code should respect:

- **Four-part chain:** battery → driver (L298N) → motors; brain (ESP32) sends signals to driver only. Power and signal paths are separate; the brain's GPIO never sources motor current.
- **Control plane:** ESP32 in WiFi **AP mode** — rover hosts its own network, no router setup needed. Serves a single HTML page with directional buttons. Commands are plain HTTP GETs (`/forward`, `/back`, `/left`, `/right`, `/stop`). Latency budget: ~20–50ms on local WiFi. Don't reach for WebSockets, MQTT, or BLE in v1 — the simplicity is the point.
- **Phase isolation:** v1 is the floor rover only. Don't pre-build abstractions for magnetic wheels (phase 2) or wall-to-ceiling transitions (phase 3). Each phase adds exactly one new unknown; speculative generality defeats that.

Reference build to anchor v1 against: <https://randomnerdtutorials.com/esp32-wi-fi-car-robot-arduino/>

## Hardware notes that affect code

- **Board:** ESP32 DOIT DevKit V1 (ESP32-WROOM-32, 30-pin, micro-USB). Pin numbering matches the Random Nerd tutorial.
- **Motor driver:** L298N. PWM speed control via ENA/ENB; direction via IN1–IN4. The L298N drops ~2V, so 4×AA (≈6V) leaves ~4V at the motors — fine for TT gearbox motors, slow but works.
- **Motors:** TT yellow-gearbox (from YIKESHU 2WD chassis kit). Motor wires are **not** pre-soldered — leads will be soldered to the motor terminals using 22 AWG stranded hookup wire when parts arrive.
- Keep pin assignments in one place (a header in `include/`, or a `constexpr` block at the top of `main.cpp`) so wiring changes are a single-file edit.
- The chassis in `docs/rover-v1-plan.svg` shows N20 micro-motors (~100×80mm). The actual v1 kit uses larger TT motors (~200×150mm chassis). The diagram is layout-only; don't infer dimensions or pinouts from it.

## Secrets

WiFi AP SSID/password and any future credentials must not be committed.

- `include/secrets.example.h` is the tracked template.
- `include/secrets.h` is gitignored — copy from the example and fill in locally.
- `.gitignore` also excludes `*.local.h` and `.env*`.

## Repo conventions

- `readme.md` is the human-facing project doc (BOM, plan, mental model). Update it when phase status or BOM changes.
- `docs/` holds diagrams and reference material.
- One `platformio.ini` env per board; v1 is `esp32doit-devkit-v1` only.

## Next steps

1. Order parts (YIKESHU 2WD chassis, ESP32 DOIT V1, L298N, 22 AWG hookup wire, AAs).
2. When ESP32 arrives: `pio run -t upload -t monitor` with the existing skeleton — confirm toolchain works before any soldering.
3. Solder motor leads; wire per Random Nerd diagram; pin assignments go in a single header.
4. Serial-only sanity (blink + motor PWM ramp on bench) before adding WiFi.
5. Add AP-mode HTTP server and HTML control page; copy `secrets.example.h` → `secrets.h`.

<!-- SHARED-CONVENTIONS:BEGIN v=d5e16e653242 — auto-managed, do not edit here; source: prompt-lab/workflow/claude-md-shared.md (edit + re-sync) -->
## Shared conventions

<!-- These are Nico's cross-repo output rules. They're materialized into each repo's
CLAUDE.md so every agent (local, cloud, third-party) sees them as plain text. Source
of truth: prompt-lab/workflow/claude-md-shared.md — edit there and re-sync, never here. -->

- **Clickable URLs.** When pointing at any web destination (dashboard, repo, PR, deploy, settings, docs, localhost), print the full bare URL — `https://example.com` or `http://localhost:8080` — on its own, never just the page's name and never a markdown `[label](url)` link. Nico's terminal auto-linkifies raw `https://` text, so a bare URL is one-click and stays copyable.

- **Number your questions.** Any time you ask Nico more than one question, present them as a numbered list (1., 2., 3.) so he can answer by number with no ambiguity. A single standalone question needs no number.

- **Self-contained smoke-test instructions.** When you ask Nico to manually test or verify an app or website, assume zero carried-over context — he should never scroll back or recall a URL/path/credential from earlier. Always include: the exact URL (full `https://…` or `http://localhost:…`, restated even if mentioned above), the precise steps in order, and what a pass vs. fail looks like. Repetition here is a feature, not clutter.

- **No marker before a copy-paste command block.** Nico's terminal renders markdown bullets (`-`, `*`, `•`) as `●`, which breaks paste into zsh. The line directly above a fenced command block must be a plain-text label ending in a colon — never a bullet, dash, asterisk, or number. For loud copy targets, lead the label with `📋` + bold `COPY THE BELOW`, then a colon, then the block.
<!-- SHARED-CONVENTIONS:END -->
