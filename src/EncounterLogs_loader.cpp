#include "EncounterLogGlobalScript.h"
#include "EncounterLogMiscScript.h"
#include "EncounterLogPlayerScript.h"
#include "EncounterLogUnitScript.h"
#include "EncounterLogWorldScript.h"

void Addmod_encounter_logsScripts()
{
    auto enabled = sConfigMgr->GetOption<bool>("EncounterLogs.General.Enabled", true);

    if (!enabled) {
        return;
    }

    new EncounterLogGlobalScript();
    new EncounterLogMiscScript();
    new EncounterLogPlayerScript();
    new EncounterLogUnitScript();
    new EncounterLogWorldScript();
}
