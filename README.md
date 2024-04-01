# Encounter logs

### This module is in beta please check progress of https://github.com/MellianStudios/mod-encounter-logs/issues/2 before using it

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
- power (including health)
- spells

player tracking is always ON in instances

### Creature (all units except player)

- spells
- movement
- health
- death

### Please note that this module currently does not have any respect for phases so if there is fights happening in different phases of same map there is no way to distinguish them

---

## Requirements
1. This module relies on multiple hooks which are not present in AC
2. This module works with custom member variables added to core
3. This module depends on nlhomann/json library which is not present in AC

> you can find all of it here https://github.com/MellianStudios/azerothcore-wotlk/tree/encounter-logs
---

## ScyllaDB
I'm not going to include install and configuration steps for server however I will include connector installation
- sudo apt install libuv1-dev
- git clone https://github.com/datastax/cpp-driver.git
- cd cpp-driver
- mkdir build && cd build
- cmake ..
- make install

Also with scylla you have to change BatchSize in config to 1 and with that i would suggest you lower SaveFrequency

--

## Credits / contributors
- [Anchy](https://github.com/AnchyDev) (general support)
