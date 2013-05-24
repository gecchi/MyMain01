#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_

#include "jp/gecchi/VioletVreath/util/QueryRanking.h"

/** �����N (0.0 �` 1.0) */
#define _RANK_ (GameGlobal::rank_)
/** �\���p�����N�l */
#define _RANK_DISP_ ((int)(_RANK_*100000))
/** �����N�A�b�v���x���l */
#define _RANK_UP_LEVEL_ (VioletVreath::GameGlobal::rank_up_level_)
#define _SCORE_ (VioletVreath::GameGlobal::score_)

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
    static void init();
};

}
#endif /*GAMEGLOBAL_H_*/

