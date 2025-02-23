#include "Energizer.h"
#include "Game.h"
#include "GameEvent.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "GamePalette.h"
#include "PathBuilder.h"
#include "Player.h"
#include "actions/EnergizePlayer.h"
#include "actions/ScareEnemies.h"
#include "behaviors/Energizing.h"
#include "behaviors/EnergizerAnimating.h"
#include <QPen>

Energizer::Energizer(GameObject *parent) :
	GameObject(parent)
{

}

int Energizer::objectType() const
{
	return OBJ_Energizer;
}
