#include "jp/ggaf/lib/actor/WallAAPyramidActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallAAPyramidActor::WallAAPyramidActor(const char* prm_name,
                                   const char* prm_model,
                                   GgafStatus* prm_pStat) :

                                      WallPartsActor(prm_name,
                                                     std::string("11/" + std::string(prm_model)).c_str(),
                                                     "WallAAPyramidEffect",
                                                     "WallAAPyramidTechnique",
                                                     prm_pStat) {

    _class_name = "WallAAPyramidActor";
    _pMeshSetModel->_set_num = 11; //WallAAPyramidActor�ő�Z�b�g����11�B

    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1); //0:BOX�p�����蔻��A1:�s���~�b�h�p�����蔻��
    pChecker->setColliAAPyramid(0, 0,0,0, 0,0,0, 0);
    setZEnableDraw(true);       //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(true);  //���g��Z�o�b�t�@���������݂���

    static volatile bool is_init = WallAAPyramidActor::initStatic(this); //�ÓI�����o������
}

D3DXHANDLE WallAAPyramidActor::_h_distance_AlphaTarget;
D3DXHANDLE WallAAPyramidActor::_h_wall_dep;
D3DXHANDLE WallAAPyramidActor::_h_wall_height;
D3DXHANDLE WallAAPyramidActor::_h_wall_width;
std::map<int, UINT> WallAAPyramidActor::_delface;
bool WallAAPyramidActor::initStatic(WallAAPyramidActor* prm_pWallAAPyramidActor) {
    ID3DXEffect* pID3DXEffect = prm_pWallAAPyramidActor->getEffect()->_pID3DXEffect;
    WallAAPyramidActor::_h_distance_AlphaTarget = pID3DXEffect->GetParameterByName( nullptr, "g_distance_AlphaTarget" );
    WallAAPyramidActor::_h_wall_dep    = pID3DXEffect->GetParameterByName( nullptr, "g_wall_dep" );
    WallAAPyramidActor::_h_wall_height = pID3DXEffect->GetParameterByName( nullptr, "g_wall_height" );
    WallAAPyramidActor::_h_wall_width  = pID3DXEffect->GetParameterByName( nullptr, "g_wall_width" );

    //�s���~�b�h�ǂł���Ȃ�΁A�`��ɂ�薳�����ŕ`��s�v�ʂ�����A
    //    c
    // a b d f
    //      e
    //
    //                 00abcdef
    //
    //    FACE_A_BIT = 32 = 0b100000
    //    FACE_B_BIT = 16 = 0b010000
    //    FACE_C_BIT = 8  = 0b001000
    //    FACE_D_BIT = 4  = 0b000100
    //    FACE_E_BIT = 2  = 0b000010
    //    FACE_F_BIT = 1  = 0b000001
    //XY�s���~�b�h�̏ꍇ�� +X -X�ʂ��Ԃ�
    //
    //�������ŕs�v�Ȗʃr�b�g�� 0
    //���ɏ������Ȃ��ꍇ�A�`�悷��ʃr�b�g�� 1
    //�ɐݒ�
                                                                                           //�Ζ�
    WallAAPyramidActor::_delface[POS_PYRAMID_nnn] = FACE_D_BIT | FACE_B_BIT | FACE_E_BIT | FACE_A_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_nnp] = FACE_D_BIT | FACE_C_BIT | FACE_B_BIT | FACE_A_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_npn] = FACE_A_BIT | FACE_B_BIT | FACE_E_BIT | FACE_D_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_npp] = FACE_A_BIT | FACE_C_BIT | FACE_B_BIT | FACE_D_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_pnn] = FACE_D_BIT | FACE_F_BIT | FACE_E_BIT | FACE_A_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_pnp] = FACE_D_BIT | FACE_C_BIT | FACE_F_BIT | FACE_A_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_ppn] = FACE_A_BIT | FACE_F_BIT | FACE_E_BIT | FACE_D_BIT;
    WallAAPyramidActor::_delface[POS_PYRAMID_ppp] = FACE_A_BIT | FACE_C_BIT | FACE_F_BIT | FACE_D_BIT;
    return true;
}

void WallAAPyramidActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_pyramid, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    prm_wall_draw_face &= WallAAPyramidActor::_delface[prm_pos_pyramid]; //�s���~�b�h�������`��s�v��
    WallPartsActor::config(prm_pWalledSectionScene, prm_pos_pyramid,  prm_wall_draw_face,  prm_aColliBoxStretch);
    CollisionChecker3D* pChecker = getCollisionChecker();
    if (prm_aColliBoxStretch[0] == 0) {
        pChecker->disable(0);
    } else {
        pChecker->setColliAAPyramid(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                       -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                       -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                        (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                        (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                        (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1)),
                                        _pos_info   );
         pChecker->enable(0);
    }
    HRESULT hr;
    ID3DXEffect* pID3DXEffect = getEffect()->_pID3DXEffect;
    hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_wall_dep, C_DX(_wall_dep)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_dep) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_wall_height, C_DX(_wall_height)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_height) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_wall_width, C_DX(_wall_width)/_rate_of_bounding_sphere_radius);
    checkDxException(hr, D3D_OK, "SetInt(_h_wall_width) �Ɏ��s���܂����B");

}

void WallAAPyramidActor::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActor�̓������f���œ����e�N�j�b�N��
                          //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* const pID3DXEffect = getEffect()->_pID3DXEffect;
    HRESULT hr;
    if (_pWalledSectionScene->_pActor_infront_alpha_target) {
        hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_distance_AlphaTarget, -(_pWalledSectionScene->_pActor_infront_alpha_target->_dest_from_vppln_infront));
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) �Ɏ��s���܂����B");
    } else {
        hr = pID3DXEffect->SetFloat(WallAAPyramidActor::_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "SetMatrix(_h_distance_AlphaTarget) �Ɏ��s���܂����B");
    }
    GgafDxFigureActor* pDrawActor = this;
    WallPartsActor* pWallPartsActor = nullptr;
    int model_set_num = _pMeshSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pWallPartsActor = (WallPartsActor*)pDrawActor;
            pWallPartsActor->_matWorld._14 = pWallPartsActor->_wall_draw_face;  //�`��ʔԍ������[���h�ϊ��s���matWorld._14 �ɖ��ߍ���
            pWallPartsActor->_matWorld._24 = pWallPartsActor->_pos_info;  //�s���~�b�h�ʒu���������[���h�ϊ��s���matWorld._24 �ɖ��ߍ���
            hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pWallPartsActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) �Ɏ��s���܂����B");
            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pWallPartsActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pMeshSetModel->GgafDxMeshSetModel::draw(this, draw_set_num);
}


WallAAPyramidActor::~WallAAPyramidActor() {
}
