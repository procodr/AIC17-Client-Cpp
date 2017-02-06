#ifndef SEWER_H
#define SEWER_H

class Sewer : public Entity {
public:
	Sewer(int id, Cell pos, Cell destination);
    int getDestination();
private:
	Cell destination;
};

#endif /* SEWER_H */
