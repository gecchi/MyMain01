#ifndef MYBUNSHINCURVELASERCHIP001_H_
#define MYBUNSHINCURVELASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

/**
 * ���g���[�U�[�̃`�b�v .
 * WateringLaserChip �� ���b�N�I���@�\��ǉ��B
 * (WateringLaserChip���番������)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class MyBunshinWateringLaserChip001 : public GgafLib::WateringLaserChip {
    /** �ϋv�͏����ݒ�l */
    int default_stamina_;

    /**
     * �I�i���b�N�I�����W�j�փ��[�U�[�`�b�v���ړ�������ׂ̍��W���v�Z
     * @param vTx �ڕWX���W
     * @param vTy �ڕWY���W
     * @param vTz �ڕWZ���W
     */
    void aimChip(int vTx, int vTy, int vTz);

public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** [r]���b�N�I�����Ă���ꍇ true */
    bool is_lockon_;
    /**
     * 0:�񃍃b�N�I���i�͂��߂���j �Ȃ̂ŁA�����̐������[�U�[���
     * 1:���b�N�I��������A�ڕW�Ɍ������Ĉړ����郂�[�h�B
     * 2:�ڕW�ɓ��B�������A�����̓��b�N�I�����O��āA�]���̈ړ����[�h�B
     */
    int lockon_st_;

    /** [r]���[�U�[���ˌ� */
    const MyBunshin* pOrg_;
    /** ���b�N�I���^�[�Q�b�g���X�g�����O */
//    const GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* pOrg_pLockonCtrler_pRingTarget_;


    const EffectLockon001_Main* pLockon_;


    /** [r/w]���x�͈́i���̒l��傫������ƁA�ō����x�������Ȃ�B�j */
    static const int MAX_VELO_RENGE;
    /** �����x�͈�(-MAX_ACCE_RENGE, MAX_ACCE_RENGE) */
    static const float MAX_ACCE_RENGE;

    /** [r/w]���x�ɑ΂�������x�̊����i���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�j */
    static const int R_MAX_ACCE;
    static const double RR_MAX_ACCE;

    static int tex_no_;
    static GgafDxCore::GgafDxModel* pModel_;


    GgafDxCore::GgafDxGeometricActor* pAimTarget_;

public:
    MyBunshinWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    /** ���˂��� */
    void setOrg(MyBunshin* prm_pOrg);

    /**
     * ���[�U�[�̃e�N�X�`����ς���
     * @param prm_tex_no
     */
    static void chengeTex(int prm_tex_no);

    virtual ~MyBunshinWateringLaserChip001();

};

}
#endif /*MYBUNSHINCURVELASERCHIP001_H_*/

