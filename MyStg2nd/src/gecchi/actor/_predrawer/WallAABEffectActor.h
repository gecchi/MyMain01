#ifndef WALLAABEFFECTACTOR_H_
#define WALLAABEFFECTACTOR_H_

namespace MyStg2nd  {


/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class WallAABEffectActor : public GgafDx9LibStg::WallAABActor {
public:
    WallAABEffectActor(const char* prm_name);

    void onCreateModel() override;

    bool isOutOfUniverse() override;

    virtual ~WallAABEffectActor() {}
};

}
#endif /*WALLAABEFFECTACTOR_H_*/
