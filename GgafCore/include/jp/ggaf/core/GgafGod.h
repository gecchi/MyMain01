#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {

/**
 * �_�N���X.
 * ���E(GgafWorld)���Ǘ����܂��B
 */
class GgafGod : public GgafObject {

public:

    /** �����H��(�ʃX���b�h)�̃G���[��ԁBNULL������ғ����^not NULL���ُ픭�� */
    static GgafCriticalException* _pException_Factory;
    /** ���ɐ��E�����������鎞�Ԃ̃I�t�Z�b�g */
    static DWORD _aDwTime_OffsetOfNextFrame[];

    /** GgafFactory::work �X���b�h�n���h��  */
    HANDLE _handleFactory01;
    /** GgafFactory::work �X���b�hID  */
    unsigned int _thID01;
    /** �N���e�B�J���Z�N�V�����i�Z�}�t�H�j */
    static CRITICAL_SECTION CS1;
    static CRITICAL_SECTION CS2;

    /** �_�̃t���[���J�n�V�X�e������ */
    DWORD _dwTime_FrameBegin;
    /** ���ɐ��E������������V�X�e������ */
    DWORD _dwTime_ScheduledNextFrame;
    /** �_�a������̃t���[���� */
    DWORD _dwFrame_God;
    /** ���E�����o���ł��Ȃ������i�X�L�b�v�����j�� */
    DWORD _dwFrame_SkipCount;
    /** ���E */
    GgafWorld* _pWorld;

    /** fps�l�i��1000ms���Ɍv�Z�����j */
    float _fFps;
    /** �O��fps�v�Z���̃V�X�e������ */
    DWORD _dwTime_Prev;
    /** �`��t���[���J�E���^ */
    DWORD _dwFrame_Visualize;
    /** �O��fps�v�Z���̕`��t���[���J�E���g�l */
    DWORD _dwFrame_PrevVisualize;

    /**  */
    static int _iNumPlayingActor;

    bool _isBehaved;

    /**
     * �R���X�g���N�^.
     * �ʃX���b�h�ōH����ғ������܂��B
     */
    GgafGod();

    /**
     * �_�̑���<BR>
     */
    void be();

    /**
     * ���E�𑶍݂�����<BR>
     */
    virtual void makeWorldBe();

    /**
     * ���E��R������<BR>
     */
    virtual void makeWorldJudge();

    /**
     * ���E���������<BR>
     */
    virtual void makeWorldMaterialize();

    /**
     * ���E�����o������<BR>
     */
    virtual void makeWorldVisualize();

    /**
     * ���E�̌�n��<BR>
     */
    virtual void makeWorldFinalize();

    /**
     * ���E���擾<BR>
     * @return ���E
     */
    virtual GgafWorld* getWorld() {
        return _pWorld;
    }

    /**
     * ���E��n��<BR>
     * @return ���E
     */
    virtual GgafWorld* createWorld() = 0;

    virtual ~GgafGod();
};

}
#endif /*GGAFGOD_H_*/
