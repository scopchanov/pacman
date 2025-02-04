#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <QLabel>

class ScoreDisplay : public QLabel
{
	Q_OBJECT
public:
	explicit ScoreDisplay(QWidget *parent = nullptr);

	void setScore(int value);
};

#endif // SCOREDISPLAY_H
