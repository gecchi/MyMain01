#include "jp/ggaf/dx/actor/BoardSetActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/BoardSetEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/BoardSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/GeoElem.h"


using namespace GgafDx;

BoardSetActor::BoardSetActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique) :

                                             FigureActor(prm_name,
                                                               prm_model_id,
                                                               TYPE_BOARDSET_MODEL,
                                                               prm_effect_id,
                                                               TYPE_BOARDSET_EFFECT,
                                                               prm_technique,
                                                               nullptr) ,
_pBoardSetModel((BoardSetModel*)_pModel),
_pBoardSetEffect((BoardSetEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDx_BoardSetActor;
    _class_name = "BoardSetActor";
    _pUvFlipper->locatePatternNo(_pBoardSetModel->_col_texture_split,
                             _pBoardSetModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    _width_px = (int)(_pBoardSetModel->_model_width_px); //��(px)
    _height_px = (int)(_pBoardSetModel->_model_height_px); //����(px)
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;

    _is_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;

    setZEnableDraw(false);
    setZWriteEnable(false);

    _z = 0;
}

void BoardSetActor::processDraw() {
    int draw_set_num = 0; //BoardSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    BoardSetEffect* pBoardSetEffect = _pBoardSetEffect;
    ID3DXEffect* pID3DXEffect = pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    FigureActor* pDrawActor = this;
    BoardSetActor* pBoardSetActor = nullptr;
    int model_set_num = _pBoardSetModel->_set_num;
    float u,v;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pBoardSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pBoardSetActor = (BoardSetActor*)pDrawActor;

            if (_align == ALIGN_RIGHT) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[draw_set_num], C_PX(pBoardSetActor->_x) - pBoardSetActor->_width_px);
            } else if (_align == ALIGN_CENTER) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[draw_set_num], C_PX(pBoardSetActor->_x) - (pBoardSetActor->_harf_width_px));
            } else {
                //ALIGN_LEFT
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[draw_set_num], C_PX(pBoardSetActor->_x));
            }
            checkDxException(hr, D3D_OK, "SetFloat(_ah_transformed_x) �Ɏ��s���܂����B");
            if (_valign == VALIGN_BOTTOM) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[draw_set_num], C_PX(pBoardSetActor->_y) - pBoardSetActor->_height_px);
            } else if (_valign == VALIGN_MIDDLE) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[draw_set_num], C_PX(pBoardSetActor->_y) - (pBoardSetActor->_harf_height_px));
            } else {
                //VALIGN_TOP
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[draw_set_num], C_PX(pBoardSetActor->_y));
            }
            checkDxException(hr, D3D_OK, "SetFloat(_ah_transformed_y) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_z[draw_set_num], C_PX(pBoardSetActor->_z));
            checkDxException(hr, D3D_OK, "SetFloat(_ah_depth_z) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[draw_set_num], pBoardSetActor->_alpha);
            checkDxException(hr, D3D_OK, "SetFloat(_ah_alpha) �Ɏ��s���܂����B");
            pBoardSetActor->_pUvFlipper->getUV(u,v);
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[draw_set_num], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[draw_set_num], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) �Ɏ��s���܂����B");

            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    Spacetime::_pActor_draw_active = pBoardSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pBoardSetModel->BoardSetModel::draw(this, draw_set_num);
}

void BoardSetActor::setPositionAt(const GeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void BoardSetActor::setPositionAt(const GeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

void BoardSetActor::setAlign(Align prm_align, Valign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

void BoardSetActor::setAlign(Align prm_align) {
    _align = prm_align;
}

void BoardSetActor::setValign(Valign prm_valign) {
    _valign = prm_valign;
}

float BoardSetActor::getModelWidth() {
    return _pBoardSetModel->_model_width_px;
}

float BoardSetActor::getModelHeight() {
    return _pBoardSetModel->_model_height_px;
}

BoardSetActor::~BoardSetActor() {
    delete _pUvFlipper;
}