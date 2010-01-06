#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_
namespace MyStg2nd {

class MyStgUtil: public GgafDx9LibStg::StgUtil {
public:

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
    static void getRankStr(int prm_rank, char* out);
};

}
#endif /*MYSTGUTIL_H_*/
