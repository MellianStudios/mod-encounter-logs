#ifndef AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H

#include <nlohmann/json.hpp>
#include "EncounterLogManager.h"
#include "Player.h"
#include "ScriptMgr.h"

class EncounterLogPlayerScript : public PlayerScript
{
public:
    EncounterLogPlayerScript() : PlayerScript("EncounterLogPlayerScript")
    {}

    void OnPlayerEnterCombat(Player *player, Unit */*enemy*/) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(player->ToUnit())) {
            return;
        }

        EncounterLogManager::registerPlayerCombat(player);

        nlohmann::json gear = nlohmann::json::object();
        nlohmann::json talents = nlohmann::json::object();
        nlohmann::json auras = nlohmann::json::array();
        nlohmann::json stats = {
            player->GetUInt32Value(UNIT_FIELD_MAXHEALTH),
            player->GetUInt32Value(UNIT_FIELD_HEALTH),
            player->GetUInt32Value(UNIT_FIELD_MAXPOWER1),
            player->GetUInt32Value(UNIT_FIELD_POWER1),
            player->GetUInt32Value(UNIT_FIELD_STAT0), // strength
            player->GetUInt32Value(UNIT_FIELD_STAT1), // agility
            player->GetUInt32Value(UNIT_FIELD_STAT2), // stamina
            player->GetUInt32Value(UNIT_FIELD_STAT3), // intellect
            player->GetUInt32Value(UNIT_FIELD_STAT4), // spirit
            player->GetUInt32Value(UNIT_FIELD_RESISTANCES), // armor
            player->GetUInt32Value(UNIT_FIELD_RESISTANCES + 1), // holy
            player->GetUInt32Value(UNIT_FIELD_RESISTANCES + 2), // fire
            player->GetUInt32Value(UNIT_FIELD_RESISTANCES + 3), // nature
            player->GetUInt32Value(UNIT_FIELD_RESISTANCES + 4), // frost
            player->GetUInt32Value(UNIT_FIELD_RESISTANCES + 5), // shadow
            player->GetUInt32Value(UNIT_FIELD_RESISTANCES + 6), // arcane
            player->GetUInt32Value(PLAYER_FIELD_COMBAT_RATING_1 + 1), // defense but weird value
            player->GetFloatValue(PLAYER_FIELD_COMBAT_RATING_1 + 2), // dodge rating
            player->GetFloatValue(PLAYER_DODGE_PERCENTAGE),
            player->GetUInt32Value(PLAYER_FIELD_COMBAT_RATING_1 + 3), // parry rating
            player->GetFloatValue(PLAYER_PARRY_PERCENTAGE),
            player->GetUInt32Value(PLAYER_FIELD_COMBAT_RATING_1 + 4), // block rating
            player->GetFloatValue(PLAYER_BLOCK_PERCENTAGE),
            player->GetUInt32Value(PLAYER_SHIELD_BLOCK),
            player->GetUInt32Value(PLAYER_EXPERTISE),
            player->GetUInt32Value(PLAYER_OFFHAND_EXPERTISE),
            player->GetUInt32Value(PLAYER_FIELD_COMBAT_RATING_1 + 5), // hit rating
            // missing hit chance
            player->GetUInt32Value(PLAYER_FIELD_COMBAT_RATING_1 + 8), // crit rating
            player->GetFloatValue(PLAYER_CRIT_PERCENTAGE),
            player->GetFloatValue(PLAYER_RANGED_CRIT_PERCENTAGE),
            player->GetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1),
            player->GetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1 + 1),
            player->GetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1 + 2),
            player->GetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1 + 3),
            player->GetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1 + 4),
            player->GetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1 + 5),
            player->GetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1 + 6),
            player->GetUInt32Value(PLAYER_FIELD_COMBAT_RATING_1 + 17), // haste rating
            player->GetFloatValue(UNIT_MOD_CAST_SPEED),
            player->GetFloatValue(UNIT_FIELD_MINDAMAGE),
            player->GetFloatValue(UNIT_FIELD_MAXDAMAGE),
            player->GetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE),
            player->GetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE),
            player->GetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE),
            player->GetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE),
            player->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME),
            player->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME + 1),
            player->GetUInt32Value(UNIT_FIELD_RANGEDATTACKTIME),
            player->GetUInt32Value(UNIT_FIELD_ATTACK_POWER),
            player->GetUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER),
            player->GetUInt32Value(PLAYER_FIELD_COMBAT_RATING_1 + 24), // armor pene
            player->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS), // spell power
            player->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 1),
            player->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 2),
            player->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 3),
            player->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 4),
            player->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 5),
            player->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + 6),
            player->GetUInt32Value(PLAYER_FIELD_MOD_HEALING_DONE_POS), // healing spell power
            player->GetFloatValue(UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER),
            player->GetFloatValue(UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER),
        };

        for (int i = 0; i <= 18; i++) {
            Item *item = player->GetItemByPos(255, i);

            std::uint_fast32_t item_id{0};
            nlohmann::json gems = nlohmann::json::object();
            std::uint_fast32_t enchant{0};
            std::uint_fast32_t bonus_enchant{0};

            if (item) {
                item_id = item->GetEntry();

                for (std::uint_fast8_t slot = SOCK_ENCHANTMENT_SLOT; slot < SOCK_ENCHANTMENT_SLOT + 3; slot++) {
                    std::uint_fast32_t enchant_id = item->GetEnchantmentId(EnchantmentSlot(slot));

                    if (!enchant_id) {
                        continue;
                    }

                    SpellItemEnchantmentEntry const *enchant_entry = sSpellItemEnchantmentStore.LookupEntry(enchant_id);

                    if (!enchant_entry) {
                        continue;
                    }

                    gems[std::to_string(slot)] = enchant_entry->GemID;
                }

                std::uint_fast32_t enchant_id = item->GetEnchantmentId(EnchantmentSlot(0));

                if (enchant_id) {
                    SpellItemEnchantmentEntry const *enchant_entry = sSpellItemEnchantmentStore.LookupEntry(enchant_id);

                    if (enchant_entry) {
                        enchant = enchant_entry->ID;
                    }
                }

                enchant_id = item->GetEnchantmentId(EnchantmentSlot(1));

                if (enchant_id) {
                    SpellItemEnchantmentEntry const *enchant_entry = sSpellItemEnchantmentStore.LookupEntry(enchant_id);

                    if (enchant_entry) {
                        bonus_enchant = enchant_entry->ID;
                    }
                }
            }

            gear[std::to_string(i)] = {
                {"i", item_id},
                {"g", gems},
                {"e", {
                    {"m", enchant},
                    {"b", bonus_enchant}
                }}
            };
        }

        for (const auto &[id, talent]: player->GetTalentMap()) {
            TalentEntry const *talent_entry = sTalentStore.LookupEntry(talent->talentID);

            for (std::uint_fast8_t rank = 0; rank < MAX_TALENT_RANK; ++rank) {
                if (
                    talent_entry->RankID[rank]
                    &&
                    player->HasTalent(talent_entry->RankID[rank], player->GetActiveSpec())
                    ) {
                    talents[std::to_string(talent->talentID)] = rank + 1;

                    break;
                }
            }
        }

        for (auto &[id, aura]: player->GetAppliedAuras()) {
            if (player->GetTalentMap().contains(aura->GetBase()->GetId())) {
                continue;
            }

            auras.push_back(
                {
                    {"i", aura->GetBase()->GetId()},
                    {"p", aura->IsPositive() ? 1 : 0},
                    {"d", aura->GetBase()->GetDuration()}
                }
            );
        }

        EncounterLogManager::getLog(player->GetInstanceId())->getBuffer().pushCombat(
            player->GetMapId(),
            player->GetInstanceId(),
            player->GetGUID().GetRawValue(),
            ENCOUNTER_LOG_STATE_START,
            gear.dump(),
            talents.dump(),
            auras.dump(),
            stats.dump(),
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnPlayerLeaveCombat(Player *player) override
    {
        if (EncounterLogManager::playerNotInCombat(player)) {
            return;
        }

        EncounterLogManager::deletePlayerCombat(player);

        nlohmann::json stats = {
            player->GetUInt32Value(UNIT_FIELD_MAXHEALTH),
            player->GetUInt32Value(UNIT_FIELD_HEALTH),
            player->GetUInt32Value(UNIT_FIELD_MAXPOWER1),
            player->GetUInt32Value(UNIT_FIELD_POWER1),
        };

        if (EncounterLogManager::hasLog(player->GetInstanceId())) {
            EncounterLogManager::getLog(player->GetInstanceId())->getBuffer().pushCombat(
                player->GetMapId(),
                player->GetInstanceId(),
                player->GetGUID().GetRawValue(),
                ENCOUNTER_LOG_STATE_END,
                "",
                "",
                "",
                stats.dump(),
                EncounterLogHelpers::getTimestamp()
            );
        }
    }

    void OnEnvironmentalDamage(Player *player, EnviromentalDamage type, uint32 damage) override
    {
        if (EncounterLogHelpers::shouldNotBeTracked(player->ToUnit())) {
            return;
        }

        EncounterLogManager::getLog(player->GetInstanceId())->getBuffer().pushSpell(
            player->GetMapId(),
            player->GetInstanceId(),
            0,
            0,
            ENCOUNTER_LOG_UNIT_EMPTY,
            0,
            ENCOUNTER_LOG_UNIT_EMPTY,
            0,
            ENCOUNTER_LOG_UNIT_EMPTY,
            EncounterLogHelpers::getGuid(player),
            ENCOUNTER_LOG_UNIT_PLAYER,
            damage,
            0,
            0,
            0,
            0,
            false,
            false,
            ENCOUNTER_LOG_SPELL_RESULT_EMPTY,
            EncounterLogHelpers::getEnvironmentalFlag(type),
            ENCOUNTER_LOG_ARBITRARY_FLAG_ENVIRONMENTAL,
            EncounterLogHelpers::getTimestamp()
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H
