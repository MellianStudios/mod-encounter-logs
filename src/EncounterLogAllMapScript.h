#ifndef AZEROTHCORE_ENCOUNTERLOGALLMAPSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGALLMAPSCRIPT_H

#include "Configuration/Config.h"
#include "Chat.h"
#include "Player.h"
#include "ScriptMgr.h"

class EncounterLogAllMapScript : AllMapScript
{
public:
    EncounterLogAllMapScript() : AllMapScript("EncounterLogAllMapScript")
    {}

    void OnPlayerEnterAll(Map *map, Player *player) override
    {
        if (map->IsDungeon() && EncounterLogManager::dungeonsDisabled()) {
            return;
        }

        if (map->IsRaid() && EncounterLogManager::raidsDisabled()) {
            return;
        }

        if (!map->IsDungeon() && !map->IsRaid()) {
            return;
        }

        auto current_time = std::chrono::system_clock::now();

        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(current_time.time_since_epoch()).count();

        EncounterLogManager::newLog(player->GetMapId(), player->GetInstanceId(), timestamp);
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGALLMAPSCRIPT_H
