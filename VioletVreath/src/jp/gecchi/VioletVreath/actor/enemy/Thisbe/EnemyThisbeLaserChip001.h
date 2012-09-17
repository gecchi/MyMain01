#ifndef ENEMYTHISBELASERCHIP001_H_
#define ENEMYTHISBELASERCHIP001_H_
namespace VioletVreath {

/**
 * �G�@�V�Y�r�[�̃��[�U�[�`�b�v����1 .
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyThisbeLaserChip001 : public GgafLib::HomingLaserChip {

public:

    GgafLib::SplineManufactureConnection* pSplManufCon_;
    GgafLib::SplineSequence* pSplSeq_;
    EnemyThisbeLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;
    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * �擪�`�b�v�̓������`
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyThisbeLaserChip001();

};

}
#endif /*ENEMYTHISBELASERCHIP001_H_*/
