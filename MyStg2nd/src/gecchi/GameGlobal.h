#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_

/** ランク (0.0 ～ 1.0) */
#define _RANK_ (GameGlobal::_rank)
/** 表示用ランク値 */
#define _RANK_DISP_ ((int)(_RANK_*100000))
/** ランクアップレベル値 */
#define _RANK_UP_LEVEL_ (MyStg2nd::GameGlobal::_rank_up_level)
#define _SCORE_ (MyStg2nd::GameGlobal::_score)

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

