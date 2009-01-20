#ifndef DELINEATEACTOR_H_
#define DELINEATEACTOR_H_
namespace GgafDx9LibStg {


class DelineateActor : public DefaultCubeActor {
	static DelineateActor* _s_pObj;
public:
	static DelineateActor* get();
	static void release();

	DelineateActor(std::string prm_name);

	//void processDrawMain() {}; //オーバーライド未実装にする。

	void drawBox(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2,  int prm_z2);


	void drawHitarea(StgChecker* prm_pChecker);

	virtual ~DelineateActor();

};


}
#endif /*DELINEATEACTOR_H_*/
