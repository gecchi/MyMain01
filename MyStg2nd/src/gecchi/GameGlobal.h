#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
namespace MyStg2nd {


class GameGlobal {
public:
    static bool _isInit;
    /** �X�R�A */
    static UINT32 _score;

    /** �X�e�[�W */
    static int _iScene;
    /** �����N�i0.0 �` 1.0�B 1.0��MAX�����N�Ƃ���) */
    static double _rank;

    static void init();
};

}
#endif /*GAMEGLOBAL_H_*/

