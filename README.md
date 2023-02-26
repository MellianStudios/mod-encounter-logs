# DO NOT USE THIS IF YOU ARE AVERAGE USER
## This module is in active development and is not intended for real usage yet

# Encounter logs

### Currently works only in instances (dungeons/raids) and (NYI) for selected creatures in open world

---

## Important info
This module is logging raw data in structure which is not intended to be read from.
This module does not provide parser nor viewer/reader this is because every project has its requirements and necessities
and it would be too much work for me to maintain something what most users including me would never use.
This means that this module is NOT recommended for basic users and requires dev skills to fully utilize.

---

### Tracking
- when player enters combat this event itself is tracked together with player gear (including gems and enchants), talents and buffs/debuffs
- players casting spells are tracked always
- creature casting spells are tracked when in combat with player
- player movement is tracked always

---

### Expectation and assumptions
- this module assumes you did not change default logic of gems and enchants

---

### Requirements
1. This module relies on hook which are not present in AC
   - OnUnitSpellCast
   - you can get it here https://github.com/MellianStudios/azerothcore-wotlk/tree/hooks note that there are other hooks not required for this module
2. This module depends on nlhomann/json library which is not present in AC

---

### Credits / contributors
- [Anchy](https://github.com/AnchyDev) (general support)
