#ifndef MYBUNSHINCURVELASERCHIP001_H_
#define MYBUNSHINCURVELASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
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
     * @param chk_done true:�܂�Aim������K�v������̂��`�F�b�N���� �^ false:�`�F�b�N���Ȃ�
     * @return chk_done �� true �̏ꍇ�̂ݖ߂�l�ɈӖ�������
     *         true�F�ڕW�ɓ��B�����̂ł���������B���邢�́A�ڕW��ʂ�߂���������̂ł���������B�^false:�܂��܂�Aim�撣��
     */
    bool aimChip(int vTx, int vTy, int vTz, bool chk_done = false);

public:

    struct AimInfo {
        MyBunshinWateringLaserChip001* pLeaderChip;
        GgafDx::GeometricActor* pTarget;
        /** T1 �ڕW���W */
        coord t1_x, t1_y, t1_z;
        coord t1_x_prev, t1_y_prev, t1_z_prev;
        coord t1_ahead_x, t1_ahead_y, t1_ahead_z;
        /** T1 �֓��B���錩���݂� active_frame�B */
        frame aim_time_out_t1;
        /** T2 �ڕW���W */
        coord t2_x, t2_y, t2_z;
        /** T2 �֓��B���錩���݂� active_frame�B*/
        frame aim_time_out_t2;
        /**
         * T1 �ڕW���W�ݒ� .
         * @param x
         * @param y
         * @param z
         */
        void setT1_and_T1Ahead(coord x, coord y, coord z) {
            t1_x_prev = t1_x = t1_ahead_x = x;
            t1_y_prev = t1_y = t1_ahead_y = y;
            t1_z_prev = t1_z = t1_ahead_z = z;
        }
        /**
         * T1 �ڕW���W�X�V .
         * @param x
         * @param y
         * @param z
         */
        void updateT1(coord x, coord y, coord z) {
            t1_x_prev = t1_x;
            t1_y_prev = t1_y;
            t1_z_prev = t1_z;
            t1_x = x;
            t1_y = y;
            t1_z = z;
        }
        void setT1Ahead(coord x, coord y, coord z) {
            t1_ahead_x = x;
            t1_ahead_y = y;
            t1_ahead_z = z;
        }
        /**
         * T2 �ڕW���W���A���ʂƃx�N�g���̉������Ƃ̌�_�ɐݒ� .
         * @param r ���ʔ��a
         * @param x1
         * @param y1
         * @param z1
         * @param x2
         * @param y2
         * @param z2
         */
        void setT2BySphere(double r, double x1, double y1, double z1, double x2, double y2, double z2) {
            UTIL::getIntersectionSphereAndVec(r, x1, y1, z1, x2, y2, z2,
                                              t2_x,t2_y,t2_z);
        }
        void setT2(coord x, coord y, coord z) {
            t2_x = x;
            t2_y = y;
            t2_z = z;
        }
    };

    /** [r]���b�N�I�����Ă���ꍇ true */
    bool is_lockon_;
    /** [r]���[�U�[���ˌ� */
    MyBunshin* pOrg_;

    const LockonCursor001_Main* pLockonCursor_;

    /** [r/w]���[�U�[�ő呬�x�i���̒l��傫������ƁA�ō����x�������Ȃ�B�j */
    static const velo MAX_VELO;
    /** �����x�͈�(0, MAX_ACCE_RENGE) */
    static const acce MAX_ACCE_RENGE;

    /** [r/w]���[�U�[���ˎ��̏������x */
    static const velo INITIAL_VELO;

    /** [r/w]���x�ɑ΂�������x�̊����i���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�j */
    static const int R_MAX_ACCE;
    /** �Œᑬ�x */
    static const velo MIN_VELO_;

    static int tex_no_;
    static GgafDx::Model* pModel_;

    /** ���ݎ��g�𐧌䂵�Ă��� ���[�_�[�`�b�v��AimInfo */
    AimInfo* pLeaderChip_AimInfo_;
    /** ���g�� AimInfo�C���X�^���X */
    AimInfo aim_info_;

    /**
      * �V������Ԃ� AimInfo ���擾 .
      * @return �V���� AimInfo
      */
     AimInfo* getNewAimInfo() {
         aim_info_.pLeaderChip = nullptr;
         aim_info_.pTarget = nullptr;
         aim_info_.t1_x = 0;
         aim_info_.t1_y = 0;
         aim_info_.t1_z = 0;
         aim_info_.t1_x_prev = 0;
         aim_info_.t1_y_prev = 0;
         aim_info_.t1_z_prev = 0;
         aim_info_.t1_ahead_x = 0;
         aim_info_.t1_ahead_y = 0;
         aim_info_.t1_ahead_z = 0;
         aim_info_.aim_time_out_t1 = 400;
         aim_info_.t2_x = 0;
         aim_info_.t2_y = 0;
         aim_info_.t2_z = 0;
         aim_info_.aim_time_out_t2 = 0;
         return &aim_info_;
     }

     /**
      * �V���� �R�s�[ AimInfo ���擾 .
      * @param pOrg
      * @return
      */
     AimInfo* getNewAimInfoCopy(AimInfo* pOrg) {
         aim_info_ = (*pOrg); //�R�s�[
         return &aim_info_;
     }

    velo sgn_vx0_, sgn_vy0_, sgn_vz0_;
    int inv_cnt_;
public:
    MyBunshinWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processBehavior_Aiming();

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

