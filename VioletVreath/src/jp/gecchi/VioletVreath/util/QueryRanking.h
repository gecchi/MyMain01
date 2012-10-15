#ifndef QUERYRANKING_H_
#define QUERYRANKING_H_
namespace VioletVreath {

#define QUERYRANKING_NAME_LEN 10
#define QUERYRANKING_SCORE_LEN 10
#define QUERYRANKING_RECORD_NUM 10
#define QUERYRANKING_FILE "SCORE_RANKING.qry"

/**
 * ハイスコアランキング用クエリー .
 * @version 1.00
 * @since 2012/10/15
 * @author Masatoshi Tsuge
 */
class QueryRanking : public GgafCore::GgafQuery {

public:
    QueryRanking();
    void init();
    void addRow(std::string& prm_name, int prm_score);
    void sort();
    bool isRankIn(int prm_score);
    void save();
    virtual ~QueryRanking();
};

}
#endif /*QUERYRANKING_H_*/
