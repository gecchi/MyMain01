#ifndef HITAREA2D_H_
#define HITAREA2D_H_

class HitArea2D : public GgafObject {

	struct HitRect2D {
		int x1;		//����x���W
		int y1;		//����y���W
		int x2;		//�E��x���W
		int y2;		//�E��y���W
		int z1;		//Z���̌��݂̎n�_z���W
		int z2;		//Z���̌��݂̏I�_z���W
	};
	struct HitLine2D {
		int x1;		//�n�_x���W
		int y1;		//�n�_y���W
		int x2;		//�I�_x���W
		int y2;		//�I�_y���W
		bool zrot; //Z����]�����L��
		int z1;		//Z���̌��݂̎n�_z���W
		int z2;		//Z���̌��݂̏I�_z���W
	};

public:

	int _iRectNum;
	int _iLineNum;

	HitRect2D* _paRect;
	HitLine2D* _paLine;

	HitArea2D(int prm_iRectNum, int prm_iLineNum);

	void setRect(int prm_index, int prm_x1, int prm_y1, int prm_x2, int prm_y2, int prm_z1 = -1, int prm_z2 = 1);

	void setLine(int prm_index, int prm_x1, int prm_y1, int prm_x2, int prm_y2, bool prm_zrot, int prm_z1 = -1, int prm_z2 = 1);

	virtual ~HitArea2D();
};

#endif /*HITAREA2D_H_*/
