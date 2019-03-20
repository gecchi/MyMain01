#include "jp/ggaf/dx/actor/PointSpriteSetActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/PointSpriteSetEffect.h"
#include "jp/ggaf/dx/model/PointSpriteSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

PointSpriteSetActor::PointSpriteSetActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique,
                                         Checker* prm_pChecker) :

                                             FigureActor(prm_name,
                                                         prm_model_id,
                                                         TYPE_POINTSPRITESET_MODEL,
                                                         prm_effect_id,
                                                         TYPE_POINTSPRITESET_EFFECT,
                                                         prm_technique,
                                                         prm_pChecker),
_pPointSpriteSetModel((PointSpriteSetModel*)_pModel),
_pPointSpriteSetEffect((PointSpriteSetEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->getDefaultTextureConnection()->peek()))
{
    _obj_class |= Obj_GgafDx_PointSpriteSetActor;
    _class_name = "PointSpriteSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    _pUvFlipper->locatePatternNo(_pPointSpriteSetModel->_texture_split_rowcol,
                             _pPointSpriteSetModel->_texture_split_rowcol );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    setZEnableDraw(false);
    setZWriteEnable(false);
}

PointSpriteSetActor::PointSpriteSetActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char prm_model_type,
                                         const char* prm_effect_id,
                                         const char prm_effect_type,
                                         const char* prm_technique,
                                         Checker* prm_pChecker) :

                                             FigureActor(prm_name,
                                                         prm_model_id,
                                                         prm_model_type,
                                                         prm_effect_id,
                                                         prm_effect_type,
                                                         prm_technique,
                                                         prm_pChecker),
_pPointSpriteSetModel((PointSpriteSetModel*)_pModel),
_pPointSpriteSetEffect((PointSpriteSetEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDx_PointSpriteSetActor;
    _class_name = "PointSpriteSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    _pUvFlipper->locatePatternNo(_pPointSpriteSetModel->_texture_split_rowcol,
                             _pPointSpriteSetModel->_texture_split_rowcol );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    setZEnableDraw(false);
    setZWriteEnable(false);
}

void PointSpriteSetActor::processDraw() {
    int draw_set_num = 0; //PointSpriteSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* const pID3DXEffect = _pPointSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;
    FigureActor* pDrawActor = this;
    PointSpriteSetActor* pPointSpriteSetActor = nullptr;
    const int model_set_num = _pPointSpriteSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pPointSpriteSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pPointSpriteSetActor = (PointSpriteSetActor*)pDrawActor;
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
    Spacetime::_pActor_draw_active = pPointSpriteSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g

    //�|�C���g�X�v���C�gON
    God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    ((PointSpriteSetModel*)_pPointSpriteSetModel)->PointSpriteSetModel::draw(this, draw_set_num);
    //�|�C���g�X�v���C�gOFF
    God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
}

PointSpriteSetActor::~PointSpriteSetActor() {
    delete _pUvFlipper;
}
