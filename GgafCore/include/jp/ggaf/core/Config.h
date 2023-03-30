#ifndef GGAF_CORE_CONFIG_H_
#define GGAF_CORE_CONFIG_H_
#include "jp/ggaf/GgafCommonHeader.h"

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

/** 秒 → フレーム数 変換 */
#define SEC_F(X)  ( (frame)((X) * (CONFIG::FPS)) )
/** ミリ秒 → フレーム数 変換 */
#define MSEC_F(X)  ( (frame)(((X) * 0.001) * (CONFIG::FPS)) )


/** 共通遅延解放フレーム数（≒エフェクト最大再生時間） */
#define GGAF_END_DELAY (SEC_F(90))
//GGAF_END_DELAYは全Element共通の解放遅延フレーム数で、
//アクター消失後、直ぐに不正ポインタになるのではなく、しばらく参照が可能とするための仕組み。
//少し長めに設定しないと、いろいろ不都合が多い。
//例えば、消滅後の爆発SE等で、3D効果のためSE発声元座標情報がしばらく必要とか、
//消滅後の消滅アクター配下に属する発射弾（子アクター）が、親アクターの座標を参照しているなど、
//消滅しても、しばらくは残存させなければいけない場合が多々ある。
//GGAF_END_DELAYには、基本的に、画面から消滅確定→完全にdeleteまでのフレームの最大フレームを指定する。
//現在は90秒。
//もし、GGAF_END_DELAYを短めに設定すると、
//消滅後の子の発射弾については、残された発射弾が突然消えるので少し不自然。という程度で問題はない。
//しかし、SEの3D効果は、エラーになるため、SE再生時間の最大フレーム数を設定しなければいけない。
//例えば効果音が90秒以上かかるようなWAVEが一つでもあるならば、90秒以上を設定しなければならない。


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
    /** [r] 1フレームの秒数 */
    static double FRAME_SEC;

    /** [r/w] 最高フレームスキップ数。つまりどんなに重くも最低描画するフレーム間隔。*/
    static uint32_t MAX_SKIP_FRAME;
    /** [r/w] 処理落ち演出を行うかどうかの第一段階の境界。1フレームあたりのアクティブなアクター数設定 */
    static uint32_t OBJNUM_TO_SLOWDOWN1;
    /** [r/w] 処理落ち演出を行うかどうかの第二段階の境界。1フレームあたりのアクティブなアクター数設定 */
    static uint32_t OBJNUM_TO_SLOWDOWN2;

    /** [r/w] 処理落ち演出を行第一段階の境界時の処理落ち割合。元の速さの遅さ倍数(1.0：処理落ちなし／1.5：1.5倍の遅さ／2.0:2倍の遅さ) */
    static double RATE_OF_SLOWDOWN1;
    /** [r/w] 処理落ち演出を行第二段階の境界時の処理落ち割合。元の速さの遅さ倍数(1.0：処理落ちなし／1.5：1.5倍の遅さ／2.0:2倍の遅さ) */
    static double RATE_OF_SLOWDOWN2;

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

