#ifndef EFFECTENTRANCE001_H_
#define EFFECTENTRANCE001_H_
namespace VioletVreath {

/**
 * 登場エフェクト、その１ .
 * @version 1.00
 * @since 2012/06/11
 * @author Masatoshi Tsuge
 */
class EffectEntrance001 : public GgafLib::DefaultSpriteSetActor {

public:
    EffectEntrance001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectEntrance001();
};

}
#endif /*EFFECTENTRANCE001_H_*/

