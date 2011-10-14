#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
namespace MyStg2nd {


class GameGlobal {
public:
    static bool _isInit;
    /** スコア */
    static UINT32 _score;

    /** ランク（0.0 ～ 1.0。 1.0がMAXランクとする) */
    static double _rank;
    static int _rank_up_level;
    static void init();
};

}
#endif /*GAMEGLOBAL_H_*/

