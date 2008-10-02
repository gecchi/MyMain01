#include "stdafx.h"

const int GgafDx9SpriteActor::ORDER_LOOP   = 1;
const int GgafDx9SpriteActor::REVERSE_LOOP   = 2;
const int GgafDx9SpriteActor::OSCILLATE_LOOP = 3;
const int GgafDx9SpriteActor::ORDER_NOLOOP = 11;
const int GgafDx9SpriteActor::REVERSE_NOLOOP = 12;
const int GgafDx9SpriteActor::NOT_ANIMATED  = 99;

GgafDx9SpriteActor::GgafDx9SpriteActor(string prm_name, string prm_spritemodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_class_name = "GgafDx9SpriteActor";
	_pSpriteModel = GgafDx9ModelManager::getSpriteModel(prm_spritemodel_name);
	_iAnimationPatternNo_Top     = 0;
	_iAnimationPatternNo_Bottom  = _pSpriteModel->_iAnimationPatternNo_Max;
	_iAnimationPatternNo_Active  = 0;
	_iAnimationFrame_Interval    = 0;
	_iAnimationMethod            = ORDER_LOOP;
	_iCounter_AnimationFrame     = 0;
	_oscillateAnimationOrderFlg = true;
}

void GgafDx9SpriteActor::processDrawMain() {

	//WORLD変換
	//単位行列→Z軸回転→平行移動　の変換行列を作成
	// |cosZ  , sinZ , 0  , 0  |
	// |-sinZ , cosZ , 0  , 0  |
	// |0     , 0    , 1  , 0  |
	// |dx    , dy	 , dz , 1  |
	static D3DXMATRIX matrixTransWorld;  //WORLD変換行列
	D3DXMatrixIdentity(&matrixTransWorld); //単位行列へ
	//float fRateScale = (LEN_UNIT*PX_UNIT);
	matrixTransWorld._11 = GgafDx9Util::COS[_RZ];
	matrixTransWorld._12 = GgafDx9Util::SIN[_RZ];
	matrixTransWorld._13 = 0.0;
	matrixTransWorld._14 = 0.0;

	matrixTransWorld._21 = (float)(-1.0*GgafDx9Util::SIN[_RZ]);
	matrixTransWorld._22 = GgafDx9Util::COS[_RZ];
	matrixTransWorld._23 = 0.0;
	matrixTransWorld._24 = 0.0;

	matrixTransWorld._31 = 0.0;
	matrixTransWorld._32 = 0.0;
	matrixTransWorld._33 = 1.0;
	matrixTransWorld._34 = 0.0;

	matrixTransWorld._41 = (float)(1.0*_X/LEN_UNIT/PX_UNIT);
	matrixTransWorld._42 = (float)(1.0*_Y/LEN_UNIT/PX_UNIT);
	matrixTransWorld._43 = (float)(1.0*_Z/LEN_UNIT/PX_UNIT);
	matrixTransWorld._44 = 1;
    GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);

	_pSpriteModel->draw(this);
}


void GgafDx9SpriteActor::addAnimationFrame() {
	_iCounter_AnimationFrame++;
	if (_iAnimationFrame_Interval < _iCounter_AnimationFrame) {
		switch (_iAnimationMethod) {
			case ORDER_LOOP :  //0,1,2,3,4,5,0,1,2,3,4,5,...
				if (_iAnimationPatternNo_Bottom > _iAnimationPatternNo_Active) {
					_iAnimationPatternNo_Active++;
				} else {
					_iAnimationPatternNo_Active = _iAnimationPatternNo_Top;
				}
				break;
			case REVERSE_LOOP : //5,4,3,2,1,0,5,4,3,2,1,5,4...
				if (_iAnimationPatternNo_Top < _iAnimationPatternNo_Active) {
					_iAnimationPatternNo_Active--;
				} else {
					_iAnimationPatternNo_Active = _iAnimationPatternNo_Bottom;
				}
				break;
			case ORDER_NOLOOP : //0,1,2,3,4,5,5,5,5,5,5,5...
				if (_iAnimationPatternNo_Bottom > _iAnimationPatternNo_Active) {
					_iAnimationPatternNo_Active++;
				} else {
					happen(EVENT_ORDER_NOLOOP_ANIMATION_FINISH); //もうアニメーションは進まないことを通知
					_iAnimationPatternNo_Active = _iAnimationPatternNo_Bottom;
				}
				break;
			case REVERSE_NOLOOP : //5,4,3,2,1,0,0,0,0,0,0...
				if (_iAnimationPatternNo_Top < _iAnimationPatternNo_Active) {
					_iAnimationPatternNo_Active--;
				} else {
					happen(EVENT_REVERSE_NOLOOP_ANIMATION_FINISH); //もうアニメーションは進まないことを通知
					_iAnimationPatternNo_Active = _iAnimationPatternNo_Top;
				}
				break;
			case OSCILLATE_LOOP :  //0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
                if (_oscillateAnimationOrderFlg) {
					if (_iAnimationPatternNo_Bottom > _iAnimationPatternNo_Active) {
						_iAnimationPatternNo_Active++;
					} else {
						_iAnimationPatternNo_Active--;
						_oscillateAnimationOrderFlg = false;
					}
                } else {
					if (_iAnimationPatternNo_Top < _iAnimationPatternNo_Active) {
						_iAnimationPatternNo_Active--;
					} else {
						_iAnimationPatternNo_Active++;
						_oscillateAnimationOrderFlg = true;
					}
                }
				break;
			case NOT_ANIMATED :
				break;
		}
		_iCounter_AnimationFrame = 0;
	}
}

GgafDx9SpriteActor::~GgafDx9SpriteActor() {
}
