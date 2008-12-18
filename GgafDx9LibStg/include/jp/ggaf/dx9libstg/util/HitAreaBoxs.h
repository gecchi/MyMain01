#ifndef HITAREABOXS_H_
#define HITAREABOXS_H_

class HitAreaBoxs : public GgafObject {

	struct Box {
		int x1;		//x座標の小さい方
		int y1;		//y座標の小さい方
		int z1;		//z座標の小さい方
		int x2;		//対角の頂点となるx座標大きい方
		int y2;		//対角の頂点となるy座標大きい方
		int z2;		//対角の頂点となるz座標大きい方
		int cx;		//中心点x座標
		int cy;		//中心点y座標
		int cz;		//中心点z座標
		int hdx;	//x幅の半分
		int hdy;	//y幅の半分
		int hdz;	//z幅の半分
		bool rotX;  //中心点を、オブジェクトの(0,0)を中心にX軸回転の移動をさせるかどうか（箱が回転するのではない）
		bool rotY;	//中心点を、オブジェクトの(0,0)を中心にY軸回転の移動をさせるかどうか（箱が回転するのではない）
		bool rotZ;	//中心点を、オブジェクトの(0,0)を中心にZ軸回転の移動をさせるかどうか（箱が回転するのではない）
		bool active; //有効フラグ
	};

public:

	int _iBoxNum;

	Box* _paBase;
	Box* _paHitArea;

	HitAreaBoxs(int prm_iBoxNum);

	void setBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);
	void enable(int prm_index);
	void disable(int prm_index);
	bool isEnable(int prm_index);

	virtual ~HitAreaBoxs();
};

#endif /*HITAREABOXS_H_*/
