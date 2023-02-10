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

        if (!caster->IsPlayer()) {
            return;
        }

        auto current_time = std::chrono::system_clock::now();

        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();

        if (targets->GetUnitTarget()) {
            if (targets->GetUnitTarget()->IsPlayer()) {
            } else {
            }
        }

        for (auto &hit: *spell->GetUniqueTargetInfo()) {
        }
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H
