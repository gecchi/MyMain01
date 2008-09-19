#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
#define RANK (GameGlobal::_iRank)

class GameGlobal {
public:

	/** スコア */
	static DWORD _dwScore;

	/** ステージ */
	static int _iScene;
	/** ステージ */
	static int _iRank;

	/** 自機へのポインタ */
	static MyShipActor* _pMyShipActor;

	static CommonScene* _pSceneCommon;
};
#endif /*GAMEGLOBAL_H_*/

