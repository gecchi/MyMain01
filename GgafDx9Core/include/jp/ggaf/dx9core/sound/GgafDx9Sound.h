#ifndef GGAFDX9SOUND_H_
#define GGAFDX9SOUND_H_
namespace GgafDx9Core {
/**
 * サウンドクラス.
 * IDirectSound8を保持し、サウンドに関するもろもろの機能を持ったクラスです
 * @version 1.00
 * @since 2008/03/04
 * @author Masatoshi Tsuge
 */
class GgafDx9Sound {
public:
    /** IDirectSound8インターフェイス */
    static IDirectSound8* _pIDirectSound8;
    static DSCAPS _dsCaps;
    static void init();
    static void release();
    static GgafDx9SeManager* _pSeManager;
    static GgafDx9BgmManager* _pBgmManager;
    static int _master_volume;
    static int _bgm_volume;
    static int _se_volume;

    /**
     * マスタボリューム設定(現在未実装).
     * TODO:マスターボリューム処理をする！
     * @param prm_master_volume
     */
    static void setMasterVolume(int prm_master_volume) {
        GgafDx9Sound::_master_volume = prm_master_volume;
    }

    static void setBgmVolume(int prm_bgm_volume) {
        GgafDx9Sound::_bgm_volume = prm_bgm_volume;
    }

    static void setSeVolume(int prm_se_volume) {
        GgafDx9Sound::_se_volume = prm_se_volume;
    }

};

}
#endif /*GGAFDX9SOUND_H_*/
