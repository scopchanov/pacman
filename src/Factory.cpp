#include "Factory.h"
#include "GameGlobals.h"
#include "components/actions/orientate/OrientateEye.h"
#include "components/actions/orientate/OrientatePlayer.h"
#include "components/actions/animate/AnimateEnemy.h"
#include "components/actions/animate/AnimateEnergizer.h"
#include "components/actions/animate/AnimatePlayer.h"
#include "components/actions/animate/AnimateTeleporter.h"
#include "components/actions/control/ControlEnemy.h"
#include "components/actions/control/ControlPlayer.h"
#include "personalities/Poking.h"
#include "personalities/Shadowing.h"
#include "personalities/Shying.h"
#include "personalities/Speeding.h"

Factory::Factory(QObject *parent) :
	QObject{parent}
{

}

AbstractAction *Factory::createAnimate(int type)
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

AbstractControl *Factory::createControl(int type)
{
	switch (type) {
	case OBJ_Player:
		return new ControlPlayer();
	case OBJ_Enemy:
		return new ControlEnemy();
	default:
		return nullptr;
	}
}

AbstractOrientate *Factory::createOrientate(int type)
{
	switch (type) {
	case OBJ_Player:
		return new OrientatePlayer();
	case OBJ_Enemy:
		return new OrientateEye();
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
