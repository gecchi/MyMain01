#ifndef WALLAAPRISMEFFECTACTOR_H_
#define WALLAAPRISMEFFECTACTOR_H_

namespace MyStg2nd  {


/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class WallAAPrismEffectActor : public GgafDx9LibStg::WallAAPrismActor {
public:
    WallAAPrismEffectActor(const char* prm_name);

    void onCreateModel() override;

    bool isOutOfUniverse() override;

    virtual ~WallAAPrismEffectActor() {}
};

}
#endif /*WALLAAPRISMEFFECTACTOR_H_*/
