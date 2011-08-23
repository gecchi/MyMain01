#ifndef MYOPTIONTORPEDOCONTROLLER_H_
#define MYOPTIONTORPEDOCONTROLLER_H_
namespace MyStg2nd {

/**
 * �����R���g���[���[ .
 * �P�I�v�V�����ɂ��P�̋����R���g���[���[��ێ����Ă��܂��B
 * �����̔��ː��́A�P�I�v�V�����̍ő働�b�N�I���\��(MyOption::_max_lockon_num)�ƈ�v���܂��B
 * @version 1.00
 * @since 2010/09/15
 * @author Masatoshi Tsuge
 */
class MyOptionTorpedoController : public GgafCore::GgafDummyActor {

public:
    /** [r]�e�A�N�^�[�ƂȂ�I�v�V���� */
    MyOption* _pMyOption;
    /** [r]�ێ����鋛���z��i�v�f���� MyOption::_max_lockon_num �j */
    MyTorpedo** _papMyTorpedo;
    /** [r]�ێ����鋛�������f�|�W�g�� */
    GgafCore::GgafActorDepository* _pDepo_TorpedoBlast;
    /** �������ˋ����� */
    int _firing_num;
    /** ���݋������˒����ǂ��� true:���Âꂩ�̋�����������/false:�S�Ă̋������񊈓���� */
    bool _in_firing;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pMyOption �e�ƂȂ�I�v�V����
     * @return
     */
    MyOptionTorpedoController(const char* prm_name, MyOption* prm_pMyOption);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

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

