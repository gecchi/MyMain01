#ifndef HOSHIBOSHI001_H_
#define HOSHIBOSHI001_H_
namespace MyStg2nd {

/**
 * 爆発エフェクトスプライト001
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class HoshiBoshi001 : public GgafDx9LibStg::DefaultPointSpriteActor {

public:
    HoshiBoshi001(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    /**
     * ＜OverRide です＞
     */
    void processBehavior() override;


    void onActive() override;

    /**
     * ＜OverRide です＞
     */
    void processJudgement() override;

    virtual ~HoshiBoshi001();
};

}
#endif /*HOSHIBOSHI001_H_*/

