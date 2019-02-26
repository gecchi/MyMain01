#ifndef GGAF_DX_SOUND_H_
#define GGAF_DX_SOUND_H_
#include "GgafDxCommonHeader.h"
#include <sstream>

//#ifdef __GNUG__
//    #define __null
//    #define NULL    0
//    #define __in
//    #define __out
//#endif
//#include <dsound.h>  //��sal.h �� include ����
//#ifdef __GNUG__
//    #undef __null
//    #undef __in
//    #undef __out
//#endif

#include "jp/ggaf/dx/manager/SeManager.h"

/**
 * �_���ێ����� SeManager �ɐڑ����A�R�l�N�V�������擾�B
 * @param X  SE��`���ʕ�����B�v���p�e�B DIR_WAVE[0] �z���́uX + ".wave"�v�Ƃ����t�@�C�������g�p����B
 *           �`�����l���w�莞�́A�X���b�V����}�� ("1,click" ���j
 */
#define connectToSeManager(X)  ((GgafDx::SeConnection*)GgafDx::Sound::_pSeManager->connect((X), this))

/**
 * �_���ێ����� BgmManager �ɐڑ����A�R�l�N�V�������擾�B
 * @param X  BGM��`���ʕ�����B�v���p�e�B DIR_OGG[0] �z������A�v���p�e�B X +"_OGG" �̒l�̃t�@�C�������g�p����B
 */
#define connectToBgmManager(X) ((GgafDx::BgmConnection*)GgafDx::Sound::_pBgmManager->connect((X), this))

struct IDirectSound8;
typedef struct _DSCAPS DSCAPS;

namespace GgafDx {

/**
 * DirectSound ���[�e�B���e�B�N���X.
 * IDirectSound8��ێ����A�T�E���h�Ɋւ���������̋@�\�����������[�e�B���e�B�ł�
 * @version 1.00
 * @since 2008/03/04
 * @author Masatoshi Tsuge
 */
class Sound {


    /** [r]�A�v���P�[�V�����E�}�X�^�[�{�����[���l(0�`1000) */
    static int _app_master_volume;
    /** [r]BGM�E�}�X�^�[�{�����[���l(0�`1000) */
    static int _bgm_master_volume;
    /** [r]�T�E���h�G�t�F�N�g�E�}�X�^�[�{�����[���l(0�`1000) */
    static int _se_master_volume;
    /** �v�Z�p�萔 */
    static const int _MAXMAX_VOLUME = (GGAF_MAX_VOLUME * GGAF_MAX_VOLUME);

public:
    /** IDirectSound8�C���^�[�t�F�C�X */
    static IDirectSound8* _pIDirectSound8;
    /** [r]DSCAPS */
    static DSCAPS* _pDsCaps;
    /** [r]Se �Ǘ��N���X */
    static SeManager* _pSeManager;
    /** [r]Bgm �Ǘ��N���X */
    static BgmManager* _pBgmManager;

    /** [r]�v�f�ԍ��Ƀ{�����[���l������ƁA�Ή��f�V�x�����擾�ł���z�� */
    static double _a_db_volume[GGAF_MAX_VOLUME+1];


public:
    /**
     * �����ݒ� .
     * �g�p�O�ɌĂяo���ĉ������BSeManager�ABgmManager ���g�p�\�ɂ��܂��B
     */
    static void init();

    /**
     * ������� .
     * �g�p��ɌĂяo���ĉ������B
     */
    static void release();

    /**
     * �A�v���S�̂̃}�X�^�{�����[���ݒ� .
     * @param prm_app_master_volume 0(����) �` 1000(�ő�)
     */
    static void setAppMasterVolume(int prm_app_master_volume);

    static int getAppMasterVolume() {
        return  _app_master_volume;
    }

    /**
     * �A�v���S�̂̃}�X�^�{�����[�������ݒ� .
     * @param prm_app_master_volume_offset ���ʑ���
     */
    static void addAppMasterVolume(int prm_app_master_volume_offset) {
        Sound::setAppMasterVolume(_app_master_volume+prm_app_master_volume_offset);
    }


    /**
     * �SBGM�̃}�X�^�{�����[���̐ݒ� .
     * @param prm_bgm_master_volume  0(����) �` 1000(�ő�)
     */
    static void setBgmMasterVolume(float prm_bgm_master_volume);

    static int getBgmMasterVolume() {
        return _bgm_master_volume;
    }

    /**
     * �SBGM�̃}�X�^�{�����[�������ݒ� .
     * @param prm_bgm_master_volume_offset ���ʑ���
     */
    static void addBgmMasterVolume(int prm_bgm_master_volume_offset) {
        Sound::setBgmMasterVolume(_bgm_master_volume+prm_bgm_master_volume_offset);
    }

    /**
     * �SSE�̃}�X�^�{�����[���̗��ݒ� .
     * @param prm_se_master_volume  0(����) �` 1000(�ő�)
     */
    static void setSeMasterVolume(float prm_se_master_volume);

    static int getSeMasterVolume() {
        return _se_master_volume;
    }

    /**
     * �SSE�̃}�X�^�{�����[�������ݒ� .
     * @param prm_se_master_volume_offset ���ʑ���
     */
    static void addSeMasterVolume(int prm_se_master_volume_offset) {
        Sound::setSeMasterVolume(_se_master_volume+prm_se_master_volume_offset);
    }

};

}
#endif /*GGAF_DX_SOUND_H_*/
