#ifndef AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H

#include "Configuration/Config.h"
#include "Chat.h"
#include "Spell.h"
#include "ScriptMgr.h"

class EncounterLogUnitScript : public UnitScript
{
public:
    EncounterLogUnitScript() : UnitScript("EncounterLogUnitScript")
    {}

    void OnUnitSpellCast(Unit *caster, SpellCastTargets *targets, Spell *spell) override
    {
        if (caster->GetMap()->IsDungeon() && EncounterLogManager::dungeonsDisabled()) {
            return;
        }

        if (caster->GetMap()->IsRaid() && EncounterLogManager::raidsDisabled()) {
            return;
        }

        if (!caster->GetMap()->IsDungeon() && !caster->GetMap()->IsRaid()) {
            return;
        }

        if (!caster->IsPlayer() || !caster->IsInCombat()) {
            return;
        }

        auto current_time = std::chrono::system_clock::now();

        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();

        std::uint_fast32_t target_guid{0};
        std::uint_fast32_t value{0};

        if (targets->GetUnitTarget()) {
            target_guid = targets->GetUnitTarget()->IsPlayer()
                          ? targets->GetUnitTarget()->GetGUID().GetRawValue()
                          : targets->GetUnitTarget()->ToCreature()->GetSpawnId();
        }

        if (spell->GetUniqueTargetInfo()->empty()) {

        } else if (spell->GetUniqueTargetInfo()->size() == 1) {
            for (auto &hit: *spell->GetUniqueTargetInfo()) {
                value = hit.damage;
            }
        } else {
            for (auto &hit: *spell->GetUniqueTargetInfo()) {
                EncounterLogManager::getLog(caster->GetInstanceId())->getBuffer().pushAreaSpell(
                    spell->m_spellInfo->Id,
                    caster->IsPlayer() ? caster->GetGUID().GetRawValue() : caster->ToCreature()->GetSpawnId(),
                    hit.targetGUID.GetRawValue(),
                    hit.crit ? ENCOUNTER_LOG_SPELL_RESULT_CRIT : (hit.reflectResult + 1),
                    timestamp,
                    hit.damage
                );
            }
        }

        EncounterLogManager::getLog(caster->GetInstanceId())->getBuffer().pushSpell(
            caster->GetMapId(),
            caster->GetInstanceId(),
            spell->m_spellInfo->Id,
            caster->IsPlayer() ? caster->GetGUID().GetRawValue() : caster->ToCreature()->GetSpawnId(),
            timestamp,
            target_guid,
            spell->GetPowerCost(),
            value
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H
