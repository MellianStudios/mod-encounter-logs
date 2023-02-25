#ifndef AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H

#include <nlohmann/json.hpp>
#include "Configuration/Config.h"
#include "Chat.h"
#include "Player.h"
#include "Spell.h"
#include "ScriptMgr.h"

class EncounterLogPlayerScript : public PlayerScript
{
public:
    EncounterLogPlayerScript() : PlayerScript("EncounterLogPlayerScript")
    {}

    void OnPlayerEnterCombat(Player *player, Unit */*enemy*/) override
    {
        auto current_time = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();

        nlohmann::json gear = {};
        std::string talents{};

        for (int i = 0; i <= 18; i++) {
            Item *item = player->GetItemByPos(255, i);

            std::uint_fast32_t item_id{0};

            if (item) {
                item_id = item->GetEntry();
            }

            gear["slot_" + std::to_string(i)] = {
                {"id", item_id}
            };
        }

        EncounterLogManager::getLog(player->GetInstanceId())->getBuffer().pushCombat(
            player->GetMapId(),
            player->GetInstanceId(),
            player->GetGUID().GetRawValue(),
            ENCOUNTER_LOG_START,
            gear.dump(),
            talents,
            timestamp
        );
    }

    void OnPlayerLeaveCombat(Player *player) override
    {
        auto current_time = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();

        // this is being run before AllMapScript::OnPlayerEnterAll
        if (!EncounterLogManager::hasLog(player->GetInstanceId())) {
            return;
        }

        EncounterLogManager::getLog(player->GetInstanceId())->getBuffer().pushCombat(
            player->GetMapId(),
            player->GetInstanceId(),
            player->GetGUID().GetRawValue(),
            ENCOUNTER_LOG_END,
            "",
            "",
            timestamp
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H
