#include "jp/ggaf/lib/actor/wall/CubeMapMassWallActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/lib/scene/WallSectionScene.h"
#include "jp/ggaf/lib/effect/MassWallEffect.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"



using namespace GgafLib;


CubeMapMassWallActor::CubeMapMassWallActor(const char* prm_name, const char* prm_model) :
        MassWallActor(prm_name,
                      prm_model,
                      "CubeMapMassWallEffect",
                      "CubeMapMassWallTechnique") ,
        GgafDx::ICubeMapActor() {
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
    checkDxException(hr, D3D_OK, "SetFloat(_h_wall_dep) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_wall_height, wall_height);
    checkDxException(hr, D3D_OK, "SetFloat(_h_wall_height) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_wall_width, wall_width);
    checkDxException(hr, D3D_OK, "SetFloat(_h_wall_width) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    if (_pWallSectionScene->_pActor_infront_alpha_target) {
        hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_distance_AlphaTarget, -(_pWallSectionScene->_pActor_infront_alpha_target->_dest_from_vppln_infront));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    } else {
        hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_distance_AlphaTarget, PX_DX(1));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    }
    //	ah = g_wall_width / g_wall_dep / 2.0; //ŒX‚« z/x iŒX‚« x/z ‚Å‚Í‚È‚­‚Äj
    //	fh = g_wall_dep/2.0;
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_ah_POS_ZX, wall_width/wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_ah_POS_ZX) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_fh_POS_ZX, wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_fh_POS_ZX) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    //	ah = g_wall_height / g_wall_width / 2.0; //ŒX‚« y/z
    //	fh = g_wall_width/2.0;                   //ŒX‚­Ž²
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_ah_POS_YZ, wall_height/wall_width/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_ah_POS_YZ) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_fh_POS_YZ, wall_width/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_fh_POS_YZ) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    //	ah = g_wall_height / g_wall_dep / 2.0; //ŒX‚« y/x
    //	fh = g_wall_dep/2.0;                   //ŒX‚­Ž²
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_ah_POS_XY, wall_height/wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_ah_POS_XY) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_fh_POS_XY, wall_dep/2.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_fh_POS_XY) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");


    hr = pID3DXEffect->SetFloat(pMassWallEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "SetFloat(_h_reflectances) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pCARETAKER->_pID3DDevice9->SetTexture(1, getCubeMapTexture());
    checkDxException(hr, D3D_OK, "SetTexture ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

    int draw_set_num = 0; //MassMeshActor‚Ì“¯‚¶ƒ‚ƒfƒ‹‚Å“¯‚¶ƒeƒNƒjƒbƒN‚ª
                          //˜A‘±‚µ‚Ä‚¢‚éƒJƒEƒ“ƒg”B“¯ˆê•`‰æ[“x‚Íˆê“x‚É•`‰æ‚·‚éB
    GgafDx::MassMeshModel* pMassMeshModel = _pMassMeshModel;
    const int model_max_draw_set_num = pMassMeshModel->_draw_set_num;
    const hashval hash_technique = _hash_technique;

    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    MassWallActor::VERTEX_instancedata* paInstancedata = MassWallActor::_aInstancedata;
    CubeMapMassWallActor* pCubeMapMassWallActor = nullptr;
    GgafDx::FigureActor* pDrawActor = this;
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassMeshModel && pDrawActor->_hash_technique == hash_technique) {
            pCubeMapMassWallActor = (CubeMapMassWallActor*)pDrawActor;
            memcpy(paInstancedata, &(pDrawActor->_matWorld), size_of_D3DXMATRIX);
            memcpy(&(paInstancedata->r), &(pDrawActor->_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
            paInstancedata->_wall_draw_face = pCubeMapMassWallActor->_wall_draw_face;
            paInstancedata->_pos_info =  pCubeMapMassWallActor->_pos_info;
            ++paInstancedata;

            pDrawActor = pDrawActor->_pNextRenderActor;
            draw_set_num++;
            if (draw_set_num >= model_max_draw_set_num) {
                break;
            }
        } else {
            break;
        }
    }
    ((GgafDx::MassMeshModel*)_pMassMeshModel)->GgafDx::MassMeshModel::draw(this, draw_set_num);
    _pNextRenderActor = pDrawActor;
}


CubeMapMassWallActor::~CubeMapMassWallActor() {
}
