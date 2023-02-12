#include "EncounterLogManager.h"

std::unordered_map<std::uint_fast32_t, std::unique_ptr<EncounterLogs>> EncounterLogManager::m_logs{};
