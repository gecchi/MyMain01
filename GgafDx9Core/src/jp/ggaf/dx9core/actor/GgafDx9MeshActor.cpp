#include "stdafx.h"

GgafDx9MeshActor::GgafDx9MeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_pMeshModel = GgafDx9ModelManager::getMeshModel(prm_meshmodel_name);
	_class_name = "GgafDx9MeshActor";
	_fAlpha = 1.0f;
}


void GgafDx9MeshActor::processDrawMain() {

	//WORLD•ÏŠ·
	static D3DXMATRIX matrixTransWorld;  //WORLD•ÏŠ·s—ñ
	float sinRX = GgafDx9Util::SIN[_RX/ANGLE_RATE];
	float cosRX = GgafDx9Util::COS[_RX/ANGLE_RATE];
	float sinRY = GgafDx9Util::SIN[_RY/ANGLE_RATE];
	float cosRY = GgafDx9Util::COS[_RY/ANGLE_RATE];
	float sinRZ = GgafDx9Util::SIN[_RZ/ANGLE_RATE];
	float cosRZ = GgafDx9Util::COS[_RZ/ANGLE_RATE];
	static float fRateScale = LEN_UNIT*PX_UNIT;
	float sx   = _SX/fRateScale;
	float sy   = _SY/fRateScale;
	float sz   = _SZ/fRateScale;

	//’PˆÊs—ñ ~ XŽ²‰ñ“] ~ ZŽ²‰ñ“] ~ YŽ²‰ñ“] ~ Šg‘åk¬ ~ •½sˆÚ“®@‚Ì•ÏŠ·s—ñ‚ðì¬•Ý’è
	//¦XYZ‚Ì‡‚Å‚È‚¢‚±‚Æ‚É’ˆÓ
	matrixTransWorld._11 = cosRZ * cosRY * sx;
	matrixTransWorld._12 = sinRZ * sy;
	matrixTransWorld._13 = cosRZ * -sinRY * sz;
	matrixTransWorld._14 = 0.0f;

	matrixTransWorld._21 = ((cosRX * -sinRZ * cosRY) + (sinRX * sinRY)) * sx;
	matrixTransWorld._22 = cosRX * cosRZ * sy;
	matrixTransWorld._23 = ((cosRX * -sinRZ * -sinRY) + (sinRX * cosRY)) * sz;
	matrixTransWorld._24 = 0.0f;

	matrixTransWorld._31 = ((-sinRX * -sinRZ * cosRY) + (cosRX * sinRY)) * sx;
	matrixTransWorld._32 = -sinRX * cosRZ * sy;
	matrixTransWorld._33 = ((-sinRX * -sinRZ * -sinRY) + (cosRX *cosRY)) * sz;
	matrixTransWorld._34 = 0.0f;

	matrixTransWorld._41 = (float)(1.0*_X/LEN_UNIT/PX_UNIT);
	matrixTransWorld._42 = (float)(1.0*_Y/LEN_UNIT/PX_UNIT);
	matrixTransWorld._43 = (float)(1.0*_Z/LEN_UNIT/PX_UNIT);
	matrixTransWorld._44 = 1.0f;

	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);


//	//’PˆÊs—ñ¨XŽ²‰ñ“]¨YŽ²‰ñ“]¨ZŽ²‰ñ“]¨Šg‘åk¬¨•½sˆÚ“®@‚Ì•ÏŠ·s—ñ‚ðì¬
//	// |cosRY*cosRZ*sx					       , cosRY*sinRZ*sy					       , -sinRY*sz	    , 0  |
//	// |(sinRX*sinRY*cosRZ + cosRX*-sinRZ)*sx  , (sinRX*sinRY*sinRZ + cosRX*cosRZ)*sy  , sinRX*cosRY*sz , 0  |
//	// |(cosRX*sinRY*cosRZ + -sinRX*-sinRZ)*sx , (cosRX*sinRY*sinRZ + -sinRX*cosRZ)*sy , cosRX*cosRY*sz , 0  |
//	// |dx                                     , dy                                    ,dz              , 1  |
//	matrixTransWorld._11 = cosRY * cosRZ * sx;
//	matrixTransWorld._12 = cosRY * sinRZ * sy;
//	matrixTransWorld._13 = -1*sinRY * sz;
//	matrixTransWorld._14 = 0.0f;
//
//	matrixTransWorld._21 = ((sinRX * sinRY * cosRZ) + (cosRX * -1*sinRZ)) * sx;
//	matrixTransWorld._22 = ((sinRX * sinRY * sinRZ) + (cosRX *    cosRZ)) * sy;
//	matrixTransWorld._23 = sinRX * cosRY * sz;
//	matrixTransWorld._24 = 0.0f;
//
//	matrixTransWorld._31 = ((cosRX * sinRY * cosRZ) + (-1*sinRX * -1*sinRZ)) * sx;
//	matrixTransWorld._32 = ((cosRX * sinRY * sinRZ) + (   sinRX * -1*cosRZ)) * sy;
//	matrixTransWorld._33 = cosRX * cosRY * sz;
//	matrixTransWorld._34 = 0.0f;
//
//	matrixTransWorld._41 = (float)(1.0*_X/LEN_UNIT/PX_UNIT);
//	matrixTransWorld._42 = (float)(1.0*_Y/LEN_UNIT/PX_UNIT);
//	matrixTransWorld._43 = (float)(1.0*_Z/LEN_UNIT/PX_UNIT);
//	matrixTransWorld._44 = 1.0f;
//	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);



/*
	//WORLD•ÏŠ·
	//’PˆÊs—ñ¨•½sˆÚ“®@‚Ì•ÏŠ·s—ñ‚ðì¬
	// |1  0  0  0 |
	// |0  1  0  0 |
	// |0  0  1  0 |
	// |dx dy dz 1 |
	D3DXMATRIX matrixTransWorld;  //WORLD•ÏŠ·s—ñ
	D3DXMatrixIdentity(&matrixTransWorld); //’PˆÊs—ñ‚Ö
	float fRateScale = LEN_UNIT;
	matrixTransWorld._11 = 1;
	matrixTransWorld._12 = 0;
	matrixTransWorld._13 = 0;
	matrixTransWorld._14 = 0;

	matrixTransWorld._21 = 0;
	matrixTransWorld._22 = 1;
	matrixTransWorld._23 = 0;
	matrixTransWorld._24 = 0;

	matrixTransWorld._31 = 0;
	matrixTransWorld._32 = 0;
	matrixTransWorld._33 = 1;
	matrixTransWorld._34 = 0;

	matrixTransWorld._41 = _X/fRateScale;
	matrixTransWorld._42 = _Y/fRateScale;
	matrixTransWorld._43 = _Z/fRateScale;
	matrixTransWorld._44 = 1;
	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);
*/



/*
	//‘O‚Ì‚â‚è•û(d‚¢)
	float fRateScale = LEN_UNIT;
	D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
	D3DXMatrixRotationY(&matrixRotX, GgafDx9Util::RAD_UNITLEN[s_RX]/fRateScale);
	D3DXMatrixRotationX(&matrixRotY, GgafDx9Util::RAD_UNITLEN[s_RY]/fRateScale);
	D3DXMatrixRotationZ(&matrixRotZ, GgafDx9Util::RAD_UNITLEN[s_RZ]/fRateScale);
	D3DXMatrixTranslation(&matrixTrans, _X/fRateScale, _Y/fRateScale, _Z/fRateScale);
	D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
*/

	_pMeshModel->draw(this);
}

GgafDx9MeshActor::~GgafDx9MeshActor() {
}
