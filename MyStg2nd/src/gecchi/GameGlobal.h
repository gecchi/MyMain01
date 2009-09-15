#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
namespace MyStg2nd {
#define RANK (GameGlobal::_iRank)
#define pMYSHIP (GameGlobal::_pMyShip)
#define pSCENECOMMON (GameGlobal::_pSceneCommon)

class GameGlobal {
public:

    /** スコア */
    static DWORD _dwScore;

    /** ステージ */
    static int _iScene;
    /** ランク */
    static int _iRank;

    /** 自機へのポインタ */
    static MyShip* _pMyShip;

    static CommonScene* _pSceneCommon;
};

}
#endif /*GAMEGLOBAL_H_*/

