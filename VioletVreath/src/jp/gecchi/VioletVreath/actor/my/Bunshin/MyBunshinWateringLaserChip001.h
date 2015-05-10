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
    /** [r]0:�񃍃b�N�I���i�͂��߂���j 1:���b�N�I�� 2:�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j */
    int lockon_st_;
    /** [r]���[�U�[���ˌ� */
    const MyBunshin* pOrg_;
    /** ���b�N�I���^�[�Q�b�g���X�g�����O */
    const GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* pOrg_pLockonCtrler_pRingTarget_;

    /** [r/w]���x�͈́i���̒l��傫������ƁA�ō����x�������Ȃ�B�j */
    static const int max_velo_renge_;
    /** �����x�͈�( max_velo_renge_ / r_max_acce_ ) */
    static const float max_acce_renge_;

    /** [r/w]���x�ɑ΂�������x�̊����i���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�j */
    static const int r_max_acce_;
    static const double rr_max_acce_;

    static int tex_no_;
    static GgafDxCore::GgafDxModel* pModel_;
    static char aaTextureName[3][51];

public:
    MyBunshinWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onDispatchedBy(MyBunshin* prm_pBunshin);
    /**
     * ���[�U�[�̃e�N�X�`����ς���
     * @param prm_tex_no
     */
    static void chengeTex(int prm_tex_no);

    virtual ~MyBunshinWateringLaserChip001();

};

}
#endif /*MYBUNSHINCURVELASERCHIP001_H_*/

