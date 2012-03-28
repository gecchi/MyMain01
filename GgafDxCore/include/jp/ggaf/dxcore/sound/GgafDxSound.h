#ifndef GGAFDXSOUND_H_
#define GGAFDXSOUND_H_

namespace GgafDxCore {
/**
 * 神が保持する GgafDxSeConnection に接続し、コネクションを取得。
 * @param X：スプライン定義識別文字列。プロパティ DIR_WAVE 配下の「X + ".wave"」というファイル名を使用する。
 *           チャンネル指定時は、スラッシュを挿入 ("1/click" 等）
 */
#define connectSeManager(X)  ((GgafDxCore::GgafDxSeConnection*)GgafDxCore::GgafDxSound::_pSeManager->connect(X))

/**
 * 神が保持する GgafDxSeConnection に接続し、コネクションを取得。
 * @param X：スプライン定義識別文字列。プロパティ DIR_OGG 配下から、プロパティ X +"_OGG" の値のファイル名を使用する。
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
    /** [r/w]マスターボリューム割合 0.0～1.0 */
    static float _master_volume_rate;
    /** [r/w]BGM全般のボリューム割合 0.0～1.0 */
    static float _bgm_volume_rate;
    /** [r/w]サウンドエフェクト全般のボリューム割合 0.0～1.0 */
    static float _se_volume_rate;
    /** [r/w]要素番号にボリューム値を入れると、対応デシベルが取得できる配列 */
    static LONG aDbVolume[GGAF_MAX_VOLUME+1];

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
