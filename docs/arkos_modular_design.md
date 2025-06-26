# Arkos Dual-Mode Networking

This repository adds an experimental architecture for switching between the default Meshtastic mesh and an Arkos specific mesh implementation.

## Network Modes

- **Meshtastic** – uses the stock routing, message formats and radio settings.
- **Arkos** – uses `ArkosRouter` and additional modules for Arkos message types.

Runtime mode selection is controlled via `currentNetworkMode` (see `NetworkMode.h`).  Modules and routing are instantiated based on this variable so that a device can switch modes without reflashing.

## Extensible Modules

- `ArkosRouter` derives from `ReliableRouter` and is the place for Arkos specific routing logic.
- `ArkosMessageModule` registers custom port numbers (`0x80`–`0x81`) for encrypted status reports and sensor alerts.
- `setupArkosModules()` is invoked when Arkos mode is enabled to construct these modules.

Proprietary extensions can live in `src/arkos` without modifying the existing GPLv3 code.  Linking against the GPL components makes the combined firmware subject to GPLv3, but independent modules that communicate over clean interfaces may remain proprietary.
