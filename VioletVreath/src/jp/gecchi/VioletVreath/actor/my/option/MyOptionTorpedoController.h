#ifndef MYOPTIONTORPEDOCONTROLLER_H_
#define MYOPTIONTORPEDOCONTROLLER_H_
namespace VioletVreath {

/**
 * �����R���g���[���[ .
 * �P�I�v�V�����ɂ��P�̋����R���g���[���[��ێ����Ă��܂��B
 * �����̔��ː��́A�P�I�v�V�����̍ő働�b�N�I���\��(MyOption::max_lockon_num_)�ƈ�v���܂��B
 * @version 1.00
 * @since 2010/09/15
 * @author Masatoshi Tsuge
 */
class MyOptionTorpedoController : public GgafCore::GgafDummyActor {

public:
    /** [r]�e�A�N�^�[�ƂȂ�I�v�V���� */
    MyOption* pMyOption_;
    /** [r]�ێ����鋛���z��i�v�f���� MyOption::max_lockon_num_ �j */
    MyTorpedo** papMyTorpedo_;
    /** [r]�ێ����鋛�������f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_TorpedoBlast_;
    /** �������ˋ����� */
    int firing_num_;
    /** ���݋������˒����ǂ��� true:���Âꂩ�̋�����������/false:�S�Ă̋������񊈓���� */
    bool in_firing_;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pMyOption �e�ƂȂ�I�v�V����
     * @return
     */
    MyOptionTorpedoController(const char* prm_name, MyOption* prm_pMyOption);

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
    void fire();

    virtual ~MyOptionTorpedoController();


};

}
#endif /*MYOPTIONTORPEDOCONTROLLER_H_*/

