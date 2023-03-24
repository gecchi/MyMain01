#ifndef RANKINGTABLE_H_
#define RANKINGTABLE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/util/Table.h"

namespace VioletVreath {

#define RANKINGTABLE_NAME_LEN 10
#define RANKINGTABLE_SCORELEN 10
#define RANKINGTABLE_RECORD_NUM 10
#define RANKINGTABLE_DATA_FILE "SCORE_RANKING.tbl"

/**
 * ハイスコアランキング用クエリ .
 * @version 1.00
 * @since 2012/10/15
 * @author Masatoshi Tsuge
 */
class RankingTable : public GgafCore::Table {

public:
    RankingTable();
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

    virtual ~RankingTable();
};

}
#endif /*RANKINGTABLE_H_*/
