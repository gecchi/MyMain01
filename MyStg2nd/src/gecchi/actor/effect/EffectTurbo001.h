#ifndef EFFECTTURBO001_H_
#define EFFECTTURBO001_H_
namespace MyStg2nd {

/**
 * ターボ溜エフェクト
 * @version 1.00
 * @since 2010/02/15
 * @author Masatoshi Tsuge
 */
class EffectTurbo001 : public GgafDx9LibStg::DefaultSpriteActor {

public:
    EffectTurbo001(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    /**
     * ＜OverRide です＞
     */
    void processBehavior() override;

    void onActive() override;

    void onInactive() override;
    /**
     * ＜OverRide です＞
     */
    void processJudgement() override;

    virtual ~EffectTurbo001();
};

}
#endif /*EFFECTTURBO001_H_*/

