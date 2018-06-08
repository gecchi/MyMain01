#include "jp/ggaf/lib/actor/wall/CubeMapMassWallActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"
#include "jp/ggaf/lib/scene/WallSectionScene.h"
#include "jp/ggaf/lib/effect/MassWallEffect.h"
#include "jp/ggaf/lib/DefaultGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


CubeMapMassWallActor::CubeMapMassWallActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        MassWallActor(prm_name,
                      prm_model,
                      "CubeMapMassWallEffect",
                      "CubeMapMassWallTechnique",
                      prm_pStat ) ,
        GgafDxICubeMapActor() {
    _class_name = "CubeMapMassWallActor";
    _obj_class |= Obj_CubeMapMassWallActor;
}

void CubeMapMassWallActor::processDraw() {
    HRESULT hr;
    MassWallEffect* pMassWallEffect = (MassWallEffect*)getEffect();
    ID3DXEffect* pID3DXEffect = pMassWallEffect->_pID3DXEffect;
    dxcoord wall_dep    = C_DX(_wall_dep)/_rate_of_bounding_sphere_radius;
    dxcoord wall_height = C_DX(_wall_height)/_rate_of_bounding_sphere_radius;
    dxcoord wall_width  = C_DX(_wall_width)/_rate_of_bounding_sphere_radius;
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_wall_dep, wall_dep);
    checkDxException(hr, D3D_OK, "SetFloat(_h_wall_dep) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_wall_height, wall_height);
    checkDxException(hr, D3D_OK, "SetFloat(_h_wall_height) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_wall_width, wall_width);
    checkDxException(hr, D3D_OK, "SetFloat(_h_wall_width) �Ɏ��s���܂����B");
    if (_pWallSectionScene->_pActor_infront_alpha_target) {
        hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_distance_AlphaTarget, -(_pWallSectionScene->_pActor_infront_alpha_target->_dest_from_vppln_infront));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) �Ɏ��s���܂����B");
    } else {
        hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_distance_AlphaTarget, PX_DX(1));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) �Ɏ��s���܂����B");
    }
    //	ah = g_wall_width / g_wall_dep / 2.0; //�X�� z/x �i�X�� x/z �ł͂Ȃ��āj
    //	fh = g_wall_dep/2.0;
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_ah_POS_ZX, wall_width/wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_ah_POS_ZX) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_fh_POS_ZX, wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_fh_POS_ZX) �Ɏ��s���܂����B");
    //	ah = g_wall_height / g_wall_width / 2.0; //�X�� y/z
    //	fh = g_wall_width/2.0;                   //�X����
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_ah_POS_YZ, wall_height/wall_width/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_ah_POS_YZ) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_fh_POS_YZ, wall_width/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_fh_POS_YZ) �Ɏ��s���܂����B");
    //	ah = g_wall_height / g_wall_dep / 2.0; //�X�� y/x
    //	fh = g_wall_dep/2.0;                   //�X����
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_ah_POS_XY, wall_height/wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_ah_POS_XY) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_fh_POS_XY, wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_fh_POS_XY) �Ɏ��s���܂����B");


    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "SetFloat(_h_reflectances) �Ɏ��s���܂����B");
    hr = GgafDxGod::_pID3DDevice9->SetTexture(1, getCubeMapTexture());
    checkDxException(hr, D3D_OK, "SetTexture �Ɏ��s���܂���");

    int draw_set_num = 0; //GgafDxMassMeshActor�̓������f���œ����e�N�j�b�N��
                          //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    GgafDxMassMeshModel* pMassMeshModel = _pMassMeshModel;
    const int model_max_set_num = pMassMeshModel->_set_num;
    const hashval hash_technique = _hash_technique;

    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    MassWallActor::VERTEX_instancedata* paInstancedata = MassWallActor::_aInstancedata;
    CubeMapMassWallActor* pCubeMapMassWallActor = nullptr;
    GgafDxFigureActor* pDrawActor = this;
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassMeshModel && pDrawActor->_hash_technique == hash_technique) {
            pCubeMapMassWallActor = (CubeMapMassWallActor*)pDrawActor;
            memcpy(paInstancedata, &(pDrawActor->_matWorld), size_of_D3DXMATRIX);
            memcpy(&(paInstancedata->r), &(pDrawActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
            paInstancedata->_wall_draw_face = pCubeMapMassWallActor->_wall_draw_face;
            paInstancedata->_pos_info =  pCubeMapMassWallActor->_pos_info;
            ++paInstancedata;
            draw_set_num++;
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
            if (draw_set_num >= model_max_set_num) {
                break;
            } else {
                pDrawActor = pDrawActor->_pNextRenderActor;
            }
        } else {
            break;
        }
    }
    ((GgafDxMassMeshModel*)_pMassMeshModel)->GgafDxMassMeshModel::draw(this, draw_set_num);
}


CubeMapMassWallActor::~CubeMapMassWallActor() {
}
