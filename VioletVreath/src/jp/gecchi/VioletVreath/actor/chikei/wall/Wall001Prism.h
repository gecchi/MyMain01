#ifndef WALL001PRISM_H_
#define WALL001PRISM_H_

namespace VioletVreath  {

/**
 * 壁ブロック(プリズム型)その１
 * @version 1.00
 * @since 2011/01/09
 * @author Masatoshi Tsuge
 */
class Wall001Prism : public GgafLib::WallAAPrismActor {
public:
    Wall001Prism(const char* prm_name);

    void onCreateModel() override;

    void processBehavior() override;

    bool isOutOfUniverse() override;

    virtual ~Wall001Prism() {}
};

}
#endif /*WALL001PRISM_H_*/
