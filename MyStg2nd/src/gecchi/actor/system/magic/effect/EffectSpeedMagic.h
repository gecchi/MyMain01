#ifndef EFFECTSPEEDMAGIC_H_
#define EFFECTSPEEDMAGIC_H_
namespace MyStg2nd {

/**
 * スピードアップのエフェクト .
 * @version 1.00
 * @since 2011/11/16
 * @author Masatoshi Tsuge
 */
class EffectSpeedMagic : public GgafLib::DefaultSpriteActor {

public:
    EffectSpeedMagic(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectSpeedMagic();
};

}
#endif /*EFFECTSPEEDMAGIC_H_*/

