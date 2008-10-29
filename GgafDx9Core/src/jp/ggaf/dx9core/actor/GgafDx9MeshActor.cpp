#include "stdafx.h"

GgafDx9MeshActor::GgafDx9MeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_pMeshModel = GgafDx9ModelManager::getMeshModel(prm_meshmodel_name);
	_class_name = "GgafDx9MeshActor";
	_fAlpha = 1.0f;
}


void GgafDx9MeshActor::processDrawMain() {

	//WORLDÏ·
	static D3DXMATRIX matrixTransWorld;  //WORLDÏ·sñ
	D3DXMatrixIdentity(&matrixTransWorld); //PÊsñÖ
	static float fRateScale = LEN_UNIT*PX_UNIT;
	s_ang s_RX = _RX / ANGLE_RATE;
	s_ang s_RY = _RY / ANGLE_RATE;
	s_ang s_RZ = _RZ / ANGLE_RATE;
	//PÊsñ¨X²ñ]¨Y²ñ]¨Z²ñ]¨gåk¬¨½sÚ®@ÌÏ·sñðì¬
	// |cosY*cosZ*sx					  , cosY*sinZ*sy					 , -sinY*sz	    , 0  |
	// |(sinX*sinY*cosZ + cosX*-sinZ)*sx  , (sinX*sinY*sinZ + cosX*cosZ)*sy	 , sinX*cosY*sz , 0  |
	// |(cosX*sinY*cosZ + -sinX*-sinZ)*sx , (cosX*sinY*sinZ + -sinX*cosZ)*sy , cosX*cosY*sz , 0  |
	// |dx								  , dy								 ,dz			, 1  |
	matrixTransWorld._11 = GgafDx9Util::COS[s_RY] * GgafDx9Util::COS[s_RZ] * (_SX/fRateScale);
	matrixTransWorld._12 = GgafDx9Util::COS[s_RY] * GgafDx9Util::SIN[s_RZ] * (_SY/fRateScale);
	matrixTransWorld._13 = -1*GgafDx9Util::SIN[s_RY] * (_SZ/fRateScale);
	matrixTransWorld._14 = 0;

	matrixTransWorld._21 = (
		 (GgafDx9Util::SIN[s_RX] * GgafDx9Util::SIN[s_RY] * GgafDx9Util::COS[s_RZ]) +
		 (GgafDx9Util::COS[s_RX] * -1 * GgafDx9Util::SIN[s_RZ])
	   ) * (
		 _SX/fRateScale
	   );
	matrixTransWorld._22 = (
		 (GgafDx9Util::SIN[s_RX] * GgafDx9Util::SIN[s_RY] * GgafDx9Util::SIN[s_RZ]) +
		 (GgafDx9Util::COS[s_RX] * GgafDx9Util::COS[s_RZ])
	   ) * (
		 _SY/fRateScale
	   );
	matrixTransWorld._23 = GgafDx9Util::SIN[s_RX] * GgafDx9Util::COS[s_RY] * (_SZ/fRateScale);

	matrixTransWorld._24 = 0;

	matrixTransWorld._31 = (
		 (GgafDx9Util::COS[s_RX] * GgafDx9Util::SIN[s_RY] * GgafDx9Util::COS[s_RZ]) +
		 (-1 * GgafDx9Util::SIN[s_RX] * -1 * GgafDx9Util::SIN[s_RZ])
	   ) * (
		 _SX/fRateScale
	   );
	matrixTransWorld._32 = (
		 (GgafDx9Util::COS[s_RX] * GgafDx9Util::SIN[s_RY] * GgafDx9Util::SIN[s_RZ]) +
		 (GgafDx9Util::SIN[s_RX] * -1 * GgafDx9Util::COS[s_RZ])
	   ) * (
		 _SY/fRateScale
	   );
	matrixTransWorld._33 = GgafDx9Util::COS[s_RX] * GgafDx9Util::COS[s_RY] * (_SZ/fRateScale);
	matrixTransWorld._34 = 0;

	matrixTransWorld._41 = (float)(1.0*_X/LEN_UNIT/PX_UNIT);
	matrixTransWorld._42 = (float)(1.0*_Y/LEN_UNIT/PX_UNIT);
	matrixTransWorld._43 = (float)(1.0*_Z/LEN_UNIT/PX_UNIT);
	matrixTransWorld._44 = 1;
	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);



/*
	//WORLDÏ·
	//PÊsñ¨½sÚ®@ÌÏ·sñðì¬
	// |1  0  0  0 |
	// |0  1  0  0 |
	// |0  0  1  0 |
	// |dx dy dz 1 |
	D3DXMATRIX matrixTransWorld;  //WORLDÏ·sñ
	D3DXMatrixIdentity(&matrixTransWorld); //PÊsñÖ
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
	//ÊÌâèû
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
