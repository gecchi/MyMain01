#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteActor::GgafDx9SpriteActor(const char* prm_name,
                                       const char* prm_spritemodel_name,
                                       const char* prm_technique,
                                       GgafDx9GeometryMover* prm_pGeoMover,
                                       GgafDx9GeometryChecker* prm_pGeoChecker) :
    GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
    TRACE("GgafDx9SpriteActor::GgafDx9SpriteActor ("<<prm_name<<","<<prm_spritemodel_name<<","<<prm_technique<<")");
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);


    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_spritemodel_name);
    _pSpriteModel = (GgafDx9SpriteModel*)_pModelCon->view();

    _class_name = "GgafDx9SpriteActor";
    _pattno_ani_top = 0;
    _pattno_ani_bottom = _pSpriteModel->_pattno_ani_Max;
    _pattno_ani_now = 0;
    _frame_ani_interval = 0;
    _animation_method = ORDER_LOOP;
    _aniframe_counter = 0;
    _isOscillateAnimationOrderFlg = true;
    _fAlpha = 1.0f;
    _isBillboardingFlg = false;


     //マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[1];
	_paD3DMaterial9[0] = *(_pSpriteModel->_pD3DMaterial9_default);

    _pEffectConnection = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection("S/GgafDx9SpriteEffect");
    _pSpriteEffect = (GgafDx9SpriteEffect*)_pEffectConnection->view();
    _pID3DXEffect = _pSpriteEffect->_pID3DXEffect;
}

void GgafDx9SpriteActor::processDrawMain() {
    //	if (_isBillboardingFlg) {
    //		_pGeoMover->setRotAngle(
    //			GgafDx9World::_pCamera->_X,
    //			GgafDx9World::_pCamera->_Y,
    //			GgafDx9World::_pCamera->_Z
    //		);
    //	} else {
    //
    //
    //	}
    HRESULT hr;
    hr = _pID3DXEffect->SetTechnique(_technique);
    whetherGgafDx9CriticalException(hr, S_OK, "GgafDx9SpriteActor::GgafDx9PrimitiveActor SetTechnique() に失敗しました。");

    static D3DXMATRIX matWorld; //WORLD変換行列
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);
    hr = _pID3DXEffect->SetMatrix(_pSpriteEffect->_hMatWorld, &matWorld );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain SetMatrix(g_matWorld) に失敗しました。");
    UINT numPass;
    hr = _pID3DXEffect->Begin( &numPass, 0 );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain Begin() に失敗しました。");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = _pID3DXEffect->BeginPass(pass);
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteActor::draw BeginPass(0) に失敗しました。");
        _pSpriteModel->draw(this);
        hr = _pID3DXEffect->EndPass();
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteActor::draw EndPass() に失敗しました。");
    }
    hr = _pID3DXEffect->End();
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain End() に失敗しました。");


}

void GgafDx9SpriteActor::setActivAnimationPattern(int prm_pattno_ani) {
    if (0 > prm_pattno_ani || prm_pattno_ani > (_pSpriteModel->_pattno_ani_Max)) {
        throwGgafCriticalException("GgafDx9SpriteActor::setActivAnimationPattern アニメーションパターン番号が範囲外です。引数="<<prm_pattno_ani);
    } else {
        _pattno_ani_now = prm_pattno_ani;
    }
}

void GgafDx9SpriteActor::setAnimationPatternRenge(int prm_top, int prm_bottom = 1) {
    if (prm_top < 0 || prm_bottom > (_pSpriteModel->_pattno_ani_Max)) {
        throwGgafCriticalException("GgafDx9SpriteActor::setAnimationPatternRenge アニメーションパターン番号が範囲外です。引数("<<prm_top<<","<<prm_bottom<<")");
    } else {
        _pattno_ani_top = prm_top;
        _pattno_ani_bottom = prm_bottom;
    }
}

void GgafDx9SpriteActor::setAnimationMethod(GgafDx9AnimationMethod prm_method, int prm_interval) {
    _animation_method = prm_method;
    _frame_ani_interval = prm_interval;
}

void GgafDx9SpriteActor::nextAnimationFrame() {
    _aniframe_counter++;
    if (_frame_ani_interval < _aniframe_counter) {
        if (_animation_method == ORDER_LOOP) { //0,1,2,3,4,5,0,1,2,3,4,5,...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == REVERSE_LOOP) { //0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == ORDER_NOLOOP) { //0,1,2,3,4,5,5,5,5,5,5,5...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                happen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //もうアニメーションは進まないことを通知
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == REVERSE_NOLOOP) { //5,4,3,2,1,0,0,0,0,0,0...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                happen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //もうアニメーションは進まないことを通知
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == OSCILLATE_LOOP) { //0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
            if (_isOscillateAnimationOrderFlg) {
                if (_pattno_ani_bottom > _pattno_ani_now) {
                    _pattno_ani_now++;
                } else {
                    _pattno_ani_now--;
                    _isOscillateAnimationOrderFlg = false;
                }
            } else {
                if (_pattno_ani_top < _pattno_ani_now) {
                    _pattno_ani_now--;
                } else {
                    _pattno_ani_now++;
                    _isOscillateAnimationOrderFlg = true;
                }
            }
        } else if (_animation_method == NOT_ANIMATED) {
            //何もしない
        }
        _aniframe_counter = 0;
    }

}

void GgafDx9SpriteActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //α設定
    _paD3DMaterial9[0].Ambient.a = _fAlpha;
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

GgafDx9SpriteActor::~GgafDx9SpriteActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectConnection->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
