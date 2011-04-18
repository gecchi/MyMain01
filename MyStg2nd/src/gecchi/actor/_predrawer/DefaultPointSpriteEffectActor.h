#ifndef DEFAULTPOINTSPRITEEFFECTACTOR_H_
#define DEFAULTPOINTSPRITEEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultPointSpriteEffectActor : public GgafDx9LibStg::DefaultPointSpriteActor {

public:
    int _CAM_ZF;

    DefaultPointSpriteEffectActor(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

//    void processPreDraw() override;

    int isOutOfView() override;

    bool isOutOfUniverse() override;

    virtual ~DefaultPointSpriteEffectActor();
};

}
#endif /*DEFAULTPOINTSPRITEEFFECTACTOR_H_*/

