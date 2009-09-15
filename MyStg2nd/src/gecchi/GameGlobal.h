#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
namespace MyStg2nd {
#define RANK (GameGlobal::_iRank)
#define pMYSHIP (GameGlobal::_pMyShip)
#define pSCENECOMMON (GameGlobal::_pSceneCommon)

class GameGlobal {
public:

    /** �X�R�A */
    static DWORD _dwScore;

    /** �X�e�[�W */
    static int _iScene;
    /** �����N */
    static int _iRank;

    /** ���@�ւ̃|�C���^ */
    static MyShip* _pMyShip;

    static CommonScene* _pSceneCommon;
};

}
#endif /*GAMEGLOBAL_H_*/

