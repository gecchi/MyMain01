#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteActor::GgafDx9SpriteActor(const char* prm_name,
                                       const char* prm_model,
                                       const char* prm_effect,
                                       const char* prm_technique,
                                       GgafDx9Checker* prm_pChecker) :

                                           GgafDx9DrawableActor(prm_name,
                                                                             prm_model,
                                                                             prm_effect,
                                                                             prm_technique,
                                                                             prm_pChecker) {
    _class_name = "GgafDx9SpriteActor";

    //���f���擾
    _pSpriteModel = (GgafDx9SpriteModel*)_pGgafDx9Model;
    _pSpriteEffect = (GgafDx9SpriteEffect*)_pGgafDx9Effect;

    //���f���̃}�e���A�����R�s�[���ĕێ�
//    _paD3DMaterial9 = NEW D3DMATERIAL9[1];
//    _paD3DMaterial9[0] = *(_pSpriteModel->_pD3DMaterial9_default);
    //�G�t�F�N�g�擾

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
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) �Ɏ��s���܂����B");
    if (_isBillboardingFlg) {
        GgafDx9GeometricActor::getWorldMatrix_BillBoardXYZ_ScMv(this, _matWorld);
    } else {
        GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(this, _matWorld);
    }
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_hMatWorld, &_matWorld );
    mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain SetMatrix(_hMatWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_hAlpha, _fAlpha);
    mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteActor::processDrawMain SetFloat(_fAlpha) �Ɏ��s���܂����B");
    _pSpriteModel->draw(this);
}

void GgafDx9SpriteActor::setActivAnimationPattern(int prm_pattno_ani) {
    if (0 > prm_pattno_ani || prm_pattno_ani > (_pSpriteModel->_pattno_ani_Max)) {
        throwGgafCriticalException("GgafDx9SpriteActor::setActivAnimationPattern �A�j���[�V�����p�^�[���ԍ����͈͊O�ł��B����="<<prm_pattno_ani);
    } else {
        _pattno_ani_now = prm_pattno_ani;
    }
}

void GgafDx9SpriteActor::resetActivAnimationPattern() {
    _pattno_ani_now = _pattno_ani_top;
}

void GgafDx9SpriteActor::setAnimationPatternRenge(int prm_top, int prm_bottom = 1) {
    if (prm_top < 0 || prm_bottom > (_pSpriteModel->_pattno_ani_Max)) {
        throwGgafCriticalException("GgafDx9SpriteActor::setAnimationPatternRenge �A�j���[�V�����p�^�[���ԍ����͈͊O�ł��B����("<<prm_top<<","<<prm_bottom<<")");
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
        if (_animation_method == ORDER_LOOP) { //��F0,1,2,3,4,5,0,1,2,3,4,5,...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == REVERSE_LOOP) { //��F0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == ORDER_NOLOOP) { //��F0,1,2,3,4,5,5,5,5,5,5,5...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == REVERSE_NOLOOP) { //��F5,4,3,2,1,0,0,0,0,0,0...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == OSCILLATE_LOOP) { //��F0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
            if (_is_reverse_order_in_oscillate_animation_flg) { //�t������
                if (_pattno_ani_top < _pattno_ani_now) {
                    _pattno_ani_now--;
                } else {
                    _pattno_ani_now++;
                    _is_reverse_order_in_oscillate_animation_flg = false;
                }
            } else {                                            //��������
                if (_pattno_ani_bottom > _pattno_ani_now) {
                    _pattno_ani_now++;
                } else {
                    _pattno_ani_now--;
                    _is_reverse_order_in_oscillate_animation_flg = true;
                }

            }
        } else if (_animation_method == NOT_ANIMATED) {
            //�������Ȃ�
        }
        _aniframe_counter = 0;
    }

}

void GgafDx9SpriteActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paD3DMaterial9[0].Ambient.a = _fAlpha;
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

GgafDx9SpriteActor::~GgafDx9SpriteActor() {
}
