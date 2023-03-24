#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/util/RankingTable.h"

/** 現在のランク値 (G_MIN_RANK ～ G_MAX_RANK) */
#define G_RANK (VioletVreath::GameGlobal::rank_)
#define G_MIN_RANK (VioletVreath::GameGlobal::min_rank_)
#define G_MAX_RANK (VioletVreath::GameGlobal::max_rank_)
/** ランク→表示用ランクレート */
#define G_RANK_R (1000.0)
/** 画面表示用ランク値 */
#define G_RANK_DISP ((int)(G_RANK*G_RANK_R))

/** ランクアップレベル値。StageWorld::processBehavior()でG_RANKに追従 */
#define G_RANKUP_LEVEL (VioletVreath::GameGlobal::rank_up_level_)
/** スコア */
#define G_SCORE (VioletVreath::GameGlobal::score_)
/** スコア */
#define G_ZANKI (VioletVreath::GameGlobal::zanki_)
/** ランキングスコア */
#define G_RANKING_TABLE (VioletVreath::GameGlobal::tblRanking_)


#define G_MAX_RANKUP_LEVEL (1230)

/**
 * ランク用関数(上限下限無し) .
 * 引数のランク値(RANK_VAL)が、
 * G_RANKが、0.0 ～ 1.0 に推移するに伴って RANK_0_VAL～RANK_1_VAL に推移する値を取得。
 * ランク値(RANK_VAL)が 0.0 を下回っても制限無し。
 * ランク値(RANK_VAL)が 1.0 を上回っても制限無し。
 */
#define RF(RANK_VAL, RANK_0_VAL, RANK_1_VAL)  ( RCNV_0_1_to( (RANK_VAL), (RANK_0_VAL), (RANK_1_VAL) ) )

/**
 * ランク用関数(上限下限有り) .
 * 引数のランク値(RANK_VAL)が、G_RANKが、0.0 ～ 1.0 に推移するに伴って RANK_0_VAL～RANK_1_VAL に推移する値を取得。
 * ランク値(RANK_VAL)が 0.0 を下回る場合は、RANK_0_VALに固定。
 * ランク値(RANK_VAL)が 1.0 を上回る場合は、RANK_1_VALに固定。
 */
#define RF_ULL(RANK_VAL, RANK_0_VAL, RANK_1_VAL)  ( ((RANK_VAL) < 0) ? (RANK_0_VAL) : ( ((RANK_VAL) > 1) ? (RANK_1_VAL) : (RCNV_0_1_to((RANK_VAL),(RANK_0_VAL),(RANK_1_VAL))) ) )

/**
 * ランク用関数(下限のみ有り) .
 * 引数のランク値(RANK_VAL)が、G_RANKが、0.0 ～ 1.0 に推移するに伴って RANK_0_VAL～RANK_1_VAL に推移する値を取得。
 * ランク値(RANK_VAL)が 0.0 を下回る場合は、RANK_0_VALに固定。
 * ランク値(RANK_VAL)が 1.0 を上回っても制限無し。
 */
#define RF_LL(RANK_VAL, RANK_0_VAL, RANK_1_VAL)  ( ((RANK_VAL) < 0) ? (RANK_0_VAL) : (RCNV_0_1_to((RANK_VAL),(RANK_0_VAL),(RANK_1_VAL))) )

/**
 * ランク用関数(上限のみ有り) .
 * 引数のランク値(RANK_VAL)が、G_RANKが、0.0 ～ 1.0 に推移するに伴って RANK_0_VAL～RANK_1_VAL に推移する値を取得。
 * ランク値(RANK_VAL)が 0.0 を下回っても制限無し。
 * ランク値(RANK_VAL)が 1.0 を上回る場合は、RANK_1_VALに固定。
 */
#define RF_UL(RANK_VAL, RANK_0_VAL, RANK_1_VAL)  ( ((RANK_VAL) > 1) ? (RANK_1_VAL) : (RCNV_0_1_to((RANK_VAL),(RANK_0_VAL),(RANK_1_VAL))) )


namespace VioletVreath {

class GameGlobal {
public:
    static bool is_init_;
    /** 現スコア */
    static int score_;
    /** 現ランク値（デフォルトは、0.0 ～ 1.0。 1.0がMAXランクとする) */
    static double rank_;
    /** ランク下限値 */
    static double min_rank_;
    /** ランク上限値 */
    static double max_rank_;
    /** 現残機 */
    static int zanki_;
    /** 現ランクレベル値 */
    static int rank_up_level_;
    /** ランキングテーブル */
    static RankingTable tblRanking_;
    /** 素数 */
    static int prime_n_[];

    /**
     * G_RANKを参照し、G_RANKUP_LEVELを加算します。
     * @return true:G_RANKUP_LEVELを加算した /false:G_RANKUP_LEVELは変化なし
     */
    static bool updateRankUpLebel();
};

}
#endif /*GAMEGLOBAL_H_*/

