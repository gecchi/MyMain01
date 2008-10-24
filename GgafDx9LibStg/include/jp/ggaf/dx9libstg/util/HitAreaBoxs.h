#ifndef HITAREABOXS_H_
#define HITAREABOXS_H_

class HitAreaBoxs : public GgafObject {

	struct Box {
		int x1;		//頂点のx座標
		int y1;		//頂点のy座標
		int z1;		//頂点のz座標
		int x2;		//対角の頂点のx座標
		int y2;		//対角の頂点のy座標
		int z2;		//対角の頂点のz座標
	};

public:

	int _iBoxNum;

	Box* _paBox;

	HitAreaBoxs(int prm_iBoxNum);

	void setBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2);
	void setBox(int prm_index, int x1, int y1, int x2, int y2);
	virtual ~HitAreaBoxs();
};

#endif /*HITAREABOXS_H_*/
