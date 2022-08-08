#ifndef MYBUNSHIN_H_
#define MYBUNSHIN_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEffectActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

namespace VioletVreath {

DECLARE_HASHVAL(EVENT_MyBunshin_ChangeGeoFinal);

#define MAX_LASER_CHIP_NUM (85)
#define MAX_AIM_INFO_NUM (MAX_LASER_CHIP_NUM / 2)

//class MyBunshin : public GgafLib::DefaultMorphMeshActor {
class MyBunshin : public VvEffectActor<GgafLib::DefaultMeshSetActor> {

public:
    MyBunshinBase* pBase_;
    /** [r]�V���b�g�̃f�|�W�g�� */
    GgafCore::ActorDepository* pDepo_MyBunshinShot_;
//    /** [r]�X�i�C�v�V���b�g�̃f�|�W�g�� */
//    GgafCore::ActorDepository* pDepo_MySnipeBunshinShot_;
    /** [r]���[�U�[�`�b�v�̃f�|�W�g�� */
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /** [r]���b�N�I���R���g���[���[ */
    MyLockonController* pLockonCtrler_;
    /** [r]�����R���g���[���[ */
    MyTorpedoController* pTorpedoCtrler_;
public:
    struct AimInfo {
        MyBunshinWateringLaserChip001* pLeaderChip;
        GgafDx::GeometricActor* pTarget;
        /** �ڕW1 */
        coord t1_x, t1_y, t1_z;
        frame spent_frames_to_t1;
        frame aim_time_out_t1;
        /** �ڕW2 */
        coord t2_x, t2_y, t2_z;
        frame spent_frames_to_t2;

        void setT2(double r, double x1, double y1, double z1, double x2, double y2, double z2) {
            UTIL::getIntersectionSphereAndVec(r, x1, y1, z1, x2, y2, z2,
                                              t2_x,t2_y,t2_z);
        }
    };
    AimInfo pass_p_[MAX_AIM_INFO_NUM];
    int pass_p_seq_;
    AimInfo* getAimInfo() {
        pass_p_seq_++;
        if (pass_p_seq_ >= MAX_AIM_INFO_NUM) {
            pass_p_seq_ = 0;
        }
        AimInfo* ap = &(pass_p_[pass_p_seq_]);
        ap->pLeaderChip = nullptr;
        ap->pTarget = nullptr;
        ap->t1_x = 0;
        ap->t1_y = 0;
        ap->t1_z = 0;
        ap->spent_frames_to_t1 = 0;
        ap->aim_time_out_t1 = 400;
        ap->t2_x = 0;
        ap->t2_y = 0;
        ap->t2_z = 0;
        ap->spent_frames_to_t2 = 0;
        return ap;
    }

public:
    MyBunshin(const char* prm_name, MyBunshinBase* prm_pBase);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processChangeGeoFinal() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~MyBunshin();

    /**
     * �t���[���[�h�ֈڍs���̓_�΃G�t�F�N�g .
     */
    void effectFreeModeIgnited();
    /**
     * �_�΃G�t�F�N�g��̔��ˏ���OK�G�t�F�N�g .
     */
    void effectFreeModeReady();
    /**
     * ���˃G�t�F�N�g
     */
    void effectFreeModeLaunch();
    /**
     * �t���[���[�h�ֈꎞ��~���̃G�t�F�N�g .
     */
    void effectFreeModePause();

    void setRadiusPosition(coord prm_radius_pos);
    void addRadiusPosition(coord prm_radius_pos);
    coord getRadiusPosition();

    void slideMvRadiusPosition(coord prm_target_radius_pos, frame prm_spent_frames);

    void setExpanse(angvelo prm_ang_expanse);
    void addExpanse(angvelo prm_ang_expanse);
    angvelo getExpanse();
    void turnExpanse(coord prm_target_ang_expanse, frame prm_spent_frames);
};

}
#endif /*MYBUNSHIN_H_*/

