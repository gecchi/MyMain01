#ifndef GGAFDX9SOUND_H_
#define GGAFDX9SOUND_H_

namespace GgafDx9Core {

#define connectSeManager(X) ((GgafDx9Core::GgafDx9SeConnection*)GgafDx9Core::GgafDx9Sound::_pSeManager->connect(X))


/**
 * �T�E���h�N���X.
 * IDirectSound8��ێ����A�T�E���h�Ɋւ���������̋@�\���������N���X�ł�
 * @version 1.00
 * @since 2008/03/04
 * @author Masatoshi Tsuge
 */
class GgafDx9Sound {
public:
    /** IDirectSound8�C���^�[�t�F�C�X */
    static IDirectSound8* _pIDirectSound8;
    static DSCAPS _dsCaps;
    static void init();
    static void release();
    static GgafDx9SeManager* _pSeManager;
    static GgafDx9BgmManager* _pBgmManager;
    static float _master_volume_rate;
    static float _bgm_volume_rate;
    static float _se_volume_rate;
    static LONG aDbVolume[GGAF_MAX_VOLUME+1];

    /**
     * �}�X�^�{�����[���ݒ�(���ݖ�����).
     * TODO:�}�X�^�[�{�����[������������I
     * @param prm_master_volume_rate
     */
    static void setMasterVolume(float prm_master_volume_rate) {
        GgafDx9Sound::_master_volume_rate = prm_master_volume_rate;
    }

    static void setBgmVolume(float prm_bgm_volume_rate) {
        GgafDx9Sound::_bgm_volume_rate = prm_bgm_volume_rate;
    }

    static void setSeVolume(float prm_se_volume_rate) {
        GgafDx9Sound::_se_volume_rate = prm_se_volume_rate;
    }

};

}
#endif /*GGAFDX9SOUND_H_*/
