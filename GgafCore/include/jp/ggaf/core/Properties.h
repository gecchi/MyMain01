#ifndef GGAF_CORE_PROPERTIES_H_
#define GGAF_CORE_PROPERTIES_H_
#include "GgafCommonHeader.h"

#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/util/Rgb.h"

namespace GgafCore {

/**
 * プロパティクラス .
 * 外部ファイルからロードし、アプリの環境変数として保持します。
 * @version 1.00
 * @since 2008/07/22
 * @author Masatoshi Tsuge
 */
class Properties : public Object {


public:
    /** [r] 保持プロパティ */
    StrMap _mapProperties;

public:
    Properties();

    Properties(std::string prm_properties_filename);

    /**
     * 外部プロパティファイルから未ロードならロードして保持プロパティへ設定、メンバ変数に反映 .
     * @param prm_properties_filename プロパティファイル
     */
    void read(std::string prm_properties_filename);

    void read(std::istream& is);

    /**
     * 保持プロパティを、外部プロパティファイルへ保存 .
     * @param prm_properties_filename プロパティファイル
     */
    void write(std::string prm_properties_filename, const char *header = nullptr);

//    void write(std::ostream &os, const char *header = nullptr);

    void print(std::ostream &os);


    /**
     * 保持プロパティにキーが存在するか調べる .
     * @param prm_key キー文字列
     * @return true:キーが存在 / false:存在しない
     */
    bool isExistKey(std::string prm_key);

    /**
     * キーに対するプロパティ値を string で取得 .
     * @param prm_key キー文字列
     * @return プロパティ値(string)
     */
    std::string getStr(std::string prm_key);

    /**
     * キーに対するプロパティ値をboolで取得 .
     * true, on, yes の文字列の場合 true とみなし、それ以外は false。
     * @param prm_key キー文字列
     * @return プロパティ値(bool)
     */
    bool getBool(std::string prm_key);

    /**
     * キーに対するプロパティ値を float で取得 .
     * 内部で atof() を使用。
     * @param prm_key キー文字列
     * @return プロパティ値(float)
     */
    float getFloat(std::string prm_key);

    /**
     * キーに対するプロパティ値を int で取得 .
     * 内部で atoi() を使用。
     * @param prm_key キー文字列
     * @return プロパティ値(int)
     */
    int getInt(std::string prm_key);

    /**
     * キーに対するプロパティ値を uint32_t で取得 .
     * 内部で _atoi64() して、uint32_tにキャスト
     * @param prm_key キー文字列
     * @return プロパティ値(uint32_t)
     */
    uint32_t getUInt(std::string prm_key);

    /**
     * キーに対するプロパティ値を double で取得 .
     * @param prm_key キー文字列
     * @return プロパティ値(double)
     */
    double getDouble(std::string prm_key);

    /**
     * キーに対するプロパティ値を Rgb で取得 .
     * Rgb は、"#FFFFFF"（#省略可）形式の文字列から、R値、G値、B値に変換して保持します。
     * @param prm_key キー文字列
     * @return プロパティ値(Rgb)
     */
    Rgb getRGB(std::string prm_key);

    /**
     * 保持プロパティに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, int prm_value);

    /**
     * 保持プロパティに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, uint32_t prm_value);

    /**
     * 保持プロパティに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, std::string prm_value);

    /**
     * 保持プロパティに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, float prm_value);

    /**
     * 保持プロパティに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, double prm_value);

    /**
     * 保持プロパティに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, bool prm_value);

    /**
     * 保持プロパティに値を設定。
     * 設定してもメンバにはまだ反映されません。
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, Rgb prm_value);

};

}
#endif /*GGAF_CORE_PROPERTIES_H_*/

