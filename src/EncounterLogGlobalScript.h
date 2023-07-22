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

    void OnChangeUpdateData(Object *object, uint16 index, uint64 value) override
    {
        if (Unit *unit = object->ToUnit()) {
            if (EncounterLogHelpers::shouldNotBeTracked(unit)) {
                return;
            }

            auto owner = EncounterLogHelpers::getOwnerRecursively(unit);

            if (unit->IsPlayer()) {
                switch (index) {
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                        EncounterLogManager::getLog(unit->GetInstanceId())->getBuffer().pushPower(
                            unit->GetMapId(),
                            unit->GetInstanceId(),
                            EncounterLogHelpers::getGuid(owner),
                            EncounterLogHelpers::getUnitType(owner),
                            EncounterLogHelpers::getGuid(unit),
                            EncounterLogHelpers::getUnitType(unit),
                            EncounterLogHelpers::getPowerFlag(index),
                            value,
                            index >= 32,
                            EncounterLogHelpers::getTimestamp()
                        );

                        break;
                    default:
                        return;
                }
            } else {
                if (index == 24 || index == 32) {
                    EncounterLogManager::getLog(unit->GetInstanceId())->getBuffer().pushPower(
                        unit->GetMapId(),
                        unit->GetInstanceId(),
                        EncounterLogHelpers::getGuid(owner),
                        EncounterLogHelpers::getUnitType(owner),
                        EncounterLogHelpers::getGuid(unit),
                        EncounterLogHelpers::getUnitType(unit),
                        ENCOUNTER_LOG_FLAG_POWER_HEALTH,
                        value,
                        index == 32,
                        EncounterLogHelpers::getTimestamp()
                    );
                }
            }
        }
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGGLOBALSCRIPT_H
