#ifndef SMPWORLD_H_
#define SMPWORLD_H_
namespace SimpleSample {

/**
 * ���E�V�[���̐��` .
 * GgafLib::DefaultScene ���p�����ăV�[���N���X���쐬���ĉ������B<BR>
 * �{�T���v���ł́u���E�v�V�[���Ɩ��Â��܂����B<BR>
 * processBehavior() ���I�[�o�[���C�h���A���t���[���̏������L�q���܂��B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpWorld : public GgafLib::DefaultScene {

public:
    /** ���͎�t */
    GgafLib::VirtualButton vb_;
    /** �e�X�g�L���� */
    SmpActor* pActor_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     */
    SmpWorld(const char* prm_name);

    /**
     * ���E�V�[���̏������� .
     */
    void initialize() override;

    /**
     * ���E�V�[���̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~SmpWorld();
};

}
#endif /*SMPWORLD_H_*/
