#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
#define RANK (GameGlobal::_iRank)

class GameGlobal {
public:

	/** �X�R�A */
	static DWORD _dwScore;

	/** �X�e�[�W */
	static int _iScene;
	/** �X�e�[�W */
	static int _iRank;

	/** ���@�ւ̃|�C���^ */
	static MyShipActor* _pMyShipActor;

	static CommonScene* _pSceneCommon;
};
#endif /*GAMEGLOBAL_H_*/

