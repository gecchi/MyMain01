#ifndef EFFECTTURBO002_H_
#define EFFECTTURBO002_H_
namespace MyStg2nd {

/**
 * �^�[�{�����G�t�F�N�g
 * @version 1.00
 * @since 2010/02/25
 * @author Masatoshi Tsuge
 */
class EffectTurbo002 : public GgafLib::DefaultSpriteActor {

public:
    EffectTurbo002(const char* prm_name);

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

    virtual ~EffectTurbo002();
};

}
#endif /*EFFECTTURBO002_H_*/

