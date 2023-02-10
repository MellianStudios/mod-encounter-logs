#ifndef AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H
#define AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H

#include "Configuration/Config.h"
#include "Chat.h"
#include "Player.h"
#include "Spell.h"
#include "ScriptMgr.h"

class EncounterLogPlayerScript : public PlayerScript
{
public:
    EncounterLogPlayerScript() : PlayerScript("EncounterLogPlayerScript")
    {}
};

#endif //AZEROTHCORE_ENCOUNTERLOGPLAYERSCRIPT_H
