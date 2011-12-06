#ifndef GGAFDXSOUND_H_
#define GGAFDXSOUND_H_

namespace GgafDxCore {

#define connectSeManager(X) ((GgafDxCore::GgafDxSeConnection*)GgafDxCore::GgafDxSound::_pSeManager->connect(X))


/**
 * サウンドクラス.
 * IDirectSound8を保持し、サウンドに関するもろもろの機能を持ったクラスです
 * @version 1.00
 * @since 2008/03/04
 * @author Masatoshi Tsuge
 */
class GgafDxSound {
public:
    /** IDirectSound8インターフェイス */
    static IDirectSound8* _pIDirectSound8;
    static DSCAPS _dsCaps;
    static void init();
    static void release();
    static GgafDxSeManager* _pSeManager;
    static GgafDxBgmManager* _pBgmManager;
    static float _master_volume_rate;
    static float _bgm_volume_rate;
    static float _se_volume_rate;
    /** 要素番号にボリューム値を入れると、対応デシベルが取得できる配列 */
    static LONG aDbVolume[GGAF_MAX_VOLUME+1];

    /**
     * マスタボリューム設定の率設定 .
     * @param prm_master_volume_rate 0.0(無音) ～ 1.0(サンプリング本来の音量)
     */
    static void setMasterVolume(float prm_master_volume_rate) {
        GgafDxSound::_master_volume_rate = prm_master_volume_rate;
    }

    /**
     * 全体的なBGMボリュームの率設定 .
     * @param prm_bgm_volume_rate  0.0(無音) ～ 1.0(サンプリング本来の音量)
     */
    static void setBgmVolume(float prm_bgm_volume_rate) {
        GgafDxSound::_bgm_volume_rate = prm_bgm_volume_rate;
    }

    /**
     * 全体的なSEボリュームの率設定 .
     * @param prm_se_volume_rate  0.0(無音) ～ 1.0(サンプリング本来の音量)
     */
    static void setSeVolume(float prm_se_volume_rate) {
        GgafDxSound::_se_volume_rate = prm_se_volume_rate;
    }

};

}
#endif /*GGAFDXSOUND_H_*/
