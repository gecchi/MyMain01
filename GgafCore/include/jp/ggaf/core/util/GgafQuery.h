#ifndef GGAFQUERY_H_
#define GGAFQUERY_H_

/** GgafQueryの１レコードの型 */
typedef std::map<std::string, std::string> GgafRecord;
#define GGAFQUERY_SEPA "\t"

namespace GgafCore {

/**
 * SELECTクエリを模したオブジェクトを扱うクラス.  <BR>
 * @version 1.00
 * @since 2012/10/02
 * @author Masatoshi Tsuge
 */
class GgafQuery : public GgafCore::GgafObject {

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
public:
    /** クエリの列番号と値のペアをもったMapのListです */
    std::vector<GgafRecord*> _lstTtable;

    /**
     * 内容が空のクエリを作成 .
     */
    GgafQuery();

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
    size_t getCount();

    bool hasRecord();

    std::string getVal(std::string prm_col, int prm_index);

    GgafRecord* getRecord(int prm_index);
    /**
     * レコードを削除します。 .
     * @param prm_index レコードindex（0～)
     * @throws GwafInternalException 引数のレコードindexが範囲外
     */
    void removeRow(int prm_index);
    void removeRows(int prm_start_index, int prm_end_index);

    void addRow(GgafRecord* prm_pRow);
    /**
     * AとBのレコードの場所(INDEX)を入れ替えます. <BR>
     * @param prm_index_A 入れ替え対象レコードINDEX A
     * @param prm_index_B 入れ替え対象レコードINDEX B
     */
    void swapIndex(int prm_index_A, int prm_index_B);

    void sortBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max);
    void sortBy(const char*, bool prm_blank_is_max);
    void sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max);
    void sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max);

    void sortDescBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max);

    /**
     * TABで分割 .
     * 空文字要素は飛ばされない。
     * <pre>
     * 【例】
     * std::vector<std::string> data = split("\taaa\tbbb\t\t\tcccc\tddd\teeee\t\t", "\t");
     * ＜結果＞
     * data[0] = (空文字)
     * data[1] = aaa
     * data[2] = bbb
     * data[3] = (空文字)
     * data[4] = (空文字)
     * data[5] = cccc
     * data[6] = ddd
     * data[7] = eeee
     * data[8] = (空文字)
     * data[9] = (空文字)
     * </pre>
     * @param str
     * @return
     */
    static inline std::vector<std::string> split(std::string str) {
        std::vector<std::string> r;
        int cutAt;
        while ((cutAt = str.find_first_of(GGAFQUERY_SEPA)) != str.npos) {
            r.push_back(str.substr(0, cutAt));
            str = str.substr(cutAt + 1);
        }
        r.push_back(str);
        return r;
    }

    void dump();
    virtual ~GgafQuery();
};

}
#endif /*GGAFQUERY_H_*/
