#include "EncounterLogGlobalScript.h"
#include "EncounterLogMiscScript.h"
#include "EncounterLogPlayerScript.h"
#include "EncounterLogUnitScript.h"
#include "EncounterLogWorldScript.h"

#if __has_include(<cassandra.h>)

#include "ScyllaDBManager.h"

#endif

void Addmod_encounter_logsScripts()
{
    auto enabled = sConfigMgr->GetOption<bool>("EncounterLogs.General.Enabled", true);

    if (!enabled) {
        return;
    }

    EncounterLogHelpers::init();

    if (!EncounterLogHelpers::isScylla() && !EncounterLogHelpers::isDatabase()) {
        LOG_FATAL("encounter_logs", "Invalid database connector");
    }

    if (EncounterLogHelpers::isScylla()) {
        ScyllaDBManager scylla{};

        scylla.createSchema();
        scylla.updateSchema();
    }

    new EncounterLogGlobalScript();
    new EncounterLogMiscScript();
    new EncounterLogPlayerScript();
    new EncounterLogUnitScript();
    new EncounterLogWorldScript();
}
