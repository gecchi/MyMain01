#ifndef EFFECTENTRANCE001_H_
#define EFFECTENTRANCE001_H_
namespace VioletVreath {

/**
 * �o��G�t�F�N�g�A����1 .
 * @version 1.00
 * @since 2012/06/11
 * @author Masatoshi Tsuge
 */
class EffectEntry001 : public GgafLib::DefaultSpriteSetActor {

public:
    EffectEntry001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectEntry001();
};

}
#endif /*EFFECTENTRANCE001_H_*/

