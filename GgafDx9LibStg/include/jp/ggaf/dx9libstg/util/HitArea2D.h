#ifndef HITAREA2D_H_
#define HITAREA2D_H_

class HitArea2D : public GgafObject {

	struct HitRect2D {
		int x1;		//左上x座標
		int y1;		//左上y座標
		int x2;		//右下x座標
		int y2;		//右下y座標
	};
	struct HitLine2D {
		int x1;		//始点x座標
		int y1;		//始点y座標
		int x2;		//終点x座標
		int y2;		//終点y座標
		bool zrot; //Z軸回転有効
	};

public:

	int _iRectNum;
	int _iLineNum;

	HitRect2D* _paRect;
	HitLine2D* _paLine;

	HitArea2D(int prm_iRectNum, int prm_iLineNum);

	void setRect(int prm_index, int prm_x1, int prm_y1, int prm_x2, int prm_y2);

	void setLine(int prm_index, int prm_x1, int prm_y1, int prm_x2, int prm_y2, bool prm_zrot);

	virtual ~HitArea2D();
};

#endif /*HITAREA2D_H_*/
