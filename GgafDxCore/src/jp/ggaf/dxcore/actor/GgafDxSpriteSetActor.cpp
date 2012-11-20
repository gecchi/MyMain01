#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSpriteSetActor::GgafDxSpriteSetActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_effect_id,
                                           const char* prm_technique,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) :

                                               GgafDxDrawableActor(prm_name,
                                                                   prm_model_id,
                                                                   "s",
                                                                   prm_effect_id,
                                                                   "s",
                                                                   prm_technique,
                                                                   prm_pStat,
                                                                   prm_pChecker) {
    _obj_class |= Obj_GgafDxSpriteSetActor;
    _class_name = "GgafDxSpriteSetActor";
    _draw_set_num = 0;
    //���f���擾
    _pSpriteSetModel = (GgafDxSpriteSetModel*)_pModel;
    _pSpriteSetEffect = (GgafDxSpriteSetEffect*)_pEffect;
    _pUvFlipper = NEW GgafDxUvFlipper(_pSpriteSetModel->_papTextureCon[0]->fetch());
    _pUvFlipper->setRotation(_pSpriteSetModel->_col_texture_split,
                             _pSpriteSetModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);

    _pFunc_calcRotMvWorldMatrix = UTIL::setWorldMatrix_RxRzRyMv;

    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
}

void GgafDxSpriteSetActor::processDraw() {
    _draw_set_num = 0; //GgafDxSpriteSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;

    GgafDxDrawableActor* pDrawActor = this;
    GgafDxSpriteSetActor* pSpriteSetActor = nullptr;
    float u,v;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pSpriteSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pSpriteSetActor = (GgafDxSpriteSetActor*)pDrawActor;
                if (_align == ALIGN_CENTER) {
                    //do nothing
                } else if (_align == ALIGN_LEFT) {
                    pSpriteSetActor->_matWorld._41 += PX_C(_pSpriteSetModel->_fSize_SpriteSetModelWidthPx/2);
                } else {
                    //ALIGN_RIGHT
                    pSpriteSetActor->_matWorld._41 -= PX_C(_pSpriteSetModel->_fSize_SpriteSetModelWidthPx/2);
                }
                if (_valign == VALIGN_MIDDLE) {
                    //do nothing
                } else if (_valign == VALIGN_TOP) {
                    pSpriteSetActor->_matWorld._42 -= PX_C(_pSpriteSetModel->_fSize_SpriteSetModelHeightPx/2);
                } else {
                    //VALIGN_BOTTOM
                    pSpriteSetActor->_matWorld._42 += PX_C(_pSpriteSetModel->_fSize_SpriteSetModelHeightPx/2);
                }
                hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_ah_matWorld[_draw_set_num], &(pSpriteSetActor->_matWorld) );
                checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw SetMatrix(_h_matWorld) �Ɏ��s���܂����B");
                pSpriteSetActor->_pUvFlipper->getUV(u,v);
                hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_offset_u[_draw_set_num], u);
                checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw() SetFloat(_h_offset_u) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_offset_v[_draw_set_num], v);
                checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw() SetFloat(_h_offset_v) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ah_alpha[_draw_set_num], pSpriteSetActor->_alpha);
                checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw SetFloat(_alpha) �Ɏ��s���܂����B");

                _draw_set_num++;
                if (_draw_set_num >= _pSpriteSetModel->_set_num) {
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
    GgafDxUniverse::_pActor_DrawActive = pSpriteSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pSpriteSetModel->draw(this, _draw_set_num);
}

void GgafDxSpriteSetActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paMaterial[0].Ambient.a = _alpha; //���[�������͍��̂Ƃ��떳�Ӗ�
    _paMaterial[0].Diffuse.a = _alpha;
}

void GgafDxSpriteSetActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paMaterial[0].Ambient.a = _alpha; //���[�������͍��̂Ƃ��떳�Ӗ�
    _paMaterial[0].Diffuse.a = _alpha;
}

void GgafDxSpriteSetActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

GgafDxSpriteSetActor::~GgafDxSpriteSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
