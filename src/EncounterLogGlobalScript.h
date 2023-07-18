#ifndef AZEROTHCORE_ENCOUNTERLOGGLOBALSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGGLOBALSCRIPT_H

#include "EncounterLogManager.h"
#include "ScriptMgr.h"

class EncounterLogGlobalScript : public GlobalScript
{
public:
    EncounterLogGlobalScript() : GlobalScript("EncounterLogGlobalScript")
    {}

    void OnAuraApplicationClientUpdate(Unit *target, Aura *aura, bool remove) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(target)) {
            return;
        }

        Unit *caster_owner = EncounterLogHelpers::getOwnerRecursively(aura->GetCaster());
        Unit *target_owner = EncounterLogHelpers::getOwnerRecursively(target);

        EncounterLogManager::getLog(target->GetInstanceId())->getBuffer().pushSpell(
            target->GetMapId(),
            target->GetInstanceId(),
            aura->GetSpellInfo()->Id,
            EncounterLogHelpers::getGuid(caster_owner),
            EncounterLogHelpers::getUnitType(caster_owner),
            EncounterLogHelpers::getGuid(aura->GetCaster()),
            EncounterLogHelpers::getUnitType(aura->GetCaster()),
            EncounterLogHelpers::getGuid(target_owner),
            EncounterLogHelpers::getUnitType(target_owner),
            EncounterLogHelpers::getGuid(target),
            EncounterLogHelpers::getUnitType(target),
            0,
            0,
            0,
            0,
            0,
            false,
            false,
            ENCOUNTER_LOG_SPELL_RESULT_EMPTY,
            ENCOUNTER_LOG_FLAG_EMPTY,
            remove ? ENCOUNTER_LOG_ARBITRARY_FLAG_AURA_REMOVE : ENCOUNTER_LOG_ARBITRARY_FLAG_AURA_APPLY,
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnBeforeClearExpiredInstancesOnLoadInstances() override
    {
        EncounterLogManager::startInstanceTracker();
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGGLOBALSCRIPT_H
