#ifndef EFFECTEXPLOSION003_H_
#define EFFECTEXPLOSION003_H_
namespace MyStg2nd {

/**
 * 爆発エフェクトスプライト003
 * @version 1.00
 * @since 2010/07/05
 * @author Masatoshi Tsuge
 */
class EffectExplosion003 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    EffectExplosion003(const char* prm_name);

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

    virtual ~EffectExplosion003();
};

}
#endif /*EFFECTEXPLOSION003_H_*/

