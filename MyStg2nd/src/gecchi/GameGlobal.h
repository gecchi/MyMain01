#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_


class GameGlobal {
public:

	/** スコア */
	static DWORD _dwScore;

	/** ステージ */
	static int _iScene;


	/** 自機へのポインタ */
	static MyShipActor* _pMyShipActor;

	static CommonScene* _pSceneCommon;
};
#endif /*GAMEGLOBAL_H_*/

