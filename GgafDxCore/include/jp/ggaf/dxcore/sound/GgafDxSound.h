#ifndef GGAFDXSOUND_H_
#define GGAFDXSOUND_H_

namespace GgafDxCore {
/**
 * 神が保持する GgafDxSeConnection に接続し、コネクションを取得。
 * @param X：スプライン定義識別文字列。プロパティ DIR_WAVE[0] 配下の「X + ".wave"」というファイル名を使用する。
 *           チャンネル指定時は、スラッシュを挿入 ("1/click" 等）
 */
#define connectSeManager(X)  ((GgafDxCore::GgafDxSeConnection*)GgafDxCore::GgafDxSound::_pSeManager->connect(X))

/**
 * 神が保持する GgafDxSeConnection に接続し、コネクションを取得。
 * @param X：スプライン定義識別文字列。プロパティ DIR_OGG[0] 配下から、プロパティ X +"_OGG" の値のファイル名を使用する。
 */
#define connectBgmManager(X) ((GgafDxCore::GgafDxBgmConnection*)GgafDxCore::GgafDxSound::_pBgmManager->connect(X))

/**
 * DirectSound ユーティリティクラス.
 * IDirectSound8を保持し、サウンドに関するもろもろの機能を持ったクラスです
 * @version 1.00
 * @since 2008/03/04
 * @author Masatoshi Tsuge
 */
class GgafDxSound {
public:
    /** IDirectSound8インターフェイス */
    static IDirectSound8* _pIDirectSound8;
    /** [r]DSCAPS */
    static DSCAPS _dsCaps;
    /** [r]GgafDxSe 管理クラス */
    static GgafDxSeManager* _pSeManager;
    /** [r]GgafDxBgm 管理クラス */
    static GgafDxBgmManager* _pBgmManager;
    /** [r/w]マスターボリューム0～100 */
    static int _master_volume;
    /** [r/w]BGM全般のボリューム0～100 */
    static int _bgm_volume;
    /** [r/w]サウンドエフェクト全般のボリューム0～100 */
    static int _se_volume;
    /** [r/w]マスターボリューム割合 0.0～1.0 */
    static float _master_volume_rate;
    /** [r/w]BGM全般のボリューム割合 0.0～1.0 */
    static float _bgm_volume_rate;
    /** [r/w]サウンドエフェクト全般のボリューム割合 0.0～1.0 */
    static float _se_volume_rate;
    /** [r/w]要素番号にボリューム値を入れると、対応デシベルが取得できる配列 */
    static int aDbVolume[GGAF_MAX_VOLUME+1];

    /**
     * 初期設定 .
     * GgafDxSeManager、GgafDxBgmManager を使用可能にします。
     */
    static void init();

    /**
     * 解放処理 .
     * 使用が済んだら呼び出して下さい。
     */
    static void release();

    /**
     * マスタボリューム設定の率設定 .
     * @param prm_master_volume 0(無音) ～ 100
     */
    static void setMasterVolume(int prm_master_volume) {
        _master_volume = prm_master_volume;
        if (_master_volume > GGAF_MAX_VOLUME) {
            _master_volume = GGAF_MAX_VOLUME;
        } else if (_master_volume < GGAF_MIN_VOLUME) {
            _master_volume = GGAF_MIN_VOLUME;
        }
        _master_volume_rate = 1.0f * _master_volume / GGAF_MAX_VOLUME;
    }

    static void addMasterVolume(int prm_master_volume_offset) {
        setMasterVolume(_master_volume+prm_master_volume_offset);
    }

    /**
     * 全BGMボリュームの率設定 .
     * @param prm_bgm_volume  0(無音) ～ 100(サンプリング本来の音量)
     */
    static void setBgmVolume(float prm_bgm_volume) {
        _bgm_volume = prm_bgm_volume;
        if (_bgm_volume > GGAF_MAX_VOLUME) {
            _bgm_volume = GGAF_MAX_VOLUME;
        } else if (_bgm_volume < GGAF_MIN_VOLUME) {
            _bgm_volume = GGAF_MIN_VOLUME;
        }
        _bgm_volume_rate = 1.0f * _bgm_volume / GGAF_MAX_VOLUME;
    }

    /**
     * 全SEボリュームの率設定 .
     * @param prm_se_volume  0(無音) ～ 100(サンプリング本来の音量)
     */
    static void setSeVolume(float prm_se_volume) {
        _se_volume = prm_se_volume;
        if (_se_volume > GGAF_MAX_VOLUME) {
            _se_volume = GGAF_MAX_VOLUME;
        } else if (_se_volume < GGAF_MIN_VOLUME) {
            _se_volume = GGAF_MIN_VOLUME;
        }
        _se_volume_rate = 1.0f * _se_volume / GGAF_MAX_VOLUME;
    }

};

}
#endif /*GGAFDXSOUND_H_*/
