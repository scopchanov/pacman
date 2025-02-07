#include "AiStateMachine.h"
#include "EnemyController.h"
#include <QTimer>

AiStateMachine::AiStateMachine(QObject *parent) :
	QObject{parent},
	_state{0},
	m_timer{new QTimer()}
{
	m_timer->setSingleShot(false);

	dodd();

	connect(m_timer, &QTimer::timeout, this, &AiStateMachine::switchStates);
}

void AiStateMachine::setFoo(EnemyController *ctrl)
{
	m_c = ctrl;
}

void AiStateMachine::dodd()
{
	if (!m_timer->isActive())
		m_timer->start(7000);
}

void AiStateMachine::switchStates()
{
	switch (_state) {
	case 0:
		m_timer->setInterval(20000);
		_state = 1;
		m_c->setState(EnemyController::ST_Chase);
		break;
	case 1:
		m_timer->setInterval(7000);
		_state = 0;
		m_c->setState(EnemyController::ST_Scatter);
		break;
	default:
		break;
	}

	// m_characterMovement->reverse();
}
