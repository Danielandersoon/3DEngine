#pragma once
#include "Component.h"
#include "Animation.h"
class Animator :
    public Component
{
public:
    std::vector<Animation> animationArray;
};

