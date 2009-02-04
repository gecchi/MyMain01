#ifndef DELINEATEACTOR_H_
#define DELINEATEACTOR_H_
namespace GgafDx9LibStg {

/**
 * 当たり判定表示用キューブクラス
 * DefaultCubeActor を継承し、当たり判定領域表示機能を追加したアクターです。
 */
class DelineateActor : public DefaultCubeActor {
	static DelineateActor* _s_pObj;
public:
	static DelineateActor* get();
	static void release();

	DelineateActor(const char* prm_name);

	//void processDrawMain() {}; //オーバーライド未実装にする。



	void drawHitarea(StgChecker* prm_pChecker);

	virtual ~DelineateActor();

};


}
#endif /*DELINEATEACTOR_H_*/
