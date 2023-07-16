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
    void OnDealMeleeDamage(CalcDamageInfo *calcDamageInfo, DamageInfo *damageInfo, uint32 overkill) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(calcDamageInfo->attacker)) {
            return;
        }

        EncounterLogManager::getLog(calcDamageInfo->attacker->GetInstanceId())->getBuffer().pushSpell(
            calcDamageInfo->attacker->GetMapId(),
            calcDamageInfo->attacker->GetInstanceId(),
            damageInfo->GetSpellInfo()->Id,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(calcDamageInfo->attacker)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(calcDamageInfo->attacker)),
            EncounterLogHelpers::getGuid(calcDamageInfo->attacker),
            EncounterLogHelpers::getUnitType(calcDamageInfo->attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(calcDamageInfo->target)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(calcDamageInfo->target)),
            EncounterLogHelpers::getGuid(calcDamageInfo->target),
            EncounterLogHelpers::getUnitType(calcDamageInfo->target),
            0,
            calcDamageInfo->damages[0].damage,
            overkill,
            calcDamageInfo->damages[0].absorb,
            calcDamageInfo->damages[0].resist,
            calcDamageInfo->blocked_amount,
            false,
            false,
            EncounterLogHelpers::getMeleeResult(calcDamageInfo->hitOutCome),
            EncounterLogHelpers::getMeleeFlag(calcDamageInfo->attackType),
            ENCOUNTER_LOG_ARBITRARY_FLAG_DAMAGE_SHIELD,
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnSendSpellNonMeleeDamageLog(SpellNonMeleeDamage *log) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(log->attacker)) {
            return;
        }

        std::int_fast32_t overkill =
            static_cast<std::int_fast32_t>(log->damage) - static_cast<std::int_fast32_t>(log->target->GetHealth());

        EncounterLogManager::getLog(log->attacker->GetInstanceId())->getBuffer().pushSpell(
            log->attacker->GetMapId(),
            log->attacker->GetInstanceId(),
            log->spellInfo->Id,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(log->attacker)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(log->attacker)),
            EncounterLogHelpers::getGuid(log->attacker),
            EncounterLogHelpers::getUnitType(log->attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(log->target)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(log->target)),
            EncounterLogHelpers::getGuid(log->target),
            EncounterLogHelpers::getUnitType(log->target),
            0,
            log->damage,
            overkill > 0 ? overkill : 0,
            log->absorb,
            log->resist,
            log->blocked,
            false,
            false,
            ENCOUNTER_LOG_SPELL_RESULT_NONE,
            ENCOUNTER_LOG_FLAG_EMPTY,
            ENCOUNTER_LOG_ARBITRARY_FLAG_EMPTY,
            EncounterLogHelpers::getTimestamp()
        );
    }

    // overkill parameter is broken
    void OnSendAttackStateUpdate(CalcDamageInfo *damageInfo, int32 /*overkill*/) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(damageInfo->attacker)) {
            return;
        }

        EncounterLogManager::getLog(damageInfo->attacker->GetInstanceId())->getBuffer().pushSpell(
            damageInfo->attacker->GetMapId(),
            damageInfo->attacker->GetInstanceId(),
            6603,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(damageInfo->attacker)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(damageInfo->attacker)),
            EncounterLogHelpers::getGuid(damageInfo->attacker),
            EncounterLogHelpers::getUnitType(damageInfo->attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(damageInfo->target)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(damageInfo->target)),
            EncounterLogHelpers::getGuid(damageInfo->target),
            EncounterLogHelpers::getUnitType(damageInfo->target),
            0,
            damageInfo->damages[0].damage,
            0,
            damageInfo->damages[0].absorb,
            damageInfo->damages[0].resist,
            damageInfo->blocked_amount,
            false,
            false,
            EncounterLogHelpers::getMeleeResult(damageInfo->hitOutCome),
            EncounterLogHelpers::getMeleeFlag(damageInfo->attackType),
            ENCOUNTER_LOG_ARBITRARY_FLAG_MELEE,
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnSendSpellDamageImmune(Unit *attacker, Unit *victim, uint32 spellId) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(attacker)) {
            return;
        }

        EncounterLogManager::getLog(attacker->GetInstanceId())->getBuffer().pushSpell(
            attacker->GetMapId(),
            attacker->GetInstanceId(),
            spellId,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(attacker)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(attacker)),
            EncounterLogHelpers::getGuid(attacker),
            EncounterLogHelpers::getUnitType(attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getGuid(victim),
            EncounterLogHelpers::getUnitType(victim),
            0,
            0,
            0,
            0,
            0,
            0,
            false,
            false,
            ENCOUNTER_LOG_SPELL_RESULT_IMMUNE,
            ENCOUNTER_LOG_FLAG_EMPTY,
            ENCOUNTER_LOG_ARBITRARY_FLAG_EMPTY,
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnSendSpellMiss(Unit *attacker, Unit *victim, uint32 spellID, SpellMissInfo missInfo) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(attacker)) {
            return;
        }

        EncounterLogManager::getLog(attacker->GetInstanceId())->getBuffer().pushSpell(
            attacker->GetMapId(),
            attacker->GetInstanceId(),
            spellID,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(attacker)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(attacker)),
            EncounterLogHelpers::getGuid(attacker),
            EncounterLogHelpers::getUnitType(attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getGuid(victim),
            EncounterLogHelpers::getUnitType(victim),
            0,
            0,
            0,
            0,
            0,
            0,
            false,
            false,
            EncounterLogHelpers::getSpellResult(missInfo),
            ENCOUNTER_LOG_FLAG_EMPTY,
            ENCOUNTER_LOG_ARBITRARY_FLAG_EMPTY,
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnSendSpellDamageResist(Unit *attacker, Unit *victim, uint32 spellId) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(attacker)) {
            return;
        }

        EncounterLogManager::getLog(attacker->GetInstanceId())->getBuffer().pushSpell(
            attacker->GetMapId(),
            attacker->GetInstanceId(),
            spellId,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(attacker)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(attacker)),
            EncounterLogHelpers::getGuid(attacker),
            EncounterLogHelpers::getUnitType(attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getGuid(victim),
            EncounterLogHelpers::getUnitType(victim),
            0,
            0,
            0,
            0,
            0,
            0,
            false,
            false,
            ENCOUNTER_LOG_SPELL_RESULT_RESIST,
            ENCOUNTER_LOG_FLAG_EMPTY,
            ENCOUNTER_LOG_ARBITRARY_FLAG_EMPTY,
            EncounterLogHelpers::getTimestamp()
        );
    }

    // confirm that log->attacker is same as attacker if yes remove attacker
    void OnSendSpellNonMeleeReflectLog(SpellNonMeleeDamage *log, Unit */*attacker*/) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(log->attacker)) {
            return;
        }

        std::int_fast32_t overkill =
            static_cast<std::int_fast32_t>(log->damage) - static_cast<std::int_fast32_t>(log->target->GetHealth());

        EncounterLogManager::getLog(log->attacker->GetInstanceId())->getBuffer().pushSpell(
            log->attacker->GetMapId(),
            log->attacker->GetInstanceId(),
            log->spellInfo->Id,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(log->attacker)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(log->attacker)),
            EncounterLogHelpers::getGuid(log->attacker),
            EncounterLogHelpers::getUnitType(log->attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(log->target)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(log->target)),
            EncounterLogHelpers::getGuid(log->target),
            EncounterLogHelpers::getUnitType(log->target),
            0,
            log->damage,
            overkill > 0 ? overkill : 0,
            log->absorb,
            log->resist,
            log->blocked,
            false,
            false,
            ENCOUNTER_LOG_SPELL_RESULT_REFLECT,
            ENCOUNTER_LOG_FLAG_EMPTY,
            ENCOUNTER_LOG_ARBITRARY_FLAG_EMPTY,
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnSendHealSpellLog(HealInfo const &healInfo, bool critical) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(healInfo.GetHealer())) {
            return;
        }

        std::int_fast32_t overheal =
            static_cast<std::int_fast32_t>(healInfo.GetHeal()) -
            static_cast<std::int_fast32_t>(healInfo.GetEffectiveHeal());

        EncounterLogManager::getLog(healInfo.GetHealer()->GetInstanceId())->getBuffer().pushSpell(
            healInfo.GetHealer()->GetMapId(),
            healInfo.GetHealer()->GetInstanceId(),
            healInfo.GetSpellInfo()->Id,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(healInfo.GetHealer())),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(healInfo.GetHealer())),
            EncounterLogHelpers::getGuid(healInfo.GetHealer()),
            EncounterLogHelpers::getUnitType(healInfo.GetHealer()),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(healInfo.GetTarget())),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(healInfo.GetTarget())),
            EncounterLogHelpers::getGuid(healInfo.GetTarget()),
            EncounterLogHelpers::getUnitType(healInfo.GetTarget()),
            0,
            healInfo.GetHeal(),
            overheal,
            healInfo.GetAbsorb(),
            0,
            0,
            critical,
            true,
            ENCOUNTER_LOG_SPELL_RESULT_NONE,
            EncounterLogHelpers::getSpellSchoolFlag(healInfo.GetSchoolMask()),
            ENCOUNTER_LOG_ARBITRARY_FLAG_EMPTY,
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnSendEnergizeSpellLog(Unit *attacker, Unit *victim, uint32 spellID, uint32 damage, Powers powerType) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(attacker)) {
            return;
        }

        EncounterLogManager::getLog(victim->GetInstanceId())->getBuffer().pushSpell(
            victim->GetMapId(),
            victim->GetInstanceId(),
            spellID,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(attacker)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(attacker)),
            EncounterLogHelpers::getGuid(attacker),
            EncounterLogHelpers::getUnitType(attacker),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getGuid(victim),
            EncounterLogHelpers::getUnitType(victim),
            0,
            damage,
            0,
            0,
            0,
            0,
            false,
            false,
            ENCOUNTER_LOG_SPELL_RESULT_NONE,
            EncounterLogHelpers::getPowerFlag(powerType),
            ENCOUNTER_LOG_ARBITRARY_FLAG_ENERGIZE,
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnSendPeriodicAuraLog(Unit *victim, SpellPeriodicAuraLogInfo *pInfo) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(victim)) {
            return;
        }

        EncounterLogManager::getLog(victim->GetInstanceId())->getBuffer().pushSpell(
            victim->GetMapId(),
            victim->GetInstanceId(),
            pInfo->auraEff->GetSpellInfo()->Id,
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(pInfo->auraEff->GetCaster())),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(pInfo->auraEff->GetCaster())),
            EncounterLogHelpers::getGuid(pInfo->auraEff->GetCaster()),
            EncounterLogHelpers::getUnitType(pInfo->auraEff->GetCaster()),
            EncounterLogHelpers::getGuid(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getUnitType(EncounterLogHelpers::getOwnerRecursively(victim)),
            EncounterLogHelpers::getGuid(victim),
            EncounterLogHelpers::getUnitType(victim),
            0,
            pInfo->damage,
            pInfo->overDamage,
            pInfo->absorb,
            pInfo->resist,
            0,
            pInfo->critical,
            false,
            ENCOUNTER_LOG_SPELL_RESULT_NONE,
            EncounterLogHelpers::getAuraTypeFlag(pInfo->auraEff->GetAuraType()),
            ENCOUNTER_LOG_ARBITRARY_FLAG_PERIODICAL,
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnUnitDeath(Unit *unit, Unit *killer) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(unit, false)) {
            return;
        }

        Unit *unit_owner = EncounterLogHelpers::getOwnerRecursively(unit);
        Unit *killer_owner = EncounterLogHelpers::getOwnerRecursively(killer);

        EncounterLogManager::getLog(unit->GetInstanceId())->getBuffer().pushDeath(
            unit->GetMapId(),
            unit->GetInstanceId(),
            EncounterLogHelpers::getGuid(unit_owner),
            EncounterLogHelpers::getUnitType(unit_owner),
            EncounterLogHelpers::getGuid(unit),
            EncounterLogHelpers::getUnitType(unit),
            EncounterLogHelpers::getGuid(killer_owner),
            EncounterLogHelpers::getUnitType(killer_owner),
            EncounterLogHelpers::getGuid(killer),
            EncounterLogHelpers::getUnitType(killer),
            EncounterLogHelpers::getTimestamp()
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H
