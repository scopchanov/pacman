#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <QObject>
#include <QHash>

class LevelState : public QObject
{
	Q_OBJECT
public:
	explicit LevelState(QObject *parent = nullptr);

	int mode() const;
	void setStepDuration(int step, qreal duration);
	void advance();
	void reset();

private:
	int _step;
	qreal _time;
	QHash<int, qreal> _stepDurations;

signals:
	void modeChanged();
};

#endif // LEVELSTATE_H
