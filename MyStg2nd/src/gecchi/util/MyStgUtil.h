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
     * �����N���l���當����ϊ�
     * @param prm_rank �����N���l(1�`100000)
     * @param out ���ʏo��[80]�K�v
     * @return
     */
    static void getRankStr(int prm_rank, char* out);
};

}
#endif /*MYSTGUTIL_H_*/
