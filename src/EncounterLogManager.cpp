#include "EncounterLogManager.h"

std::unordered_map<std::uint_fast32_t, std::unique_ptr<EncounterLogs>> EncounterLogManager::m_logs{};
std::uint_fast32_t scope{sConfigMgr->GetOption<std::uint_fast32_t>("EncounterLogs.Logging.Scope", 3)};
