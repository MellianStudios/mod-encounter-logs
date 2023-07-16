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
#include "EncounterLogDefines.h"

// Note that these data types here are irrelevant since on most of modern computers all of them will be implemented as "long"

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
    int flag;
    EncounterLogArbitraryFlag arbitrary_flag;
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
        int flag,
        EncounterLogArbitraryFlag arbitrary_flag,
        std::uint_fast64_t timestamp
    )
        : map_id{map_id}, instance_id{instance_id}, spell_id{spell_id}, caster_owner_guid{caster_owner_guid},
        caster_owner_type{caster_owner_type}, caster_guid{caster_guid}, caster_type{caster_type},
        target_owner_guid{target_owner_guid}, target_owner_type{target_owner_type}, target_guid{target_guid},
        target_type{target_type}, cost{cost}, value{value}, over_value{over_value}, absorb_value{absorb_value},
        resist_value{resist_value}, block_value{block_value}, is_critical{is_critical}, is_positive{is_positive},
        result{result}, flag{flag}, arbitrary_flag{arbitrary_flag}, timestamp{timestamp}
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
        result_string.append(std::to_string(arbitrary_flag));
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
        EncounterLogSpellFlag flag,
        EncounterLogArbitraryFlag arbitrary_flag,
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
            arbitrary_flag,
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
                            "INSERT INTO encounter_log_spells (map_id, instance_id, spell_id, caster_owner_guid, caster_owner_type, caster_guid, caster_type, target_owner_guid, target_owner_type, target_guid, target_type, cost, value, over_value, absorb_value, resist_value, block_value, is_critical, is_positive, result, flag, arbitrary_flag, timestamp) VALUES " +
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
            if (
                creature->IsSummon()
                ||
                creature->IsPet()
                ||
                creature->IsHunterPet()
                ||
                creature->IsTotem()
                ||
                creature->IsVehicle()
                ) {
                return creature->GetCreatureTemplate()->Entry;
            }

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

    [[nodiscard]] static EncounterLogSpellFlag getMeleeFlag(WeaponAttackType type)
    {
        switch (type) {
            case BASE_ATTACK:
                return ENCOUNTER_LOG_FLAG_BASE_ATTACK;
            case OFF_ATTACK:
                return ENCOUNTER_LOG_FLAG_OFF_ATTACK;
            case RANGED_ATTACK:
                return ENCOUNTER_LOG_FLAG_RANGED_ATTACK;
            case MAX_ATTACK:
                return ENCOUNTER_LOG_FLAG_MAX_ATTACK;
        }
    }

    [[nodiscard]] static EncounterLogSpellFlag getPowerFlag(Powers power)
    {
        switch (power) {
            case POWER_MANA:
                return ENCOUNTER_LOG_FLAG_POWER_MANA;
            case POWER_RAGE:
                return ENCOUNTER_LOG_FLAG_POWER_RAGE;
            case POWER_FOCUS:
                return ENCOUNTER_LOG_FLAG_POWER_FOCUS;
            case POWER_ENERGY:
                return ENCOUNTER_LOG_FLAG_POWER_ENERGY;
            case POWER_HAPPINESS:
                return ENCOUNTER_LOG_FLAG_POWER_HAPPINESS;
            case POWER_RUNE:
                return ENCOUNTER_LOG_FLAG_POWER_RUNE;
            case POWER_RUNIC_POWER:
                return ENCOUNTER_LOG_FLAG_POWER_RUNIC_POWER;
            case MAX_POWERS:
                return ENCOUNTER_LOG_FLAG_MAX_POWERS;
            case POWER_ALL:
                return ENCOUNTER_LOG_FLAG_POWER_ALL;
            case POWER_HEALTH:
                return ENCOUNTER_LOG_FLAG_POWER_HEALTH;
        }
    }

    [[nodiscard]] static EncounterLogSpellFlag getSpellSchoolFlag(SpellSchoolMask mask)
    {
        switch (mask) {
            case SPELL_SCHOOL_MASK_NONE:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_NONE;
            case SPELL_SCHOOL_MASK_NORMAL:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_NORMAL;
            case SPELL_SCHOOL_MASK_HOLY:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_HOLY;
            case SPELL_SCHOOL_MASK_FIRE:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_FIRE;
            case SPELL_SCHOOL_MASK_NATURE:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_NATURE;
            case SPELL_SCHOOL_MASK_FROST:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_FROST;
            case SPELL_SCHOOL_MASK_SHADOW:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_SHADOW;
            case SPELL_SCHOOL_MASK_ARCANE:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_ARCANE;
            case SPELL_SCHOOL_MASK_SPELL:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_SPELL;
            case SPELL_SCHOOL_MASK_MAGIC:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_MAGIC;
            case SPELL_SCHOOL_MASK_ALL:
                return ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_ALL;
        }
    }

    [[nodiscard]] static EncounterLogSpellFlag getEnvironmentalFlag(EnviromentalDamage flag)
    {
        switch (flag) {
            case DAMAGE_EXHAUSTED:
                return ENCOUNTER_LOG_FLAG_DAMAGE_EXHAUSTED;
            case DAMAGE_DROWNING:
                return ENCOUNTER_LOG_FLAG_DAMAGE_DROWNING;
            case DAMAGE_FALL:
                return ENCOUNTER_LOG_FLAG_DAMAGE_FALL;
            case DAMAGE_LAVA:
                return ENCOUNTER_LOG_FLAG_DAMAGE_LAVA;
            case DAMAGE_SLIME:
                return ENCOUNTER_LOG_FLAG_DAMAGE_SLIME;
            case DAMAGE_FIRE:
                return ENCOUNTER_LOG_FLAG_DAMAGE_FIRE;
            case DAMAGE_FALL_TO_VOID:
                return ENCOUNTER_LOG_FLAG_DAMAGE_FALL_TO_VOID;
        }
    }

    [[nodiscard]] static EncounterLogSpellFlag getAuraTypeFlag(AuraType type)
    {
        switch (type) {
            case SPELL_AURA_NONE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_NONE;
            case SPELL_AURA_BIND_SIGHT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_BIND_SIGHT;
            case SPELL_AURA_MOD_POSSESS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POSSESS;
            case SPELL_AURA_PERIODIC_DAMAGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_DAMAGE;
            case SPELL_AURA_DUMMY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_DUMMY;
            case SPELL_AURA_MOD_CONFUSE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CONFUSE;
            case SPELL_AURA_MOD_CHARM:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CHARM;
            case SPELL_AURA_MOD_FEAR:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FEAR;
            case SPELL_AURA_PERIODIC_HEAL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_HEAL;
            case SPELL_AURA_MOD_ATTACKSPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKSPEED;
            case SPELL_AURA_MOD_THREAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_THREAT;
            case SPELL_AURA_MOD_TAUNT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TAUNT;
            case SPELL_AURA_MOD_STUN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STUN;
            case SPELL_AURA_MOD_DAMAGE_DONE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE;
            case SPELL_AURA_MOD_DAMAGE_TAKEN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_TAKEN;
            case SPELL_AURA_DAMAGE_SHIELD:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_DAMAGE_SHIELD;
            case SPELL_AURA_MOD_STEALTH:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STEALTH;
            case SPELL_AURA_MOD_STEALTH_DETECT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STEALTH_DETECT;
            case SPELL_AURA_MOD_INVISIBILITY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INVISIBILITY;
            case SPELL_AURA_MOD_INVISIBILITY_DETECT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INVISIBILITY_DETECT;
            case SPELL_AURA_OBS_MOD_HEALTH:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_OBS_MOD_HEALTH;
            case SPELL_AURA_OBS_MOD_POWER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_OBS_MOD_POWER;
            case SPELL_AURA_MOD_RESISTANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RESISTANCE;
            case SPELL_AURA_PERIODIC_TRIGGER_SPELL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_TRIGGER_SPELL;
            case SPELL_AURA_PERIODIC_ENERGIZE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_ENERGIZE;
            case SPELL_AURA_MOD_PACIFY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PACIFY;
            case SPELL_AURA_MOD_ROOT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ROOT;
            case SPELL_AURA_MOD_SILENCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SILENCE;
            case SPELL_AURA_REFLECT_SPELLS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_REFLECT_SPELLS;
            case SPELL_AURA_MOD_STAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STAT;
            case SPELL_AURA_MOD_SKILL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SKILL;
            case SPELL_AURA_MOD_INCREASE_SPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_SPEED;
            case SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED;
            case SPELL_AURA_MOD_DECREASE_SPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DECREASE_SPEED;
            case SPELL_AURA_MOD_INCREASE_HEALTH:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_HEALTH;
            case SPELL_AURA_MOD_INCREASE_ENERGY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_ENERGY;
            case SPELL_AURA_MOD_SHAPESHIFT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SHAPESHIFT;
            case SPELL_AURA_EFFECT_IMMUNITY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_EFFECT_IMMUNITY;
            case SPELL_AURA_STATE_IMMUNITY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_STATE_IMMUNITY;
            case SPELL_AURA_SCHOOL_IMMUNITY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SCHOOL_IMMUNITY;
            case SPELL_AURA_DAMAGE_IMMUNITY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_DAMAGE_IMMUNITY;
            case SPELL_AURA_DISPEL_IMMUNITY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_DISPEL_IMMUNITY;
            case SPELL_AURA_PROC_TRIGGER_SPELL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PROC_TRIGGER_SPELL;
            case SPELL_AURA_PROC_TRIGGER_DAMAGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PROC_TRIGGER_DAMAGE;
            case SPELL_AURA_TRACK_CREATURES:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_TRACK_CREATURES;
            case SPELL_AURA_TRACK_RESOURCES:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_TRACK_RESOURCES;
            case SPELL_AURA_46:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_46;
            case SPELL_AURA_MOD_PARRY_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PARRY_PERCENT;
            case SPELL_AURA_PERIODIC_TRIGGER_SPELL_FROM_CLIENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_TRIGGER_SPELL_FROM_CLIENT;
            case SPELL_AURA_MOD_DODGE_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DODGE_PERCENT;
            case SPELL_AURA_MOD_CRITICAL_HEALING_AMOUNT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRITICAL_HEALING_AMOUNT;
            case SPELL_AURA_MOD_BLOCK_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BLOCK_PERCENT;
            case SPELL_AURA_MOD_WEAPON_CRIT_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_WEAPON_CRIT_PERCENT;
            case SPELL_AURA_PERIODIC_LEECH:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_LEECH;
            case SPELL_AURA_MOD_HIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HIT_CHANCE;
            case SPELL_AURA_MOD_SPELL_HIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_HIT_CHANCE;
            case SPELL_AURA_TRANSFORM:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_TRANSFORM;
            case SPELL_AURA_MOD_SPELL_CRIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_CRIT_CHANCE;
            case SPELL_AURA_MOD_INCREASE_SWIM_SPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_SWIM_SPEED;
            case SPELL_AURA_MOD_DAMAGE_DONE_CREATURE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE_CREATURE;
            case SPELL_AURA_MOD_PACIFY_SILENCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PACIFY_SILENCE;
            case SPELL_AURA_MOD_SCALE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SCALE;
            case SPELL_AURA_PERIODIC_HEALTH_FUNNEL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_HEALTH_FUNNEL;
            case SPELL_AURA_63:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_63;
            case SPELL_AURA_PERIODIC_MANA_LEECH:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_MANA_LEECH;
            case SPELL_AURA_MOD_CASTING_SPEED_NOT_STACK:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CASTING_SPEED_NOT_STACK;
            case SPELL_AURA_FEIGN_DEATH:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_FEIGN_DEATH;
            case SPELL_AURA_MOD_DISARM:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DISARM;
            case SPELL_AURA_MOD_STALKED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STALKED;
            case SPELL_AURA_SCHOOL_ABSORB:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SCHOOL_ABSORB;
            case SPELL_AURA_EXTRA_ATTACKS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_EXTRA_ATTACKS;
            case SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL;
            case SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT;
            case SPELL_AURA_MOD_POWER_COST_SCHOOL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POWER_COST_SCHOOL;
            case SPELL_AURA_REFLECT_SPELLS_SCHOOL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_REFLECT_SPELLS_SCHOOL;
            case SPELL_AURA_MOD_LANGUAGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_LANGUAGE;
            case SPELL_AURA_FAR_SIGHT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_FAR_SIGHT;
            case SPELL_AURA_MECHANIC_IMMUNITY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MECHANIC_IMMUNITY;
            case SPELL_AURA_MOUNTED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOUNTED;
            case SPELL_AURA_MOD_DAMAGE_PERCENT_DONE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
            case SPELL_AURA_MOD_PERCENT_STAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PERCENT_STAT;
            case SPELL_AURA_SPLIT_DAMAGE_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SPLIT_DAMAGE_PCT;
            case SPELL_AURA_WATER_BREATHING:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_WATER_BREATHING;
            case SPELL_AURA_MOD_BASE_RESISTANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BASE_RESISTANCE;
            case SPELL_AURA_MOD_REGEN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_REGEN;
            case SPELL_AURA_MOD_POWER_REGEN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POWER_REGEN;
            case SPELL_AURA_CHANNEL_DEATH_ITEM:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_CHANNEL_DEATH_ITEM;
            case SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
            case SPELL_AURA_MOD_HEALTH_REGEN_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALTH_REGEN_PERCENT;
            case SPELL_AURA_PERIODIC_DAMAGE_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_DAMAGE_PERCENT;
            case SPELL_AURA_90:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_90;
            case SPELL_AURA_MOD_DETECT_RANGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DETECT_RANGE;
            case SPELL_AURA_PREVENTS_FLEEING:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PREVENTS_FLEEING;
            case SPELL_AURA_MOD_UNATTACKABLE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_UNATTACKABLE;
            case SPELL_AURA_INTERRUPT_REGEN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_INTERRUPT_REGEN;
            case SPELL_AURA_GHOST:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_GHOST;
            case SPELL_AURA_SPELL_MAGNET:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SPELL_MAGNET;
            case SPELL_AURA_MANA_SHIELD:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MANA_SHIELD;
            case SPELL_AURA_MOD_SKILL_TALENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SKILL_TALENT;
            case SPELL_AURA_MOD_ATTACK_POWER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACK_POWER;
            case SPELL_AURA_AURAS_VISIBLE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_AURAS_VISIBLE;
            case SPELL_AURA_MOD_RESISTANCE_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RESISTANCE_PCT;
            case SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS;
            case SPELL_AURA_MOD_TOTAL_THREAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TOTAL_THREAT;
            case SPELL_AURA_WATER_WALK:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_WATER_WALK;
            case SPELL_AURA_FEATHER_FALL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_FEATHER_FALL;
            case SPELL_AURA_HOVER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_HOVER;
            case SPELL_AURA_ADD_FLAT_MODIFIER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ADD_FLAT_MODIFIER;
            case SPELL_AURA_ADD_PCT_MODIFIER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ADD_PCT_MODIFIER;
            case SPELL_AURA_ADD_TARGET_TRIGGER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ADD_TARGET_TRIGGER;
            case SPELL_AURA_MOD_POWER_REGEN_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POWER_REGEN_PERCENT;
            case SPELL_AURA_ADD_CASTER_HIT_TRIGGER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ADD_CASTER_HIT_TRIGGER;
            case SPELL_AURA_OVERRIDE_CLASS_SCRIPTS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_OVERRIDE_CLASS_SCRIPTS;
            case SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN;
            case SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT;
            case SPELL_AURA_MOD_HEALING:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING;
            case SPELL_AURA_MOD_REGEN_DURING_COMBAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_REGEN_DURING_COMBAT;
            case SPELL_AURA_MOD_MECHANIC_RESISTANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MECHANIC_RESISTANCE;
            case SPELL_AURA_MOD_HEALING_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING_PCT;
            case SPELL_AURA_119:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_119;
            case SPELL_AURA_UNTRACKABLE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_UNTRACKABLE;
            case SPELL_AURA_EMPATHY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_EMPATHY;
            case SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT;
            case SPELL_AURA_MOD_TARGET_RESISTANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TARGET_RESISTANCE;
            case SPELL_AURA_MOD_RANGED_ATTACK_POWER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_ATTACK_POWER;
            case SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN;
            case SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT;
            case SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS;
            case SPELL_AURA_MOD_POSSESS_PET:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POSSESS_PET;
            case SPELL_AURA_MOD_SPEED_ALWAYS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPEED_ALWAYS;
            case SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS;
            case SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS;
            case SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT;
            case SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
            case SPELL_AURA_MOD_MANA_REGEN_INTERRUPT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MANA_REGEN_INTERRUPT;
            case SPELL_AURA_MOD_HEALING_DONE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING_DONE;
            case SPELL_AURA_MOD_HEALING_DONE_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING_DONE_PERCENT;
            case SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE;
            case SPELL_AURA_MOD_MELEE_HASTE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_HASTE;
            case SPELL_AURA_FORCE_REACTION:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_FORCE_REACTION;
            case SPELL_AURA_MOD_RANGED_HASTE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_HASTE;
            case SPELL_AURA_MOD_RANGED_AMMO_HASTE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_AMMO_HASTE;
            case SPELL_AURA_MOD_BASE_RESISTANCE_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BASE_RESISTANCE_PCT;
            case SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE;
            case SPELL_AURA_SAFE_FALL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SAFE_FALL;
            case SPELL_AURA_MOD_PET_TALENT_POINTS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PET_TALENT_POINTS;
            case SPELL_AURA_ALLOW_TAME_PET_TYPE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ALLOW_TAME_PET_TYPE;
            case SPELL_AURA_MECHANIC_IMMUNITY_MASK:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MECHANIC_IMMUNITY_MASK;
            case SPELL_AURA_RETAIN_COMBO_POINTS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_RETAIN_COMBO_POINTS;
            case SPELL_AURA_REDUCE_PUSHBACK:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_REDUCE_PUSHBACK;
            case SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT;
            case SPELL_AURA_TRACK_STEALTHED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_TRACK_STEALTHED;
            case SPELL_AURA_MOD_DETECTED_RANGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DETECTED_RANGE;
            case SPELL_AURA_SPLIT_DAMAGE_FLAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SPLIT_DAMAGE_FLAT;
            case SPELL_AURA_MOD_STEALTH_LEVEL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STEALTH_LEVEL;
            case SPELL_AURA_MOD_WATER_BREATHING:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_WATER_BREATHING;
            case SPELL_AURA_MOD_REPUTATION_GAIN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_REPUTATION_GAIN;
            case SPELL_AURA_PET_DAMAGE_MULTI:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PET_DAMAGE_MULTI;
            case SPELL_AURA_MOD_SHIELD_BLOCKVALUE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SHIELD_BLOCKVALUE;
            case SPELL_AURA_NO_PVP_CREDIT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_NO_PVP_CREDIT;
            case SPELL_AURA_MOD_AOE_AVOIDANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_AOE_AVOIDANCE;
            case SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT;
            case SPELL_AURA_POWER_BURN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_POWER_BURN;
            case SPELL_AURA_MOD_CRIT_DAMAGE_BONUS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRIT_DAMAGE_BONUS;
            case SPELL_AURA_164:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_164;
            case SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS;
            case SPELL_AURA_MOD_ATTACK_POWER_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACK_POWER_PCT;
            case SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT;
            case SPELL_AURA_MOD_DAMAGE_DONE_VERSUS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE_VERSUS;
            case SPELL_AURA_MOD_CRIT_PERCENT_VERSUS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRIT_PERCENT_VERSUS;
            case SPELL_AURA_DETECT_AMORE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_DETECT_AMORE;
            case SPELL_AURA_MOD_SPEED_NOT_STACK:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPEED_NOT_STACK;
            case SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK;
            case SPELL_AURA_173:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_173;
            case SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT;
            case SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT;
            case SPELL_AURA_SPIRIT_OF_REDEMPTION:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SPIRIT_OF_REDEMPTION;
            case SPELL_AURA_AOE_CHARM:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_AOE_CHARM;
            case SPELL_AURA_MOD_DEBUFF_RESISTANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DEBUFF_RESISTANCE;
            case SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE;
            case SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS;
            case SPELL_AURA_181:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_181;
            case SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT;
            case SPELL_AURA_MOD_CRITICAL_THREAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRITICAL_THREAT;
            case SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE;
            case SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE;
            case SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE;
            case SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE;
            case SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE;
            case SPELL_AURA_MOD_RATING:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RATING;
            case SPELL_AURA_MOD_FACTION_REPUTATION_GAIN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FACTION_REPUTATION_GAIN;
            case SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED;
            case SPELL_AURA_MOD_MELEE_RANGED_HASTE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_RANGED_HASTE;
            case SPELL_AURA_MELEE_SLOW:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MELEE_SLOW;
            case SPELL_AURA_MOD_TARGET_ABSORB_SCHOOL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TARGET_ABSORB_SCHOOL;
            case SPELL_AURA_MOD_TARGET_ABILITY_ABSORB_SCHOOL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TARGET_ABILITY_ABSORB_SCHOOL;
            case SPELL_AURA_MOD_COOLDOWN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_COOLDOWN;
            case SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE;
            case SPELL_AURA_198:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_198;
            case SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT;
            case SPELL_AURA_MOD_XP_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_XP_PCT;
            case SPELL_AURA_FLY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_FLY;
            case SPELL_AURA_IGNORE_COMBAT_RESULT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_IGNORE_COMBAT_RESULT;
            case SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE;
            case SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE;
            case SPELL_AURA_MOD_SCHOOL_CRIT_DMG_TAKEN:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SCHOOL_CRIT_DMG_TAKEN;
            case SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED;
            case SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED;
            case SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED;
            case SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS;
            case SPELL_AURA_MOD_VEHICLE_SPEED_ALWAYS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_VEHICLE_SPEED_ALWAYS;
            case SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK;
            case SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT;
            case SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT;
            case SPELL_AURA_214:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_214;
            case SPELL_AURA_ARENA_PREPARATION:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ARENA_PREPARATION;
            case SPELL_AURA_HASTE_SPELLS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_HASTE_SPELLS;
            case SPELL_AURA_MOD_MELEE_HASTE_2:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_HASTE_2;
            case SPELL_AURA_HASTE_RANGED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_HASTE_RANGED;
            case SPELL_AURA_MOD_MANA_REGEN_FROM_STAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MANA_REGEN_FROM_STAT;
            case SPELL_AURA_MOD_RATING_FROM_STAT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RATING_FROM_STAT;
            case SPELL_AURA_IGNORED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_IGNORED;
            case SPELL_AURA_222:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_222;
            case SPELL_AURA_RAID_PROC_FROM_CHARGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_RAID_PROC_FROM_CHARGE;
            case SPELL_AURA_224:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_224;
            case SPELL_AURA_RAID_PROC_FROM_CHARGE_WITH_VALUE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_RAID_PROC_FROM_CHARGE_WITH_VALUE;
            case SPELL_AURA_PERIODIC_DUMMY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_DUMMY;
            case SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE;
            case SPELL_AURA_DETECT_STEALTH:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_DETECT_STEALTH;
            case SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE;
            case SPELL_AURA_230:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_230;
            case SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE;
            case SPELL_AURA_MECHANIC_DURATION_MOD:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MECHANIC_DURATION_MOD;
            case SPELL_AURA_CHANGE_MODEL_FOR_ALL_HUMANOIDS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_CHANGE_MODEL_FOR_ALL_HUMANOIDS;
            case SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK;
            case SPELL_AURA_MOD_DISPEL_RESIST:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DISPEL_RESIST;
            case SPELL_AURA_CONTROL_VEHICLE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_CONTROL_VEHICLE;
            case SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER;
            case SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER;
            case SPELL_AURA_MOD_SCALE_2:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SCALE_2;
            case SPELL_AURA_MOD_EXPERTISE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_EXPERTISE;
            case SPELL_AURA_FORCE_MOVE_FORWARD:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_FORCE_MOVE_FORWARD;
            case SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING;
            case SPELL_AURA_MOD_FACTION:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FACTION;
            case SPELL_AURA_COMPREHEND_LANGUAGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_COMPREHEND_LANGUAGE;
            case SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL;
            case SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL_NOT_STACK:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL_NOT_STACK;
            case SPELL_AURA_CLONE_CASTER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_CLONE_CASTER;
            case SPELL_AURA_MOD_COMBAT_RESULT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_COMBAT_RESULT_CHANCE;
            case SPELL_AURA_CONVERT_RUNE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_CONVERT_RUNE;
            case SPELL_AURA_MOD_INCREASE_HEALTH_2:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_HEALTH_2;
            case SPELL_AURA_MOD_ENEMY_DODGE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ENEMY_DODGE;
            case SPELL_AURA_MOD_SPEED_SLOW_ALL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPEED_SLOW_ALL;
            case SPELL_AURA_MOD_BLOCK_CRIT_CHANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BLOCK_CRIT_CHANCE;
            case SPELL_AURA_MOD_DISARM_OFFHAND:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DISARM_OFFHAND;
            case SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT;
            case SPELL_AURA_NO_REAGENT_USE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_NO_REAGENT_USE;
            case SPELL_AURA_MOD_TARGET_RESIST_BY_SPELL_CLASS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TARGET_RESIST_BY_SPELL_CLASS;
            case SPELL_AURA_258:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_258;
            case SPELL_AURA_MOD_HOT_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HOT_PCT;
            case SPELL_AURA_SCREEN_EFFECT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SCREEN_EFFECT;
            case SPELL_AURA_PHASE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PHASE;
            case SPELL_AURA_ABILITY_IGNORE_AURASTATE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ABILITY_IGNORE_AURASTATE;
            case SPELL_AURA_ALLOW_ONLY_ABILITY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ALLOW_ONLY_ABILITY;
            case SPELL_AURA_264:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_264;
            case SPELL_AURA_265:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_265;
            case SPELL_AURA_266:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_266;
            case SPELL_AURA_MOD_IMMUNE_AURA_APPLY_SCHOOL:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_IMMUNE_AURA_APPLY_SCHOOL;
            case SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT;
            case SPELL_AURA_MOD_IGNORE_TARGET_RESIST:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_IGNORE_TARGET_RESIST;
            case SPELL_AURA_MOD_ABILITY_IGNORE_TARGET_RESIST:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ABILITY_IGNORE_TARGET_RESIST;
            case SPELL_AURA_MOD_DAMAGE_FROM_CASTER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_FROM_CASTER;
            case SPELL_AURA_IGNORE_MELEE_RESET:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_IGNORE_MELEE_RESET;
            case SPELL_AURA_X_RAY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_X_RAY;
            case SPELL_AURA_ABILITY_CONSUME_NO_AMMO:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ABILITY_CONSUME_NO_AMMO;
            case SPELL_AURA_MOD_IGNORE_SHAPESHIFT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_IGNORE_SHAPESHIFT;
            case SPELL_AURA_MOD_DAMAGE_DONE_FOR_MECHANIC:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE_FOR_MECHANIC;
            case SPELL_AURA_MOD_MAX_AFFECTED_TARGETS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MAX_AFFECTED_TARGETS;
            case SPELL_AURA_MOD_DISARM_RANGED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DISARM_RANGED;
            case SPELL_AURA_INITIALIZE_IMAGES:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_INITIALIZE_IMAGES;
            case SPELL_AURA_MOD_ARMOR_PENETRATION_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ARMOR_PENETRATION_PCT;
            case SPELL_AURA_MOD_HONOR_GAIN_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HONOR_GAIN_PCT;
            case SPELL_AURA_MOD_BASE_HEALTH_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BASE_HEALTH_PCT;
            case SPELL_AURA_MOD_HEALING_RECEIVED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING_RECEIVED;
            case SPELL_AURA_LINKED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_LINKED;
            case SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR;
            case SPELL_AURA_ABILITY_PERIODIC_CRIT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_ABILITY_PERIODIC_CRIT;
            case SPELL_AURA_DEFLECT_SPELLS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_DEFLECT_SPELLS;
            case SPELL_AURA_IGNORE_HIT_DIRECTION:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_IGNORE_HIT_DIRECTION;
            case SPELL_AURA_PREVENT_DURABILITY_LOSS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PREVENT_DURABILITY_LOSS;
            case SPELL_AURA_MOD_CRIT_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRIT_PCT;
            case SPELL_AURA_MOD_XP_QUEST_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_XP_QUEST_PCT;
            case SPELL_AURA_OPEN_STABLE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_OPEN_STABLE;
            case SPELL_AURA_OVERRIDE_SPELLS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_OVERRIDE_SPELLS;
            case SPELL_AURA_PREVENT_REGENERATE_POWER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PREVENT_REGENERATE_POWER;
            case SPELL_AURA_295:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_295;
            case SPELL_AURA_SET_VEHICLE_ID:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SET_VEHICLE_ID;
            case SPELL_AURA_BLOCK_SPELL_FAMILY:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_BLOCK_SPELL_FAMILY;
            case SPELL_AURA_STRANGULATE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_STRANGULATE;
            case SPELL_AURA_299:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_299;
            case SPELL_AURA_SHARE_DAMAGE_PCT:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SHARE_DAMAGE_PCT;
            case SPELL_AURA_SCHOOL_HEAL_ABSORB:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_SCHOOL_HEAL_ABSORB;
            case SPELL_AURA_302:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_302;
            case SPELL_AURA_MOD_DAMAGE_DONE_VERSUS_AURASTATE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE_VERSUS_AURASTATE;
            case SPELL_AURA_MOD_FAKE_INEBRIATE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FAKE_INEBRIATE;
            case SPELL_AURA_MOD_MINIMUM_SPEED:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MINIMUM_SPEED;
            case SPELL_AURA_306:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_306;
            case SPELL_AURA_HEAL_ABSORB_TEST:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_HEAL_ABSORB_TEST;
            case SPELL_AURA_MOD_CRIT_CHANCE_FOR_CASTER:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRIT_CHANCE_FOR_CASTER;
            case SPELL_AURA_309:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_309;
            case SPELL_AURA_MOD_CREATURE_AOE_DAMAGE_AVOIDANCE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CREATURE_AOE_DAMAGE_AVOIDANCE;
            case SPELL_AURA_311:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_311;
            case SPELL_AURA_312:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_312;
            case SPELL_AURA_313:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_313;
            case SPELL_AURA_PREVENT_RESURRECTION:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PREVENT_RESURRECTION;
            case SPELL_AURA_UNDERWATER_WALKING:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_UNDERWATER_WALKING;
            case SPELL_AURA_PERIODIC_HASTE:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_HASTE;
            case TOTAL_AURAS:
                return ENCOUNTER_LOG_FLAG_SPELL_AURA_TOTAL_AURAS;
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
