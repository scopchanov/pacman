#ifndef MANAGELEVELSTATE_H
#define MANAGELEVELSTATE_H

#include "AbstractTimedAction.h"
#include <QHash>

class LevelState;

class ManageLevelState : public AbstractTimedAction
{
	Q_OBJECT
public:
	explicit ManageLevelState(AbstractComponent *parent = nullptr);

	void setStepDuration(int step, qreal duration);
	int type() const override;
	void reset() override;

protected:
	void performTasks() override;

private:
	LevelState *levelState() const;

	qreal _time;
	QHash<int, qreal> _stepDurations;
};

#endif // MANAGELEVELSTATE_H
