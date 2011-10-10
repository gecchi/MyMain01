#ifndef MYOPTIONLOCKONCONTROLLER_H_
#define MYOPTIONLOCKONCONTROLLER_H_
namespace MyStg2nd {


/**
 * ���b�N�I���R���g���[���[ .
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class MyOptionLockonController : public GgafCore::GgafDummyActor {

public:
    /** ���C�����b�N�I���G�t�F�N�g */
    EffectLockon001_Main* _pMainLockonEffect;
    /** ���b�N�I���^�[�Q�b�g���X�g�����O */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* _pRingTarget;

    MyOptionLockonController(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void processBehavior() override;

    void processJudgement() override;

    void releaseAllLockon();

    void lockon(GgafDxCore::GgafDxGeometricActor* prm_pTarget);

    virtual ~MyOptionLockonController();
    /**
     * _pRingTarget���e�\��(�f�o�b�O�p) .
     * @param pMain
     */
    void dumpTarget(GgafDxCore::GgafDxGeometricActor* pMain);


};

}
#endif /*MYOPTIONLOCKONCONTROLLER_H_*/

