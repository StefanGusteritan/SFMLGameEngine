#include "Object.h"

Child::Child(bool activeState, bool visibility, Object *p)
{
    this->active = activeState;
    this->visible = visibility;

    this->parent = p;

    this->localPosition = this->sprite.getPosition();
    this->localRotation = this->sprite.getRotation();
    this->localScale = this->sprite.getScale();
}

bool Child::IsActive()
{
    return this->parent->IsActive() && this->active;
}

void Child::Update()
{
    this->sprite.setPosition(this->parent->GetPosition() + this->localPosition);
    this->sprite.setRotation(this->parent->GetRotation() + this->localRotation);
    this->sprite.setScale(this->parent->GetScale() + this->localScale);
}

bool Child::IsVisible()
{
    return this->parent->IsVisible() && this->visible;
}
