#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
namespace MyStg2nd {
#define _RANK_ (GameGlobal::_rank)
#define _SCORE_ (GameGlobal::_score)
#define pCOMMONSCENE (GameGlobal::_pSceneCommon)
#define pGAMESCENE (GameGlobal::_pSceneGame)

class GameGlobal {
public:
    static boolean _isInit;
    /** �X�R�A */
    static UINT32 _score;

    /** �X�e�[�W */
    static int _iScene;
    /** �����N�i0.0 �` 1.0�B 1.0��MAX�����N�Ƃ���) */
    static double _rank;

    static CommonScene* _pSceneCommon;
    static GameScene* _pSceneGame;
    static void init();
};

}
#endif /*GAMEGLOBAL_H_*/

