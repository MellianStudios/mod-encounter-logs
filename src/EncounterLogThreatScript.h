#ifndef AZEROTHCORE_ENCOUNTERLOGTHREATSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGTHREATSCRIPT_H

#include "Configuration/Config.h"
#include "ScriptMgr.h"
#include "Map.h"
#include "Player.h"

class EncounterLogThreatScript : ThreatScript
{
public:
    EncounterLogThreatScript() : ThreatScript("EncounterLogThreatScript")
    {}

    void OnAddHostileReferenceToThreatContainer(HostileReference *hostileRef) override
    {
        if (!hostileRef->GetVictim()) {
            return;
        }

        if (hostileRef->GetVictim()->GetMap()->IsDungeon() && EncounterLogManager::dungeonsDisabled()) {
            return;
        }

        if (hostileRef->GetVictim()->GetMap()->IsRaid() && EncounterLogManager::raidsDisabled()) {
            return;
        }

        if (!hostileRef->GetVictim()->GetMap()->IsDungeon() && !hostileRef->GetVictim()->GetMap()->IsRaid()) {
            return;
        }

        if (!hostileRef->GetVictim()->IsPlayer()) {
            return;
        }

        auto current_time = std::chrono::system_clock::now();

        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();

        EncounterLogManager::getLog(hostileRef->GetVictim()->GetInstanceId())->getBuffer().pushCombat(
            hostileRef->GetOwner()->GetMapId(),
            hostileRef->GetOwner()->GetInstanceId(),
            hostileRef->GetOwner()->ToCreature()->GetSpawnId(),
            ENCOUNTER_LOG_CREATURE,
            ENCOUNTER_LOG_START,
            timestamp
        );

        EncounterLogManager::getLog(hostileRef->GetVictim()->GetInstanceId())->getBuffer().pushCombat(
            hostileRef->GetVictim()->GetMapId(),
            hostileRef->GetVictim()->GetInstanceId(),
            hostileRef->GetVictim()->GetGUID().GetRawValue(),
            ENCOUNTER_LOG_PLAYER,
            ENCOUNTER_LOG_START,
            timestamp
        );
    }

    void OnRemoveHostileReferenceFromThreatContainer(HostileReference *hostileRef) override
    {
        if (!hostileRef->GetVictim()) {
            return;
        }

        if (hostileRef->GetVictim()->GetMap()->IsDungeon() && EncounterLogManager::dungeonsDisabled()) {
            return;
        }

        if (hostileRef->GetVictim()->GetMap()->IsRaid() && EncounterLogManager::raidsDisabled()) {
            return;
        }

        if (!hostileRef->GetVictim()->GetMap()->IsDungeon() && !hostileRef->GetVictim()->GetMap()->IsRaid()) {
            return;
        }

        if (!hostileRef->GetVictim()->IsPlayer()) {
            return;
        }

        auto current_time = std::chrono::system_clock::now();

        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();

        EncounterLogManager::getLog(hostileRef->GetVictim()->GetInstanceId())->getBuffer().pushCombat(
            hostileRef->GetOwner()->GetMapId(),
            hostileRef->GetOwner()->GetInstanceId(),
            hostileRef->GetOwner()->ToCreature()->GetSpawnId(),
            ENCOUNTER_LOG_CREATURE,
            ENCOUNTER_LOG_END,
            timestamp
        );

        EncounterLogManager::getLog(hostileRef->GetVictim()->GetInstanceId())->getBuffer().pushCombat(
            hostileRef->GetVictim()->GetMapId(),
            hostileRef->GetVictim()->GetInstanceId(),
            hostileRef->GetVictim()->GetGUID().GetRawValue(),
            ENCOUNTER_LOG_PLAYER,
            ENCOUNTER_LOG_END,
            timestamp
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGTHREATSCRIPT_H
