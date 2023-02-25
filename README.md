# DO NOT USE THIS IF YOU ARE AVERAGE USER
## This module is in active development and is not intended for real usage yet

# Encounter logs

### Currently works only in instances (dungeons/raids) and (NYI) for selected creatures in open world

### Tracking
- all players
- all creatures
- damage
- healing
- resources (hp/mana/rage/energy/runic power)
- movement
- auras (buffs/debuffs)
- talents
- gear (including everything)

### Requirements
1. This module relies on hooks which are not present in AC
   - OnUnitSpellCast
   - OnAddHostileReferenceToThreatContainer
   - OnRemoveHostileReferenceFromThreatContainer
   - you can get them here https://github.com/MellianStudios/azerothcore-wotlk/tree/hooks note that there are other hooks not required for this module
2. This module depends on nlhomann/json library which is not present in AC

### Credits / contributors
- [Anchy](https://github.com/AnchyDev) (general support)
