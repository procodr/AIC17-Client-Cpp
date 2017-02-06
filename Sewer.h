#ifndef SEWER_H
#define SEWER_H

#include "Entity.h"

class Sewer : public Entity {
public:
    Sewer(int id, Cell pos, int destId);

    int getDestId();

private:
    int destId;
};

#endif /* SEWER_H */
