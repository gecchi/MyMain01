#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBoardSetActor::GgafDxBoardSetActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_effect_id,
                                           const char* prm_technique) :
                                               GgafDxDrawableActor(prm_name,
                                                                    prm_model_id,
                                                                    "b",
                                                                    prm_effect_id,
                                                                    "b",
                                                                    prm_technique,
                                                                    NULL,
                                                                    NULL) {
    _obj_class |= Obj_GgafDxBoardSetActor;
    _class_name = "GgafDxBoardSetActor";

    _pBoardSetModel = (GgafDxBoardSetModel*)_pModel;
    _pBoardSetEffect = (GgafDxBoardSetEffect*)_pEffect;
//    _pUvFlipper = NEW GgafDxUvFlipper(this);
//    _pUvFlipper->forcePtnNoRange(0, _pBoardSetModel->_pattno_max);
//    _pUvFlipper->setActivePtnNo(0);
//    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);

    _pUvFlipper = NEW GgafDxUvFlipper(_pBoardSetModel->_papTextureCon[0]->use());
    _pUvFlipper->setRotation(_pBoardSetModel->_col_texture_split,
                             _pBoardSetModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);

    _width_px = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx); //��(px)
    _height_px = (int)(_pBoardSetModel->_fSize_BoardSetModelHeightPx); //����(px)
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _fAlpha = 1.0f;

    _is2DActor = true;
    _pFunc_calcRotMvWorldMatrix = NULL;

    _Z = 0;
}

void GgafDxBoardSetActor::processDraw() {
    _draw_set_num = 0; //GgafDxBoardSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDxDrawableActor* pDrawActor = this;
    GgafDxBoardSetActor* pBoardSetActor = NULL;
    float u,v;
//    GgafDxRectUV* pRectUV_Active;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pBoardSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pBoardSetActor = (GgafDxBoardSetActor*)pDrawActor;

                if (_align == ALIGN_RIGHT) {
                    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[_draw_set_num], float(CO2PX(_X)-_width_px));
                } else if (_align == ALIGN_CENTER) {
                    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[_draw_set_num], float(CO2PX(_X)-_width_px/2));
                } else {
                    //ALIGN_LEFT
                    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[_draw_set_num], float(CO2PX(_X)));
                }
                checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw SetFloat(_ahTransformedX) �Ɏ��s���܂����B");
                if (_valign == VALIGN_BOTTOM) {
                    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[_draw_set_num], float(CO2PX(_Y)-_height_px));
                } else if (_valign == VALIGN_MIDDLE) {
                    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[_draw_set_num], float(CO2PX(_Y)-_height_px/2));
                } else {
                    //VALIGN_TOP
                    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[_draw_set_num], float(CO2PX(_Y)));
                }
                checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw SetFloat(_ahTransformedY) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[_draw_set_num], float(CO2PX(_Z)));
                checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw SetFloat(_ahDepthZ) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[_draw_set_num], pDrawActor->_fAlpha);
                checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw SetFloat(_ahAlpha) �Ɏ��s���܂����B");

//                pRectUV_Active = _pBoardSetModel->_paRectUV + (((GgafDxBoardSetActor*)(pDrawActor))->_pUvFlipper->_pattno_uvflip_now);
                pBoardSetActor->_pUvFlipper->getUV(u,v);
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[_draw_set_num], u);
                checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[_draw_set_num], v);
                checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");

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
    GgafDxUniverse::_pActor_DrawActive = pBoardSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pBoardSetModel->draw(this, _draw_set_num);
}

void GgafDxBoardSetActor::locateAs(GgafDxGeoElem* prm_pGeoElem) {
    _X = prm_pGeoElem->_X;
    _Y = prm_pGeoElem->_Y;
}

void GgafDxBoardSetActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

GgafDxBoardSetActor::~GgafDxBoardSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}