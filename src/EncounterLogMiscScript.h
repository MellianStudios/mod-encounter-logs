#ifndef AZEROTHCORE_ENCOUNTERLOGMISCSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGMISCSCRIPT_H

#include "EncounterLogManager.h"
#include "ScriptMgr.h"

class EncounterLogMiscScript : MiscScript
{
public:
    EncounterLogMiscScript() : MiscScript("EncounterLogMiscScript")
    {}

    void OnInstanceSave(InstanceSave *instanceSave) override
    {
        EncounterLogManager::newLog(
            instanceSave->GetMapId(),
            instanceSave->GetInstanceId(),
            EncounterLogHelpers::getTimestamp()
        );
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGMISCSCRIPT_H
