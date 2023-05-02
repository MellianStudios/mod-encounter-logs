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
            ENCOUNTER_LOG_START,
            player->GetMaxHealth(),
            player->GetHealth(),
            player->GetMaxPower(POWER_ALL),
            player->GetPower(POWER_ALL),
            gear.dump(),
            talents.dump(),
            auras.dump(),
            EncounterLogHelpers::getTimestamp()
        );
    }

    void OnPlayerLeaveCombat(Player *player) override
    {
        if (EncounterLogManager::playerNotInCombat(player)) {
            return;
        }

        EncounterLogManager::deletePlayerCombat(player);

        if (EncounterLogManager::hasLog(player->GetInstanceId())) {
            EncounterLogManager::getLog(player->GetInstanceId())->getBuffer().pushCombat(
                player->GetMapId(),
                player->GetInstanceId(),
                player->GetGUID().GetRawValue(),
                ENCOUNTER_LOG_END,
                player->GetMaxHealth(),
                player->GetHealth(),
                player->GetMaxPower(POWER_ALL),
                player->GetPower(POWER_ALL),
                "",
                "",
                "",
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
            player->GetGUID().GetCounter(),
            ENCOUNTER_LOG_PLAYER,
            0,
            player->GetGUID().GetCounter(),
            ENCOUNTER_LOG_PLAYER,
            0,
            damage,
            0,
            ENCOUNTER_LOG_SPELL_RESULT_EMPTY,
            EncounterLogHelpers::getTimestamp(),
            false,
            ENCOUNTER_LOG_ARBITRARY_FLAG_ENVIRONMENTAL
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H
