#ifndef MANAGELEVELMODE_H
#define MANAGELEVELMODE_H

#include "AbstractTimedAction.h"
#include <QHash>

class LevelMode;

class ManageLevelMode : public AbstractTimedAction
{
	Q_OBJECT
public:
	explicit ManageLevelMode(AbstractComponent *parent = nullptr);

	void setStepDuration(int step, qreal duration);
	int type() const override;
	void reset() override;

protected:
	void performTasks() override;

private:
	LevelMode *levelMode() const;

	qreal _time;
	QHash<int, qreal> _stepDurations;
};

#endif // MANAGELEVELMODE_H
