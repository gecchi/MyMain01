#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteActor::GgafDx9SpriteActor(const char* prm_name,
                                       const char* prm_model,
                                       const char* prm_effect,
                                       const char* prm_technique,
                                       GgafDx9GeometryMover* prm_pGeoMover,
                                       GgafDx9GeometryChecker* prm_pGeoChecker) :

                                       GgafDx9UntransformedActor(prm_name,
                                                                 prm_pGeoMover,
                                                                 prm_pGeoChecker) {
    _class_name = "GgafDx9SpriteActor";

    TRACE("GgafDx9SpriteActor::GgafDx9SpriteActor ("<<prm_name<<","<<prm_model<<","<<prm_technique<<")");
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);

    //モデル取得
    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pSpriteModel = (GgafDx9SpriteModel*)_pModelCon->view();
    //モデルのマテリアルをコピーして保持
    _paD3DMaterial9 = NEW D3DMATERIAL9[1];
    _paD3DMaterial9[0] = *(_pSpriteModel->_pD3DMaterial9_default);
    //エフェクト取得
    _pEffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pSpriteEffect = (GgafDx9SpriteEffect*)_pEffectCon->view();

	_pattno_ani_top = 0;
    _pattno_ani_bottom = _pSpriteModel->_pattno_ani_Max;
    _pattno_ani_now = 0;
    _frame_ani_interval = 0;
    _animation_method = ORDER_LOOP;
    _aniframe_counter = 0;
    _is_reverse_order_in_oscillate_animation_flg = false;
    _isBillboardingFlg = false;
}

void GgafDx9SpriteActor::processDrawMain() {
	//TODO:ビルボード
    //	if (_isBillboardingFlg) {
    //		_pGeoMover->setRotAngle(
    //			GgafDx9Universe::_pCamera->_X,
    //			GgafDx9Universe::_pCamera->_Y,
    //			GgafDx9Universe::_pCamera->_Z
    //		);
    //	} else {
    //
    //
    //	}
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pSpriteEffect->_pID3DXEffect;

    HRESULT hr;
//    hr = pID3DXEffect->SetTechnique(_technique);
//    potentialDx9Exception(hr, S_OK, "GgafDx9SpriteActor::GgafDx9MeshActor SetTechnique("<<_technique<<") に失敗しました。");

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");

    static D3DXMATRIX matWorld; //UNIVERSE変換行列
    if (_isBillboardingFlg) {
        GgafDx9UntransformedActor::getWorldMatrix_BillBoardXYZ_ScMv(this, matWorld);
    } else {
        GgafDx9UntransformedActor::getWorldMatrix_RxRzRyScMv(this, matWorld);
    }
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_hMatWorld, &matWorld );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain SetMatrix(_hMatWorld) に失敗しました。");
    //α設定
    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_hAlpha, _fAlpha);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain SetFloat(_fAlpha) に失敗しました。");


    //    UINT numPass;
//    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
//    potentialDx9Exception(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain Begin() に失敗しました。");
//    for (UINT pass = 0; pass < numPass; pass++) {
//        hr = pID3DXEffect->BeginPass(pass);
//        potentialDx9Exception(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain BeginPass(0) に失敗しました。");
        _pSpriteModel->draw(this);
//        hr = pID3DXEffect->EndPass();
//        potentialDx9Exception(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain EndPass() に失敗しました。");
//    }
//    hr = pID3DXEffect->End();
//    potentialDx9Exception(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain End() に失敗しました。");


}

void GgafDx9SpriteActor::setActivAnimationPattern(int prm_pattno_ani) {
    if (0 > prm_pattno_ani || prm_pattno_ani > (_pSpriteModel->_pattno_ani_Max)) {
        throwGgafCriticalException("GgafDx9SpriteActor::setActivAnimationPattern アニメーションパターン番号が範囲外です。引数="<<prm_pattno_ani);
    } else {
        _pattno_ani_now = prm_pattno_ani;
    }
}

void GgafDx9SpriteActor::resetActivAnimationPattern() {
    _pattno_ani_now = _pattno_ani_top;
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

void GgafDx9SpriteActor::addNextAnimationFrame() {
//    _TRACE_(getName()<<":_pattno_ani_now="<<_pattno_ani_now<<"/_pattno_ani_bottom="<<_pattno_ani_bottom<<"/_pattno_ani_top="<<_pattno_ani_top<<"/_is_reverse_order_in_oscillate_animation_flg="<<_is_reverse_order_in_oscillate_animation_flg<<"");

    _aniframe_counter++;
    if (_frame_ani_interval < _aniframe_counter) {
        if (_animation_method == ORDER_LOOP) { //例：0,1,2,3,4,5,0,1,2,3,4,5,...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == REVERSE_LOOP) { //例：0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == ORDER_NOLOOP) { //例：0,1,2,3,4,5,5,5,5,5,5,5...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //もうアニメーションは進まないことを通知
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == REVERSE_NOLOOP) { //例：5,4,3,2,1,0,0,0,0,0,0...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //もうアニメーションは進まないことを通知
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == OSCILLATE_LOOP) { //例：0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
            if (_is_reverse_order_in_oscillate_animation_flg) { //逆順序時
                if (_pattno_ani_top < _pattno_ani_now) {
                    _pattno_ani_now--;
                } else {
                    _pattno_ani_now++;
                    _is_reverse_order_in_oscillate_animation_flg = false;
                }
            } else {                                            //正順序時
                if (_pattno_ani_bottom > _pattno_ani_now) {
                    _pattno_ani_now++;
                } else {
                    _pattno_ani_now--;
                    _is_reverse_order_in_oscillate_animation_flg = true;
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
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paD3DMaterial9[0].Ambient.a = _fAlpha;
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

GgafDx9SpriteActor::~GgafDx9SpriteActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
