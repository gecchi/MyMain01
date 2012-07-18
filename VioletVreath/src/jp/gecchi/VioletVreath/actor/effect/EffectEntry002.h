#ifndef EFFECTENTRANCE002_H_
#define EFFECTENTRANCE002_H_
namespace VioletVreath {

/**
 * 登場エフェクト、その2 .
 * @version 1.00
 * @since 2012/07/18
 * @author Masatoshi Tsuge
 */
class EffectEntry002 : public GgafLib::DefaultSpriteSetActor {

public:
    EffectEntry002(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectEntry002();
};

}
#endif /*EFFECTENTRANCE002_H_*/

