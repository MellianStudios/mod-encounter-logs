#include "EncounterLogManager.h"

bool EncounterLogHelpers::m_is_scylla{false};
bool EncounterLogHelpers::m_is_database{false};

std::unordered_map<std::uint_fast32_t, std::unique_ptr<EncounterLogs>> EncounterLogManager::m_logs{};
std::unordered_map<std::uint_fast32_t, bool> EncounterLogManager::m_players_in_combat{};
std::unique_ptr<EncounterLogActiveInstanceTracker> EncounterLogManager::m_instance_tracker{nullptr};
bool EncounterLogManager::m_open_world_tracking{false};
std::unordered_map<std::uint_fast32_t, bool> EncounterLogManager::m_open_world_tracked_creature_entries{};
std::unordered_map<std::uint_fast32_t, bool> EncounterLogManager::m_open_world_tracked_creature_guids{};
std::uint_fast32_t EncounterLogManager::m_scope{};
