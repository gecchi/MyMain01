#ifndef GGAFQUERY_H_
#define GGAFQUERY_H_

/** GgafQueryの１レコードの型 */
typedef std::map<const char*, std::string> GgafRecord;

namespace GgafCore {

/**
 * SQLのSELECTの結果（クエリ）を格納し、オブジェクトとして扱うことを目的としたクラス.  <BR>
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
    void sortBy(const char* prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
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
    void sortDescBy(const char* prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
                    bool prm_blank_is_max);
public:
    /** クエリの列番号と値のペアをもったMapのListです */
    std::vector<GgafRecord*> _lstTtable;

    GgafQuery();

    size_t getCount();

    bool hasRecord();

    std::string get(const char* prm_col, int prm_index);

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



    void sortBy(const char* prm_col[], int prm_col_num, bool prm_blank_is_max);

    void sortBy(const char* prm_col, bool prm_blank_is_max = false);

    void sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max = false);

    void sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max = false);


    void sortDescBy(const char* prm_col[], int prm_col_num, bool prm_blank_is_max);

    void sortDescBy(const char* prm_col, bool prm_blank_is_max = false);
    void sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max = false);
    void sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max = false);

    void dump();
    virtual ~GgafQuery();
};

}
#endif /*GGAFQUERY_H_*/
