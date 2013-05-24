#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_

#include "jp/gecchi/VioletVreath/util/QueryRanking.h"

/** ランク (0.0 ～ 1.0) */
#define _RANK_ (GameGlobal::rank_)
/** 表示用ランク値 */
#define _RANK_DISP_ ((int)(_RANK_*100000))
/** ランクアップレベル値 */
#define _RANK_UP_LEVEL_ (VioletVreath::GameGlobal::rank_up_level_)
#define _SCORE_ (VioletVreath::GameGlobal::score_)

namespace VioletVreath {

class GameGlobal {
public:
    static bool is_init_;
    /** スコア */
    static int score_;
    /** ランク（0.0 ～ 1.0。 1.0がMAXランクとする) */
    static double rank_;
    static int rank_up_level_;
    static QueryRanking qryRanking_;
    static void init();
};

}
#endif /*GAMEGLOBAL_H_*/

