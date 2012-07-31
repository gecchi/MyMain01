#ifndef MYTORPEDOCONTROLLER_H_
#define MYTORPEDOCONTROLLER_H_
namespace VioletVreath {

/**
 * �����R���g���[���[ .
 * �P�I�v�V�����ɂ��P�̋����R���g���[���[��ێ����Ă��܂��B
 * �����̔��ː��́A�P�I�v�V�����̍ő働�b�N�I���\��(MyOption::max_lockon_num_)�ƈ�v���܂��B
 * @version 1.00
 * @since 2010/09/15
 * @author Masatoshi Tsuge
 */
class MyTorpedoController : public GgafCore::GgafDummyActor {

public:
    /** [r]�e�A�N�^�[�ƂȂ�I�v�V���� */
    GgafDxCore::GgafDxGeometricActor* pOrg_;
    MyLockonController* pLockonCtrlr_;
    /** [r]�ێ����鋛���z��i�v�f���� MyOption::max_lockon_num_ �j */
    MyTorpedo** papTorpedo_;
    /** [r]�ێ����鋛�������f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_TorpedoBlast_;
    /** �������ˋ����� */
    int firing_num_;
    /** ���݋������˒����ǂ��� true:���Âꂩ�̋�����������/false:�S�Ă̋������񊈓���� */
    bool in_firing_;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pOrg �e�ƂȂ�I�v�V����
     * @return
     */
    MyTorpedoController(const char* prm_name, GgafDxCore::GgafDxGeometricActor* prm_pOrg, MyLockonController* prm_pLockonCtrlr);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    /**
     * ��������Ĕ��˂���B
     * �A���A���Âꂩ�̋������������̏ꍇ�́A�������Ȃ��B
     * �S�Ă̋������񊈓���ԂŁA�{���\�b�h�����s����Ƌ�������Ĕ��˂���B
     */
    bool fire();

    virtual ~MyTorpedoController();


};

}
#endif /*MYTORPEDOCONTROLLER_H_*/

