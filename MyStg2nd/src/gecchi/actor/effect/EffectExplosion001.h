#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_
namespace MyStg2nd {

/**
 * �����G�t�F�N�g�X�v���C�g001
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class EffectExplosion001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    EffectExplosion001(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize() override;

    /**
     * ��OverRide �ł���
     */
    void processBehavior() override;


    void onActive() override;

    /**
     * ��OverRide �ł���
     */
    void processJudgement() override;

    virtual ~EffectExplosion001();
};

}
#endif /*EFFECTEXPLOSION001_H_*/

