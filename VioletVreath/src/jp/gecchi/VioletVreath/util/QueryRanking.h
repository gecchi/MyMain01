#ifndef QUERYRANKING_H_
#define QUERYRANKING_H_
namespace VioletVreath {

#define QUERYRANKING_NAME_LEN 10
#define QUERYRANKING_SCORE_LEN 10
#define QUERYRANKING_RECORD_NUM 10
#define QUERYRANKING_DATA_FILE "SCORE_RANKING.qry"

/**
 * ハイスコアランキング用クエリ .
 * @version 1.00
 * @since 2012/10/15
 * @author Masatoshi Tsuge
 */
class QueryRanking : public GgafCore::GgafQuery {

public:
    QueryRanking();
    /**
     * 初期化 .
     * データファイルがある場合は読み込み。
     * データファイルがない場合はデフォルトのランキングクエリの内部作成。
     */
    void init();

    /**
     * ランキングクエリの末尾にデータ追加する .
     * @param prm_name スコアネーム
     * @param prm_score スコア
     */
    void addRow(std::string& prm_name, int prm_score);

    /**
     * ランキングクエリのソートを行う .
     */
    void sort();

    /**
     * ランキングのスコアを調べて、ランク・インするかどうか調べる 。
     * @param prm_score スコア
     * @return true:ランク・イン/false:ランク外
     */
    bool isRankIn(int prm_score);

    /**
     * ランキングクエリをデータファイルに保存する。
     */
    void save();

    virtual ~QueryRanking();
};

}
#endif /*QUERYRANKING_H_*/
