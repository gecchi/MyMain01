#ifndef EFFECTENTRANCE003_H_
#define EFFECTENTRANCE003_H_
namespace VioletVreath {

/**
 * 登場エフェクト、その3 .
 * @version 1.00
 * @since 2012/07/18
 * @author Masatoshi Tsuge
 */
class EffectEntry003 : public GgafLib::DefaultSpriteSetActor {

public:
    EffectEntry003(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectEntry003();
};

}
#endif /*EFFECTENTRANCE003_H_*/

