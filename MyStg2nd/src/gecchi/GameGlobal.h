#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_

/** �����N (0.0 �` 1.0) */
#define _RANK_ (GameGlobal::_rank)
/** �\���p�����N�l */
#define _RANK_DISP_ ((int)(_RANK_*100000))
/** �����N�A�b�v���x���l */
#define _RANK_UP_LEVEL_ (MyStg2nd::GameGlobal::_rank_up_level)
#define _SCORE_ (MyStg2nd::GameGlobal::_score)

namespace MyStg2nd {

class GameGlobal {
public:
    static bool _isInit;
    /** �X�R�A */
    static UINT32 _score;
    /** �����N�i0.0 �` 1.0�B 1.0��MAX�����N�Ƃ���) */
    static double _rank;
    static int _rank_up_level;
    static void init();
};

}
#endif /*GAMEGLOBAL_H_*/

