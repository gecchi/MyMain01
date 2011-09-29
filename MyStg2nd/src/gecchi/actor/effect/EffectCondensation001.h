#ifndef EFFECTCONDENSATION001_H_
#define EFFECTCONDENSATION001_H_
namespace MyStg2nd {

/**
 * 発射前の溜表現エフェクトその１ .
 * @version 1.00
 * @since 2010/03/19
 * @author Masatoshi Tsuge
 */
class EffectCondensation001 : public GgafLib::DefaultSpriteSetActor {

public:
    EffectCondensation001(const char* prm_name);

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

    virtual ~EffectCondensation001();
};

}
#endif /*EFFECTCONDENSATION001_H_*/

