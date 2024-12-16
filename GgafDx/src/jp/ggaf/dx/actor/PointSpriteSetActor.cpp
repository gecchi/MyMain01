#include "jp/ggaf/dx/actor/PointSpriteSetActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/PointSpriteSetEffect.h"
#include "jp/ggaf/dx/model/PointSpriteSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

PointSpriteSetActor::PointSpriteSetActor(const char* prm_name,
                                         const char* prm_model,
                                         const char* prm_effect_id,
                                         const char* prm_technique) :

                                             FigureActor(prm_name,
                                                         prm_model,
                                                         TYPE_POINTSPRITESET_MODEL,
                                                         prm_effect_id,
                                                         TYPE_POINTSPRITESET_EFFECT,
                                                         prm_technique),
_pPointSpriteSetModel((PointSpriteSetModel*)_pModel),
_pPointSpriteSetEffect((PointSpriteSetEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper())
{
    _obj_class |= Obj_GgafDx_PointSpriteSetActor;
    _class_name = "PointSpriteSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    _pUvFlipper->locatePatternNo(_pPointSpriteSetModel->_texture_split_rowcol,
                                 _pPointSpriteSetModel->_texture_split_rowcol );
    useZBufferDrawing(false);
    setZBufferWriteEnable(false);
}

PointSpriteSetActor::PointSpriteSetActor(const char* prm_name,
                                         const char* prm_model,
                                         const char prm_model_type,
                                         const char* prm_effect_id,
                                         const char prm_effect_type,
                                         const char* prm_technique) :

                                             FigureActor(prm_name,
                                                         prm_model,
                                                         prm_model_type,
                                                         prm_effect_id,
                                                         prm_effect_type,
                                                         prm_technique),
_pPointSpriteSetModel((PointSpriteSetModel*)_pModel),
_pPointSpriteSetEffect((PointSpriteSetEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper()) {

    _obj_class |= Obj_GgafDx_PointSpriteSetActor;
    _class_name = "PointSpriteSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    _pUvFlipper->locatePatternNo(_pPointSpriteSetModel->_texture_split_rowcol,
                                 _pPointSpriteSetModel->_texture_split_rowcol );
    useZBufferDrawing(false);
    setZBufferWriteEnable(false);
}

void PointSpriteSetActor::processDraw() {
    int draw_set_num = 0; //PointSpriteSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* const pID3DXEffect = _pPointSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;
    FigureActor* pDrawActor = this;
    PointSpriteSetActor* pPointSpriteSetActor = nullptr;
    const int model_draw_set_num = _pPointSpriteSetModel->_draw_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pPointSpriteSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pPointSpriteSetActor = (PointSpriteSetActor*)pDrawActor;
            pPointSpriteSetActor->_matWorld._14 = pPointSpriteSetActor->_pUvFlipper->_pattno_uvflip_now;//UV�̃A�N�e�B�u�p�^�[���ԍ������[���h�ϊ��s���matWorld._14 �ɖ��ߍ���
            hr = pID3DXEffect->SetMatrix(_pPointSpriteSetEffect->_ah_matWorld[draw_set_num], &(pPointSpriteSetActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetValue(_pPointSpriteSetEffect->_ah_colMaterialDiffuse[draw_set_num], &(pPointSpriteSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
            checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

            pDrawActor = pDrawActor->_pNextRenderActor;
            draw_set_num++;
            if (draw_set_num >= model_draw_set_num) {
                break;
            }
        } else {
            break;
        }
    }
    _pNextRenderActor = pDrawActor;

    //�|�C���g�X�v���C�gON
    pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    ((PointSpriteSetModel*)_pPointSpriteSetModel)->PointSpriteSetModel::draw(this, draw_set_num);
    //�|�C���g�X�v���C�gOFF
    pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
}

void PointSpriteSetActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pPointSpriteSetModel = (PointSpriteSetModel*)_pModel;
}

PointSpriteSetActor::~PointSpriteSetActor() {
    delete _pUvFlipper;
}
