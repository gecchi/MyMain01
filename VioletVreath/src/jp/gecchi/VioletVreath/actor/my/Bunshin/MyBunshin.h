#ifndef MYBUNSHIN_H_
#define MYBUNSHIN_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"
namespace VioletVreath {



HASHVAL(EVENT_MyBunshin_ChangeGeoFinal);


//class MyBunshin : public GgafLib::DefaultMorphMeshActor {
class MyBunshin : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_FIRE_LASER  ,
        SE_FIRE_SHOT   ,
        SE_FIRE_TORPEDO,
    };
    MyBunshinBase* pBase_;
    /** [r]�V���b�g�̃f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_MyBunshinShot_;
    /** [r]�X�i�C�v�V���b�g�̃f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_MySnipeBunshinShot_;
    /** [r]���[�U�[�`�b�v�̃f�|�W�g�� */
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /** [r]���b�N�I���R���g���[���[ */
    MyLockonController* pLockonCtrler_;
    /** [r]�����R���g���[���[ */
    MyTorpedoController* pTorpedoCtrler_;

    /** [r]�g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;
    /** [r]�t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** [r]�J���[���X�g���� */
    GgafDxCore::GgafDxColorist* pColorist_;
public:
    struct AimInfo {
        frame begining_frame_of_GameScene_;
        MyBunshinWateringLaserChip001* pLeaderChip_;
        GgafDxCore::GgafDxGeometricActor* pTarget;
        /** �ڕW1 */
        coord t1_x, t1_y, t1_z;
        frame _spent_frames_to_t1;
        /** �ڕW2 */
        coord t2_x, t2_y, t2_z;
        frame _spent_frames_to_t2;
        void setT2(double r, double x1, double y1, double z1, double x2, double y2, double z2) {
            UTIL::getIntersectionSphereAndVec(r, x1, y1, z1, x2, y2, z2,
                                              t2_x,t2_y,t2_z);
        }
    };
    AimInfo pass_p_[20];
    int pass_p_seq_;
    AimInfo* getAimInfo() {
        pass_p_seq_++;
        if (pass_p_seq_ >= 20) {
            pass_p_seq_ = 0;
        }
        AimInfo* ap = &(pass_p_[pass_p_seq_]);
        ap->begining_frame_of_GameScene_ = P_GAME_SCENE->getBehaveingFrame();
        ap->pLeaderChip_ = nullptr;
        ap->pTarget = nullptr;
        ap->t1_x = 0;
        ap->t1_y = 0;
        ap->t1_z = 0;
        ap->_spent_frames_to_t1 = 0;
        ap->t2_x = 0;
        ap->t2_y = 0;
        ap->t2_z = 0;
        ap->_spent_frames_to_t2 = 0;
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

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

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

    void setRadiusPosition(coord prm_radius_place);
    void addRadiusPosition(coord prm_radius_place);
    coord getRadiusPosition();

    void slideMvRadiusPosition(coord prm_target_radius_place, frame prm_spent_frames);

    void setExpanse(angvelo prm_ang_expanse);
    void addExpanse(angvelo prm_ang_expanse);
    angvelo getExpanse();
    void turnExpanse(coord prm_target_ang_expanse, frame prm_spent_frames);
};

}
#endif /*MYBUNSHIN_H_*/

