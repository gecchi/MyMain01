#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_

#include "jp/gecchi/VioletVreath/util/QueryRanking.h"

/** �����N (0.0 �` 1.0) */
#define G_RANK (VioletVreath::GameGlobal::rank_)
/** �\���p�����N�l */
#define G_RANK_DISP ((int)(G_RANK*100000))
/** �����N�A�b�v���x���l */
#define G_RANKUP_LEVEL (VioletVreath::GameGlobal::rank_up_level_)
/** �X�R�A */
#define G_SCORE (VioletVreath::GameGlobal::score_)
/** �����L���O�X�R�A */
#define G_RANKING (VioletVreath::GameGlobal::qryRanking_)

namespace VioletVreath {

class GameGlobal {
public:
    static bool is_init_;
    /** �X�R�A */
    static int score_;
    /** �����N�i0.0 �` 1.0�B 1.0��MAX�����N�Ƃ���) */
    static double rank_;
    static int rank_up_level_;
    static QueryRanking qryRanking_;
};

}
#endif /*GAMEGLOBAL_H_*/

