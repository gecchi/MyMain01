#ifndef EFFECTTURBO001_H_
#define EFFECTTURBO001_H_
namespace MyStg2nd {

/**
 * �^�[�{���G�t�F�N�g
 * @version 1.00
 * @since 2010/02/15
 * @author Masatoshi Tsuge
 */
class EffectTurbo001 : public GgafDx9LibStg::DefaultSpriteActor {

public:
    EffectTurbo001(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize() override;

    /**
     * ��OverRide �ł���
     */
    void processBehavior() override;

    void onActive() override;

    void onInactive() override;
    /**
     * ��OverRide �ł���
     */
    void processJudgement() override;

    virtual ~EffectTurbo001();
};

}
#endif /*EFFECTTURBO001_H_*/

