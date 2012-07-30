#ifndef MYOPTIONLOCKONCONTROLLER_H_
#define MYOPTIONLOCKONCONTROLLER_H_
namespace VioletVreath {


/**
 * ���b�N�I���R���g���[���[ .
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class MyLockonController : public GgafCore::GgafDummyActor {

public:
    /** ���C�����b�N�I���G�t�F�N�g */
    EffectLockon001_Main* pMainLockonEffect_;
    /** ���b�N�I���^�[�Q�b�g���X�g�����O */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* pRingTarget_;

    MyLockonController(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void releaseAllLockon();

    void lockon(GgafDxCore::GgafDxGeometricActor* prm_pTarget);

    virtual ~MyLockonController();
    /**
     * pRingTarget_���e�\��(�f�o�b�O�p) .
     * @param pMain
     */
    void dumpTarget(GgafDxCore::GgafDxGeometricActor* pMain);


};

}
#endif /*MYOPTIONLOCKONCONTROLLER_H_*/

