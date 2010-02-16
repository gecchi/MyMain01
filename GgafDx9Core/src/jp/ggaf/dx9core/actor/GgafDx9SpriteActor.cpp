#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteActor::GgafDx9SpriteActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_effect_id,
                                       const char* prm_technique,
                                       GgafDx9Checker* prm_pChecker) :

                                           GgafDx9DrawableActor(prm_name,
                                                                prm_model_id,
                                                                "S",
                                                                prm_effect_id,
                                                                "S",
                                                                prm_technique,
                                                                prm_pChecker) {
    _class_name = "GgafDx9SpriteActor";

    //���f���擾
    _pSpriteModel = (GgafDx9SpriteModel*)_pGgafDx9Model;
    _pSpriteEffect = (GgafDx9SpriteEffect*)_pGgafDx9Effect;

    _pattno_uvflip_top = 0;
    _pattno_uvflip_bottom = _pSpriteModel->_pattno_uvflip_Max;
    _pattno_uvflip_now = 0;
    _frame_uvflip_interval = 0;
    _uvflip_method = FLIP_ORDER_LOOP;
    _aniframe_counter = 0;
    _is_reverse_order_in_oscillate_animation_flg = false;
    _pFunc_calcWorldMatrix = GgafDx9Util::calcWorldMatrix_ScRxRzRyMv;
}

void GgafDx9SpriteActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_hMatView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) �Ɏ��s���܂����B");
    (*_pFunc_calcWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_hMatWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9SpriteActor::processDraw SetMatrix(_hMatWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_hAlpha, _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDx9SpriteActor::processDraw SetFloat(_fAlpha) �Ɏ��s���܂����B");

//    // Z�o�b�t�@�𖳌���
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//    // Z�o�b�t�@�������ݕs��
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    _pSpriteModel->draw(this);

//    // Z�o�b�t�@��L����
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
//    // Z�o�b�t�@�������݉�
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

void GgafDx9SpriteActor::setUvFlipPtnNo(int prm_pattno_uvflip) {
    if (0 > prm_pattno_uvflip || prm_pattno_uvflip > (_pSpriteModel->_pattno_uvflip_Max)) {
        throwGgafCriticalException("GgafDx9SpriteActor::setUvFlipPtnNo �A�j���[�V�����p�^�[���ԍ����͈͊O�ł��B����="<<prm_pattno_uvflip);
    } else {
        _pattno_uvflip_now = prm_pattno_uvflip;
    }
}

void GgafDx9SpriteActor::resetUvFlipPtnNo() {
    _pattno_uvflip_now = _pattno_uvflip_top;
}

void GgafDx9SpriteActor::forceUvFlipPtnRange(int prm_top, int prm_bottom = 1) {
    if (prm_top < 0 || prm_bottom > (_pSpriteModel->_pattno_uvflip_Max)) {
        throwGgafCriticalException("GgafDx9SpriteActor::forceUvFlipPtnRange �A�j���[�V�����p�^�[���ԍ����͈͊O�ł��B����("<<prm_top<<","<<prm_bottom<<")");
    } else {
        _pattno_uvflip_top = prm_top;
        _pattno_uvflip_bottom = prm_bottom;
    }
}

void GgafDx9SpriteActor::setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval) {
    _uvflip_method = prm_method;
    _frame_uvflip_interval = prm_interval;
}

void GgafDx9SpriteActor::behaveUvFlip() {
//    _TRACE_(getName()<<":_pattno_uvflip_now="<<_pattno_uvflip_now<<"/_pattno_uvflip_bottom="<<_pattno_uvflip_bottom<<"/_pattno_uvflip_top="<<_pattno_uvflip_top<<"/_is_reverse_order_in_oscillate_animation_flg="<<_is_reverse_order_in_oscillate_animation_flg<<"");

    _aniframe_counter++;
    if (_frame_uvflip_interval < _aniframe_counter) {
        if (_uvflip_method == FLIP_ORDER_LOOP) { //��F0,1,2,3,4,5,0,1,2,3,4,5,...
            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
                _pattno_uvflip_now++;
            } else {
                _pattno_uvflip_now = _pattno_uvflip_top;
            }
        } else if (_uvflip_method == FLIP_REVERSE_LOOP) { //��F0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
            if (_pattno_uvflip_top < _pattno_uvflip_now) {
                _pattno_uvflip_now--;
            } else {
                _pattno_uvflip_now = _pattno_uvflip_bottom;
            }
        } else if (_uvflip_method == FLIP_ORDER_NOLOOP) { //��F0,1,2,3,4,5,5,5,5,5,5,5...
            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
                _pattno_uvflip_now++;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
                _pattno_uvflip_now = _pattno_uvflip_bottom;
            }
        } else if (_uvflip_method == FLIP_REVERSE_NOLOOP) { //��F5,4,3,2,1,0,0,0,0,0,0...
            if (_pattno_uvflip_top < _pattno_uvflip_now) {
                _pattno_uvflip_now--;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
                _pattno_uvflip_now = _pattno_uvflip_top;
            }
        } else if (_uvflip_method == FLIP_OSCILLATE_LOOP) { //��F0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
            if (_is_reverse_order_in_oscillate_animation_flg) { //�t������
                if (_pattno_uvflip_top < _pattno_uvflip_now) {
                    _pattno_uvflip_now--;
                } else {
                    _pattno_uvflip_now++;
                    _is_reverse_order_in_oscillate_animation_flg = false;
                }
            } else {                                            //��������
                if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
                    _pattno_uvflip_now++;
                } else {
                    _pattno_uvflip_now--;
                    _is_reverse_order_in_oscillate_animation_flg = true;
                }

            }
        } else if (_uvflip_method == NOT_ANIMATED) {
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
