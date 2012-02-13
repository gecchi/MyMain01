#ifndef HOSHIBOSHI002_H_
#define HOSHIBOSHI002_H_
namespace VioletVreath {
//現在未使用
/**
 * 爆発エフェクトスプライト002
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class HoshiBoshi002 : public GgafLib::DefaultPointSpriteActor {

public:
    int _CAM_ZF;

    HoshiBoshi002(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

    int isOutOfView() override;

    bool isOutOfUniverse() override;

    virtual ~HoshiBoshi002();
};

}
#endif /*HOSHIBOSHI002_H_*/

