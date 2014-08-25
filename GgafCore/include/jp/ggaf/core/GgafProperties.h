#ifndef GGAFCORE_GGAFPROPERTIES_H_
#define GGAFCORE_GGAFPROPERTIES_H_
#include "GgafCommonHeader.h"

#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/core/util/GgafRgb.h"

#ifdef PROPERTY
    #undef PROPERTY
#endif
#define PROPERTY GgafCore::GgafProperties

namespace GgafCore {

/**
 * プロパティクラス .
 * 外部ファイルからロードし、アプリの環境変数として保持します。
 * @version 1.00
 * @since 2008/07/22
 * @author Masatoshi Tsuge
 */
class GgafProperties {


public:
    /** [r/w] 最高フレームスキップ数。つまりどんなに重くも最低描画するフレーム間隔。*/
    static uint32_t MAX_SKIP_FRAME;
    /** [r/w] 60fps→40fpsの処理落ち演出を行うかどうかの境界。1フレームあたり内部描画回数で設定 */
    static int DRAWNUM_TO_SLOWDOWN1;
    /** [r/w] 40fps→30fpsの処理落ち演出を行うかどうかの境界。1フレームあたり内部描画回数で設定 */
    static int DRAWNUM_TO_SLOWDOWN2;
    /** [r/w] ゴミ箱を掃除(インスタンス解放)を行うことが出来るFPS */
    static float FPS_TO_CLEAN_GARBAGE_BOX;
    /** [r] アプリケーションのリソースディレクトリ */
    static std::string DIR_RESOURCE;
    /** [r] アプリケーションのスキンフォルダ名(リソースディレクトリ配下) */
    static std::string DIRNAME_RESOURCE_SKIN;
    /** [r] アプリケーションのスキンフォルダのデフォルトスキン名(リソースディレクトリのスキンフォルダ配下) */
    static std::string DIRNAME_RESOURCE_SKIN_DEFAULT;
    /** [r] アプリケーションのスキンフォルダのユーザースキン名(リソースディレクトリのスキンフォルダ配下) */
    static std::string DIRNAME_RESOURCE_SKIN_USER;

    ////// 以下は、上記プロパティから生成される読み出し専用プロパティ ////////

    /** [r] アプリケーションのスキンディレクトリ */
    static std::string DIR_SKIN;
    /** [r] アプリケーションのデフォルトスキンディレクトリ(0:default/1:ユーザー/2:カレント) */
    static std::string DIR_SKIN_KIND[3];




    /** [r] 保持プロパティMAP */
    static GgafStrMap* _pMapProperties;

public:
    /**
     * 外部プロパティファイルから未ロードならロードして保持プロパティMAPへ設定、メンバ変数に反映 .
     * @param prm_properties_filename プロパティファイル
     */
    static void load(std::string prm_properties_filename);

    /**
     * 保持プロパティMAPを、外部プロパティファイルへ保存 .
     * @param prm_properties_filename プロパティファイル
     */
    static void save(std::string prm_properties_filename);

    /**
     * 保持プロパティを解放 .
     */
    static void clean();

    /**
     * 保持プロパティMAPにキーが存在するか調べる .
     * @param prm_key キー文字列
     * @return true:キーが存在 / false:存在しない
     */
    static bool isExistKey(std::string prm_key);

    /**
     * キーに対するプロパティ値を string で取得 .
     * @param prm_key キー文字列
     * @return プロパティ値(string)
     */
    static std::string getStr(std::string prm_key);

    /**
     * キーに対するプロパティ値をboolで取得 .
     * true, on, yes の文字列の場合 true とみなし、それ以外は false。
     * @param prm_key キー文字列
     * @return プロパティ値(bool)
     */
    static bool getBool(std::string prm_key);

    /**
     * キーに対するプロパティ値を float で取得 .
     * 内部で atof() を使用。
     * @param prm_key キー文字列
     * @return プロパティ値(float)
     */
    static float getFloat(std::string prm_key);

    /**
     * キーに対するプロパティ値を int で取得 .
     * 内部で atoi() を使用。
     * @param prm_key キー文字列
     * @return プロパティ値(int)
     */
    static int getInt(std::string prm_key);

    /**
     * キーに対するプロパティ値を uint32_t で取得 .
     * 内部で _atoi64() して、uint32_tにキャスト
     * @param prm_key キー文字列
     * @return プロパティ値(uint32_t)
     */
    static uint32_t getUInt(std::string prm_key);

    /**
     * キーに対するプロパティ値を double で取得 .
     * @param prm_key キー文字列
     * @return プロパティ値(double)
     */
    static double getDouble(std::string prm_key);

    /**
     * キーに対するプロパティ値を GgafRgb で取得 .
     * GgafRgb は、"#FFFFFF"（#省略可）形式の文字列から、R値、G値、B値に変換して保持します。
     * @param prm_key キー文字列
     * @return プロパティ値(GgafRgb)
     */
    static GgafRgb getRGB(std::string prm_key);

    /**
     * 保持プロパティMAPに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, int prm_value);

    /**
     * 保持プロパティMAPに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, uint32_t prm_value);

    /**
     * 保持プロパティMAPに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, std::string prm_value);

    /**
     * 保持プロパティMAPに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, float prm_value);

    /**
     * 保持プロパティMAPに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, double prm_value);

    /**
     * 保持プロパティMAPに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, bool prm_value);

    /**
     * 保持プロパティMAPに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, GgafRgb prm_value);

};

}
#endif /*GGAFCORE_GGAFPROPERTIES_H_*/

