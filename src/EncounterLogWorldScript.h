#ifndef AZEROTHCORE_ENCOUNTERLOGWORLDSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGWORLDSCRIPT_H

#include "EncounterLogManager.h"
#include "ScriptMgr.h"

class EncounterLogWorldScript : WorldScript
{
public:
    EncounterLogWorldScript() : WorldScript("EncounterLogWorldScript")
    {}

    void OnStartup() override
    {
        EncounterLogManager::init();
    }
};

#endif //AZEROTHCORE_ENCOUNTERLOGWORLDSCRIPT_H
