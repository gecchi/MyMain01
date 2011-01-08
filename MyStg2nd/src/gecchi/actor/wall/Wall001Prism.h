#ifndef WALL001PRISM_H_
#define WALL001PRISM_H_

namespace MyStg2nd  {

/**
 * ï«ÉuÉçÉbÉNÇªÇÃÇP
 */
class Wall001Prism : public GgafDx9LibStg::WallAAPrismActor {
public:
    Wall001Prism(const char* prm_name);

    void onCreateModel() override;

    bool isOutOfUniverse() override;

    virtual ~Wall001Prism() {}
};

}
#endif /*WALL001PRISM_H_*/
