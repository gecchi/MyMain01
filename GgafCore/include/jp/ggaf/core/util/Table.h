#ifndef GGAF_CORE_TABLE_H_
#define GGAF_CORE_TABLE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>
#include <vector>
#include <map>

/** Tableファイルのセパレータ */
#define GGAFTABLE_SEPA "\t"

namespace GgafCore {

/** Tableの１レコードの型 */
typedef std::map<std::string, std::string> Record;

/**
 * DBのクエリ結果のようなオブジェクトを扱うクラス.
 * 内部データを全て std::string で保持している。
 * @version 1.00
 * @since 2012/10/02
 * @author Masatoshi Tsuge
 */
class Table : public Object {

private:
    /**
     * 引数の列の配列順の要素値で、内部レコードを昇順ソートし並べ変えます. <BR>
     * クイックソート使用。<BR>
     * @param prm_col 昇順ソートする順番の列名配列
     * @param prm_col_num 列名配列要素数
     * @param prm_begin_index 開始INDEX
     * @param prm_end_index 終了INDEX
     * @param prm_blank_is_max true:空文字("")を最大値とします／false:空文字("")を最小値とします。
     */
    void sortBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
                bool prm_blank_is_max);

    /**
     * 引数の列の配列順の要素値で、内部レコードを降順ソートし並べ変えます. <BR>
     * クイックソート使用。<BR>
     * @param prm_col 降順ソートする順番の列名配列
     * @param prm_col_num 列名配列要素数
     * @param prm_begin_index 開始INDEX
     * @param prm_end_index 終了INDEX
     * @param prm_blank_is_max true:空文字("")を最大値とします／false:空文字("")を最小値とします。
     */
    void sortDescBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
                    bool prm_blank_is_max);

    /** クエリの列番号と値のペアをもったMapのListです */
    std::vector<Record*> _lstTtable;

public:
    /**
     * 内容が空のクエリを作成 .
     */
    Table();

    /**
     * TSVでファイルを読み込んで、クエリを作成 .
     * @param prm_file_name
     */
    void importFromFile(std::string prm_file_name);

    /**
     * TSVでファイルに保存 .
     * ヘッダーは１行目(index=0)のレコードが信用されます。
     * @param prm_file_name 保存ファイル名
     */
    void exportToFile(std::string prm_file_name);

    /**
     * レコード件数を返す .
     * @return レコード件数
     */
    size_t getCount() const;

    bool hasRecord() const ;

    /**
     * データを取得 .
     * @param prm_col   列名
     * @param prm_index レコードindex(0～)
     * @return データ値
     */
    std::string getVal(std::string& prm_col, int prm_index);

    /**
     * データを取得 .
     * @param prm_col   列名
     * @param prm_index レコードindex(0～)
     * @return データ値
     */
    std::string getVal(const char* prm_col, int prm_index);

    /**
     * データを上書き設定します .
     * @param prm_col    列名
     * @param prm_index  レコードindex(0～)
     * @param prm_val    上書きする設定値
     */
    void setVal(std::string& prm_col, int prm_index, std::string& prm_val);
    /**
     * データを上書き設定します .
     * @param prm_col    列名
     * @param prm_index  レコードindex(0～)
     * @param prm_val    上書きする設定値
     */
    void setVal(const char* prm_col, int prm_index, std::string& prm_val);
    /**
     * データを上書き設定します .
     * @param prm_col    列名
     * @param prm_index  レコードindex(0～)
     * @param prm_val    上書きする設定値
     */
    void setVal(std::string& prm_col, int prm_index, const char* prm_val);
    /**
     * データを上書き設定します .
     * @param prm_col    列名
     * @param prm_index  レコードindex(0～)
     * @param prm_val    上書きする設定値
     */
    void setVal(const char* prm_col, int prm_index, const char* prm_val);

    /**
     * レコードを取得します。 .
     * @param prm_index レコードindex(0～)
     * @return
     */
    Record* getRecord(int prm_index);

    /**
     * レコードを削除します。 .
     * @param prm_index レコードindex(0～)
     */
    void removeRow(int prm_index);

    /**
     * 指定index以降のレコードを削除します。 .
     * @param prm_start_index レコードindex(0～)
     */
    void removeRows(int prm_start_index);

    /**
     * 指定範囲indexのレコードを削除します。 .
     * @param prm_start_index 削除開始index(0 ～)
     * @param prm_end_index   削除終了index(0 ～ getCount()-1)
     */
    void removeRows(int prm_start_index, int prm_end_index);

    /**
     * レコードを末尾行に追加します .
     * Record オブジェクトのポインタを渡して下さい。<BR>
     * 本クエリオブジェクト開放時に、全Recordの解放が行われる仕様です。
     * 呼び元で Record オブジェクトの delete は不要。(むしろ、出来ません。行わないで下さい)
     * @param prm_pRow ヒープに作成したレコードオブジェクト（のポインタ）
     */
    void addRow(Record* prm_pRow);

    /**
     * レコードを末尾行に空レコードを追加します
     */
    void addNewRow();

    /**
     * AとBのレコードの場所(INDEX)を入れ替えます. <BR>
     * @param prm_index_A 入れ替え対象レコードINDEX A
     * @param prm_index_B 入れ替え対象レコードINDEX B
     */
    void swapIndex(int prm_index_A, int prm_index_B);

    /**
     * 引数の列で昇順ソートします .
     * @param prm_col 列名
     * @param prm_blank_is_max 空文字("")をソート順の最大とするか否か。
     */
    void sortBy(const char* prm_col, bool prm_blank_is_max);
    /**
     * 引数の列で昇順ソートします .
     * @param prm_col1  第１ソート列名
     * @param prm_col2  第２ソート列名
     * @param prm_blank_is_max 空文字("")をソート順の最大とするか否か。
     */
    void sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max);
    void sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max);
    void sortBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max);

    void sortDescBy(const char* prm_col, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max);
    void sortDescBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max);

    /**
     * 空文字を考慮してTAB文字で分割 .
     * <pre>
     * 【例】
     * std::vector<std::string> data = split("\taaa\tbbb\t\t\tcccc\tddd\teeee\t\t", "\t");
     * ＜結果＞
     * data[0] = (空文字)
     * data[1] = "aaa"
     * data[2] = "bbb"
     * data[3] = (空文字)
     * data[4] = (空文字)
     * data[5] = "cccc"
     * data[6] = "ddd"
     * data[7] = "eeee"
     * data[8] = (空文字)
     * data[9] = (空文字)
     * </pre>
     * @param str
     * @return 文字列のベクタリスト
     */
    static inline std::vector<std::string> split(std::string str) {
        std::vector<std::string> r;
        size_t cutAt;
        while ((cutAt = str.find_first_of(GGAFTABLE_SEPA)) != str.npos) {
            r.push_back(str.substr(0, cutAt));
            str = str.substr(cutAt + 1);
        }
        r.push_back(str);
        return r;
    }

    void dump();
    virtual ~Table();
};

}
#endif /*GGAF_CORE_TABLE_H_*/
