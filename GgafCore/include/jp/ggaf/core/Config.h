#ifndef GGAF_CORE_CONFIG_H_
#define GGAF_CORE_CONFIG_H_
#include "GgafCommonHeader.h"

#include "jp/ggaf/core/Properties.h"
#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/util/Rgb.h"
#ifndef _MSC_VER
    #include <atomic>
#endif

#ifdef CONFIG
    #undef CONFIG
#endif
#define CONFIG GgafCore::Config

namespace GgafCore {

/**
 * プロパティクラス .
 * 外部ファイルからロードし、アプリの環境変数として保持します。
 * @version 1.00
 * @since 2008/07/22
 * @author Masatoshi Tsuge
 */
class Config {

public:
    /** [r/w] FPS */
    static frame FPS;
    /** [r/w] 最高フレームスキップ数。つまりどんなに重くも最低描画するフレーム間隔。*/
    static uint32_t MAX_SKIP_FRAME;
    /** [r/w] 60fps→40fpsの処理落ち演出を行うかどうかの境界。1フレームあたり内部描画回数で設定 */
    static uint32_t OBJNUM_TO_SLOWDOWN1;
    /** [r/w] 40fps→30fpsの処理落ち演出を行うかどうかの境界。1フレームあたり内部描画回数で設定 */
    static uint32_t OBJNUM_TO_SLOWDOWN2;
    /** [r/w] ゴミ箱を掃除(インスタンス解放)を行うことが出来るFPS */
    static float FPS_TO_CLEAN_GARBAGE_BOX;
    /** [r] アプリケーションのリソースディレクトリ */
    static std::string DIR_RESOURCE;
    /** [r] アプリケーションのスキンフォルダ名(リソースディレクトリ配下) */
    static std::string DIRNAME_RESOURCE_SKIN;
    /** [r] アプリケーションのスキンフォルダのシステムスキン名(リソースディレクトリのスキンフォルダ配下) */
    static std::string DIRNAME_RESOURCE_SKIN_SYSTEM;
    /** [r] アプリケーションのスキンフォルダのユーザースキン名(リソースディレクトリのスキンフォルダ配下) */
    static std::string DIRNAME_RESOURCE_SKIN_USER;

    ////// 以下は、上記プロパティから生成される読み出し専用プロパティ ////////

    /** [r] アプリケーションのスキンディレクトリ */
    static std::string DIR_SKIN;
    /** [r] アプリケーションのシステムスキンディレクトリ(0:システム/1:ユーザー/2:直下) */
    static std::string DIR_SKIN_KIND[3];


#ifdef _MSC_VER
    //TODO:VC++2005以降(x86) の volatile は、メモリバリア効果がある（と思う）。
    //gcc(x86)は、アトミック保証は無いが std::atomic が使える。VC++に atomic が実装されるまではとりあえず・・・。
    static volatile bool _is_lock;
#else
    static volatile std::atomic<bool> _is_lock;
#endif

    /** [r] 保持プロパティ */
    static Properties _properties;


public:
    /**
     * 外部プロパティファイルからロードして保持プロパティへ設定、メンバ変数に反映 .
     * @param prm_properties_filename プロパティファイル
     */
    static void loadProperties(std::string prm_properties_filename);

};

}
#endif /*GGAF_CORE_CONFIG_H_*/

