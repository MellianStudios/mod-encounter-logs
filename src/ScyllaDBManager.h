#ifndef AZEROTHCORE_SCYLLADBMANAGER_H
#define AZEROTHCORE_SCYLLADBMANAGER_H

#include <cassandra.h>
#include <future>
#include <iomanip>
#include <random>
#include <regex>

class ScyllaDBQueryResult
{
public:
    ScyllaDBQueryResult(const CassResult *raw_result) : m_raw_result(raw_result), m_row_iter(cass_iterator_from_result(raw_result))
    {}

    const CassRow *fetch()
    {
        if (!cass_iterator_next(m_row_iter)) {
            return nullptr;
        } else {
            return cass_iterator_get_row(m_row_iter);
        }
    }

    ~ScyllaDBQueryResult()
    {
        cass_iterator_free(m_row_iter);
        cass_result_free(m_raw_result);
    }

private:
    const CassResult *m_raw_result;
    CassIterator *m_row_iter;
};

class ScyllaDBManager
{
public:
    ScyllaDBManager()
    {
        m_cluster = cass_cluster_new();
        m_session = cass_session_new();

        auto host = sConfigMgr->GetOption<std::string>("EncounterLogs.ScyllaDB.Host", "127.0.0.1");
        auto port = sConfigMgr->GetOption<int>("EncounterLogs.ScyllaDB.Port", 9042);
        m_keyspace = sConfigMgr->GetOption<std::string>("EncounterLogs.ScyllaDB.Keyspace", "encounter_logs");
        m_check_async_queries = sConfigMgr->GetOption<bool>("EncounterLogs.ScyllaDB.CheckAsyncQueries", false);
        m_save_frequency = sConfigMgr->GetOption<std::uint_fast32_t>("EncounterLogs.System.SaveFrequency", 1000);
        auto username = sConfigMgr->GetOption<std::string>("EncounterLogs.ScyllaDB.Username", "admin");
        auto password = sConfigMgr->GetOption<std::string>("EncounterLogs.ScyllaDB.Password", "admin");

        cass_cluster_set_contact_points(m_cluster, host.c_str());
        cass_cluster_set_port(m_cluster, port);
        cass_cluster_set_credentials(m_cluster, username.c_str(), password.c_str());

        m_connect_future = cass_session_connect(m_session, m_cluster);
        cass_future_wait(m_connect_future);

        if (cass_future_error_code(m_connect_future) != CASS_OK) {
            const char *message;
            size_t message_length;
            cass_future_error_message(m_connect_future, &message, &message_length);
            std::string error_message(message, message_length);

            LOG_FATAL("encounter_logs", "Unable to connect to ScyllaDB: {}", error_message);
        }

        if (m_check_async_queries) {
            m_checker = std::thread([&]() {
                while (!m_stop_checker) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(m_save_frequency));

                    checkQueries();
                }
            });
        }
    }

    ~ScyllaDBManager()
    {
        close();
    }

    void createSchema()
    {
        auto replication_strategy = sConfigMgr->GetOption<std::string>("EncounterLogs.ScyllaDB.ReplicationStrategy", "SimpleStrategy");
        auto replication_factor = sConfigMgr->GetOption<std::string>("EncounterLogs.ScyllaDB.ReplicationFactor", "1");

        const CassSchemaMeta *schema_meta = cass_session_get_schema_meta(m_session);
        const CassKeyspaceMeta *keyspace_meta = cass_schema_meta_keyspace_by_name(schema_meta, m_keyspace.c_str());

        if (keyspace_meta == nullptr) {
            std::string keyspace{"CREATE KEYSPACE {} WITH replication = {{'class': '" + replication_strategy + "', 'replication_factor': '" + replication_factor + "' }};"};
            std::string updates{"CREATE TABLE {keyspace}.updates (id uuid PRIMARY KEY, name int);"};
            std::string encounter_logs{
                "CREATE TABLE {keyspace}.encounter_logs ("
                "id uuid PRIMARY KEY,"
                "map_id smallint,"
                "instance_id smallint,"
                "timestamp bigint);"
            };
            std::string encounter_log_instance_resets{
                "CREATE TABLE {keyspace}.encounter_log_instance_resets ("
                "id uuid PRIMARY KEY,"
                "map_id smallint,"
                "instance_id smallint,"
                "timestamp bigint);"
            };
            std::string encounter_log_combats{
                "CREATE TABLE {keyspace}.encounter_log_combats ("
                "id uuid PRIMARY KEY,"
                "map_id smallint,"
                "instance_id smallint,"
                "guid varint,"
                "state tinyint,"
                "gear text,"
                "talents text,"
                "auras text,"
                "stats text,"
                "timestamp bigint);"
            };
            std::string encounter_log_spells{
                "CREATE TABLE {keyspace}.encounter_log_spells ("
                "id uuid PRIMARY KEY,"
                "map_id smallint,"
                "instance_id smallint,"
                "spell_id varint,"
                "caster_owner_guid varint,"
                "caster_owner_type tinyint,"
                "caster_guid varint,"
                "caster_type tinyint,"
                "target_owner_guid varint,"
                "target_owner_type varint,"
                "target_guid varint,"
                "target_type tinyint,"
                "value int,"
                "over_value int,"
                "absorb_value int,"
                "resist_value int,"
                "block_value int,"
                "is_critical boolean,"
                "is_positive boolean,"
                "result tinyint,"
                "flag smallint,"
                "arbitrary_flag smallint,"
                "timestamp bigint);"
            };
            std::string encounter_log_movements{
                "CREATE TABLE {keyspace}.encounter_log_movements ("
                "id uuid PRIMARY KEY,"
                "map_id smallint,"
                "instance_id smallint,"
                "owner_guid varint,"
                "owner_type varint,"
                "guid varint,"
                "type tinyint,"
                "x double,"
                "y double,"
                "z double,"
                "o double,"
                "timestamp bigint);"
            };
            std::string encounter_log_deaths{
                "CREATE TABLE {keyspace}.encounter_log_deaths ("
                "id uuid PRIMARY KEY,"
                "map_id smallint,"
                "instance_id smallint,"
                "owner_guid varint,"
                "owner_type tinyint,"
                "guid varint,"
                "type tinyint,"
                "killer_owner_guid varint,"
                "killer_owner_type tinyint,"
                "killer_guid varint,"
                "killer_type tinyint,"
                "timestamp bigint);"
            };
            std::string encounter_log_powers{
                "CREATE TABLE {keyspace}.encounter_log_powers ("
                "id uuid PRIMARY KEY,"
                "map_id smallint,"
                "instance_id smallint,"
                "owner_guid varint,"
                "owner_type tinyint,"
                "guid varint,"
                "type tinyint,"
                "power_type smallint,"
                "value int,"
                "is_max boolean,"
                "timestamp bigint);"
            };

            execute(keyspace);
            execute(updates);
            execute(encounter_logs);
            execute(encounter_log_instance_resets);
            execute(encounter_log_combats);
            execute(encounter_log_spells);
            execute(encounter_log_movements);
            execute(encounter_log_deaths);
            execute(encounter_log_powers);
        }

        std::string query = "INSERT INTO encounter_logs.encounter_log_combats (id, map_id, instance_id, guid, state, gear, talents, auras, stats, timestamp) VALUES (1f31a267-c6eb-4828-a99a-6b5bce9678d0,533,1,3,1,'','','','',1711905162283);";

        execute(query);
    }

    void updateSchema()
    {
        std::shared_ptr<ScyllaDBQueryResult> result = select("SELECT name FROM {keyspace}.updates;");

        std::unordered_map<std::uint_fast32_t, bool> updates{};

        if (result) {
            const CassRow *row{nullptr};

            while ((row = result->fetch()) != nullptr) {
                const CassValue *field = cass_row_get_column(row, 0);

                cass_int32_t name;

                cass_value_get_int32(field, &name);

                updates.insert({name, true});
            }
        }
    }

    void execute(std::string &query)
    {
        query = std::regex_replace(query, std::regex("\\{keyspace}"), m_keyspace);
        query = std::regex_replace(query, std::regex("\\{uuid}"), uuid());

        CassStatement *statement = cass_statement_new(query.c_str(), 0);
        CassFuture *query_future = cass_session_execute(m_session, statement);

        cass_future_wait(query_future);

        if (cass_future_error_code(query_future) != CASS_OK) {
            const char *error_message;
            size_t error_message_length;
            cass_future_error_message(query_future, &error_message, &error_message_length);

            LOG_ERROR("encounter_logs", "Query execution failed: {}.", std::string(error_message, error_message_length));
        }

        cass_future_free(query_future);
        cass_statement_free(statement);
    }

    void executeAsync(std::string &query)
    {
        query = std::regex_replace(query, std::regex("\\{keyspace}"), m_keyspace);
        query = std::regex_replace(query, std::regex("\\{uuid}"), uuid());

        CassStatement *statement = cass_statement_new(query.c_str(), 0);
        CassFuture *query_future = cass_session_execute(m_session, statement);

        if (m_check_async_queries) {
            m_queries.push_back(query_future);
        }
    }

    std::shared_ptr<ScyllaDBQueryResult> select(const std::string &query)
    {
        CassStatement *statement = cass_statement_new(std::regex_replace(query, std::regex("\\{keyspace}"), m_keyspace).c_str(), 0);

        CassFuture *result_future = cass_session_execute(m_session, statement);
        cass_statement_free(statement);

        if (cass_future_error_code(result_future) != CASS_OK) {
            LOG_FATAL("encounter_logs", "Query execution failed");

            return {};
        }

        const CassResult *raw_result = cass_future_get_result(result_future);

        return std::make_shared<ScyllaDBQueryResult>(raw_result);
    }

    void checkQueries()
    {
        for (auto it = m_queries.begin(); it != m_queries.end();) {
            CassFuture *query_future = *it;

            if (cass_future_ready(query_future)) {
                if (cass_future_error_code(query_future) != CASS_OK) {
                    const char *message;
                    size_t message_length;
                    cass_future_error_message(query_future, &message, &message_length);

                    LOG_ERROR("encounter_logs", "Query execution failed: {}.", std::string(message, message_length));
                }

                cass_future_free(query_future);
                it = m_queries.erase(it);
            } else {
                ++it;
            }
        }
    }

    void close()
    {
        CassFuture *close_future;

        close_future = cass_session_close(m_session);

        cass_future_wait(close_future);
        cass_future_free(close_future);
        cass_cluster_free(m_cluster);
        cass_session_free(m_session);

        if (m_check_async_queries) {
            m_stop_checker = true;

            m_checker.join();
        }
    }

private:
    CassCluster *m_cluster{nullptr};
    CassFuture *m_connect_future{nullptr};
    CassSession *m_session{nullptr};
    std::string m_keyspace;
    bool m_check_async_queries{false};
    std::uint_fast32_t m_save_frequency;
    std::list<CassFuture *> m_queries;
    std::thread m_checker;
    std::atomic<bool> m_stop_checker{false};

    [[nodiscard]] static std::string uuid()
    {
        CassUuidGen *uuid_gen = cass_uuid_gen_new();

        CassUuid uuid;

        cass_uuid_gen_random(uuid_gen, &uuid);

        char buffer[CASS_UUID_STRING_LENGTH];

        cass_uuid_string(uuid, buffer);

        std::string uuid_string(buffer);

        cass_uuid_gen_free(uuid_gen);

        return uuid_string;
    }
};

#endif //AZEROTHCORE_SCYLLADBMANAGER_H
