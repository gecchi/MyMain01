#ifndef GGAF_DX_SOUND_H_
#define GGAF_DX_SOUND_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include <sstream>

//#ifdef __GNUG__
//    #define __null
//    #define NULL    0
//    #define __in
//    #define __out
//#endif
//#include <dsound.h>  //←sal.h を include する
//#ifdef __GNUG__
//    #undef __null
//    #undef __in
//    #undef __out
//#endif

#include "jp/ggaf/dx/manager/SeManager.h"

/**
 * 管理者が保持する SeManager に接続し、コネクションを取得。
 * @param X  SE定義識別文字列。プロパティ DIR_SE[0] 配下の「X + ".wave"」というファイル名を使用する。
 *           チャンネル指定時は、スラッシュを挿入 ("1,click" 等）
 */
#define connectToSeManager(X)  ((GgafDx::SeConnection*)GgafDx::Sound::_pSeManager->connect((X), this))

/**
 * 管理者が保持する BgmManager に接続し、コネクションを取得。
 * @param X  BGM定義識別文字列。プロパティ DIR_BGM[0] 配下から、プロパティ X +"_OGG" の値のファイル名を使用する。
 */
#define connectToBgmManager(X) ((GgafDx::BgmConnection*)GgafDx::Sound::_pBgmManager->connect((X), this))

struct IDirectSound8;
typedef struct _DSCAPS DSCAPS;

namespace GgafDx {

/**
 * DirectSound ユーティリティクラス.
 * IDirectSound8を保持し、サウンドに関するもろもろの機能を持ったユーティリティです
 * @version 1.00
 * @since 2008/03/04
 * @author Masatoshi Tsuge
 */
class Sound {


    /** [r]アプリケーション・マスターボリューム値(0～1000) */
    static int _app_master_volume;
    /** [r]BGM・マスターボリューム値(0～1000) */
    static int _bgm_master_volume;
    /** [r]サウンドエフェクト・マスターボリューム値(0～1000) */
    static int _se_master_volume;
    /** 計算用定数 */
    static const int _MAXMAX_VOLUME = (GGAF_MAX_VOLUME * GGAF_MAX_VOLUME);

public:
    /** IDirectSound8インターフェイス */
    static IDirectSound8* _pIDirectSound8;
    /** [r]DSCAPS */
    static DSCAPS* _pDsCaps;
    /** [r]Se 管理クラス */
    static SeManager* _pSeManager;
    /** [r]Bgm 管理クラス */
    static BgmManager* _pBgmManager;

    /** [r]要素番号にボリューム値を入れると、対応デシベルが取得できる配列 */
    static double _a_db_volume[GGAF_MAX_VOLUME+1];


public:
    /**
     * 初期設定 .
     * 使用前に呼び出して下さい。SeManager、BgmManager を使用可能にします。
     */
    static void init();

    /**
     * 解放処理 .
     * 使用後に呼び出して下さい。
     */
    static void release();

    /**
     * アプリ全体のマスタボリューム設定 .
     * @param prm_app_master_volume 0(無音) ～ 1000(最大)
     */
    static void setAppMasterVolume(int prm_app_master_volume);

    static int getAppMasterVolume() {
        return  _app_master_volume;
    }

    /**
     * アプリ全体のマスタボリューム増分設定 .
     * @param prm_app_master_volume_offset 音量増分
     */
    static void addAppMasterVolume(int prm_app_master_volume_offset) {
        Sound::setAppMasterVolume(_app_master_volume+prm_app_master_volume_offset);
    }


    /**
     * 全BGMのマスタボリュームの設定 .
     * @param prm_bgm_master_volume  0(無音) ～ 1000(最大)
     */
    static void setBgmMasterVolume(float prm_bgm_master_volume);

    static int getBgmMasterVolume() {
        return _bgm_master_volume;
    }

    /**
     * 全BGMのマスタボリューム増分設定 .
     * @param prm_bgm_master_volume_offset 音量増分
     */
    static void addBgmMasterVolume(int prm_bgm_master_volume_offset) {
        Sound::setBgmMasterVolume(_bgm_master_volume+prm_bgm_master_volume_offset);
    }

    /**
     * 全SEのマスタボリュームの率設定 .
     * @param prm_se_master_volume  0(無音) ～ 1000(最大)
     */
    static void setSeMasterVolume(float prm_se_master_volume);

    static int getSeMasterVolume() {
        return _se_master_volume;
    }

    /**
     * 全SEのマスタボリューム増分設定 .
     * @param prm_se_master_volume_offset 音量増分
     */
    static void addSeMasterVolume(int prm_se_master_volume_offset) {
        Sound::setSeMasterVolume(_se_master_volume+prm_se_master_volume_offset);
    }

};

}
#endif /*GGAF_DX_SOUND_H_*/
