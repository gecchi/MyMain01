#ifndef MYBUNSHIN_H_
#define MYBUNSHIN_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

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

    void effectFreeModeIgnited();
    void effectFreeModeReady();
    void effectFreeModeLaunch();


    void setRadiusPosition(coord prm_radius_position);
    void addRadiusPosition(coord prm_radius_position);
    coord getRadiusPosition();

    void slideMvRadiusPosition(coord prm_target_radius_position, frame prm_spent_frames);

    void setExpanse(angvelo prm_ang_expanse);
    void addExpanse(angvelo prm_ang_expanse);
    angvelo getExpanse();
    void turnExpanse(coord prm_target_ang_expanse, frame prm_spent_frames);
};

}
#endif /*MYBUNSHIN_H_*/
