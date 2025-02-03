#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <QLabel>

class ScoreDisplay : public QLabel
{
	Q_OBJECT
public:
	explicit ScoreDisplay(QWidget *parent = nullptr);
};

#endif // SCOREDISPLAY_H
