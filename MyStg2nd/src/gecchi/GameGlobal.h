#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
namespace MyStg2nd {
#define RANK (GameGlobal::_iRank)
#define pMYSHIP (GameGlobal::_pMyShip)
#define pCOMMONSCENE (GameGlobal::_pSceneCommon)
#define pGAMESCENE (GameGlobal::_pSceneGame)

class GameGlobal {
public:
    static boolean _isInit;
    /** �X�R�A */
    static DWORD _dwScore;

    /** �X�e�[�W */
    static int _iScene;
    /** �����N */
    static int _iRank;

    /** ���@�ւ̃|�C���^ */
    static MyShip* _pMyShip;
    /** */
    static int _lim_MyShip_top;
    static int _lim_MyShip_bottom;
    static int _lim_MyShip_front;
    static int _lim_MyShip_behaind;
    static int _lim_MyShip_zleft;
    static int _lim_MyShip_zright;
    static CommonScene* _pSceneCommon;
    static GameScene* _pSceneGame;
    static void init();
};

}
#endif /*GAMEGLOBAL_H_*/

