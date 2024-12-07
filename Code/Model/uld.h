#ifndef ULD_H
#define ULD_H

using namespace std;

class ULD
{
public:
    int uldIdentifier, length, width, height, weightLimit;

    ULD(int uldIdentifier, int length, int width, int height, int weightLimit)
    {
        this->uldIdentifier = uldIdentifier;
        this->length = length;
        this->width = width;
        this->height = height;
        this->weightLimit = weightLimit;
    }

    ULD()
    {
        this->uldIdentifier = 0;
        this->length = 0;
        this->width = 0;
        this->height = 0;
        this->weightLimit = 0;
    }
};

#endif