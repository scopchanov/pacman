#ifndef DEENERGIZER_H
#define DEENERGIZER_H

#include "AbstractGameObject.h"

class Deenergizer : public AbstractGameObject
{
public:
	explicit Deenergizer(AbstractGameObject *parent = nullptr);

	void reset() override ;

	int objectType() const override final;
};

#endif // DEENERGIZER_H
