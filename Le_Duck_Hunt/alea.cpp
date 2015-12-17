#include "alea.h"

int alea(int mini, int maxi)
{
    return (rand() % (++maxi - mini))  + mini;
}
