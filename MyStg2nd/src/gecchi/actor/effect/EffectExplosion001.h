#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_
namespace MyStg2nd {

/**
 * 爆発エフェクトスプライト001
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class EffectExplosion001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    EffectExplosion001(const char* prm_name);

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

    virtual ~EffectExplosion001();
};

}
#endif /*EFFECTEXPLOSION001_H_*/

