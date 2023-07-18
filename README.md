# Encounter logs

### This module is in alpha version please check progress of https://github.com/MellianStudios/mod-encounter-logs/issues/2 before using it

---

## Important info
- This module logs raw data in a format that isn't designed for direct reading.
- This module doesn't include a parser or a viewer/reader, as each project has its own specific requirements and needs. It would be too much effort to maintain a feature that most users, including myself, would rarely use. As a result, this module is not recommended for basic users and requires development skills for full utilization.
- This module has the potential to generate vast amounts of data in the database, particularly for servers with a higher population. This can put significant strain on your database, storage, CPU, and network.

---

## Tracking

Tracking can be turned ON/OFF for dungeons/raids/specific creatures in open world

For all options see config

### Player

- combat
- gear (at combat start)
- talents (at combat start)
- auras (at combat start)
- stats (at combat start)
- movement
- death
- power
- spells

player tracking is always ON in instances

### Creature (all units except player)

- spells
- movement
- death

---

## Requirements
1. This module relies on multiple hooks which are not present in AC
2. This module depends on nlhomann/json library which is not present in AC

> you can find library integration and hooks here https://github.com/MellianStudios/azerothcore-wotlk/tree/encounter-logs
---

## Credits / contributors
- [Anchy](https://github.com/AnchyDev) (general support)
