#include "EncounterLogManager.h"
#include "EncounterLogAllMapScript.h"
#include "EncounterLogMovementHandlerScript.h"
#include "EncounterLogPlayerScript.h"
#include "EncounterLogUnitScript.h"

void Addmod_encounter_logsScripts()
{
    auto enabled = sConfigMgr->GetOption<bool>("EncounterLogs.General.Enabled", true);

    if (!enabled) {
        return;
    }

    new EncounterLogMovementHandlerScript();
    new EncounterLogAllMapScript();
    new EncounterLogPlayerScript();
    new EncounterLogUnitScript();
}
