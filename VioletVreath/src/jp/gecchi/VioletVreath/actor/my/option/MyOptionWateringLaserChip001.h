#ifndef MYOPTIONCURVELASERCHIP001_H_
#define MYOPTIONCURVELASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

/**
 * �I�v�V�������[�U�[�̃`�b�v .
 * WateringLaserChip �� ���b�N�I���@�\��ǉ��B
 * (WateringLaserChip���番������)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class MyOptionWateringLaserChip001 : public GgafLib::WateringLaserChip {
    /** �ϋv�͏����ݒ�l */
    int default_stamina_;
    /** �����x�͈�( max_velo_renge_ / r_max_acce_ ) */
    float max_acce_renge_;
    /** �`�b�v�̓������v�Z */
    void moveChip(int vTx, int vTy, int vTz);

public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** [r]���b�N�I�����Ă���ꍇ true */
    bool is_lockon_;
    /** [r]0:�񃍃b�N�I���i�͂��߂���j 1:���b�N�I�� 2:�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j */
    int lockon_st_;
    /** [r]���[�U�[���ˌ� */
    MyOption* pOrg_;
    /** [r/w]���x�͈́i���̒l��傫������ƁA�ō����x�������Ȃ�B�j */
    int max_velo_renge_;
    /** [r/w]���x�ɑ΂�������x�̊����i���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�j */
    int r_max_acce_;
    double rr_max_acce_;
    static int tex_no_;
    static GgafDxCore::GgafDxModel* pModel_;
    static char aaTextureName[3][51];

public:
    MyOptionWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    /**
     * ���[�U�[�̃e�N�X�`����ς���
     * @param prm_tex_no
     */
    static void chengeTex(int prm_tex_no);

    virtual ~MyOptionWateringLaserChip001();

};

}
#endif /*MYOPTIONCURVELASERCHIP001_H_*/

