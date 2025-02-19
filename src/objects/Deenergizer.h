#ifndef DEENERGIZER_H
#define DEENERGIZER_H

#include "GameObject.h"

class Deenergizer : public GameObject
{
public:
	explicit Deenergizer(GameObject *parent = nullptr);

	void reset() override ;

	int objectType() const override final;
};

#endif // DEENERGIZER_H
