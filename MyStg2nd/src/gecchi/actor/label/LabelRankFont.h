#ifndef RANKFONT_H_
#define RANKFONT_H_
namespace MyStg2nd {

/**
 * ランクフォント .
 * @version 1.00
 * @since 2011/06/04
 * @author Masatoshi Tsuge
 */
class LabelRankFont : public GgafDx9LibStg::StringBoardActor {
private:
    /**
     * 使用不可
     */
    virtual void update(coord X, coord Y, const char* prm_str) override {}
    /**
     * 使用不可
     */
    virtual void update(coord X, coord Y, char* prm_str) override {}
    /**
     * 使用不可
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str) override {}
    /**
     * 使用不可
     */
    virtual void update(coord X, coord Y, coord Z, char* prm_str) override {}
    /**
     * 使用不可
     */
    virtual void update(const char* prm_str) override {}
    /**
     * 使用不可
     */
    virtual void update(char* prm_str) override {}
public:
    int _rank;
    int _tmp_rank;
    static char RANK_1stDeg[10][6];
    static char RANK_10thDeg[10][5];
    static char RANK_100thDeg[10][7];
    static char RANK_1000thDeg[10][9];
    static char RANK_10000thDeg[10][46];
    static char RANK_INF[7];

    /**
     * ランク数値から文字列変換
     * @param prm_rank ランク数値(1～100000)
     * @param out 結果出力[80]必要
     * @return
     */
    static void cnvRankStr(int prm_rank, char* out);

    LabelRankFont(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    /**
     * 右揃え固定長表示にオーバーライド .
     */
    virtual void processDraw() override;

    virtual ~LabelRankFont();

};

}
#endif /*RANKFONT_H_*/
