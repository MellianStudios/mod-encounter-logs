#ifndef AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H

#include "Configuration/Config.h"
#include "Chat.h"
#include "Pet.h"
#include "Spell.h"
#include "ScriptMgr.h"
#include "TemporarySummon.h"
#include "Totem.h"

class EncounterLogUnitScript : public UnitScript
{
private:
    std::uint_fast8_t getResultNumber(bool crit, SpellMissInfo miss, SpellMissInfo reflect)
    {
        if (crit) {
            return ENCOUNTER_LOG_SPELL_RESULT_CRIT;
        }

        if (miss > SPELL_MISS_NONE && reflect > SPELL_MISS_NONE) {
            return ENCOUNTER_LOG_DEBUG_RESULT;
        }

        return std::max(miss, reflect) + 1;
    }

public:
    EncounterLogUnitScript() : UnitScript("EncounterLogUnitScript")
    {}

    void OnUnitSpellCast(Unit *caster, SpellCastTargets *targets, Spell *spell) override
    {
        // this is being run before AllMapScript::OnPlayerEnterAll
        if (!EncounterLogManager::hasLog(caster->GetInstanceId())) {
            return;
        }

        if (caster->GetMap()->IsDungeon() && EncounterLogManager::dungeonsDisabled()) {
            return;
        }

        if (caster->GetMap()->IsRaid() && EncounterLogManager::raidsDisabled()) {
            return;
        }

        if (!caster->GetMap()->IsDungeon() && !caster->GetMap()->IsRaid()) {
            return;
        }

        if (!caster->IsPlayer() && !caster->IsCreatedByPlayer()) {
            if (!caster->IsInCombat()) {
                return;
            }

            bool in_combat_with_player{false};

            for (auto hostile: caster->GetThreatMgr().GetThreatList()) {
                if (hostile->GetVictim()->IsPlayer() || hostile->GetVictim()->IsCreatedByPlayer()) {
                    in_combat_with_player = true;

                    break;
                }
            }

            if (!in_combat_with_player) {
                return;
            }
        }

        std::uint_fast16_t map_id{caster->GetMapId()};
        std::uint_fast16_t instance_id{caster->GetInstanceId()};
        std::uint_fast32_t spell_id{spell->m_spellInfo->Id};
        std::uint_fast32_t caster_owner_guid{0};
        std::uint_fast32_t caster_guid{ENCOUNTER_LOG_DEBUG_GUID};
        std::uint_fast8_t caster_type{ENCOUNTER_LOG_DEBUG_TYPE};
        std::uint_fast32_t target_owner_guid{0};
        std::uint_fast32_t target_guid{ENCOUNTER_LOG_DEBUG_GUID};
        std::uint_fast8_t target_type{ENCOUNTER_LOG_DEBUG_TYPE};
        std::uint_fast32_t cost{spell->GetPowerCost()};
        std::uint_fast32_t value{0};
        std::uint_fast8_t result{ENCOUNTER_LOG_SPELL_RESULT_EMPTY};

        auto current_time = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();

        bool value_not_present{false};

        if (caster->IsPlayer()) {
            caster_guid = caster->ToPlayer()->GetGUID().GetRawValue();
            caster_type = ENCOUNTER_LOG_PLAYER;
        } else if (caster->IsCreatedByPlayer()) {
            caster_owner_guid = caster->GetOwner()->ToPlayer()->GetGUID().GetRawValue();

            if (caster->IsPet() || caster->IsHunterPet()) {
                caster_guid = caster->ToPet()->GetGUID().GetEntry();
                caster_type = ENCOUNTER_LOG_PET;
            } else if (caster->IsTotem()) {
                caster_guid = caster->ToTotem()->GetGUID().GetEntry();
                caster_type = ENCOUNTER_LOG_TOTEM;
            } else if (caster->IsSummon()) {
                caster_guid = caster->ToTempSummon()->GetGUID().GetEntry();
                caster_type = ENCOUNTER_LOG_SUMMON;
            }
        } else {
            if (caster->IsPet()) {
                caster_owner_guid = caster->GetOwner()->ToCreature()->GetSpawnId();
                caster_guid = caster->ToPet()->GetGUID().GetEntry();
                caster_type = ENCOUNTER_LOG_PET;
            } else if (caster->IsTotem()) {
                caster_owner_guid = caster->GetOwner()->ToCreature()->GetSpawnId();
                caster_guid = caster->ToTotem()->GetGUID().GetEntry();
                caster_type = ENCOUNTER_LOG_TOTEM;
            } else if (caster->IsSummon()) {
                caster_owner_guid = caster->GetOwner()->ToCreature()->GetSpawnId();
                caster_guid = caster->ToTempSummon()->GetGUID().GetEntry();
                caster_type = ENCOUNTER_LOG_SUMMON;
            } else {
                caster_guid = caster->ToCreature()->GetSpawnId();
                caster_type = ENCOUNTER_LOG_CREATURE;
            }
        }

        if (Unit *target = targets->GetUnitTarget()) {
            if (target->IsPlayer()) {
                target_guid = target->ToPlayer()->GetGUID().GetRawValue();
                target_type = ENCOUNTER_LOG_PLAYER;
            } else if (target->IsCreatedByPlayer()) {
                target_owner_guid = caster->GetOwner()->ToPlayer()->GetGUID().GetRawValue();

                if (target->IsPet() || target->IsHunterPet()) {
                    target_guid = target->ToPet()->GetGUID().GetEntry();
                    target_type = ENCOUNTER_LOG_PET;
                } else if (target->IsTotem()) {
                    target_guid = target->ToTotem()->GetGUID().GetEntry();
                    target_type = ENCOUNTER_LOG_TOTEM;
                } else if (target->IsSummon()) {
                    target_guid = target->ToTempSummon()->GetGUID().GetEntry();
                    target_type = ENCOUNTER_LOG_SUMMON;
                }
            } else {
                if (target->IsPet()) {
                    target_owner_guid = target->GetOwner()->ToCreature()->GetSpawnId();
                    target_guid = target->ToPet()->GetGUID().GetEntry();
                    target_type = ENCOUNTER_LOG_PET;
                } else if (target->IsTotem()) {
                    target_owner_guid = target->GetOwner()->ToCreature()->GetSpawnId();
                    target_guid = target->ToTotem()->GetGUID().GetEntry();
                    target_type = ENCOUNTER_LOG_TOTEM;
                } else if (target->IsSummon()) {
                    target_owner_guid = target->GetOwner()->ToCreature()->GetSpawnId();
                    target_guid = target->ToTempSummon()->GetGUID().GetEntry();
                    target_type = ENCOUNTER_LOG_SUMMON;
                } else {
                    target_guid = target->ToCreature()->GetSpawnId();
                    target_type = ENCOUNTER_LOG_CREATURE;
                }
            }
        }

        if (spell->GetUniqueTargetInfo()->empty()) {
            value_not_present = true;
        } else if (spell->GetUniqueTargetInfo()->size() == 1) {
            for (auto &hit: *spell->GetUniqueTargetInfo()) {
                value = hit.damage;
                result = getResultNumber(hit.crit, hit.missCondition, hit.reflectResult);
            }
        } else {
            for (auto &hit: *spell->GetUniqueTargetInfo()) {
                std::uint_fast32_t area_target_owner_guid{0};
                std::uint_fast32_t area_target_guid{ENCOUNTER_LOG_DEBUG_GUID};
                std::uint_fast8_t area_target_type{ENCOUNTER_LOG_DEBUG_TYPE};

                if (Unit *target = ObjectAccessor::GetUnit(*caster, hit.targetGUID)) {
                    if (target->IsPlayer()) {
                        area_target_guid = target->ToPlayer()->GetGUID().GetRawValue();
                        area_target_type = ENCOUNTER_LOG_PLAYER;
                    } else if (target->IsCreatedByPlayer()) {
                        area_target_owner_guid = caster->GetOwner()->ToPlayer()->GetGUID().GetRawValue();

                        if (target->IsPet() || target->IsHunterPet()) {
                            area_target_guid = target->ToPet()->GetGUID().GetEntry();
                            area_target_type = ENCOUNTER_LOG_PET;
                        } else if (target->IsTotem()) {
                            area_target_guid = target->ToTotem()->GetGUID().GetEntry();
                            area_target_type = ENCOUNTER_LOG_TOTEM;
                        } else if (target->IsSummon()) {
                            area_target_guid = target->ToTempSummon()->GetGUID().GetEntry();
                            area_target_type = ENCOUNTER_LOG_SUMMON;
                        }
                    } else {
                        if (target->IsPet()) {
                            area_target_owner_guid = target->GetOwner()->ToCreature()->GetSpawnId();
                            area_target_guid = target->ToPet()->GetGUID().GetEntry();
                            area_target_type = ENCOUNTER_LOG_PET;
                        } else if (target->IsTotem()) {
                            area_target_owner_guid = target->GetOwner()->ToCreature()->GetSpawnId();
                            area_target_guid = target->ToTotem()->GetGUID().GetEntry();
                            area_target_type = ENCOUNTER_LOG_TOTEM;
                        } else if (target->IsSummon()) {
                            area_target_owner_guid = target->GetOwner()->ToCreature()->GetSpawnId();
                            area_target_guid = target->ToTempSummon()->GetGUID().GetEntry();
                            area_target_type = ENCOUNTER_LOG_SUMMON;
                        } else {
                            area_target_guid = target->ToCreature()->GetSpawnId();
                            area_target_type = ENCOUNTER_LOG_CREATURE;
                        }
                    }
                }

                EncounterLogManager::getLog(instance_id)->getBuffer().pushAreaSpell(
                    spell_id,
                    caster_owner_guid,
                    caster_guid,
                    caster_type,
                    area_target_owner_guid,
                    area_target_guid,
                    area_target_type,
                    hit.damage,
                    getResultNumber(hit.crit, hit.missCondition, hit.reflectResult),
                    timestamp
                );
            }
        }

        LOG_ERROR("test", "spell {}", spell->m_spellInfo->SpellName[0]);
        EncounterLogManager::getLog(instance_id)->getBuffer().pushSpell(
            map_id,
            instance_id,
            spell_id,
            caster_owner_guid,
            caster_guid,
            caster_type,
            target_owner_guid,
            target_guid,
            target_type,
            cost,
            value,
            result,
            timestamp,
            value_not_present
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGUNITSCRIPT_H
