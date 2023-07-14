#ifndef AZEROTHCORE_ENCOUNTERLOGMANAGER_H
#define AZEROTHCORE_ENCOUNTERLOGMANAGER_H

#include <utility>
#include "Chat.h"
#include "Configuration/Config.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "Pet.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "TemporarySummon.h"
#include "Totem.h"
#include "Unit.h"

// Note that these data types here are irrelevant since on most of modern computers all of them will be implemented as "long"

enum EncounterLogDebugValues
{
    ENCOUNTER_LOG_DEBUG_TYPE = 0,
    ENCOUNTER_LOG_DEBUG_RESULT = 255,
    ENCOUNTER_LOG_DEBUG_GUID = 123456789,
};

enum EncounterLogScope
{
    ENCOUNTER_LOG_SCOPE_DUNGEON = 1,
    ENCOUNTER_LOG_SCOPE_RAID = 2,
    ENCOUNTER_LOG_SCOPE_EVERYTHING = 3
};

enum EncounterLogState
{
    ENCOUNTER_LOG_STATE_START = 1,
    ENCOUNTER_LOG_STATE_END = 2,
};

enum EncounterLogUnitType
{
    ENCOUNTER_LOG_UNIT_EMPTY = 0,
    ENCOUNTER_LOG_UNIT_PLAYER = 1,
    ENCOUNTER_LOG_UNIT_CREATURE = 2,
    ENCOUNTER_LOG_UNIT_PET = 3,
    ENCOUNTER_LOG_UNIT_TOTEM = 4,
    ENCOUNTER_LOG_UNIT_SUMMON = 5,
    ENCOUNTER_LOG_UNIT_VEHICLE = 6,
    ENCOUNTER_LOG_UNIT_OBJECT = 7,
};

enum EncounterLogSpellResult
{
    ENCOUNTER_LOG_SPELL_RESULT_EMPTY = 0,
    ENCOUNTER_LOG_SPELL_RESULT_NONE = 1, // hit
    ENCOUNTER_LOG_SPELL_RESULT_MISS = 2,
    ENCOUNTER_LOG_SPELL_RESULT_RESIST = 3,
    ENCOUNTER_LOG_SPELL_RESULT_DODGE = 4,
    ENCOUNTER_LOG_SPELL_RESULT_PARRY = 5,
    ENCOUNTER_LOG_SPELL_RESULT_BLOCK = 6,
    ENCOUNTER_LOG_SPELL_RESULT_EVADE = 7,
    ENCOUNTER_LOG_SPELL_RESULT_IMMUNE = 8,
    ENCOUNTER_LOG_SPELL_RESULT_DEFLECT = 9,
    ENCOUNTER_LOG_SPELL_RESULT_ABSORB = 10,
    ENCOUNTER_LOG_SPELL_RESULT_REFLECT = 11,
    ENCOUNTER_LOG_SPELL_RESULT_CRIT = 12,
    ENCOUNTER_LOG_SPELL_RESULT_GLANCING = 13,
    ENCOUNTER_LOG_SPELL_RESULT_CRUSHING = 14,
};

enum EncounterLogArbitraryFlag
{
    ENCOUNTER_LOG_ARBITRARY_FLAG_EMPTY = 0,
    ENCOUNTER_LOG_ARBITRARY_FLAG_AURA_APPLY = 1,
    ENCOUNTER_LOG_ARBITRARY_FLAG_AURA_REMOVE = 2,
    ENCOUNTER_LOG_ARBITRARY_FLAG_ENVIRONMENTAL = 3,
    ENCOUNTER_LOG_ARBITRARY_FLAG_BASE_ATTACK = 4,
    ENCOUNTER_LOG_ARBITRARY_FLAG_OFF_ATTACK = 5,
    ENCOUNTER_LOG_ARBITRARY_FLAG_RANGED_ATTACK = 6,
    ENCOUNTER_LOG_ARBITRARY_FLAG_MAX_ATTACK = 7,
};

class EncounterLogCombat
{
private:
    std::uint_fast16_t map_id;
    std::uint_fast16_t instance_id;
    std::uint_fast32_t guid;
    EncounterLogState state;
    std::uint_fast32_t max_hp;
    std::uint_fast32_t hp;
    std::uint_fast32_t max_resource;
    std::uint_fast32_t resource;
    std::string gear;
    std::string talents;
    std::string auras;
    std::uint_fast64_t timestamp;

public:
    EncounterLogCombat(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t guid,
        EncounterLogState state,
        std::uint_fast32_t max_hp,
        std::uint_fast32_t hp,
        std::uint_fast32_t max_resource,
        std::uint_fast32_t resource,
        std::string gear,
        std::string talents,
        std::string auras,
        std::uint_fast64_t timestamp
    )
        : map_id{map_id}, instance_id{instance_id}, guid{guid}, state{state}, max_hp{max_hp}, hp{hp},
        max_resource{max_resource}, resource{resource}, gear{std::move(gear)}, talents{std::move(talents)},
        auras{std::move(auras)}, timestamp{timestamp}
    {}

    [[nodiscard]] std::string asString() const
    {
        std::string result{"("};

        result.append(std::to_string(map_id));
        result.append(",");
        result.append(std::to_string(instance_id));
        result.append(",");
        result.append(std::to_string(guid));
        result.append(",");
        result.append(std::to_string(state));
        result.append(",");
        result.append(std::to_string(max_hp));
        result.append(",");
        result.append(std::to_string(hp));
        result.append(",");
        result.append(std::to_string(max_resource));
        result.append(",");
        result.append(std::to_string(resource));
        result.append(",");
        result.append(gear.empty() ? "null" : "'" + gear + "'");
        result.append(",");
        result.append(talents.empty() ? "null" : "'" + talents + "'");
        result.append(",");
        result.append(auras.empty() ? "null" : "'" + auras + "'");
        result.append(",");
        result.append(std::to_string(timestamp));
        result.append(")");

        return result;
    }
};

class EncounterLogSpell
{
private:
    std::uint_fast16_t map_id;
    std::uint_fast16_t instance_id;
    std::uint_fast32_t spell_id;
    std::uint_fast32_t caster_owner_guid;
    EncounterLogUnitType caster_owner_type;
    std::uint_fast32_t caster_guid;
    EncounterLogUnitType caster_type;
    std::uint_fast32_t target_owner_guid;
    EncounterLogUnitType target_owner_type;
    std::uint_fast32_t target_guid;
    EncounterLogUnitType target_type;
    std::uint_fast32_t cost;
    std::uint_fast32_t value;
    std::uint_fast32_t over_value;
    std::uint_fast32_t absorb_value;
    std::uint_fast32_t resist_value;
    std::uint_fast32_t block_value;
    bool is_critical;
    bool is_positive;
    EncounterLogSpellResult result;
    EncounterLogArbitraryFlag flag;
    std::uint_fast64_t timestamp;

public:
    EncounterLogSpell(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t spell_id,
        std::uint_fast32_t caster_owner_guid,
        EncounterLogUnitType caster_owner_type,
        std::uint_fast32_t caster_guid,
        EncounterLogUnitType caster_type,
        std::uint_fast32_t target_owner_guid,
        EncounterLogUnitType target_owner_type,
        std::uint_fast32_t target_guid,
        EncounterLogUnitType target_type,
        std::uint_fast32_t cost,
        std::uint_fast32_t value,
        std::uint_fast32_t over_value,
        std::uint_fast32_t absorb_value,
        std::uint_fast32_t resist_value,
        std::uint_fast32_t block_value,
        bool is_critical,
        bool is_positive,
        EncounterLogSpellResult result,
        EncounterLogArbitraryFlag flag,
        std::uint_fast64_t timestamp
    )
        : map_id{map_id}, instance_id{instance_id}, spell_id{spell_id}, caster_owner_guid{caster_owner_guid},
        caster_owner_type{caster_owner_type}, caster_guid{caster_guid}, caster_type{caster_type},
        target_owner_guid{target_owner_guid}, target_owner_type{target_owner_type}, target_guid{target_guid},
        target_type{target_type}, cost{cost}, value{value}, over_value{over_value}, absorb_value{absorb_value},
        resist_value{resist_value}, block_value{block_value}, is_critical{is_critical}, is_positive{is_positive},
        result{result}, flag{flag}, timestamp{timestamp}
    {}

    [[nodiscard]] std::string asString() const
    {
        std::string result_string{"("};

        bool has_caster_owner{caster_owner_guid != caster_guid && caster_owner_guid != 0};
        bool has_target_owner{target_owner_guid != target_guid && target_owner_guid != 0};

        result_string.append(std::to_string(map_id));
        result_string.append(",");
        result_string.append(std::to_string(instance_id));
        result_string.append(",");
        result_string.append(std::to_string(spell_id));
        result_string.append(",");
        result_string.append(has_caster_owner ? std::to_string(caster_owner_guid) : "0");
        result_string.append(",");
        result_string.append(has_caster_owner ? std::to_string(caster_owner_type) : "0");
        result_string.append(",");
        result_string.append(std::to_string(caster_guid));
        result_string.append(",");
        result_string.append(std::to_string(caster_type));
        result_string.append(",");
        result_string.append(has_target_owner ? std::to_string(target_owner_guid) : "0");
        result_string.append(",");
        result_string.append(has_target_owner ? std::to_string(target_owner_type) : "0");
        result_string.append(",");
        result_string.append(std::to_string(target_guid));
        result_string.append(",");
        result_string.append(std::to_string(target_type));
        result_string.append(",");
        result_string.append(std::to_string(cost));
        result_string.append(",");
        result_string.append(std::to_string(value));
        result_string.append(",");
        result_string.append(std::to_string(over_value));
        result_string.append(",");
        result_string.append(std::to_string(absorb_value));
        result_string.append(",");
        result_string.append(std::to_string(resist_value));
        result_string.append(",");
        result_string.append(std::to_string(block_value));
        result_string.append(",");
        result_string.append(is_critical ? "1" : "0");
        result_string.append(",");
        result_string.append(is_positive ? "1" : "0");
        result_string.append(",");
        result_string.append(std::to_string(result));
        result_string.append(",");
        result_string.append(std::to_string(flag));
        result_string.append(",");
        result_string.append(std::to_string(timestamp));
        result_string.append(")");

        return result_string;
    }
};

class EncounterLogMovement
{
private:
    std::uint_fast16_t map_id;
    std::uint_fast16_t instance_id;
    std::uint_fast32_t owner_guid;
    EncounterLogUnitType owner_type;
    std::uint_fast32_t guid;
    EncounterLogUnitType type;
    double x;
    double y;
    double z;
    double o;
    std::uint_fast64_t timestamp;

public:
    EncounterLogMovement(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t owner_guid,
        EncounterLogUnitType owner_type,
        std::uint_fast32_t guid,
        EncounterLogUnitType type,
        double x,
        double y,
        double z,
        double o,
        std::uint_fast64_t timestamp
    )
        : map_id{map_id}, instance_id{instance_id}, owner_guid{owner_guid}, owner_type{owner_type}, guid{guid},
        type{type}, x{x}, y{y}, z{z}, o{o}, timestamp{timestamp}
    {}

    [[nodiscard]] std::string asString() const
    {
        std::string result_string{"("};

        bool has_owner{owner_guid != guid && owner_guid != 0};

        result_string.append(std::to_string(map_id));
        result_string.append(",");
        result_string.append(std::to_string(instance_id));
        result_string.append(",");
        result_string.append(has_owner ? std::to_string(owner_guid) : "0");
        result_string.append(",");
        result_string.append(has_owner ? std::to_string(owner_type) : "0");
        result_string.append(",");
        result_string.append(std::to_string(guid));
        result_string.append(",");
        result_string.append(std::to_string(type));
        result_string.append(",");
        result_string.append(std::to_string(x));
        result_string.append(",");
        result_string.append(std::to_string(y));
        result_string.append(",");
        result_string.append(std::to_string(z));
        result_string.append(",");
        result_string.append(std::to_string(o));
        result_string.append(",");
        result_string.append(std::to_string(timestamp));
        result_string.append(")");

        return result_string;
    }
};

class EncounterLogDeath
{
private:
    std::uint_fast16_t map_id;
    std::uint_fast16_t instance_id;
    std::uint_fast32_t owner_guid;
    EncounterLogUnitType owner_type;
    std::uint_fast32_t guid;
    EncounterLogUnitType type;
    std::uint_fast32_t killer_owner_guid;
    EncounterLogUnitType killer_owner_type;
    std::uint_fast32_t killer_guid;
    EncounterLogUnitType killer_type;
    std::uint_fast64_t timestamp;

public:
    EncounterLogDeath(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t owner_guid,
        EncounterLogUnitType owner_type,
        std::uint_fast32_t guid,
        EncounterLogUnitType type,
        std::uint_fast32_t killer_owner_guid,
        EncounterLogUnitType killer_owner_type,
        std::uint_fast32_t killer_guid,
        EncounterLogUnitType killer_type,
        std::uint_fast64_t timestamp
    )
        : map_id{map_id}, instance_id{instance_id}, owner_guid{owner_guid}, owner_type{owner_type}, guid{guid},
        type{type}, killer_owner_guid{killer_owner_guid}, killer_owner_type{killer_owner_type},
        killer_guid{killer_guid}, killer_type{killer_type}, timestamp{timestamp}
    {}

    [[nodiscard]] std::string asString() const
    {
        std::string result_string{"("};

        bool has_owner{owner_guid != guid && owner_guid != 0};
        bool has_killer_owner{killer_owner_guid != killer_guid && killer_owner_guid != 0};

        result_string.append(std::to_string(map_id));
        result_string.append(",");
        result_string.append(std::to_string(instance_id));
        result_string.append(",");
        result_string.append(has_owner ? std::to_string(owner_guid) : "0");
        result_string.append(",");
        result_string.append(has_owner ? std::to_string(owner_type) : "0");
        result_string.append(",");
        result_string.append(std::to_string(guid));
        result_string.append(",");
        result_string.append(std::to_string(type));
        result_string.append(",");
        result_string.append(has_killer_owner ? std::to_string(killer_owner_guid) : "0");
        result_string.append(",");
        result_string.append(has_killer_owner ? std::to_string(killer_owner_type) : "0");
        result_string.append(",");
        result_string.append(std::to_string(killer_guid));
        result_string.append(",");
        result_string.append(std::to_string(killer_type));
        result_string.append(",");
        result_string.append(std::to_string(timestamp));
        result_string.append(")");

        return result_string;
    }
};

class Circumrota
{
private:
    std::mutex mutex;
    std::map<std::uint_fast32_t, EncounterLogCombat> combat_buffer;
    std::atomic<std::uint_fast32_t> combat_first{1};
    std::atomic<std::uint_fast32_t> combat_last{1};
    std::map<std::uint_fast32_t, EncounterLogSpell> spell_buffer;
    std::atomic<std::uint_fast32_t> spell_first{1};
    std::atomic<std::uint_fast32_t> spell_last{1};
    std::map<std::uint_fast32_t, EncounterLogMovement> movement_buffer;
    std::atomic<std::uint_fast32_t> movement_first{1};
    std::atomic<std::uint_fast32_t> movement_last{1};
    std::map<std::uint_fast32_t, EncounterLogDeath> death_buffer;
    std::atomic<std::uint_fast32_t> death_first{1};
    std::atomic<std::uint_fast32_t> death_last{1};

public:
    std::uint_fast32_t pushCombat(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t guid,
        EncounterLogState state,
        std::uint_fast32_t max_hp,
        std::uint_fast32_t hp,
        std::uint_fast32_t max_resource,
        std::uint_fast32_t resource,
        std::string gear,
        std::string talents,
        std::string auras,
        std::uint_fast64_t timestamp
    )
    {
        std::lock_guard<std::mutex> lock(mutex);

        combat_buffer.insert({combat_first, {
            map_id,
            instance_id,
            guid,
            state,
            max_hp,
            hp,
            max_resource,
            resource,
            std::move(gear),
            std::move(talents),
            std::move(auras),
            timestamp
        }});

        combat_first++;

        return combat_first;
    }

    [[nodiscard]] std::string retrieveCombats(std::size_t count)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (combat_buffer.empty()) {
            return "";
        }

        count = std::min(count, combat_buffer.size());

        std::string result;
        result.reserve(count * 40);

        std::uint_fast32_t i{1};

        while (i <= count) {
            result.append(combat_buffer.at(combat_last).asString());

            if (i != count) {
                result.append(",");
            }

            combat_buffer.erase(combat_last);
            i++;
            combat_last++;
        }

        return result;
    }

    [[nodiscard]] std::uint_fast32_t getCombatBufferSize()
    {
        std::lock_guard<std::mutex> lock(mutex);

        return combat_buffer.size();
    }

    std::uint_fast32_t pushSpell(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t spell_id,
        std::uint_fast32_t caster_owner_guid,
        EncounterLogUnitType caster_owner_type,
        std::uint_fast32_t caster_guid,
        EncounterLogUnitType caster_type,
        std::uint_fast32_t target_owner_guid,
        EncounterLogUnitType target_owner_type,
        std::uint_fast32_t target_guid,
        EncounterLogUnitType target_type,
        std::uint_fast32_t cost,
        std::uint_fast32_t value,
        std::uint_fast32_t over_value,
        std::uint_fast32_t absorb_value,
        std::uint_fast32_t resist_value,
        std::uint_fast32_t block_value,
        bool is_critical,
        bool is_positive,
        EncounterLogSpellResult result,
        EncounterLogArbitraryFlag flag,
        std::uint_fast64_t timestamp
    )
    {
        std::lock_guard<std::mutex> lock(mutex);

        spell_buffer.insert({spell_first, {
            map_id,
            instance_id,
            spell_id,
            caster_owner_guid,
            caster_owner_type,
            caster_guid,
            caster_type,
            target_owner_guid,
            target_owner_type,
            target_guid,
            target_type,
            cost,
            value,
            over_value,
            absorb_value,
            resist_value,
            block_value,
            is_critical,
            is_positive,
            result,
            flag,
            timestamp
        }});

        spell_first++;

        return spell_first;
    }

    [[nodiscard]] std::string retrieveSpells(std::size_t count)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (spell_buffer.empty()) {
            return "";
        }

        count = std::min(count, spell_buffer.size());

        std::string result;
        result.reserve(count * 40);

        std::uint_fast32_t i{1};

        while (i <= count) {
            result.append(spell_buffer.at(spell_last).asString());

            if (i != count) {
                result.append(",");
            }

            spell_buffer.erase(spell_last);
            i++;
            spell_last++;
        }

        return result;
    }

    [[nodiscard]] std::uint_fast32_t getSpellBufferSize()
    {
        std::lock_guard<std::mutex> lock(mutex);

        return spell_buffer.size();
    }

    std::uint_fast32_t pushMovement(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t owner_guid,
        EncounterLogUnitType owner_type,
        std::uint_fast32_t guid,
        EncounterLogUnitType type,
        double x,
        double y,
        double z,
        double o,
        std::uint_fast64_t timestamp
    )
    {
        std::lock_guard<std::mutex> lock(mutex);

        movement_buffer.insert({movement_first, {
            map_id,
            instance_id,
            owner_guid,
            owner_type,
            guid,
            type,
            x,
            y,
            z,
            o,
            timestamp
        }});

        movement_first++;

        return movement_first;
    }

    [[nodiscard]] std::string retrieveMovements(std::size_t count)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (movement_buffer.empty()) {
            return "";
        }

        count = std::min(count, movement_buffer.size());

        std::string result;
        result.reserve(count * 40);

        std::uint_fast32_t i{1};

        while (i <= count) {
            result.append(movement_buffer.at(movement_last).asString());

            if (i != count) {
                result.append(",");
            }

            movement_buffer.erase(movement_last);
            i++;
            movement_last++;
        }

        return result;
    }

    [[nodiscard]] std::uint_fast32_t getMovementBufferSize()
    {
        std::lock_guard<std::mutex> lock(mutex);

        return movement_buffer.size();
    }

    std::uint_fast32_t pushDeath(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t owner_guid,
        EncounterLogUnitType owner_type,
        std::uint_fast32_t guid,
        EncounterLogUnitType type,
        std::uint_fast32_t killer_owner_guid,
        EncounterLogUnitType killer_owner_type,
        std::uint_fast32_t killer_guid,
        EncounterLogUnitType killer_type,
        std::uint_fast64_t timestamp
    )
    {
        std::lock_guard<std::mutex> lock(mutex);

        death_buffer.insert({death_first, {
            map_id,
            instance_id,
            owner_guid,
            owner_type,
            guid,
            type,
            killer_owner_guid,
            killer_owner_type,
            killer_guid,
            killer_type,
            timestamp
        }});

        death_first++;

        return death_first;
    }

    [[nodiscard]] std::string retrieveDeaths(std::size_t count)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (death_buffer.empty()) {
            return "";
        }

        count = std::min(count, death_buffer.size());

        std::string result;
        result.reserve(count * 40);

        std::uint_fast32_t i{1};

        while (i <= count) {
            result.append(death_buffer.at(death_last).asString());

            if (i != count) {
                result.append(",");
            }

            death_buffer.erase(death_last);
            i++;
            death_last++;
        }

        return result;
    }

    [[nodiscard]] std::uint_fast32_t getDeathBufferSize()
    {
        std::lock_guard<std::mutex> lock(mutex);

        return death_buffer.size();
    }
};

class EncounterLogs
{
private:
    std::uint_fast32_t m_map_id;
    std::uint_fast32_t m_instance_id;
    std::uint_fast64_t m_timestamp;
    std::thread m_saver;
    std::atomic<bool> m_stop_saver{false};
    Circumrota m_buffer;

public:
    EncounterLogs(
        std::uint_fast32_t map_id,
        std::uint_fast32_t instance_id,
        std::uint_fast64_t timestamp,
        bool with_record = true
    ) : m_map_id{map_id}, m_instance_id{instance_id}, m_timestamp{timestamp}
    {
        if (with_record) {
            LoginDatabase.Execute(
                "INSERT INTO encounter_logs (map_id, instance_id, timestamp) VALUES (" +
                std::to_string(m_map_id) + "," + std::to_string(m_instance_id) + "," + std::to_string(m_timestamp) +
                ")"
            );
        }

        m_saver = std::thread([&]() {
            while (!m_stop_saver) {
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(
                        sConfigMgr->GetOption<std::uint_fast32_t>("EncounterLogs.System.SaveFrequency", 1000)
                    )
                );

                auto batch_size = sConfigMgr->GetOption<std::uint_fast32_t>("EncounterLogs.System.BatchSize", 1000);

                auto combat_buffer_size = m_buffer.getCombatBufferSize();
                auto spell_buffer_size = m_buffer.getSpellBufferSize();
                auto movement_buffer_size = m_buffer.getMovementBufferSize();
                auto death_buffer_size = m_buffer.getDeathBufferSize();

                std::uint_fast32_t combat_count{0};
                std::uint_fast32_t combat_query_count{1};

                if (combat_buffer_size < batch_size) {
                    combat_count = combat_buffer_size;
                } else {
                    combat_count = batch_size;
                    combat_query_count = combat_buffer_size / batch_size;
                }

                if (combat_count > 0) {
                    for (std::uint_fast32_t i = 1; i <= combat_query_count; i++) {
                        LoginDatabase.Execute(
                            "INSERT INTO encounter_log_combats (map_id, instance_id, guid, state, max_hp, hp, max_resource, resource, gear, talents, auras, timestamp) VALUES " +
                            m_buffer.retrieveCombats(combat_count)
                        );
                    }
                }

                std::uint_fast32_t spell_count{0};
                std::uint_fast32_t spell_query_count{1};

                if (spell_buffer_size < batch_size) {
                    spell_count = spell_buffer_size;
                } else {
                    spell_count = batch_size;
                    spell_query_count = spell_buffer_size / batch_size;
                }

                if (spell_count > 0) {
                    for (std::uint_fast32_t i = 1; i <= spell_query_count; i++) {
                        LoginDatabase.Execute(
                            "INSERT INTO encounter_log_spells (map_id, instance_id, spell_id, caster_owner_guid, caster_owner_type, caster_guid, caster_type, target_owner_guid, target_owner_type, target_guid, target_type, cost, value, over_value, absorb_value, resist_value, block_value, is_critical, is_positive, result, flag, timestamp) VALUES " +
                            m_buffer.retrieveSpells(spell_count)
                        );
                    }
                }

                std::uint_fast32_t movement_count{0};
                std::uint_fast32_t movement_query_count{1};

                if (movement_buffer_size < batch_size) {
                    movement_count = movement_buffer_size;
                } else {
                    movement_count = batch_size;
                    movement_query_count = movement_buffer_size / batch_size;
                }

                if (movement_count > 0) {
                    for (std::uint_fast32_t i = 1; i <= movement_query_count; i++) {
                        LoginDatabase.Execute(
                            "INSERT INTO encounter_log_movements (map_id, instance_id, owner_guid, owner_type, guid, type, x, y, z, o, `timestamp`) VALUES " +
                            m_buffer.retrieveMovements(movement_count)
                        );
                    }
                }

                std::uint_fast32_t death_count{0};
                std::uint_fast32_t death_query_count{1};

                if (death_buffer_size < batch_size) {
                    death_count = death_buffer_size;
                } else {
                    death_count = batch_size;
                    death_query_count = death_buffer_size / batch_size;
                }

                if (death_count > 0) {
                    for (std::uint_fast32_t i = 1; i <= death_query_count; i++) {
                        LoginDatabase.Execute(
                            "INSERT INTO encounter_log_deaths (map_id, instance_id, owner_guid, owner_type, guid, type, killer_owner_guid, killer_owner_type, killer_guid, killer_type, `timestamp`) VALUES " +
                            m_buffer.retrieveDeaths(death_count)
                        );
                    }
                }
            }
        });
    }

    ~EncounterLogs()
    {
        m_stop_saver = true;

        m_saver.join();
    }

    Circumrota &getBuffer()
    {
        return m_buffer;
    }
};

class EncounterLogHelpers
{
public:
    [[nodiscard]] static std::uint_fast32_t getGuid(Unit *unit)
    {
        if (Creature *creature = unit->ToCreature()) {
            return creature->GetSpawnId();
        }

        return unit->GetGUID().GetCounter();
    }

    [[nodiscard]] static bool isNotEngagedWithPlayer(Unit *unit)
    {
        if (unit->IsPlayer()) {
            return false;
        }

        return std::ranges::none_of(unit->GetThreatMgr().GetThreatList(), [](HostileReference *ref) {
            return getOwnerRecursively(ref->GetVictim())->IsPlayer();
        });
    }

    [[nodiscard]] static Unit *getOwnerRecursively(Unit *unit)
    {
        if (Unit *owner = unit->GetOwner()) {
            return getOwnerRecursively(owner);
        }

        return unit;
    }

    [[nodiscard]] static EncounterLogUnitType getUnitType(Unit *unit)
    {
        if (unit->IsPlayer()) {
            return ENCOUNTER_LOG_UNIT_PLAYER;
        }

        if (unit->IsPet() || unit->IsHunterPet()) {
            return ENCOUNTER_LOG_UNIT_PET;
        }

        if (unit->IsTotem()) {
            return ENCOUNTER_LOG_UNIT_TOTEM;
        }

        if (unit->IsSummon()) {
            return ENCOUNTER_LOG_UNIT_SUMMON;
        }

        if (unit->IsVehicle()) {
            return ENCOUNTER_LOG_UNIT_VEHICLE;
        }

        if (unit->IsWorldObject()) {
            return ENCOUNTER_LOG_UNIT_OBJECT;
        }

        return ENCOUNTER_LOG_UNIT_CREATURE;
    }

    [[nodiscard]] static std::uint_fast64_t getTimestamp()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }

    [[nodiscard]] static EncounterLogSpellResult getMeleeResult(MeleeHitOutcome result)
    {
        switch (result) {
            case MELEE_HIT_EVADE:
                return ENCOUNTER_LOG_SPELL_RESULT_EVADE;
            case MELEE_HIT_MISS:
                return ENCOUNTER_LOG_SPELL_RESULT_MISS;
            case MELEE_HIT_DODGE:
                return ENCOUNTER_LOG_SPELL_RESULT_DODGE;
            case MELEE_HIT_BLOCK:
                return ENCOUNTER_LOG_SPELL_RESULT_BLOCK;
            case MELEE_HIT_PARRY:
                return ENCOUNTER_LOG_SPELL_RESULT_PARRY;
            case MELEE_HIT_GLANCING:
                return ENCOUNTER_LOG_SPELL_RESULT_GLANCING;
            case MELEE_HIT_CRIT:
                return ENCOUNTER_LOG_SPELL_RESULT_CRIT;
            case MELEE_HIT_CRUSHING:
                return ENCOUNTER_LOG_SPELL_RESULT_CRUSHING;
            case MELEE_HIT_NORMAL:
                return ENCOUNTER_LOG_SPELL_RESULT_NONE;
        }
    }

    [[nodiscard]] static EncounterLogSpellResult getSpellResult(SpellMissInfo result)
    {
        switch (result) {
            case SPELL_MISS_NONE:
                return ENCOUNTER_LOG_SPELL_RESULT_NONE;
            case SPELL_MISS_MISS:
                return ENCOUNTER_LOG_SPELL_RESULT_MISS;
            case SPELL_MISS_RESIST:
                return ENCOUNTER_LOG_SPELL_RESULT_RESIST;
            case SPELL_MISS_DODGE:
                return ENCOUNTER_LOG_SPELL_RESULT_DODGE;
            case SPELL_MISS_PARRY:
                return ENCOUNTER_LOG_SPELL_RESULT_PARRY;
            case SPELL_MISS_BLOCK:
                return ENCOUNTER_LOG_SPELL_RESULT_BLOCK;
            case SPELL_MISS_EVADE:
                return ENCOUNTER_LOG_SPELL_RESULT_EVADE;
            case SPELL_MISS_IMMUNE:
            case SPELL_MISS_IMMUNE2:
                return ENCOUNTER_LOG_SPELL_RESULT_IMMUNE;
            case SPELL_MISS_DEFLECT:
                return ENCOUNTER_LOG_SPELL_RESULT_DEFLECT;
            case SPELL_MISS_ABSORB:
                return ENCOUNTER_LOG_SPELL_RESULT_ABSORB;
            case SPELL_MISS_REFLECT:
                return ENCOUNTER_LOG_SPELL_RESULT_REFLECT;
        }
    }

    [[nodiscard]] static EncounterLogArbitraryFlag getMeleeFlag(WeaponAttackType type)
    {
        switch (type) {
            case BASE_ATTACK:
                return ENCOUNTER_LOG_ARBITRARY_FLAG_BASE_ATTACK;
            case OFF_ATTACK:
                return ENCOUNTER_LOG_ARBITRARY_FLAG_OFF_ATTACK;
            case RANGED_ATTACK:
                return ENCOUNTER_LOG_ARBITRARY_FLAG_RANGED_ATTACK;
            case MAX_ATTACK:
                return ENCOUNTER_LOG_ARBITRARY_FLAG_MAX_ATTACK;
        }
    }

    [[nodiscard]] static inline bool shouldNotBeTracked(Unit *unit, bool check_threat_list = true);
};

class EncounterLogActiveInstanceTracker
{
private:
    std::thread m_tracker;
    std::atomic<bool> m_stop_tracker{false};
    // this is not protected from data race
    // DO NOT WORK WITH THIS VARIABLE ANYWHERE OUTSIDE OF THREAD
    std::unordered_map<std::uint_fast32_t, std::uint_fast32_t> m_active_instances{};

public:
    EncounterLogActiveInstanceTracker()
    {
        QueryResult instances = CharacterDatabase.Query("SELECT id, map FROM instance");

        if (instances) {
            do {
                Field *instance = instances->Fetch();

                m_active_instances.insert(
                    {
                        instance[0].Get<std::uint_fast32_t>(),
                        instance[1].Get<std::uint_fast32_t>()
                    }
                );

            } while (instances->NextRow());
        }

        m_tracker = std::thread([&]() {
            while (!m_stop_tracker) {
                std::this_thread::sleep_for(60s);

                QueryResult instances = CharacterDatabase.Query("SELECT id, map FROM instance");

                std::unordered_map<std::uint_fast32_t, std::uint_fast32_t> expired_instances = m_active_instances;

                if (instances) {
                    do {
                        Field *instance = instances->Fetch();

                        std::uint_fast32_t instance_id = instance[0].Get<std::uint_fast32_t>();

                        if (expired_instances.count(instance_id)) {
                            expired_instances.erase(instance_id);
                        } else {
                            m_active_instances.insert({instance_id, instance[1].Get<std::uint_fast32_t>()});
                        }

                    } while (instances->NextRow());
                }

                std::uint_fast64_t timestamp = EncounterLogHelpers::getTimestamp();

                for (auto [instance_id, map_id]: expired_instances) {
                    LoginDatabase.Execute(
                        "INSERT INTO encounter_log_instance_resets (map_id, instance_id, timestamp) VALUES (" +
                        std::to_string(map_id) + "," + std::to_string(instance_id) + "," +
                        std::to_string(timestamp) + ")"
                    );

                    m_active_instances.erase(instance_id);
                }
            }
        });
    }

    ~EncounterLogActiveInstanceTracker()
    {
        m_stop_tracker = true;

        m_tracker.join();
    }
};

class EncounterLogManager
{
private:
    static std::unordered_map<std::uint_fast32_t, std::unique_ptr<EncounterLogs>> m_logs;
    static std::unordered_map<std::uint_fast32_t, bool> m_players_in_combat;
    static std::unique_ptr<EncounterLogActiveInstanceTracker> m_instance_tracker;

public:
    static void init()
    {
        QueryResult instances = CharacterDatabase.Query("SELECT id, map FROM instance");

        if (instances) {
            do {
                Field *instance = instances->Fetch();

                newLog(
                    instance[1].Get<std::uint_fast32_t>(),
                    instance[0].Get<std::uint_fast32_t>(),
                    0,
                    false
                );
            } while (instances->NextRow());
        }
    }

    static void newLog(
        std::uint_fast32_t map_id,
        std::uint_fast32_t instance_id,
        std::uint_fast64_t timestamp,
        bool with_record = true
    )
    {
        if (m_logs.contains(instance_id)) {
            return;
        }

        m_logs.insert({instance_id, std::make_unique<EncounterLogs>(map_id, instance_id, timestamp, with_record)});
    }

    static void startInstanceTracker()
    {
        m_instance_tracker = std::make_unique<EncounterLogActiveInstanceTracker>();
    }

    [[nodiscard]] static EncounterLogs *getLog(std::uint_fast32_t instance_id)
    {
        return m_logs.at(instance_id).get();
    }

    static bool hasLog(std::uint_fast32_t instance_id)
    {
        return m_logs.contains(instance_id);
    }

    [[nodiscard]] static bool dungeonsDisabled()
    {
        auto scope = sConfigMgr->GetOption<std::uint_fast32_t>("EncounterLogs.Logging.Scope", 3);

        return scope != ENCOUNTER_LOG_SCOPE_EVERYTHING && scope != ENCOUNTER_LOG_SCOPE_DUNGEON;
    }

    [[nodiscard]] static bool raidsDisabled()
    {
        auto scope = sConfigMgr->GetOption<std::uint_fast32_t>("EncounterLogs.Logging.Scope", 3);

        return scope != ENCOUNTER_LOG_SCOPE_EVERYTHING && scope != ENCOUNTER_LOG_SCOPE_RAID;
    }

    [[nodiscard]] static bool creatureIsTracked(Unit *unit)
    {
        auto config = sConfigMgr->GetOption<std::string>("EncounterLogs.Logging.OpenWorld", "");

        if (config.empty()) {
            return false;
        }

        std::map<std::uint_fast32_t, bool> creatures;

        const char *delimiter_c = ";";

        char *argument = std::strtok((char *) config.c_str(), ";");

        while (argument) {
            creatures.insert({std::stoi(argument), true});

            argument = std::strtok(nullptr, delimiter_c);
        }

        if (creatures.count(EncounterLogHelpers::getGuid(unit))) {
            return true;
        }

        return false;
    }

    static void registerPlayerCombat(Player *player)
    {
        m_players_in_combat.insert({player->GetGUID().GetCounter(), true});
    }

    static void deletePlayerCombat(Player *player)
    {
        m_players_in_combat.erase(player->GetGUID().GetCounter());
    }

    [[nodiscard]] static bool playerNotInCombat(Player *player)
    {
        return m_players_in_combat.contains(player->GetGUID().GetCounter());
    }
};

inline bool EncounterLogHelpers::shouldNotBeTracked(Unit *unit, bool check_threat_list)
{
    if (!unit->GetMap()->IsDungeon() && !EncounterLogManager::creatureIsTracked(unit)) {
        return true;
    }

    if (unit->GetMap()->IsRaid() && EncounterLogManager::raidsDisabled()) {
        return true;
    }

    if (unit->GetMap()->IsNonRaidDungeon() && EncounterLogManager::dungeonsDisabled()) {
        return true;
    }

    if (!EncounterLogManager::hasLog(unit->GetInstanceId())) {
        return true;
    }

    if (check_threat_list && EncounterLogHelpers::isNotEngagedWithPlayer(unit)) {
        return true;
    }

    return false;
}

#endif //AZEROTHCORE_ENCOUNTERLOGMANAGER_H
