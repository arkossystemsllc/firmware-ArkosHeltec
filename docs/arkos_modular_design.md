# Arkos Dual-Mode Networking

This repository adds an experimental architecture for switching between the default Meshtastic mesh and an Arkos specific mesh implementation.

## Network Modes

- **Meshtastic** – uses the stock routing, message formats and radio settings.
- **Arkos** – uses `ArkosRouter` and additional modules for Arkos message types.

Runtime mode selection is controlled via `currentNetworkMode` (see `NetworkMode.h`).  Modules and routing are instantiated based on this variable so that a device can switch modes without reflashing.

### ArkosMesh Options

`ArkosConfig` exposes runtime flags for topology (peer, federated or star), power‑aware operation and low‑probability‑of‑detection mode. These settings can be changed dynamically by proprietary modules or future admin commands.

## Extensible Modules

- `ArkosRouter` derives from `ReliableRouter` and implements low-latency route selection, retries, and silent forwarding of authorized traffic.
- `ArkosMessageModule` registers custom port numbers (`0x80`–`0x83`) and understands sensor reports, control commands, and binary payloads.
- `setupArkosModules()` is invoked when Arkos mode is enabled to construct these modules.

Proprietary extensions can live in `src/arkos` without modifying the existing GPLv3 code.  Linking against the GPL components makes the combined firmware subject to GPLv3, but independent modules that communicate over clean interfaces may remain proprietary.
