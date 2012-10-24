#ifndef ENEMYTHISBELASERCHIP002_H_
#define ENEMYTHISBELASERCHIP002_H_
namespace VioletVreath {

class EnemyThisbeLaserChip002 : public GgafLib::RefractionLaserChip {


public:
    /** ���ˎ��G�t�F�N�g�f�|�W�g���ւ̐ڑ� */
    DepositoryConnection* pConn_RefractionEffectDepository_;

    GgafLib::SplineManufactureConnection* pSplManufCon_;
    GgafLib::SplineSequence* pSplSeq_;

    EnemyThisbeLaserChip002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onRefractionBegin(int prm_num_refraction) override;

    void onRefractionFinish(int prm_num_refraction) override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyThisbeLaserChip002();

};

}
#endif /*ENEMYTHISBELASERCHIP002_H_*/

