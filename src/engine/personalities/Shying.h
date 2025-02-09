#ifndef SHYING_H
#define SHYING_H

#include "AbstractPersonality.h"

class Shying : public AbstractPersonality
{
public:
	explicit Shying(GameObject *parent = nullptr);

	GameObject *partner() const;
	void setPartner(GameObject *partner);
	int type() const override;

	Vector2 calculateTarget() const override;

private:
	GameObject *_partner;
};

#endif // SHYING_H
