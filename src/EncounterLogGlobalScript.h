#ifndef AZEROTHCORE_ENCOUNTERLOGGLOBALSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGGLOBALSCRIPT_H

#include "EncounterLogManager.h"
#include "ScriptMgr.h"

class EncounterLogGlobalScript : public GlobalScript
{
public:
    EncounterLogGlobalScript() : GlobalScript("EncounterLogGlobalScript")
    {}

    void OnSpellSendSpellGo(Spell *spell) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(spell->GetCaster())) {
            return;
        }

        if (spell->GetUniqueTargetInfo()->empty()) {

        } else if (spell->GetUniqueTargetInfo()->size() == 1) {
            for (auto &hit: *spell->GetUniqueTargetInfo()) {
            }
        } else {
            for (auto &hit: *spell->GetUniqueTargetInfo()) {
            }
        }
    }

    void OnAuraApplicationClientUpdate(Unit *target, Aura *aura, bool remove) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(target)) {
            return;
        }

        EncounterLogManager::getLog(target->GetInstanceId())->getBuffer().pushSpell(
            target->GetMapId(),
            target->GetInstanceId(),
            aura->GetSpellInfo()->Id,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(aura->GetCaster())),
            EncounterLogHelpers::getGuid(aura->GetCaster()),
            EncounterLogHelpers::getUnitType(aura->GetCaster()),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(target)),
            EncounterLogHelpers::getGuid(target),
            EncounterLogHelpers::getUnitType(target),
            0,
            0,
            0,
            ENCOUNTER_LOG_SPELL_RESULT_EMPTY,
            EncounterLogHelpers::getTimestamp(),
            true,
            remove ? ENCOUNTER_LOG_ARBITRARY_FLAG_AURA_REMOVE : ENCOUNTER_LOG_ARBITRARY_FLAG_AURA_APPLY
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGGLOBALSCRIPT_H
