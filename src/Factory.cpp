#include "Factory.h"
#include "GameGlobals.h"
#include "actions/EyeOrientate.h"
#include "actions/PlayerOrientate.h"
#include "actions/animate/AnimateEnemy.h"
#include "actions/animate/AnimateEnergizer.h"
#include "actions/animate/AnimatePlayer.h"
#include "actions/animate/AnimateTeleporter.h"
#include "behaviors/EnemyControlling.h"
#include "behaviors/PlayerControlling.h"
#include "personalities/Poking.h"
#include "personalities/Shadowing.h"
#include "personalities/Shying.h"
#include "personalities/Speeding.h"

Factory::Factory(QObject *parent) :
	QObject{parent}
{

}

AbstractAction *Factory::createAnimating(int type)
{
	switch (type) {
	case OBJ_Player:
		return new AnimatePlayer();
	case OBJ_Enemy:
		return new AnimateEnemy();
	case OBJ_Energizer:
		return new AnimateEnergizer();
	case OBJ_Teleporter:
		return new AnimateTeleporter();
	default:
		return nullptr;
	}
}

AbstractControllingBehavior *Factory::createControlling(int type)
{
	switch (type) {
	case OBJ_Player:
		return new PlayerControlling();
	case OBJ_Enemy:
		return new EnemyControlling();
	default:
		return nullptr;
	}
}

AbstractOrientate *Factory::createOrientating(int type)
{
	switch (type) {
	case OBJ_Player:
		return new PlayerOrientate();
	case OBJ_Enemy:
		return new EyeOrientate();
	default:
		return nullptr;
	}
}

AbstractPersonality *Factory::createPersonality(int type)
{
	switch (type) {
	case PT_Shadowing:
		return new Shadowing();
	case PT_Speeding:
		return new Speeding();
	case PT_Shying:
		return new Shying();
	case PT_Poking:
		return new Poking();
	default:
		return nullptr;
	}
}
