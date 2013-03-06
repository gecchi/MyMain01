#ifndef GGAFDXSOUND_H_
#define GGAFDXSOUND_H_

namespace GgafDxCore {
/**
 * 神が保持する GgafDxSeManager に接続し、コネクションを取得。
 * @param X：SE定義識別文字列。プロパティ DIR_WAVE[0] 配下の「X + ".wave"」というファイル名を使用する。
 *           チャンネル指定時は、スラッシュを挿入 ("1/click" 等）
 */
#define connectToSeManager(X)  ((GgafDxCore::GgafDxSeConnection*)GgafDxCore::GgafDxSound::_pSeManager->connect(X))

/**
 * 神が保持する GgafDxBgmManager に接続し、コネクションを取得。
 * @param X：BGM定義識別文字列。プロパティ DIR_OGG[0] 配下から、プロパティ X +"_OGG" の値のファイル名を使用する。
 */
#define connectToBgmManager(X) ((GgafDxCore::GgafDxBgmConnection*)GgafDxCore::GgafDxSound::_pBgmManager->connect(X))

/**
 * DirectSound ユーティリティクラス.
 * IDirectSound8を保持し、サウンドに関するもろもろの機能を持ったユーティリティです
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
    /** [r]アプリケーション・マスターボリューム値(0～100) */
    static int _app_master_volume;
    /** [r]BGM・マスターボリューム値(0～100) */
    static int _bgm_master_volume;
    /** [r]サウンドエフェクト・マスターボリューム値(0～100) */
    static int _se_master_volume;
    /** [r]アプリケーション・マスターボリュームの割合 0.0～1.0 */
    static float _app_master_volume_rate;
    /** [r]BGM・マスターボリュームの割合 0.0～1.0 */
    static float _bgm_master_volume_rate;
    /** [r]サウンドエフェクト・マスターボリューム割合 0.0～1.0 */
    static float _se_master_volume_rate;
    /** [r]要素番号にボリューム値を入れると、対応デシベルが取得できる配列 */
    static int aDbVolume[GGAF_MAX_VOLUME+1];

public:
    /**
     * 初期設定 .
     * 使用前に呼び出して下さい。GgafDxSeManager、GgafDxBgmManager を使用可能にします。
     */
    static void init();

    /**
     * 解放処理 .
     * 使用後に呼び出して下さい。
     */
    static void release();

    /**
     * アプリ全体のマスタボリューム設定 .
     * @param prm_app_master_volume 0(無音) ～ 100(最大)
     */
    static void setApplicationMasterVolume(int prm_app_master_volume);

    /**
     * アプリ全体のマスタボリューム増分設定 .
     * @param prm_app_master_volume_offset 音量増分
     */
    static void addApplicationMasterVolume(int prm_app_master_volume_offset);

    /**
     * 全BGMのマスタボリュームの設定 .
     * @param prm_bgm_master_volume  0(無音) ～ 100(最大)
     */
    static void setBgmMasterVolume(float prm_bgm_master_volume);

    /**
     * 全BGMのマスタボリューム増分設定 .
     * @param prm_bgm_master_volume_offset 音量増分
     */
    static void addBgmMasterVolume(int prm_bgm_master_volume_offset);

    /**
     * 全SEのマスタボリュームの率設定 .
     * @param prm_se_master_volume  0(無音) ～ 100(最大)
     */
    static void setSeMasterVolume(float prm_se_master_volume);

    /**
     * 全SEのマスタボリューム増分設定 .
     * @param prm_se_master_volume_offset 音量増分
     */
    static void addSeMasterVolume(int prm_se_master_volume_offset);
};

}
#endif /*GGAFDXSOUND_H_*/
