#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
#define RANK (GameGlobal::_iRank)

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
#endif /*GAMEGLOBAL_H_*/

