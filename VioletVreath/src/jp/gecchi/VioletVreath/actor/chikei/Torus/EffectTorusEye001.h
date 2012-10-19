#ifndef EFFECTTORUSEYE001_H_
#define EFFECTTORUSEYE001_H_
namespace VioletVreath {

/**
 * トーラス目玉レーザー発射前チャージエフェクト
 * @version 1.00
 * @since 2012/10/19
 * @author Masatoshi Tsuge
 */
class EffectTorusEye001 : public GgafLib::DefaultSpriteActor {

public:
    int cnt_;

    EffectTorusEye001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectTorusEye001();
};

}
#endif /*EFFECTTORUSEYE001_H_*/

