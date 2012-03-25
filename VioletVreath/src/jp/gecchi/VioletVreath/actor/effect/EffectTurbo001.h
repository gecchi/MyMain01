#ifndef EFFECTTURBO001_H_
#define EFFECTTURBO001_H_
namespace VioletVreath {

/**
 * �^�[�{���G�t�F�N�g
 * @version 1.00
 * @since 2010/02/15
 * @author Masatoshi Tsuge
 */
class EffectTurbo001 : public GgafLib::DefaultSpriteActor {

public:
    EffectTurbo001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectTurbo001();
};

}
#endif /*EFFECTTURBO001_H_*/
