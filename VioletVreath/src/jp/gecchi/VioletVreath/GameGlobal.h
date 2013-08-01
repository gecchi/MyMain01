#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_

#include "jp/gecchi/VioletVreath/util/QueryRanking.h"

/** ランク (0.0 ～ 1.0) */
#define G_RANK (VioletVreath::GameGlobal::rank_)
/** ランク→表示用ランクレート */
#define G_RANK_R (1000.0)
/** 表示用ランク値 */
#define G_RANK_DISP ((int)(G_RANK*G_RANK_R))

/** ランクアップレベル値。StageWorld::processBehavior()でG_RANKに追従 */
#define G_RANKUP_LEVEL (VioletVreath::GameGlobal::rank_up_level_)
/** スコア */
#define G_SCORE (VioletVreath::GameGlobal::score_)
/** ランキングスコア */
#define G_RANKING (VioletVreath::GameGlobal::qryRanking_)


#define G_MAX_RANKUP_LEVEL (1230)

namespace VioletVreath {

class GameGlobal {
public:
    static bool is_init_;
    /** スコア */
    static int score_;
    /** ランク値（0.0 ～ 1.0。 1.0がMAXランクとする) */
    static double rank_;

    static int rank_up_level_;
    static QueryRanking qryRanking_;
    static int prime_n_[];
    /**
     * G_RANKを参照し、G_RANKUP_LEVELを加算します。
     * @return true:G_RANKUP_LEVELを加算した /false:G_RANKUP_LEVELは変化なし
     */
    static bool updateRankUpLebel();
};

}
#endif /*GAMEGLOBAL_H_*/

