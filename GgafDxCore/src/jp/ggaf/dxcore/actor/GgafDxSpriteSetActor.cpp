#include "stdafx.h"
using namespace std;
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

    //���f���擾
    _pSpriteSetModel = (GgafDxSpriteSetModel*)_pModel;
    _pSpriteSetEffect = (GgafDxSpriteSetEffect*)_pEffect;
    _pUvFlipper = NEW GgafDxUvFlipper(_pSpriteSetModel->_papTextureCon[0]->use());
    _pUvFlipper->setRotation(_pSpriteSetModel->_col_texture_split,
                             _pSpriteSetModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);

    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
}

void GgafDxSpriteSetActor::processDraw() {
    _draw_set_num = 0; //GgafDxSpriteSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;

    GgafDxDrawableActor* pDrawActor = this;
    GgafDxSpriteSetActor* pSpriteSetActor = NULL;
//    GgafDxRectUV* pRectUV_Active;
    float u,v;
//    pTargetActor->_pUvFlipper->getUV(u,v);
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pSpriteSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pSpriteSetActor = (GgafDxSpriteSetActor*)pDrawActor;

                hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_ah_matWorld[_draw_set_num], &(pDrawActor->_matWorld) );
                checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw SetMatrix(_h_matWorld) �Ɏ��s���܂����B");
                pSpriteSetActor->_pUvFlipper->getUV(u,v);
                hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetU[_draw_set_num], u);
                checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetV[_draw_set_num], v);
                checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahAlpha[_draw_set_num], pDrawActor->_fAlpha);
                checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw SetFloat(_fAlpha) �Ɏ��s���܂����B");

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

void GgafDxSpriteSetActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paMaterial[0].Ambient.a = _fAlpha; //���[�������͍��̂Ƃ��떳�Ӗ�
    _paMaterial[0].Diffuse.a = _fAlpha;
}

void GgafDxSpriteSetActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paMaterial[0].Ambient.a = _fAlpha; //���[�������͍��̂Ƃ��떳�Ӗ�
    _paMaterial[0].Diffuse.a = _fAlpha;
}

GgafDxSpriteSetActor::~GgafDxSpriteSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
