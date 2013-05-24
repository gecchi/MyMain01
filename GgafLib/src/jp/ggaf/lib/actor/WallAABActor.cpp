#include "stdafx.h"
#include "jp/ggaf/lib/actor/WallAABActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallAABActor::WallAABActor(const char* prm_name,
                           const char* prm_model,
                           GgafStatus* prm_pStat) :

                           WallPartsActor(prm_name,
                                          std::string("16/" + std::string(prm_model)).c_str(),
                                          "WallAABEffect",
                                          "WallAABTechnique",
                                          prm_pStat) {

    _class_name = "WallAABActor";
    _pMeshSetModel->_set_num = 16; //WallPartsActor�ő�Z�b�g����16�B
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    _h_distance_AlphaTarget = pID3DXEffect->GetParameterByName( nullptr, "g_distance_AlphaTarget" );
    _ah_wall_draw_face[0]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face001" );
    _ah_wall_draw_face[1]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face002" );
    _ah_wall_draw_face[2]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face003" );
    _ah_wall_draw_face[3]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face004" );
    _ah_wall_draw_face[4]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face005" );
    _ah_wall_draw_face[5]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face006" );
    _ah_wall_draw_face[6]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face007" );
    _ah_wall_draw_face[7]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face008" );
    _ah_wall_draw_face[8]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face009" );
    _ah_wall_draw_face[9]   = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face010" );
    _ah_wall_draw_face[10]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face011" );
    _ah_wall_draw_face[11]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face012" );
    _ah_wall_draw_face[12]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face013" );
    _ah_wall_draw_face[13]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face014" );
    _ah_wall_draw_face[14]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face015" );
    _ah_wall_draw_face[15]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face016" );
//    _ah_wall_draw_face[16]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face017" );
//    _ah_wall_draw_face[17]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face018" );
//    _ah_wall_draw_face[18]  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_draw_face019" );


    _pColliChecker->makeCollision(1); //0:BOX�p�����蔻��A1:�v���Y���p�����蔻��
    _pColliChecker->setColliAAB(0, 0,0,0, 0,0,0);
    setZEnable(true);       //Z�o�b�t�@�͍l���L��
    setZWriteEnable(true);  //Z�o�b�t�@�͏������ݗL��
}


void WallAABActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    WallPartsActor::config(prm_pWalledSectionScene, prm_pos_prism,  prm_wall_draw_face,  prm_aColliBoxStretch);

    if (prm_aColliBoxStretch[0] == 0) {
        _pColliChecker->disable(0);
    } else {
        _pColliChecker->setColliAAB(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                       -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                       -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                        (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                        (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                        (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1))
                                       );
         _pColliChecker->enable(0);
    }
}

void WallAABActor::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    if (_pWalledSectionScene->_pTarget_FrontAlpha) {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -(_pWalledSectionScene->_pTarget_FrontAlpha->_dest_from_vppln_front));
        checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(_h_distance_AlphaTarget) �Ɏ��s���܂����B");
    } else {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(_h_distance_AlphaTarget) �Ɏ��s���܂����B");
    }
    GgafDxDrawableActor* pDrawActor = this;
    WallPartsActor* pWallPartsActor = nullptr;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pWallPartsActor = (WallPartsActor*)pDrawActor;
//                _TRACE_("WallAABActor::processDraw() pWallPartsActor->_wall_draw_face="<<(pWallPartsActor->_wall_draw_face)<<" befor._matWorld._14="<<(pWallPartsActor->_matWorld._14));

                //pWallPartsActor->_matWorld._14 = pWallPartsActor->_wall_draw_face;  //�`��ʔԍ������[���h�ϊ��s���matWorld._14 �ɖ��ߍ���

                hr = pID3DXEffect->SetInt(_ah_wall_draw_face[draw_set_num], pWallPartsActor->_wall_draw_face);
                checkDxException(hr, D3D_OK, "WallPartsActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pWallPartsActor->_matWorld));
                checkDxException(hr, D3D_OK, "WallPartsActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

                //_set_num 19��18�ɁA���邢�͂Q�Ƃ��R�Ɍ��炵�Ă݂��͂ǂ���
                //FX��VS_2_0 �ɕς��Ă݂Ă͂ǂ���
                //



//                D3DXMATRIX& mat = pWallPartsActor->_matWorld;
//                _TRACE_(mat._11<<","<<mat._12<<","<<mat._13<<","<<mat._14);
//                _TRACE_(mat._21<<","<<mat._22<<","<<mat._23<<","<<mat._24);
//                _TRACE_(mat._31<<","<<mat._32<<","<<mat._33<<","<<mat._34);
//                _TRACE_(mat._41<<","<<mat._42<<","<<mat._43<<","<<mat._44);
//                _TRACE_("------------");

                draw_set_num++;
                if (draw_set_num >= _pMeshSetModel->_set_num) {
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
    GgafDxUniverse::_pActor_DrawActive = pWallPartsActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pMeshSetModel->draw(this, draw_set_num);
}


WallAABActor::~WallAABActor() {
}
