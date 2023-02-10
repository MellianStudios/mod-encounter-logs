#ifndef AZEROTHCORE_ENCOUNTERLOGMANAGER_H
#define AZEROTHCORE_ENCOUNTERLOGMANAGER_H

#include "Configuration/Config.h"
#include "DatabaseEnv.h"
#include "Log.h"

// Note that these data types here are irrelevant since on most of modern computers all of them will be implemented as "long"

enum EncounterLogScope
{
    ENCOUNTER_LOG_DUNGEON = 1,
    ENCOUNTER_LOG_RAID = 2,
    ENCOUNTER_LOG_EVERYTHING = 3
};

enum EncounterLogState
{
    ENCOUNTER_LOG_START = 1,
    ENCOUNTER_LOG_END = 2,
};

enum EncounterLogUnitType
{
    ENCOUNTER_LOG_PLAYER = 1,
    ENCOUNTER_LOG_CREATURE = 2,
};

enum EncounterLogCostType
{
    ENCOUNTER_LOG_NONE = 1,
    ENCOUNTER_LOG_MANA = 2,
    ENCOUNTER_LOG_HP = 3,
};

/*
 * absorb
 * resist (portion)
 * block
 */
enum EncounterLogSpellResult
{
    ENCOUNTER_LOG_HIT = 1,
    ENCOUNTER_LOG_MISS = 2,
    ENCOUNTER_LOG_CRIT = 3,
    ENCOUNTER_LOG_DODGE = 4,
    ENCOUNTER_LOG_PARRY = 5,
    ENCOUNTER_LOG_RESIST = 6,
    ENCOUNTER_LOG_REFLECT = 7,
    ENCOUNTER_LOG_IMMUNE = 8,
    ENCOUNTER_LOG_EVADE = 9,
};

class EncounterLogCombat
{
private:
    std::uint_fast16_t map_id;
    std::uint_fast16_t instance_id;
    std::uint_fast32_t guid;
    std::uint_fast8_t unit_type;
    std::uint_fast8_t state;
    std::uint_fast64_t timestamp;

public:
    EncounterLogCombat(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t guid,
        std::uint_fast8_t unit_type,
        std::uint_fast8_t state,
        std::uint_fast64_t timestamp
    ) : map_id{map_id}, instance_id{instance_id}, guid{guid}, unit_type{unit_type},
        state{state}, timestamp{timestamp}
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
        result.append(std::to_string(unit_type));
        result.append(",");
        result.append(std::to_string(state));
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
    std::uint_fast32_t caster_guid;
    std::uint_fast32_t target_guid;
    std::uint_fast8_t cost_type;
    std::uint_fast32_t cost;
    std::uint_fast32_t value;
    std::uint_fast8_t result;
    std::uint_fast64_t timestamp;

public:
    EncounterLogSpell(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t spell_id,
        std::uint_fast32_t caster_guid,
        std::uint_fast8_t cost_type,
        std::uint_fast64_t timestamp,
        std::uint_fast32_t target_guid = 0,
        std::uint_fast32_t cost = 0,
        std::uint_fast32_t value = 0,
        std::uint_fast8_t result = 1
    ) : map_id{map_id}, instance_id{instance_id}, spell_id{spell_id}, caster_guid{caster_guid},
        target_guid{target_guid}, cost_type{cost_type}, cost{cost}, value{value}, result{result}, timestamp{timestamp}
    {}

    [[nodiscard]] std::string asString() const
    {
        std::string result_string{"("};

        result_string.append(std::to_string(map_id));
        result_string.append(",");
        result_string.append(std::to_string(instance_id));
        result_string.append(",");
        result_string.append(std::to_string(spell_id));
        result_string.append(",");
        result_string.append(std::to_string(caster_guid));
        result_string.append(",");
        result_string.append(std::to_string(target_guid));
        result_string.append(",");
        result_string.append(std::to_string(cost_type));
        result_string.append(",");
        result_string.append(std::to_string(cost));
        result_string.append(",");
        result_string.append(std::to_string(value));
        result_string.append(",");
        result_string.append(std::to_string(result));
        result_string.append(",");
        result_string.append(std::to_string(timestamp));
        result_string.append(")");

        return result_string;
    }
};

class EncounterLogAreaSpell
{
private:
    std::uint_fast32_t spell_id;
    std::uint_fast32_t caster_guid;
    std::uint_fast32_t target_guid;
    std::uint_fast32_t value;
    std::uint_fast8_t result;
    std::uint_fast64_t timestamp;

public:
    EncounterLogAreaSpell(
        std::uint_fast32_t spell_id,
        std::uint_fast32_t caster_guid,
        std::uint_fast32_t target_guid,
        std::uint_fast8_t result,
        std::uint_fast64_t timestamp,
        std::uint_fast32_t value = 0
    ) : spell_id{spell_id}, caster_guid{caster_guid}, target_guid{target_guid}, value{value}, result{result},
        timestamp{timestamp}
    {}

    [[nodiscard]] std::string asString() const
    {
        std::string result_string{"("};

        result_string.append(std::to_string(spell_id));
        result_string.append(",");
        result_string.append(std::to_string(caster_guid));
        result_string.append(",");
        result_string.append(std::to_string(target_guid));
        result_string.append(",");
        result_string.append(std::to_string(value));
        result_string.append(",");
        result_string.append(std::to_string(result));
        result_string.append(",");
        result_string.append(std::to_string(timestamp));
        result_string.append(")");

        return result_string;
    }
};

class EncounterLogAttack
{
private:
    std::uint_fast16_t map_id;
    std::uint_fast16_t instance_id;
    std::uint_fast32_t attacker_guid;
    std::uint_fast32_t target_guid;
    std::uint_fast32_t value;
    std::uint_fast8_t result;
    std::uint_fast64_t timestamp;

public:
    EncounterLogAttack(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t attacker_guid,
        std::uint_fast32_t target_guid,
        std::uint_fast8_t result,
        std::uint_fast64_t timestamp,
        std::uint_fast32_t value = 0
    ) : map_id{map_id}, instance_id{instance_id}, attacker_guid{attacker_guid}, target_guid{target_guid}, value{value},
        result{result}, timestamp{timestamp}
    {}

    [[nodiscard]] std::string asString() const
    {
        std::string result_string{"("};

        result_string.append(std::to_string(map_id));
        result_string.append(",");
        result_string.append(std::to_string(instance_id));
        result_string.append(",");
        result_string.append(std::to_string(attacker_guid));
        result_string.append(",");
        result_string.append(std::to_string(target_guid));
        result_string.append(",");
        result_string.append(std::to_string(value));
        result_string.append(",");
        result_string.append(std::to_string(result));
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
    std::uint_fast32_t guid;
    double x;
    double y;
    double z;
    double o;
    std::uint_fast64_t timestamp;

public:
    EncounterLogMovement(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t guid,
        double x,
        double y,
        double z,
        double o,
        std::uint_fast64_t timestamp
    ) : map_id{map_id}, instance_id{instance_id}, guid{guid}, x{x}, y{y}, z{z}, o{o}, timestamp{timestamp}
    {}

    [[nodiscard]] std::string asString() const
    {
        std::string result_string{"("};

        result_string.append(std::to_string(map_id));
        result_string.append(",");
        result_string.append(std::to_string(instance_id));
        result_string.append(",");
        result_string.append(std::to_string(guid));
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

class Circumrota
{
private:
    std::map<std::uint_fast32_t, EncounterLogCombat> combat_buffer;
    std::atomic<std::uint_fast32_t> combat_first{1};
    std::atomic<std::uint_fast32_t> combat_last{1};
    std::map<std::uint_fast32_t, EncounterLogSpell> spell_buffer;
    std::atomic<std::uint_fast32_t> spell_first{1};
    std::atomic<std::uint_fast32_t> spell_last{1};
    std::map<std::uint_fast32_t, EncounterLogAreaSpell> area_spell_buffer;
    std::atomic<std::uint_fast32_t> area_spell_first{1};
    std::atomic<std::uint_fast32_t> area_spell_last{1};
    std::map<std::uint_fast32_t, EncounterLogAttack> attack_buffer;
    std::atomic<std::uint_fast32_t> attack_first{1};
    std::atomic<std::uint_fast32_t> attack_last{1};
    std::map<std::uint_fast32_t, EncounterLogMovement> movement_buffer;
    std::atomic<std::uint_fast32_t> movement_first{1};
    std::atomic<std::uint_fast32_t> movement_last{1};

public:
    std::uint_fast32_t pushCombat(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t guid,
        std::uint_fast8_t unit_type,
        std::uint_fast8_t state,
        std::uint_fast64_t timestamp
    )
    {
        combat_buffer.insert({combat_first, {
            map_id,
            instance_id,
            guid,
            unit_type,
            state,
            timestamp
        }});

        combat_first++;

        return combat_first;
    }

    [[nodiscard]] std::string retrieveCombats(std::size_t count)
    {
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
        return combat_buffer.size();
    }

    std::uint_fast32_t pushSpell(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t spell_id,
        std::uint_fast32_t caster_guid,
        std::uint_fast8_t cost_type,
        std::uint_fast64_t timestamp,
        std::uint_fast32_t target_guid = 0,
        std::uint_fast32_t cost = 0,
        std::uint_fast32_t value = 0,
        std::uint_fast8_t result = 1
    )
    {
        spell_buffer.insert({spell_first, {
            map_id,
            instance_id,
            spell_id,
            caster_guid,
            cost_type,
            timestamp,
            target_guid,
            cost,
            value,
            result
        }});

        spell_first++;

        return spell_first;
    }

    [[nodiscard]] std::string retrieveSpells(std::size_t count)
    {
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
        return spell_buffer.size();
    }

    std::uint_fast32_t pushAreaSpell(
        std::uint_fast32_t spell_id,
        std::uint_fast32_t caster_guid,
        std::uint_fast32_t target_guid,
        std::uint_fast8_t result,
        std::uint_fast64_t timestamp,
        std::uint_fast32_t value = 0
    )
    {
        area_spell_buffer.insert({area_spell_first, {
            spell_id,
            caster_guid,
            target_guid,
            result,
            timestamp,
            value
        }});

        area_spell_first++;

        return area_spell_first;
    }

    [[nodiscard]] std::string retrieveAreaSpells(std::size_t count)
    {
        if (area_spell_buffer.empty()) {
            return "";
        }

        count = std::min(count, area_spell_buffer.size());

        std::string result;
        result.reserve(count * 40);

        std::uint_fast32_t i{1};

        while (i <= count) {
            result.append(area_spell_buffer.at(area_spell_last).asString());

            if (i != count) {
                result.append(",");
            }

            area_spell_buffer.erase(area_spell_last);
            i++;
            area_spell_last++;
        }

        return result;
    }

    [[nodiscard]] std::uint_fast32_t getAreaSpellBufferSize()
    {
        return area_spell_buffer.size();
    }

    std::uint_fast32_t pushAttack(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t attacker_guid,
        std::uint_fast32_t target_guid,
        std::uint_fast8_t result,
        std::uint_fast64_t timestamp,
        std::uint_fast32_t value = 0
    )
    {
        attack_buffer.insert({attack_first, {
            map_id,
            instance_id,
            attacker_guid,
            target_guid,
            result,
            timestamp,
            value
        }});

        attack_first++;

        return attack_first;
    }

    [[nodiscard]] std::string retrieveAttacks(std::size_t count)
    {
        if (attack_buffer.empty()) {
            return "";
        }

        count = std::min(count, attack_buffer.size());

        std::string result;
        result.reserve(count * 40);

        std::uint_fast32_t i{1};

        while (i <= count) {
            result.append(attack_buffer.at(attack_last).asString());

            if (i != count) {
                result.append(",");
            }

            attack_buffer.erase(attack_last);
            i++;
            attack_last++;
        }

        return result;
    }

    [[nodiscard]] std::uint_fast32_t getAttackBufferSize()
    {
        return attack_buffer.size();
    }

    std::uint_fast32_t pushMovement(
        std::uint_fast16_t map_id,
        std::uint_fast16_t instance_id,
        std::uint_fast32_t guid,
        double x,
        double y,
        double z,
        double o,
        std::uint_fast64_t timestamp
    )
    {
        movement_buffer.insert({movement_first, {
            map_id,
            instance_id,
            guid,
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
        return movement_buffer.size();
    }
};

class EncounterLogs
{
private:
    std::uint_fast32_t m_map_id;
    std::uint_fast32_t m_instance_id;
    std::uint_fast32_t m_started_at;
    std::thread m_saver;
    std::atomic<bool> m_stop_saver{false};
    Circumrota m_buffer;

public:
    EncounterLogs(std::uint_fast32_t map_id, std::uint_fast32_t instance_id, std::uint_fast32_t started_at)
        : m_map_id{map_id}, m_instance_id{instance_id}, m_started_at{started_at}
    {
        LoginDatabase.Execute(
            "INSERT INTO encounter_logs (map_id, instance_id, started_at) VALUES (" +
            std::to_string(m_map_id) + "," + std::to_string(m_instance_id) + "," + std::to_string(m_started_at) +
            ")"
        );

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
                auto area_spell_buffer_size = m_buffer.getAreaSpellBufferSize();
                auto attack_buffer_size = m_buffer.getAttackBufferSize();
                auto movement_buffer_size = m_buffer.getMovementBufferSize();

                std::uint_fast32_t combat_count{0};
                std::uint_fast32_t combat_query_count{1};

                if (combat_buffer_size < batch_size) {
                    combat_count = combat_buffer_size;
                } else {
                    combat_count = batch_size;
                    combat_query_count = combat_buffer_size % batch_size;
                }

                if (combat_count > 0) {
                    for (std::uint_fast32_t i = 1; i <= combat_query_count; i++) {
                        LoginDatabase.Execute(
                            "INSERT INTO encounter_log_combats (map_id, instance_id, guid, unit_type, state, timestamp) VALUES " +
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
                    spell_query_count = spell_buffer_size % batch_size;
                }

                if (spell_count > 0) {
                    for (std::uint_fast32_t i = 1; i <= spell_query_count; i++) {
                        LoginDatabase.Execute(
                            "INSERT INTO encounter_log_spells (map_id, instance_id, spell_id, caster_guid, target_guid, cost_type, cost, value, result, timestamp) VALUES " +
                            m_buffer.retrieveSpells(spell_count)
                        );
                    }
                }

                std::uint_fast32_t area_spell_count{0};
                std::uint_fast32_t area_spell_query_count{1};

                if (area_spell_buffer_size < batch_size) {
                    area_spell_count = area_spell_buffer_size;
                } else {
                    area_spell_count = batch_size;
                    area_spell_query_count = area_spell_buffer_size % batch_size;
                }

                if (area_spell_count > 0) {
                    for (std::uint_fast32_t i = 1; i <= area_spell_query_count; i++) {
                        LoginDatabase.Execute(
                            "INSERT INTO encounter_log_area_spells (spell_id, caster_guid, target_guid, value, result, timestamp) VALUES " +
                            m_buffer.retrieveAreaSpells(area_spell_count)
                        );
                    }
                }

                std::uint_fast32_t attack_count{0};
                std::uint_fast32_t attack_query_count{1};

                if (attack_buffer_size < batch_size) {
                    attack_count = attack_buffer_size;
                } else {
                    attack_count = batch_size;
                    attack_query_count = attack_buffer_size % batch_size;
                }

                if (attack_count > 0) {
                    for (std::uint_fast32_t i = 1; i <= attack_query_count; i++) {
                        LoginDatabase.Execute(
                            "INSERT INTO encounter_log_attacks (map_id, instance_id, attacker_guid, target_guid, value, result, timestamp) VALUES " +
                            m_buffer.retrieveAttacks(attack_count)
                        );
                    }
                }

                std::uint_fast32_t movement_count{0};
                std::uint_fast32_t movement_query_count{1};

                if (movement_buffer_size < batch_size) {
                    movement_count = movement_buffer_size;
                } else {
                    movement_count = batch_size;
                    movement_query_count = movement_buffer_size % batch_size;
                }

                if (movement_count > 0) {
                    for (std::uint_fast32_t i = 1; i <= movement_query_count; i++) {
                        LoginDatabase.Execute(
                            "INSERT INTO encounter_log_movements (map_id, instance_id, guid, x, y, z, o, `timestamp`) VALUES " +
                            m_buffer.retrieveMovements(movement_count)
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

class EncounterLogManager
{
private:
    static std::uint_fast32_t scope;
    static std::unordered_map<std::uint_fast32_t, std::unique_ptr<EncounterLogs>> m_logs;

public:
    static void newLog(std::uint_fast32_t map_id, std::uint_fast32_t instance_id, std::uint_fast32_t started_at)
    {
        if (m_logs.contains(instance_id)) {
            return;
        }

        m_logs.insert({instance_id, std::make_unique<EncounterLogs>(map_id, instance_id, started_at)});
    }

    static EncounterLogs *getLog(std::uint_fast32_t instance_id)
    {
        return m_logs.at(instance_id).get();
    }

    static bool dungeonsDisabled()
    {
        return scope == ENCOUNTER_LOG_EVERYTHING || scope == ENCOUNTER_LOG_DUNGEON;
    }

    static bool raidsDisabled()
    {
        return scope == ENCOUNTER_LOG_EVERYTHING || scope == ENCOUNTER_LOG_RAID;
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGMANAGER_H