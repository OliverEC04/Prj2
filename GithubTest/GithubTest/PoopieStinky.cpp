#include "PoopieStinky.h"

PoopieStinky::PoopieStinky(int poop)
{
    setPoop(poop);
}

void PoopieStinky::setPoop(int poop)
{
    poop_ = poop;
}

int PoopieStinky::getPoop()
{
    return poop_;
}
