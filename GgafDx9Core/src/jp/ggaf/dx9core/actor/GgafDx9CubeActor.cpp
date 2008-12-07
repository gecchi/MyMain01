#include "stdafx.h"

GgafDx9CubeActor::GgafDx9CubeActor(string prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9MeshActor(prm_name, "cube", prm_pGeoMover, prm_pGeoChecker) {
	_class_name = "GgafDx9CubeActor";
}

void GgafDx9CubeActor::processDrawMain() {

	//WORLD•ÏŠ·
	//XYZŠg‘åk¬¨ZŽ²‰ñ“]¨•½sˆÚ“®@‚Ì•ÏŠ·s—ñ‚ðì¬
	// |sx*cosZ , sx*sinZ , 0    , 0  |
	// |sy*-sinZ, sy*cosZ , 0    , 0  |
	// |0       , 0       , sz   , 0  |
	// |dx      , dy	  , dz   , 1  |
	static float fRateScale = LEN_UNIT*PX_UNIT;
	static D3DXMATRIX matrixTransWorld;  //WORLD•ÏŠ·s—ñ
	D3DXMatrixIdentity(&matrixTransWorld); //’PˆÊs—ñ‚Ö
	s_ang s_RZ = _RZ / ANGLE_RATE;
	//float fRateScale = (LEN_UNIT*PX_UNIT);
	matrixTransWorld._11 = (_SX/fRateScale) * GgafDx9Util::COS[s_RZ];
	matrixTransWorld._12 = (_SX/fRateScale) * GgafDx9Util::SIN[s_RZ];
	matrixTransWorld._13 = 0.0;
	matrixTransWorld._14 = 0.0;

	matrixTransWorld._21 = (float)((_SY/fRateScale) * -1.0 * GgafDx9Util::SIN[s_RZ]);
	matrixTransWorld._22 = (float)((_SY/fRateScale)        * GgafDx9Util::COS[s_RZ]);
	matrixTransWorld._23 = 0.0;
	matrixTransWorld._24 = 0.0;

	matrixTransWorld._31 = 0.0;
	matrixTransWorld._32 = 0.0;
	matrixTransWorld._33 = (float)(_SZ/fRateScale);
	matrixTransWorld._34 = 0.0;

	matrixTransWorld._41 = (float)(1.0*_X/LEN_UNIT/PX_UNIT);
	matrixTransWorld._42 = (float)(1.0*_Y/LEN_UNIT/PX_UNIT);
	matrixTransWorld._43 = (float)(1.0*_Z/LEN_UNIT/PX_UNIT);
	matrixTransWorld._44 = 1.0;

	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);

	_pMeshModel->draw(this);
}

GgafDx9CubeActor::~GgafDx9CubeActor() {
}
