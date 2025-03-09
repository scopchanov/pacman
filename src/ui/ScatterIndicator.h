#ifndef SCATTERINDICATOR_H
#define SCATTERINDICATOR_H

#include "AbstractIndicator.h"

class ScatterIndicator : public AbstractIndicator
{
	Q_OBJECT
public:
	explicit ScatterIndicator(QWidget *parent = nullptr);
};

#endif // SCATTERINDICATOR_H
