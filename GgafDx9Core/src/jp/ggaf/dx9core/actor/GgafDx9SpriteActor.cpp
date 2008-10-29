#include "stdafx.h"



GgafDx9SpriteActor::GgafDx9SpriteActor(string prm_name, string prm_spritemodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_class_name = "GgafDx9SpriteActor";
	_pSpriteModel = GgafDx9ModelManager::getSpriteModel(prm_spritemodel_name);
	_iAnimationPatternNo_Top     = 0;
	_iAnimationPatternNo_Bottom  = _pSpriteModel->_iAnimationPatternNo_Max;
	_iAnimationPatternNo_Active  = 0;
	_iAnimationFrame_Interval    = 0;
	_animation_method            = ORDER_LOOP;
	_iCounter_AnimationFrame     = 0;
	_oscillateAnimationOrderFlg = true;
	_fAlpha = 1.0f;
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
	s_ang s_RZ = _RZ / ANGLE_RATE;

	//float fRateScale = (LEN_UNIT*PX_UNIT);
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

	matrixTransWorld._41 = (float)(1.0*_X/LEN_UNIT/PX_UNIT);
	matrixTransWorld._42 = (float)(1.0*_Y/LEN_UNIT/PX_UNIT);
	matrixTransWorld._43 = (float)(1.0*_Z/LEN_UNIT/PX_UNIT);
	matrixTransWorld._44 = 1;
    GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &matrixTransWorld);

	_pSpriteModel->draw(this);
}

void GgafDx9SpriteActor::setActivAnimationPattern(int prm_iAnimationPatternNo) {
	if (0 > prm_iAnimationPatternNo || prm_iAnimationPatternNo > (_pSpriteModel->_iAnimationPatternNo_Max)) {
		throw_GgafCriticalException("GgafDx9SpriteActor::setActivAnimationPattern アニメーションパターン番号が範囲外です。引数="<<prm_iAnimationPatternNo);
	} else {
		_iAnimationPatternNo_Active = prm_iAnimationPatternNo;
	}
}

void GgafDx9SpriteActor::setAnimationPatternRenge(int prm_iTop, int prm_bottom = 1) {
	if (prm_iTop < 0 || prm_bottom > (_pSpriteModel->_iAnimationPatternNo_Max)) {
		throw_GgafCriticalException("GgafDx9SpriteActor::setAnimationPatternRenge アニメーションパターン番号が範囲外です。引数("<<prm_iTop<<","<<prm_bottom<<")");
	} else {
		_iAnimationPatternNo_Top = prm_iTop;
		_iAnimationPatternNo_Bottom = prm_bottom;
	}
}

void GgafDx9SpriteActor::setAnimationMethod(GgafDx9AnimationMethod prm_method, int prm_iInterval) {
	_animation_method = prm_method;
	_iAnimationFrame_Interval = prm_iInterval;
}

void GgafDx9SpriteActor::nextAnimationFrame() {
	_iCounter_AnimationFrame++;
	if (_iAnimationFrame_Interval < _iCounter_AnimationFrame) {
		if (_animation_method == ORDER_LOOP) {  //0,1,2,3,4,5,0,1,2,3,4,5,...
			if (_iAnimationPatternNo_Bottom > _iAnimationPatternNo_Active) {
				_iAnimationPatternNo_Active++;
			} else {
				_iAnimationPatternNo_Active = _iAnimationPatternNo_Top;
			}
		} else if (_animation_method == REVERSE_LOOP) { //0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
			if (_iAnimationPatternNo_Top < _iAnimationPatternNo_Active) {
				_iAnimationPatternNo_Active--;
			} else {
				_iAnimationPatternNo_Active = _iAnimationPatternNo_Bottom;
			}
		} else if (_animation_method == ORDER_NOLOOP) { //0,1,2,3,4,5,5,5,5,5,5,5...
			if (_iAnimationPatternNo_Bottom > _iAnimationPatternNo_Active) {
				_iAnimationPatternNo_Active++;
			} else {
				happen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //もうアニメーションは進まないことを通知
				_iAnimationPatternNo_Active = _iAnimationPatternNo_Bottom;
			}
		} else if (_animation_method == REVERSE_NOLOOP) { //5,4,3,2,1,0,0,0,0,0,0...
			if (_iAnimationPatternNo_Top < _iAnimationPatternNo_Active) {
				_iAnimationPatternNo_Active--;
			} else {
				happen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //もうアニメーションは進まないことを通知
				_iAnimationPatternNo_Active = _iAnimationPatternNo_Top;
			}
		} else if (_animation_method == OSCILLATE_LOOP) { //0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
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
		} else if (_animation_method == NOT_ANIMATED) {
			//何もしない
		}
		_iCounter_AnimationFrame = 0;
	}
}

GgafDx9SpriteActor::~GgafDx9SpriteActor() {
}
