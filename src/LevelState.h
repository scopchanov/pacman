#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <QObject>
#include <QHash>

class LevelState : public QObject
{
	Q_OBJECT
public:
	explicit LevelState(QObject *parent = nullptr);

	int step() const;
	void setStep(int step);
	int mode() const;

	void setStepDuration(int step, qreal duration);
	void incrementStep();
	void advance();
	void reset();

private:
	int _step;
	qreal _time;
	QHash<int, qreal> _stepDurations;

signals:
	void modeChanged(int mode);
};

#endif // LEVELSTATE_H
