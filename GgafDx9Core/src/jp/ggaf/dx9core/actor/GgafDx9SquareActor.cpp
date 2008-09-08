#include "stdafx.h"


GgafDx9SquareActor::GgafDx9SquareActor(string prm_name, string prm_squaremodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_class_name = "GgafDx9SquareActor";
	_pSquareModel = GgafDx9ModelManager::getSquareModel(prm_squaremodel_name);
}

void GgafDx9SquareActor::processDrawMain() {
	//WORLD•ÏŠ·
	//XYŠg‘åk¬¨ZŽ²‰ñ“]¨•½sˆÚ“®@‚Ì•ÏŠ·s—ñ‚ðì¬
	// |sx*cosZ , sx*sinZ , 0  , 0  |
	// |sy*-sinZ, sy*cosZ , 0  , 0  |
	// |0       , 0       , 1  , 0  |
	// |dx      , dy	  , 0  , 1  |
	static float fRateScale = LEN_UNIT;
	static D3DXMATRIX matrixTransWorld;  //WORLD•ÏŠ·s—ñ
	D3DXMatrixIdentity(&matrixTransWorld); //’PˆÊs—ñ‚Ö
	//float fRateScale = (LEN_UNIT*PX_UNIT);
	matrixTransWorld._11 = (_SX/fRateScale) * GgafDx9Util::_aCos[_RZ];
	matrixTransWorld._12 = (_SX/fRateScale) * GgafDx9Util::_aSin[_RZ];
	matrixTransWorld._13 = 0.0;
	matrixTransWorld._14 = 0.0;

	matrixTransWorld._21 = (float)((_SY/fRateScale) * -1.0 * GgafDx9Util::_aSin[_RZ]);
	matrixTransWorld._22 = (float)((_SY/fRateScale)        * GgafDx9Util::_aCos[_RZ]);
	matrixTransWorld._23 = 0.0;
	matrixTransWorld._24 = 0.0;

	matrixTransWorld._31 = 0.0;
	matrixTransWorld._32 = 0.0;
	matrixTransWorld._33 = 1.0;
	matrixTransWorld._34 = 0.0;

	matrixTransWorld._41 = (float)(1.0*_X/LEN_UNIT/PX_UNIT);
	matrixTransWorld._42 = (float)(1.0*_Y/LEN_UNIT/PX_UNIT);
	matrixTransWorld._43 = 0.0;
	matrixTransWorld._44 = 1.0;

    GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);

	_pSquareModel->draw(this);
}

GgafDx9SquareActor::~GgafDx9SquareActor() {
}
