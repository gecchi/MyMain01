#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteSetActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxPointSpriteSetModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxPointSpriteSetActor::GgafDxPointSpriteSetActor(const char* prm_name,
                                                     const char* prm_model_id,
                                                     const char* prm_effect_id,
                                                     const char* prm_technique,
                                                     GgafStatus* prm_pStat,
                                                     GgafDxChecker* prm_pChecker) :

                                                         GgafDxFigureActor(prm_name,
                                                                           prm_model_id,
                                                                           "o",
                                                                           prm_effect_id,
                                                                           "o",
                                                                           prm_technique,
                                                                           prm_pStat,
                                                                           prm_pChecker),
_pPointSpriteSetModel((GgafDxPointSpriteSetModel*)_pModel),
_pPointSpriteSetEffect((GgafDxPointSpriteSetEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {
    _obj_class |= Obj_GgafDxPointSpriteSetActor;
    _class_name = "GgafDxPointSpriteSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    _pUvFlipper->setRotation(_pPointSpriteSetModel->_texture_split_rowcol,
                             _pPointSpriteSetModel->_texture_split_rowcol );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    setZEnableDraw(false);
    setZWriteEnable(false);
}

GgafDxPointSpriteSetActor::GgafDxPointSpriteSetActor(const char* prm_name,
                                                     const char* prm_model_id,
                                                     const char* prm_model_type,
                                                     const char* prm_effect_id,
                                                     const char* prm_effect_type,
                                                     const char* prm_technique,
                                                     GgafStatus* prm_pStat,
                                                     GgafDxChecker* prm_pChecker) :

                                                         GgafDxFigureActor(prm_name,
                                                                           prm_model_id,
                                                                           prm_model_type,
                                                                           prm_effect_id,
                                                                           prm_effect_type,
                                                                           prm_technique,
                                                                           prm_pStat,
                                                                           prm_pChecker),
_pPointSpriteSetModel((GgafDxPointSpriteSetModel*)_pModel),
_pPointSpriteSetEffect((GgafDxPointSpriteSetEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDxPointSpriteSetActor;
    _class_name = "GgafDxPointSpriteSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    _pUvFlipper->setRotation(_pPointSpriteSetModel->_texture_split_rowcol,
                             _pPointSpriteSetModel->_texture_split_rowcol );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    setZEnableDraw(false);
    setZWriteEnable(false);
}

void GgafDxPointSpriteSetActor::processDraw() {
    int draw_set_num = 0; //GgafDxPointSpriteSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* const pID3DXEffect = _pPointSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDxFigureActor* pDrawActor = this;
    GgafDxPointSpriteSetActor* pPointSpriteSetActor = nullptr;
    const int model_set_num = _pPointSpriteSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pPointSpriteSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pPointSpriteSetActor = (GgafDxPointSpriteSetActor*)pDrawActor;
            pPointSpriteSetActor->_matWorld._14 = pPointSpriteSetActor->_pUvFlipper->_pattno_uvflip_now;//UV�̃A�N�e�B�u�p�^�[���ԍ������[���h�ϊ��s���matWorld._14 �ɖ��ߍ���
            hr = pID3DXEffect->SetMatrix(_pPointSpriteSetEffect->_ah_matWorld[draw_set_num], &(pPointSpriteSetActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetValue(_pPointSpriteSetEffect->_ah_colMaterialDiffuse[draw_set_num], &(pPointSpriteSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
            checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pPointSpriteSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g

    //�|�C���g�X�v���C�gON
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    ((GgafDxPointSpriteSetModel*)_pPointSpriteSetModel)->GgafDxPointSpriteSetModel::draw(this, draw_set_num);
    //�|�C���g�X�v���C�gOFF
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
}

GgafDxPointSpriteSetActor::~GgafDxPointSpriteSetActor() {
    delete _pUvFlipper;
}
