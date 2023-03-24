#ifndef RANKFONT_H_
#define RANKFONT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * ランク表示 .
 * @version 1.00
 * @since 2011/06/04
 * @author Masatoshi Tsuge
 */
class LabelRankFont : public GgafLib::FontBoardActor {
    static char RANK_1stDeg[][6];
    static char RANK_10thDeg[][5];
    static char RANK_100thDeg[][7];
    static char RANK_1000thDeg[][9];
    static char RANK_10000thDeg[][46];
    static char RANK_INF[];

public:
    /** [r]前フレームのG_RANK_DISP */
    int tmp_rank_;

public:
    LabelRankFont(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    /**
     * ランク数値から文字列変換
     * @param prm_rank ランク数値(1～100000)
     * @param out 結果文字列 (char[64]以上)
     * @return
     */
    void cnvRankStr(int prm_rank, char* out);

    virtual ~LabelRankFont();

};

}
#endif /*RANKFONT_H_*/
