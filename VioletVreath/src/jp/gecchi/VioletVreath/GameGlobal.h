#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/util/RankingTable.h"

#define G_MIN_RANK (0.0)
#define G_MAX_RANK (1.0)
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
/** スコア */
#define G_ZANKI (VioletVreath::GameGlobal::zanki_)
/** ランキングスコア */
#define G_RANKING_TABLE (VioletVreath::GameGlobal::tblRanking_)


#define G_MAX_RANKUP_LEVEL (1230)

/**
 * ランク用関数(上限下限無し) .
 * 引数のランク値(RANK_VAL)が、
 * G_MIN_RANK ～ G_MAX_RANK に推移するに伴って MIN_VAL～MAX_VAL に推移する値を取得。
 */
#define RF(RANK_VAL, MIN_VAL, MAX_VAL)  ( RCNV( (G_MIN_RANK), (G_MAX_RANK), (RANK_VAL), (MIN_VAL), (MAX_VAL) ) )

/**
 * ランク用関数(上限下限有り) .
 * 引数のランク値(RANK_VAL)が、G_MIN_RANK ～ G_MAX_RANK に推移するに伴って MIN_VAL～MAX_VAL に推移する値を取得。
 * 但し、定義域(RANK_VAL)：G_MIN_RANK <= RANK_VAL <= G_MIN_RANK  に対して、
 *         値域(N)       ：   MIN_VAL <=    N     <= MAX_VAL     を返す。
 * ランク値(RANK_VAL)がG_MIN_RANKを下回る場合は、MIN_VALに固定。
 * ランク値(RANK_VAL)がG_MAX_RANKを上回る場合は、MAX_VALに固定。
 */
#define RF_ULL(RANK_VAL, MIN_VAL, MAX_VAL)  ( ((RANK_VAL) < (G_MIN_RANK)) ? (MIN_VAL) : ( ((RANK_VAL) > (G_MAX_RANK)) ? (MAX_VAL) : (RCNV((G_MIN_RANK), (G_MAX_RANK), (RANK_VAL), (MIN_VAL), (MAX_VAL))) ) )

/**
 * ランク用関数(下限のみ有り) .
 * 引数のランク値(RANK_VAL)が、G_MIN_RANK ～ G_MAX_RANK に推移するに伴って MIN_VAL～MAX_VAL に推移する値を取得。
 * 但し、定義域(RANK_VAL)：G_MIN_RANK <= RANK_VAL  に対して、
 *         値域(N)       ：   MIN_VAL <=    N      を返す。
 * ランク値(RANK_VAL)がG_MIN_RANKを下回る場合は、MIN_VALに固定。
 */
#define RF_LL(RANK_VAL, MIN_VAL, MAX_VAL)  ( ((RANK_VAL) < (G_MIN_RANK)) ? (MIN_VAL) : (RCNV((G_MIN_RANK), (G_MAX_RANK), (RANK_VAL), (MIN_VAL), (MAX_VAL))) )

/**
 * ランク用関数(上限のみ有り) .
 * 引数のランク値(RANK_VAL)が、G_MIN_RANK ～ G_MAX_RANK に推移するに伴って MIN_VAL～MAX_VAL に推移する値を取得。
 * 但し、定義域(RANK_VAL)：RANK_VAL <= G_MIN_RANK  に対して、
 *         値域(N)       ：   N     <= MAX_VAL     を返す。
 * ランク値(RANK_VAL)がG_MAX_RANKを上回る場合は、MAX_VALに固定。
 */
#define RF_UL(RANK_VAL, MIN_VAL, MAX_VAL)  ( ((RANK_VAL) > (G_MAX_RANK)) ? (MAX_VAL) : (RCNV((G_MIN_RANK), (G_MAX_RANK), (RANK_VAL), (MIN_VAL), (MAX_VAL))) )


namespace VioletVreath {

class GameGlobal {
public:
    static bool is_init_;
    /** 現スコア */
    static int score_;
    /** 現ランク値（0.0 ～ 1.0。 1.0がMAXランクとする) */
    static double rank_;
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

