#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BoardSetActor::GgafDx9BoardSetActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_effect_id,
                                           const char* prm_technique) :
                                               GgafDx9DrawableActor(prm_name,
                                                                    prm_model_id,
                                                                    "b",
                                                                    prm_effect_id,
                                                                    "b",
                                                                    prm_technique,
                                                                    NULL) {
    _obj_class |= Obj_GgafDx9BoardSetActor;
    _class_name = "GgafDx9BoardSetActor";

    _pBoardSetModel = (GgafDx9BoardSetModel*)_pGgafDx9Model;
    _pBoardSetEffect = (GgafDx9BoardSetEffect*)_pGgafDx9Effect;
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
    _pUvFlipper->forcePtnNoRange(0, _pBoardSetModel->_pattno_max);
    _pUvFlipper->setPtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
    _fAlpha = 1.0f;

    _isTransformed = true;
    _pFunc_calcRotMvWorldMatrix = NULL;
}

void GgafDx9BoardSetActor::processDraw() {
    _draw_set_num = 0; //GgafDx9BoardSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDx9DrawableActor* pDrawActor = this;
    GgafDx9BoardSetActor* pBoardSetActor;
    GgafDx9RectUV* pRectUV_Active;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pGgafDx9Model == _pBoardSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pBoardSetActor = (GgafDx9BoardSetActor*)pDrawActor;

                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[_draw_set_num], pDrawActor->_x);
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[_draw_set_num], pDrawActor->_y);
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[_draw_set_num], pDrawActor->_z);
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[_draw_set_num], pDrawActor->_fAlpha);
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahAlpha) �Ɏ��s���܂����B");

                pRectUV_Active = _pBoardSetModel->_paRectUV + (((GgafDx9BoardSetActor*)(pDrawActor))->_pUvFlipper->_pattno_uvflip_now);
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[_draw_set_num], pRectUV_Active->_aUV[0].tu);
                checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[_draw_set_num], pRectUV_Active->_aUV[0].tv);
                checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");

                _draw_set_num++;
                if (_draw_set_num >= _pBoardSetModel->_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDx9Universe::_pActor_DrawActive = pBoardSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pBoardSetModel->draw(this, _draw_set_num);





////////////////////////////////////////////////////////////////////////////////
//
//
//    _draw_set_num = 1; //����`��[�x�ɁAGgafDx9BoardSetActor�̓������f���������e�N�j�b�N��
//                       //�A�����Ă���J�E���g��
//    GgafDx9DrawableActor* _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
//    while (true) {
//        if (_pNextDrawActor != NULL)  {
//            if (_pNextDrawActor->_pGgafDx9Model == _pBoardSetModel &&
//                _pNextDrawActor->_hash_technique == _hash_technique
//            ) {
//                _draw_set_num++;
//                if (_draw_set_num > _pBoardSetModel->_set_num) {
//                    _draw_set_num = _pBoardSetModel->_set_num;
//                    break;
//                }
//                _pNextDrawActor = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
//            } else {
//                break;
//            }
//        } else {
//            break;
//        }
//    }
//
//    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
//    HRESULT hr;
//
//    GgafDx9DrawableActor *pDrawActor;
//    GgafDx9RectUV* pRectUV_Active;
//
//
//    pDrawActor = this;
//    for (int i = 0; i < _draw_set_num; i++) {
//
//        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], pDrawActor->_x);
//        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
//        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[i], pDrawActor->_y);
//        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
//        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[i], pDrawActor->_z);
//        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
//        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[i], pDrawActor->_fAlpha);
//        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahAlpha) �Ɏ��s���܂����B");
//
//        pRectUV_Active = _pBoardSetModel->_paRectUV + (((GgafDx9BoardSetActor*)(pDrawActor))->_pUvFlipper->_pattno_uvflip_now);
//        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
//        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
//        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
//        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
//        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
//        if (i > 0) {
//            //�A�N�e�B�u��i�߂�
//            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
//        }
//    }
//    _pBoardSetModel->draw(this, _draw_set_num);
}


GgafDx9BoardSetActor::~GgafDx9BoardSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
