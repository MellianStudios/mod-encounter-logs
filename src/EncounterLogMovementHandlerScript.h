#ifndef AZEROTHCORE_ENCOUNTERLOGMOVEMENTHANDLERSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGMOVEMENTHANDLERSCRIPT_H

#include "Configuration/Config.h"
#include "EncounterLogManager.h"
#include "ScriptMgr.h"

class EncounterLogMovementHandlerScript : MovementHandlerScript
{
public:
    EncounterLogMovementHandlerScript() : MovementHandlerScript("EncounterLogMovementHandlerScript")
    {}

    void OnPlayerMove(Player *player, MovementInfo /*movementInfo*/, uint32 /*opcode*/) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(player->ToUnit())) {
            return;
        }

        EncounterLogManager::getLog(player->GetInstanceId())->getBuffer().pushMovement(
            player->GetMapId(),
            player->GetInstanceId(),
            0,
            player->GetGUID().GetRawValue(),
            ENCOUNTER_LOG_PLAYER,
            player->PositionXYZOStream().m_pos->m_positionX,
            player->PositionXYZOStream().m_pos->m_positionY,
            player->PositionXYZOStream().m_pos->m_positionZ,
            player->PositionXYZOStream().m_pos->m_orientation,
            EncounterLogHelpers::getTimestamp()
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGMOVEMENTHANDLERSCRIPT_H
