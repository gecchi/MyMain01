#ifndef DEFAULTPOINTSPRITEEFFECTACTOR_H_
#define DEFAULTPOINTSPRITEEFFECTACTOR_H_
namespace VioletVreath {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultPointSpriteTestActor : public GgafLib::DefaultPointSpriteActor {

public:
    int CAM_ZF_;

    DefaultPointSpriteTestActor(const char* prm_name);

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

    virtual ~DefaultPointSpriteTestActor();
};

}
#endif /*DEFAULTPOINTSPRITEEFFECTACTOR_H_*/

