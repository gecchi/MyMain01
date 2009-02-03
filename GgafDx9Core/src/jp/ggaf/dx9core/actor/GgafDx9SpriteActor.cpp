#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteActor::GgafDx9SpriteActor(string prm_name, string prm_spritemodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_class_name = "GgafDx9SpriteActor";
	_pModelLead = (GgafDx9ModelLead*)GgafDx9God::_pModelManager->lead(prm_spritemodel_name.c_str());
	_pSpriteModel = (GgafDx9SpriteModel*)_pModelLead->getResource();
	_iAnimationPatternNo_Top     = 0;
	_iAnimationPatternNo_Bottom  = _pSpriteModel->_iAnimationPatternNo_Max;
	_iAnimationPatternNo_Active  = 0;
	_iAnimationFrame_Interval    = 0;
	_animation_method            = ORDER_LOOP;
	_iCounter_AnimationFrame     = 0;
	_oscillateAnimationOrderFlg = true;
	_fAlpha = 1.0f;
	_isBillboarding = false;

	//マテリアルをコピー
	_paD3DMaterial9 = NEW D3DMATERIAL9[1];
	_paD3DMaterial9[0] = *(_pSpriteModel->_pD3DMaterial9_default);

}

void GgafDx9SpriteActor::processDrawMain() {
//	if (_isBillboarding) {
//		_pGeoMover->setAxisRotAngle(
//			GgafDx9World::_pCamera->_X,
//			GgafDx9World::_pCamera->_Y,
//			GgafDx9World::_pCamera->_Z
//		);
//	} else {
//
//
//	}
//
	GgafDx9UntransformedActor::setWorldTransformRzMv(this);
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

void GgafDx9SpriteActor::setAlpha(float prm_fAlpha) {
	_fAlpha = prm_fAlpha;
	//α設定
	_paD3DMaterial9[0].Ambient.a = _fAlpha;
	_paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

GgafDx9SpriteActor::~GgafDx9SpriteActor() {
	RELEASE_SAFE(_pModelLead);
	DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
