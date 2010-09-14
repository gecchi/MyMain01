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
    /** �P�I�v�V����������̍ő�\���b�N�I�����i���C���{�T�u�j */
    static int _max_lockon_num;
    /** ���C�����b�N�I���G�t�F�N�g */
    EffectLockon001_Main* _pMainLockonEffect;
    /** ���b�N�I���^�[�Q�b�g���X�g�����O */
    GgafCore::GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor>* _pRingTarget;

    MyOptionLockonController(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void releaseAllLockon();

    void lockon(GgafDx9Core::GgafDx9GeometricActor* prm_pTarget);

    virtual ~MyOptionLockonController();
    /**
     * _pRingTarget���e�\��(�f�o�b�O�p) .
     * @param pMain
     */
    void dumpTarget(GgafDx9Core::GgafDx9GeometricActor* pMain);


};

}
#endif /*MYOPTIONLOCKONCONTROLLER_H_*/

