#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9UntransformedActor::GgafDx9UntransformedActor(string prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9BaseActor(prm_name),
_X_OffScreenLeft((int)(-1*GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)),
_X_OffScreenRight((int)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)),
_Y_OffScreenTop((int)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2)),
_Y_OffScreenBottom((int)(-1*GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2))
{
	_class_name = "GgafDx9UntransformedActor";
	_X  = _Y  = _Z  = 0;
	_RX = _RY = _RZ = 0;
	_SX = _SY = _SZ = LEN_UNIT;
//	_incX  = _incY  = _incZ  = 0;
//	_incRX = _incRY = _incRZ = 0;
	_pGeoMover = prm_pGeoMover;
	_pGeoChecker = prm_pGeoChecker;
	_paD3DMaterial9 = NULL;
	_fAlpha = 1.0f;
}

bool GgafDx9UntransformedActor::processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
	GgafDx9UntransformedActor* pActor_Opponent = dynamic_cast<GgafDx9UntransformedActor*>(prm_pActor_Opponent);
	if (pActor_Opponent != NULL) {
		return _pGeoChecker -> isBump(pActor_Opponent->_pGeoChecker);
	} else {
		return false;
	}
}

void GgafDx9UntransformedActor::processDrawPrior() {
	//TODO:—vŒŸØ
	if (_isPlaying && !_wasBlinded && _isAlive) {
		GgafDx9World::setDrawDepthLevel(((_Z/LEN_UNIT)+(GgafDx9God::_iPxDep / 2)) / (GgafDx9God::_iPxDep / MAX_DRAW_DEPTH_LEVEL), this);
	}
}

void GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(GgafDx9UntransformedActor* prm_pActor) {
	//WORLD•ÏŠ·
	//’PˆÊs—ñ ~ XŽ²‰ñ“] ~ ZŽ²‰ñ“] ~ YŽ²‰ñ“] ~ Šg‘åk¬ ~ •½sˆÚ“®@‚Ì•ÏŠ·s—ñ‚ðì¬•ƒfƒoƒCƒX‚ÉÝ’è .
	//¦XYZ‚Ì‡‚Å‚È‚¢‚±‚Æ‚É’ˆÓ
	// |                         cosRZ*cosRY*sx,          sinRZ*sy,                         cosRZ*-sinRY*sz,   0  |
	// | ( cosRX*-sinRZ*cosRY + sinRX*sinRY)*sx,    cosRX*cosRZ*sy, ( cosRX*-sinRZ*-sinRY + sinRX*cosRY)*sz,   0  |
	// | (-sinRX*-sinRZ*cosRY + cosRX*sinRY)*sx,   -sinRX*cosRZ*sy, (-sinRX*-sinRZ*-sinRY + cosRX*cosRY)*sz,   0  |
	// |                                     dx,                dy,                                      dz,   1  |

	static D3DXMATRIX matrixTransWorld;  //WORLD•ÏŠ·s—ñ
	static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
	static float fRateScale = 1.0*LEN_UNIT*PX_UNIT;
	static float sx, sy, sz;
	sinRX = GgafDx9Util::SIN[prm_pActor->_RX/ANGLE_RATE];
	cosRX = GgafDx9Util::COS[prm_pActor->_RX/ANGLE_RATE];
	sinRY = GgafDx9Util::SIN[prm_pActor->_RY/ANGLE_RATE];
	cosRY = GgafDx9Util::COS[prm_pActor->_RY/ANGLE_RATE];
	sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ/ANGLE_RATE];
	cosRZ = GgafDx9Util::COS[prm_pActor->_RZ/ANGLE_RATE];
	sx = prm_pActor->_SX/fRateScale;
	sy = prm_pActor->_SY/fRateScale;
	sz = prm_pActor->_SZ/fRateScale;

	matrixTransWorld._11 = cosRZ * cosRY * sx;
	matrixTransWorld._12 = sinRZ * sy;
	matrixTransWorld._13 = cosRZ * -sinRY * sz;
	matrixTransWorld._14 = 0.0f;

	matrixTransWorld._21 = ((cosRX * -sinRZ *  cosRY) + (sinRX * sinRY)) * sx;
	matrixTransWorld._22 = cosRX * cosRZ * sy;
	matrixTransWorld._23 = ((cosRX * -sinRZ * -sinRY) + (sinRX * cosRY)) * sz;
	matrixTransWorld._24 = 0.0f;

	matrixTransWorld._31 = ((-sinRX * -sinRZ *  cosRY) + (cosRX * sinRY)) * sx;
	matrixTransWorld._32 = -sinRX * cosRZ * sy;
	matrixTransWorld._33 = ((-sinRX * -sinRZ * -sinRY) + (cosRX * cosRY)) * sz;
	matrixTransWorld._34 = 0.0f;

	matrixTransWorld._41 = (float)(1.0*prm_pActor->_X/LEN_UNIT/PX_UNIT);
	matrixTransWorld._42 = (float)(1.0*prm_pActor->_Y/LEN_UNIT/PX_UNIT);
	matrixTransWorld._43 = (float)(1.0*prm_pActor->_Z/LEN_UNIT/PX_UNIT);
	matrixTransWorld._44 = 1.0f;

	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);
	/*
		//‘O‚Ì‚â‚è•û
		float fRateScale = LEN_UNIT;
		D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
		D3DXMatrixRotationY(&matrixRotX, GgafDx9Util::RAD_UNITLEN[s_RX]/fRateScale);
		D3DXMatrixRotationX(&matrixRotY, GgafDx9Util::RAD_UNITLEN[s_RY]/fRateScale);
		D3DXMatrixRotationZ(&matrixRotZ, GgafDx9Util::RAD_UNITLEN[s_RZ]/fRateScale);
		D3DXMatrixTranslation(&matrixTrans, _X/fRateScale, _Y/fRateScale, _Z/fRateScale);
		D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
	*/
}

void GgafDx9UntransformedActor::setWorldTransformRzMv(GgafDx9UntransformedActor* prm_pActor) {
	//WORLD•ÏŠ·
	//’PˆÊs—ñ ~ ZŽ²‰ñ“] ~ •½sˆÚ“®@‚Ì•ÏŠ·s—ñ‚ðì¬•ƒfƒoƒCƒX‚ÉÝ’è
	// |cosZ  , sinZ , 0  , 0  |
	// |-sinZ , cosZ , 0  , 0  |
	// |0     , 0    , 1  , 0  |
	// |dx    , dy	 , dz , 1  |
	static D3DXMATRIX matrixTransWorld;  //WORLD•ÏŠ·s—ñ
	static s_ang s_RZ;
	s_RZ = prm_pActor->_RZ / ANGLE_RATE;

	matrixTransWorld._11 = GgafDx9Util::COS[s_RZ];
	matrixTransWorld._12 = GgafDx9Util::SIN[s_RZ];
	matrixTransWorld._13 = 0.0;
	matrixTransWorld._14 = 0.0;

	matrixTransWorld._21 = (float)(-1.0*GgafDx9Util::SIN[s_RZ]);
	matrixTransWorld._22 = GgafDx9Util::COS[s_RZ];
	matrixTransWorld._23 = 0.0;
	matrixTransWorld._24 = 0.0;

	matrixTransWorld._31 = 0.0;
	matrixTransWorld._32 = 0.0;
	matrixTransWorld._33 = 1.0;
	matrixTransWorld._34 = 0.0;

	matrixTransWorld._41 = (float)(1.0 * prm_pActor->_X/LEN_UNIT/PX_UNIT);
	matrixTransWorld._42 = (float)(1.0 * prm_pActor->_Y/LEN_UNIT/PX_UNIT);
	matrixTransWorld._43 = (float)(1.0 * prm_pActor->_Z/LEN_UNIT/PX_UNIT);
	matrixTransWorld._44 = 1;

	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);
}

void GgafDx9UntransformedActor::setWorldTransformScRzMxyz(GgafDx9UntransformedActor* prm_pActor) {

	//WORLD•ÏŠ·
	//’PˆÊs—ñ ~ Šg‘åk¬ ~ ZŽ²‰ñ“] ~ •½sˆÚ“®@‚Ì•ÏŠ·s—ñ‚ðì¬•ƒfƒoƒCƒX‚ÉÝ’è
	// |sx*cosZ , sx*sinZ , 0    , 0  |
	// |sy*-sinZ, sy*cosZ , 0    , 0  |
	// |0       , 0       , sz   , 0  |
	// |dx      , dy	  , dz   , 1  |
	static D3DXMATRIX matrixTransWorld;
	static float fRateScale = 1.0*LEN_UNIT*PX_UNIT;
	static s_ang s_RZ;
	static float sx, sy, sz;

	s_RZ = prm_pActor->_RZ / ANGLE_RATE;
	sx = prm_pActor->_SX/fRateScale;
	sy = prm_pActor->_SY/fRateScale;
	sz = prm_pActor->_SZ/fRateScale;

	matrixTransWorld._11 = sx * GgafDx9Util::COS[s_RZ];
	matrixTransWorld._12 = sx * GgafDx9Util::SIN[s_RZ];
	matrixTransWorld._13 = 0.0;
	matrixTransWorld._14 = 0.0;

	matrixTransWorld._21 = sy * -1.0 * GgafDx9Util::SIN[s_RZ];
	matrixTransWorld._22 = sy        * GgafDx9Util::COS[s_RZ];
	matrixTransWorld._23 = 0.0;
	matrixTransWorld._24 = 0.0;

	matrixTransWorld._31 = 0.0;
	matrixTransWorld._32 = 0.0;
	matrixTransWorld._33 = sz;
	matrixTransWorld._34 = 0.0;

	matrixTransWorld._41 = (float)(1.0*prm_pActor->_X/LEN_UNIT/PX_UNIT);
	matrixTransWorld._42 = (float)(1.0*prm_pActor->_Y/LEN_UNIT/PX_UNIT);
	matrixTransWorld._43 = (float)(1.0*prm_pActor->_Z/LEN_UNIT/PX_UNIT);
	matrixTransWorld._44 = 1.0;

	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);
}

GgafDx9UntransformedActor::~GgafDx9UntransformedActor() {
	DELETE_POSSIBLE_NULL(_pGeoMover);
	DELETE_POSSIBLE_NULL(_pGeoChecker);
}
