#ifndef FISH_H
#define FISH_H

class Fish
{
public:
    Fish(int id, int x, int y, bool color, bool queen, bool sick, bool team);

    int getId();
    pair<int, int> getPos();
    bool getColor();
    bool isQueen();
    bool isSick();
    bool getTeam();

    Node * getNode(int index);

private:
    int id;
    int x, y;
    bool color, queen, sick, team;
};

#endif
