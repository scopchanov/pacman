#ifndef SHYING_H
#define SHYING_H

#include "AbstractPersonality.h"

class Shying : public AbstractPersonality
{
public:
	explicit Shying(AbstractGameObject *parent = nullptr);

	AbstractGameObject *partner() const;
	void setPartner(AbstractGameObject *partner);
	int type() const override;

	Vector2 calculateTarget() const override;

private:
	AbstractGameObject *_partner;
};

#endif // SHYING_H
