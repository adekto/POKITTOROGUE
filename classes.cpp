//#include "sprites.h"
class Ent {
    public:
    int x,y;
    int id=11;
    Ent(int xx,int yy) {x=xx; y=yy;};
    void draw();
};


class Goblin : public Ent {
    public:

    int id=11;
};
