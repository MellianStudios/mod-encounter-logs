#ifndef AZEROTHCORE_ENCOUNTERLOGMOVEMENTHANDLERSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGMOVEMENTHANDLERSCRIPT_H

#include "Configuration/Config.h"
#include "ScriptMgr.h"

class EncounterLogMovementHandlerScript : MovementHandlerScript
{
public:
    EncounterLogMovementHandlerScript() : MovementHandlerScript("EncounterLogMovementHandlerScript")
    {}

    void OnPlayerMove(Player *player, MovementInfo /*movementInfo*/, uint32 /*opcode*/) override
    {
        if (player->GetMap()->IsDungeon() && EncounterLogManager::dungeonsDisabled()) {
            return;
        }

        if (player->GetMap()->IsRaid() && EncounterLogManager::raidsDisabled()) {
            return;
        }

        if (!player->GetMap()->IsDungeon() && !player->GetMap()->IsRaid()) {
            return;
        }

        auto current_time = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();

        EncounterLogManager::getLog(player->GetInstanceId())->getBuffer().pushMovement(
            player->GetMapId(),
            player->GetInstanceId(),
            player->GetGUID().GetRawValue(),
            player->PositionXYZOStream().m_pos->m_positionX,
            player->PositionXYZOStream().m_pos->m_positionY,
            player->PositionXYZOStream().m_pos->m_positionZ,
            player->PositionXYZOStream().m_pos->m_orientation,
            timestamp
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGMOVEMENTHANDLERSCRIPT_H
