#ifndef GGAFDXSOUND_H_
#define GGAFDXSOUND_H_

namespace GgafDxCore {

#define connectSeManager(X) ((GgafDxCore::GgafDxSeConnection*)GgafDxCore::GgafDxSound::_pSeManager->connect(X))


/**
 * �T�E���h�N���X.
 * IDirectSound8��ێ����A�T�E���h�Ɋւ���������̋@�\���������N���X�ł�
 * @version 1.00
 * @since 2008/03/04
 * @author Masatoshi Tsuge
 */
class GgafDxSound {
public:
    /** IDirectSound8�C���^�[�t�F�C�X */
    static IDirectSound8* _pIDirectSound8;
    static DSCAPS _dsCaps;
    static void init();
    static void release();
    static GgafDxSeManager* _pSeManager;
    static GgafDxBgmManager* _pBgmManager;
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
        GgafDxSound::_master_volume_rate = prm_master_volume_rate;
    }

    static void setBgmVolume(float prm_bgm_volume_rate) {
        GgafDxSound::_bgm_volume_rate = prm_bgm_volume_rate;
    }

    static void setSeVolume(float prm_se_volume_rate) {
        GgafDxSound::_se_volume_rate = prm_se_volume_rate;
    }

};

}
#endif /*GGAFDXSOUND_H_*/
