#ifndef GGAFPROPERTIES_H_
#define GGAFPROPERTIES_H_

#ifdef GGAF_PROPERTY
    #undef GGAF_PROPERTY
#endif
#define GGAF_PROPERTY(X) (GgafCore::GgafProperties::X)

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
    static UINT32 MAX_SKIP_FRAME;
    /** [r/w] 60fps→40fpsの処理落ち演出を行うかどうかの境界。1フレームあたり内部描画回数で設定 */
    static int DRAWNUM_TO_SLOWDOWN1;
    /** [r/w] 40fps→30fpsの処理落ち演出を行うかどうかの境界。1フレームあたり内部描画回数で設定 */
    static int DRAWNUM_TO_SLOWDOWN2;
    /** [r/w] ゴミ箱を掃除(インスタンス解放)を行うことが出来るFPS */
    static float FPS_TO_CLEAN_GARBAGE_BOX;
    /** [r] 保持プロパティMAP */
    static GgafStrMap* _pMapProperties;

    /**
     * 外部プロパティファイルから未ロードならロードしてプロパティ保持 .
     * @param prm_properties_filename プロパティファイル
     */
    static void load(std::string prm_properties_filename);

    /**
     * 保持プロパティを解放 .
     */
    static void clean();

    /**
     * 保持プロパティにキーが存在するか調べる .
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
     * キーに対するプロパティ値を float で取得 .
     * 内部で atoi() を使用。
     * @param prm_key キー文字列
     * @return プロパティ値(int)
     */
    static int getInt(std::string prm_key);

    /**
     * キーに対するプロパティ値を UINT32 で取得 .
     * 内部で _atoi64() して、UINT32にキャスト
     * @param prm_key キー文字列
     * @return プロパティ値(UINT32)
     */
    static UINT32 getUInt(std::string prm_key);

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

};

}
#endif /*GGAFPROPERTIES_H_*/

