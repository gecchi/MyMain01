#ifndef GGAFDXSOUND_H_
#define GGAFDXSOUND_H_

namespace GgafDxCore {
/**
 * �_���ێ����� GgafDxSeManager �ɐڑ����A�R�l�N�V�������擾�B
 * @param X�FSE��`���ʕ�����B�v���p�e�B DIR_WAVE[0] �z���́uX + ".wave"�v�Ƃ����t�@�C�������g�p����B
 *           �`�����l���w�莞�́A�X���b�V����}�� ("1/click" ���j
 */
#define connectToSeManager(X)  ((GgafDxCore::GgafDxSeConnection*)GgafDxCore::GgafDxSound::_pSeManager->connect(X))

/**
 * �_���ێ����� GgafDxBgmManager �ɐڑ����A�R�l�N�V�������擾�B
 * @param X�FBGM��`���ʕ�����B�v���p�e�B DIR_OGG[0] �z������A�v���p�e�B X +"_OGG" �̒l�̃t�@�C�������g�p����B
 */
#define connectToBgmManager(X) ((GgafDxCore::GgafDxBgmConnection*)GgafDxCore::GgafDxSound::_pBgmManager->connect(X))

/**
 * DirectSound ���[�e�B���e�B�N���X.
 * IDirectSound8��ێ����A�T�E���h�Ɋւ���������̋@�\�����������[�e�B���e�B�ł�
 * @version 1.00
 * @since 2008/03/04
 * @author Masatoshi Tsuge
 */
class GgafDxSound {
public:
    /** IDirectSound8�C���^�[�t�F�C�X */
    static IDirectSound8* _pIDirectSound8;
    /** [r]DSCAPS */
    static DSCAPS _dsCaps;
    /** [r]GgafDxSe �Ǘ��N���X */
    static GgafDxSeManager* _pSeManager;
    /** [r]GgafDxBgm �Ǘ��N���X */
    static GgafDxBgmManager* _pBgmManager;
    /** [r]�A�v���P�[�V�����E�}�X�^�[�{�����[���l(0�`100) */
    static int _app_master_volume;
    /** [r]BGM�E�}�X�^�[�{�����[���l(0�`100) */
    static int _bgm_master_volume;
    /** [r]�T�E���h�G�t�F�N�g�E�}�X�^�[�{�����[���l(0�`100) */
    static int _se_master_volume;
    /** [r]�A�v���P�[�V�����E�}�X�^�[�{�����[���̊��� 0.0�`1.0 */
    static float _app_master_volume_rate;
    /** [r]BGM�E�}�X�^�[�{�����[���̊��� 0.0�`1.0 */
    static float _bgm_master_volume_rate;
    /** [r]�T�E���h�G�t�F�N�g�E�}�X�^�[�{�����[������ 0.0�`1.0 */
    static float _se_master_volume_rate;
    /** [r]�v�f�ԍ��Ƀ{�����[���l������ƁA�Ή��f�V�x�����擾�ł���z�� */
    static int aDbVolume[GGAF_MAX_VOLUME+1];

public:
    /**
     * �����ݒ� .
     * �g�p�O�ɌĂяo���ĉ������BGgafDxSeManager�AGgafDxBgmManager ���g�p�\�ɂ��܂��B
     */
    static void init();

    /**
     * ������� .
     * �g�p��ɌĂяo���ĉ������B
     */
    static void release();

    /**
     * �A�v���S�̂̃}�X�^�{�����[���ݒ� .
     * @param prm_app_master_volume 0(����) �` 100(�ő�)
     */
    static void setApplicationMasterVolume(int prm_app_master_volume);

    /**
     * �A�v���S�̂̃}�X�^�{�����[�������ݒ� .
     * @param prm_app_master_volume_offset ���ʑ���
     */
    static void addApplicationMasterVolume(int prm_app_master_volume_offset);

    /**
     * �SBGM�̃}�X�^�{�����[���̐ݒ� .
     * @param prm_bgm_master_volume  0(����) �` 100(�ő�)
     */
    static void setBgmMasterVolume(float prm_bgm_master_volume);

    /**
     * �SBGM�̃}�X�^�{�����[�������ݒ� .
     * @param prm_bgm_master_volume_offset ���ʑ���
     */
    static void addBgmMasterVolume(int prm_bgm_master_volume_offset);

    /**
     * �SSE�̃}�X�^�{�����[���̗��ݒ� .
     * @param prm_se_master_volume  0(����) �` 100(�ő�)
     */
    static void setSeMasterVolume(float prm_se_master_volume);

    /**
     * �SSE�̃}�X�^�{�����[�������ݒ� .
     * @param prm_se_master_volume_offset ���ʑ���
     */
    static void addSeMasterVolume(int prm_se_master_volume_offset);
};

}
#endif /*GGAFDXSOUND_H_*/
