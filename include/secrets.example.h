#pragma once

// Copy this file to `secrets.h` and fill in real values.
// `secrets.h` is gitignored. Do not commit credentials.

// AP-mode SSID + password the rover broadcasts.
// Password must be >= 8 chars or WiFi.softAP() will fail silently.
#define ROVER_AP_SSID "rover"
#define ROVER_AP_PASSWORD "changeme123"
