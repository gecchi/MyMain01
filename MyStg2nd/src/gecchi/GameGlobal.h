#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
namespace MyStg2nd {


class GameGlobal {
public:
    static bool _isInit;
    /** スコア */
    static UINT32 _score;

    /** ステージ */
    static int _iScene;
    /** ランク（0.0 ～ 1.0。 1.0がMAXランクとする) */
    static double _rank;

    static void init();
};

}
#endif /*GAMEGLOBAL_H_*/

