#ifndef HITAREABOXS_H_
#define HITAREABOXS_H_

class HitAreaBoxs : public GgafObject {

	struct Box {
		int x1;		//���_��x���W
		int y1;		//���_��y���W
		int z1;		//���_��z���W
		int x2;		//�Ίp�̒��_��x���W
		int y2;		//�Ίp�̒��_��y���W
		int z2;		//�Ίp�̒��_��z���W
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
