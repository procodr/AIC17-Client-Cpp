#ifndef MAPIMP_H
#define MAPIMP_H

#include "Map.h"
#include "Sewer.h"

class MapImp : public Map {
public:
    MapImp(Size size);

    const Size &getSize() const;

    Entity *getEntity(int x, int y);

    bool getShadow(int x, int y);

    Cell getDest(int x, int y);

    void addEntity(Entity &entity);

    void delEntity(int x, int y);

    void addShadow(int x, int y);

    void delShadow(int x, int y);

    void addSewer(Sewer sewer);

private:
    Size size;
    std::vector<std::vector<Entity *> > entityMap;
    std::vector<std::vector<int> > darknessMap;
    std::vector<std::vector<Cell> > destMap;

    void changeShadow(int x, int y, int delta);
};

#endif /* MAPIMP_H */
