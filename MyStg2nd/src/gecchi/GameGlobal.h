#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
namespace MyStg2nd {
#define _RANK_ (GameGlobal::_rank)
#define _SCORE_ (GameGlobal::_score)
#define pMYSHIP (GameGlobal::_pMyShip)
#define pCOMMONSCENE (GameGlobal::_pSceneCommon)
#define pGAMESCENE (GameGlobal::_pSceneGame)

class GameGlobal {
public:
    static boolean _isInit;
    /** スコア */
    static UINT32 _score;

    /** ステージ */
    static int _iScene;
    /** ランク */
    static double _rank;

    /** 自機へのポインタ */
    static MyShip* _pMyShip;
    /** */

    static CommonScene* _pSceneCommon;
    static GameScene* _pSceneGame;
    static void init();
};

}
#endif /*GAMEGLOBAL_H_*/

