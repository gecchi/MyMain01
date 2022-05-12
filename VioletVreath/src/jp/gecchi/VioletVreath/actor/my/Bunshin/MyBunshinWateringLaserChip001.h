#ifndef MYBUNSHINCURVELASERCHIP001_H_
#define MYBUNSHINCURVELASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "MyBunshin.h"
#include <fstream>

namespace VioletVreath {

/**
 * ���g���[�U�[�̃`�b�v .
 * WateringLaserChip �� ���b�N�I���@�\��ǉ��B
 * (WateringLaserChip���番������)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class MyBunshinWateringLaserChip001 : public VvMyActor<GgafLib::WateringLaserChip> {
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

    /** [r]���b�N�I�����Ă���ꍇ true */
    bool is_lockon_;

    /** [r]���[�U�[���ˌ� */
    MyBunshin* pOrg_;

    const LockonCursor001_Main* pLockonCursor_;


    /** [r/w]���x�͈́i���̒l��傫������ƁA�ō����x�������Ȃ�B�j */
    static const velo MAX_VELO_RENGE;
    /** [r]�v�Z�p */
    static const double INV_MAX_VELO_RENGE;
    /** �����x�͈�(0, MAX_ACCE_RENGE) */
    static const acce MAX_ACCE_RENGE;

    static const velo INITIAL_VELO;

    /** [r/w]���x�ɑ΂�������x�̊����i���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�j */
    static const int R_MAX_ACCE;
    static const double RR_MAX_ACCE;
    /** �Œᑬ�x */
    static const velo MIN_VELO_;

    static int tex_no_;
    static GgafDx::Model* pModel_;

    MyBunshin::AimInfo* pAimInfo_;

    coord tmp_x_, tmp_y_, tmp_z_;

    velo sgn_vx0_, sgn_vy0_, sgn_vz0_;
    int inv_cnt_;
public:
    MyBunshinWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

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

