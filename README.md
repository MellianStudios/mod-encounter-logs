# Encounter logs

### Currently works only in instances (dungeons/raids) and (NYI) for selected creatures in open world
### Check progress of https://github.com/MellianStudios/mod-encounter-logs/issues/2 before using this module

---

## Important info
- This module logs raw data in a format that isn't designed for direct reading.
- This module doesn't include a parser or a viewer/reader, as each project has its own specific requirements and needs. It would be too much effort to maintain a feature that most users, including myself, would rarely use. As a result, this module is not recommended for basic users and requires development skills for full utilization.
- This module has the potential to generate vast amounts of data in the database, particularly for servers with a higher population. This can put significant strain on your database, storage, CPU, and network.

---

### Tracking
- when player enters combat this event itself is tracked together with player gear (including gems and enchants), talents and buffs/debuffs
- players casting spells are tracked always
- player movement is tracked always
- creature casting spells are tracked when in combat with player
- creature movement is tracked when in combat with player

Pets, summons and vehicles are tracked in same fashion in relation to whether they are owned by player or creature

---

### Expectation and assumptions
- this module assumes you did not change default logic of item enchantments

---

### Requirements
1. This module relies on multiple hooks which are not present in AC
2. This module depends on nlhomann/json library which is not present in AC

> you can find library integration and hooks here https://github.com/MellianStudios/azerothcore-wotlk/tree/encounter-logs
---

### Credits / contributors
- [Anchy](https://github.com/AnchyDev) (general support)
