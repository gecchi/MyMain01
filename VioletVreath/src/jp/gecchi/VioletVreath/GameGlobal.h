#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_

#include "jp/gecchi/VioletVreath/util/QueryRanking.h"

/** ランク (0.0 ～ 1.0) */
#define G_RANK (VioletVreath::GameGlobal::rank_)
/** 表示用ランク値 */
#define G_RANK_DISP ((int)(G_RANK*100000))
/** ランクアップレベル値 */
#define G_RANKUP_LEVEL (VioletVreath::GameGlobal::rank_up_level_)
/** スコア */
#define G_SCORE (VioletVreath::GameGlobal::score_)
/** ランキングスコア */
#define G_RANKING (VioletVreath::GameGlobal::qryRanking_)

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
};

}
#endif /*GAMEGLOBAL_H_*/

