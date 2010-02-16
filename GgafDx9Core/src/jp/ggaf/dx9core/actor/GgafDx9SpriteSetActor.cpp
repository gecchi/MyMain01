#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteSetActor::GgafDx9SpriteSetActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_effect_id,
                                       const char* prm_technique,
                                       GgafDx9Checker* prm_pChecker) :

                                           GgafDx9DrawableActor(prm_name,
                                                                prm_model_id,
                                                                "s",
                                                                prm_effect_id,
                                                                "s",
                                                                prm_technique,
                                                                prm_pChecker) {
    _class_name = "GgafDx9SpriteSetActor";

    //���f���擾
    _pSpriteSetModel = (GgafDx9SpriteSetModel*)_pGgafDx9Model;
    _pSpriteSetEffect = (GgafDx9SpriteSetEffect*)_pGgafDx9Effect;
    _pUvFliper = NEW GgafDx9UvFliper(this);
    _pUvFliper->forceUvFlipPtnRange(0, _pSpriteSetModel->_pattno_uvflip_Max);
    _pUvFliper->setUvFlipPtnNo(0);
    _pUvFliper->setUvFlipMethod(FLIP_ORDER_LOOP, 1);
    _pFunc_calcWorldMatrix = GgafDx9Util::calcWorldMatrix_ScRxRzRyMv;
}

void GgafDx9SpriteSetActor::processDraw() {
    _draw_set_num = 1; //����`��[�x�ɁAGgafDx9SpriteSetActor�̓������f�����A�����Ă���J�E���g��
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pSpriteSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > _pSpriteSetModel->_set_num) {
                    _draw_set_num = _pSpriteSetModel->_set_num;
                    break;
                }
                _pNextDrawActor = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_hMatView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) �Ɏ��s���܂����B");

    GgafDx9DrawableActor *pDrawActor;
    GgafDx9RectUV* pRectUV_Active;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        (*_pFunc_calcWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_ahMatWorld[i], &(pDrawActor->_matWorld) );
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw SetMatrix(_hMatWorld) �Ɏ��s���܂����B");
        //����`���UV

        pRectUV_Active = _pSpriteSetModel->_paRectUV + (((GgafDx9SpriteSetActor*)(pDrawActor))->_pUvFliper->_pattno_uvflip_now);

        hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");

        hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahAlpha[i], pDrawActor->_fAlpha);
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw SetFloat(_fAlpha) �Ɏ��s���܂����B");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    // Z�o�b�t�@�𖳌���
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Z�o�b�t�@�������ݕs��
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    _pSpriteSetModel->draw(this);

    // Z�o�b�t�@��L����
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�������݉�
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//void GgafDx9SpriteSetActor::setUvFlipPtnNo(int prm_pattno_uvflip) {
//    if (0 > prm_pattno_uvflip || prm_pattno_uvflip > (_pSpriteSetModel->_pattno_uvflip_Max)) {
//        throwGgafCriticalException("GgafDx9SpriteSetActor::setUvFlipPtnNo �A�j���[�V�����p�^�[���ԍ����͈͊O�ł��B����="<<prm_pattno_uvflip);
//    } else {
//        _pattno_uvflip_now = prm_pattno_uvflip;
//    }
//}
//
//void GgafDx9SpriteSetActor::resetUvFlipPtnNo() {
//    _pattno_uvflip_now = _pattno_uvflip_top;
//}
//
//void GgafDx9SpriteSetActor::forceUvFlipPtnRange(int prm_top, int prm_bottom = 1) {
//    if (prm_top < 0 || prm_bottom > (_pSpriteSetModel->_pattno_uvflip_Max)) {
//        throwGgafCriticalException("GgafDx9SpriteSetActor::forceUvFlipPtnRange �A�j���[�V�����p�^�[���ԍ����͈͊O�ł��B����("<<prm_top<<","<<prm_bottom<<")");
//    } else {
//        _pattno_uvflip_top = prm_top;
//        _pattno_uvflip_bottom = prm_bottom;
//    }
//}
//
//void GgafDx9SpriteSetActor::setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval) {
//    _uvflip_method = prm_method;
//    _frame_uvflip_interval = prm_interval;
//}
//
//void GgafDx9SpriteSetActor::behaveUvFlip() {
////    _TRACE_(getName()<<":_pattno_uvflip_now="<<_pattno_uvflip_now<<"/_pattno_uvflip_bottom="<<_pattno_uvflip_bottom<<"/_pattno_uvflip_top="<<_pattno_uvflip_top<<"/_is_reverse_order_in_oscillate_animation_flg="<<_is_reverse_order_in_oscillate_animation_flg<<"");
//
//    _frame_counter_uvflip++;
//    if (_frame_uvflip_interval < _frame_counter_uvflip) {
//        if (_uvflip_method == FLIP_ORDER_LOOP) { //��F0,1,2,3,4,5,0,1,2,3,4,5,...
//            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
//                _pattno_uvflip_now++;
//            } else {
//                _pattno_uvflip_now = _pattno_uvflip_top;
//            }
//        } else if (_uvflip_method == FLIP_REVERSE_LOOP) { //��F0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
//            if (_pattno_uvflip_top < _pattno_uvflip_now) {
//                _pattno_uvflip_now--;
//            } else {
//                _pattno_uvflip_now = _pattno_uvflip_bottom;
//            }
//        } else if (_uvflip_method == FLIP_ORDER_NOLOOP) { //��F0,1,2,3,4,5,5,5,5,5,5,5...
//            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
//                _pattno_uvflip_now++;
//            } else {
//                processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
//                _pattno_uvflip_now = _pattno_uvflip_bottom;
//            }
//        } else if (_uvflip_method == FLIP_REVERSE_NOLOOP) { //��F5,4,3,2,1,0,0,0,0,0,0...
//            if (_pattno_uvflip_top < _pattno_uvflip_now) {
//                _pattno_uvflip_now--;
//            } else {
//                processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
//                _pattno_uvflip_now = _pattno_uvflip_top;
//            }
//        } else if (_uvflip_method == FLIP_OSCILLATE_LOOP) { //��F0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
//            if (_is_reverse_order_in_oscillate_animation_flg) { //�t������
//                if (_pattno_uvflip_top < _pattno_uvflip_now) {
//                    _pattno_uvflip_now--;
//                } else {
//                    _pattno_uvflip_now++;
//                    _is_reverse_order_in_oscillate_animation_flg = false;
//                }
//            } else {                                            //��������
//                if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
//                    _pattno_uvflip_now++;
//                } else {
//                    _pattno_uvflip_now--;
//                    _is_reverse_order_in_oscillate_animation_flg = true;
//                }
//
//            }
//        } else if (_uvflip_method == NOT_ANIMATED) {
//            //�������Ȃ�
//        }
//        _frame_counter_uvflip = 0;
//    }
//
//}

void GgafDx9SpriteSetActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paD3DMaterial9[0].Ambient.a = _fAlpha; //�����̂Ƃ��떳�Ӗ�
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

GgafDx9SpriteSetActor::~GgafDx9SpriteSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFliper);
}
