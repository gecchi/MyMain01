#ifndef DELINEATEACTOR_H_
#define DELINEATEACTOR_H_


class DelineateActor : public DefaultSquareActor {
	static DelineateActor* _pObj;
public:
	static DelineateActor* get();
	static void release();

	DelineateActor(string prm_name, string prm_xname);

	//void processDrawMain() {}; //オーバーライド未実装にする。

	void drawRect(int prm_x1, int prm_y1, int prm_x2, int prm_y2);

	void drawLine(int prm_x1, int prm_y1, int prm_x2, int prm_y2);

	void drawHitarea(StgChecker* prm_pChecker);

	virtual ~DelineateActor();

};


#endif /*DELINEATEACTOR_H_*/
