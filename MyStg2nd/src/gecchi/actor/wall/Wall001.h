#ifndef WALL001_H_
#define WALL001_H_

namespace MyStg2nd {

class Wall001 : public GgafDx9LibStg::WallActor {
public:
    Wall001(const char* prm_name);

    void onCreateModel() override;

    bool isOutOfUniverse() override;

    virtual ~Wall001() {}
};

}
#endif /*WALL001_H_*/
