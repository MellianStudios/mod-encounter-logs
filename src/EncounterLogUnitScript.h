#ifndef AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H

#include "EncounterLogManager.h"
#include "ScriptMgr.h"

class EncounterLogUnitScript : public UnitScript
{
public:
    EncounterLogUnitScript() : UnitScript("EncounterLogUnitScript")
    {}

    // BE WARY THAT THIS IS FOR EFFECTS LIKE THORNS NOT FOR MELEE HITS
    void OnDealMeleeDamage(CalcDamageInfo *calcDamageInfo, DamageInfo *damageInfo, uint32 /*overkill*/) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(calcDamageInfo->attacker)) {
            return;
        }

        EncounterLogManager::getLog(calcDamageInfo->attacker->GetInstanceId())->getBuffer().pushSpell(
            calcDamageInfo->attacker->GetMapId(),
            calcDamageInfo->attacker->GetInstanceId(),
            damageInfo->GetSpellInfo()->Id,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(calcDamageInfo->attacker)),
            EncounterLogHelpers::getGuid(calcDamageInfo->attacker),
            EncounterLogHelpers::getUnitType(calcDamageInfo->attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(calcDamageInfo->target)),
            EncounterLogHelpers::getGuid(calcDamageInfo->target),
            EncounterLogHelpers::getUnitType(calcDamageInfo->target),
            0,
            calcDamageInfo->damages[0].damage,
            0,
            EncounterLogHelpers::getMeleeResult(calcDamageInfo->hitOutCome),
            EncounterLogHelpers::getTimestamp(),
            false,
            EncounterLogHelpers::getMeleeFlag(calcDamageInfo->attackType)
        );
    }

    void OnSendSpellNonMeleeDamageLog(SpellNonMeleeDamage *log) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(log->attacker)) {
            return;
        }
    }

    void OnSendAttackStateUpdate(CalcDamageInfo *damageInfo, int32 overkill) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(damageInfo->attacker)) {
            return;
        }

        EncounterLogManager::getLog(damageInfo->attacker->GetInstanceId())->getBuffer().pushSpell(
            damageInfo->attacker->GetMapId(),
            damageInfo->attacker->GetInstanceId(),
            6603,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(damageInfo->attacker)),
            EncounterLogHelpers::getGuid(damageInfo->attacker),
            EncounterLogHelpers::getUnitType(damageInfo->attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(damageInfo->target)),
            EncounterLogHelpers::getGuid(damageInfo->target),
            EncounterLogHelpers::getUnitType(damageInfo->target),
            0,
            damageInfo->damages[0].damage,
            0,
            EncounterLogHelpers::getMeleeResult(damageInfo->hitOutCome),
            EncounterLogHelpers::getTimestamp(),
            false,
            EncounterLogHelpers::getMeleeFlag(damageInfo->attackType)
        );
    }

    void OnSendSpellDamageImmune(Unit *attacker, Unit *victim, uint32 spellId) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(attacker)) {
            return;
        }
    }

    void OnSendSpellMiss(Unit *attacker, Unit *victim, uint32 spellID, SpellMissInfo missInfo) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(attacker)) {
            return;
        }
    }

    void OnSendSpellDamageResist(Unit *attacker, Unit *victim, uint32 spellId) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(attacker)) {
            return;
        }
    }

    // confirm that log->attacker is same as attacker if yes remove attacker
    void OnSendSpellNonMeleeReflectLog(SpellNonMeleeDamage *log, Unit *attacker) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(log->attacker)) {
            return;
        }
    }

    void OnSendHealSpellLog(HealInfo const &healInfo, bool critical) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(healInfo.GetHealer())) {
            return;
        }
    }

    void OnSendEnergizeSpellLog(Unit *attacker, Unit *victim, uint32 spellID, uint32 damage, Powers powerType) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(attacker)) {
            return;
        }
    }

    void OnSendPeriodicAuraLog(Unit *victim, SpellPeriodicAuraLogInfo *pInfo) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(victim)) {
            return;
        }
    }

    void OnUnitDeath(Unit *unit, Unit *killer) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(unit, false)) {
            return;
        }

        EncounterLogManager::getLog(unit->GetInstanceId())->getBuffer().pushDeath(
            unit->GetMapId(),
            unit->GetInstanceId(),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(unit)),
            EncounterLogHelpers::getGuid(unit),
            EncounterLogHelpers::getUnitType(unit),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(killer)),
            EncounterLogHelpers::getGuid(killer),
            EncounterLogHelpers::getUnitType(killer),
            EncounterLogHelpers::getTimestamp()
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H
