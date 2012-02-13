#ifndef EFFECTMYSHIPEXPLOSION_H_
#define EFFECTMYSHIPEXPLOSION_H_
namespace VioletVreath {

/**
 * ���@����
 * @version 1.00
 * @since 2010/11/10
 * @author Masatoshi Tsuge
 */
class EffectMyShipExplosion : public GgafLib::DefaultSpriteSetActor {

public:
    EffectMyShipExplosion(const char* prm_name);

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

    virtual ~EffectMyShipExplosion();
};

}
#endif /*EFFECTMYSHIPEXPLOSION_H_*/

