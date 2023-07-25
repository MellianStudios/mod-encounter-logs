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

    void OnChangeUpdateData(Object *object, uint16 index, uint64 value) override
    {
        if (Unit *unit = object->ToUnit()) {
            if (!object->IsInWorld() || EncounterLogHelpers::shouldNotBeTracked(unit)) {
                return;
            }

            if (unit->IsPlayer()) {
                switch (index) {
                    case 24:
                        if (object->m_encounter_log_previous_health != value) {
                            EncounterLogHelpers::storePower(unit, index, value);
                        }

                        break;
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                        if (object->m_encounter_log_previous_power != value) {
                            EncounterLogHelpers::storePower(unit, index, value);
                        }

                        break;
                    case 32:
                        if (object->m_encounter_log_previous_max_health != value) {
                            EncounterLogHelpers::storePower(unit, index, value);
                        }

                        break;
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                        if (object->m_encounter_log_previous_max_power != value) {
                            EncounterLogHelpers::storePower(unit, index, value);
                        }

                        break;
                    default:
                        return;
                }
            } else {
                switch (index) {
                    case 24:
                        if (object->m_encounter_log_previous_health != value) {
                            EncounterLogHelpers::storePower(unit, index, value);
                        }

                        break;
                    case 32:
                        if (object->m_encounter_log_previous_max_health != value) {
                            EncounterLogHelpers::storePower(unit, index, value);
                        }

                        break;
                    default:
                        return;
                }
            }
        }
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGGLOBALSCRIPT_H
