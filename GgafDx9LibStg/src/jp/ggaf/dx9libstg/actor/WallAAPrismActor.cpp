#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

boolean WallAAPrismActor::init = false;

_MAP_<int, UINT> WallAAPrismActor::_delface;

WallAAPrismActor::WallAAPrismActor(const char* prm_name,
                                   const char* prm_model) :

                                      WallActor(prm_name,
                                                string("17/" + string(prm_model)).c_str(),
                                                "WallAAPrismEffect",
                                                "WallAAPrismTechnique") {

    _class_name = "WallAAPrismActor";
    _pMeshSetModel->_set_num = 11; //WallActor�ő�Z�b�g����20�B


    _pCollisionChecker->makeCollision(1); //0:BOX�p�����蔻��A1:�v���Y���p�����蔻��
    _pCollisionChecker->setColliAAPrism(0, 0,0,0, 0,0,0, 0);
    setZEnable(true);       //Z�o�b�t�@�͍l���L��
    setZWriteEnable(true);  //Z�o�b�t�@�͏������ݗL��
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    _h_distance_AlphaTarget = pID3DXEffect->GetParameterByName( NULL, "g_distance_AlphaTarget" );
    _h_wall_dep    = pID3DXEffect->GetParameterByName( NULL, "g_wall_dep" );
    _h_wall_height = pID3DXEffect->GetParameterByName( NULL, "g_wall_height" );
    _h_wall_width  = pID3DXEffect->GetParameterByName( NULL, "g_wall_width" );
    //_h_pos_prism = pID3DXEffect->GetParameterByName( NULL, "g_pos_prism" );
    if (init == false) {
        //�v���Y���ǂł���Ȃ�΁A�`��ɂ�薳�����ŕ`��s�v�ʂ�����A
        //    c
        // a b d f
        //      e
        //
        //                 00abcdef
        //
        //    FACE_A_BIT = 0b100000 = 0
        //    FACE_B_BIT = 0b010000 = 9
        //    FACE_C_BIT = 0b001000 = 8
        //    FACE_D_BIT = 0b000100 = 4
        //    FACE_E_BIT = 0b000010 = 2
        //    FACE_F_BIT = 0b000001 = 1
        //XY�v���Y���̏ꍇ�� +X -X�ʂ��Ԃ�
        _delface[POS_PRISM_XY_nn] = ~FACE_F_BIT;
        _delface[POS_PRISM_XY_np] = ~FACE_F_BIT;
        _delface[POS_PRISM_XY_pn] = ~FACE_B_BIT;
        _delface[POS_PRISM_XY_pp] = ~FACE_B_BIT;

        //YZ�v���Y���̏ꍇ�� +Z -Z�ʂ��Ԃ�
        _delface[POS_PRISM_YZ_nn] = ~FACE_C_BIT;
        _delface[POS_PRISM_YZ_np] = ~FACE_E_BIT;
        _delface[POS_PRISM_YZ_pn] = ~FACE_C_BIT;
        _delface[POS_PRISM_YZ_pp] = ~FACE_E_BIT;

        //ZX�v���Y���̏ꍇ�� +X -X�ʂ��Ԃ�
        _delface[POS_PRISM_ZX_nn] = ~FACE_F_BIT;
        _delface[POS_PRISM_ZX_np] = ~FACE_B_BIT;
        _delface[POS_PRISM_ZX_pn] = ~FACE_F_BIT;
        _delface[POS_PRISM_ZX_pp] = ~FACE_B_BIT;
        init = true;
    }
}

void WallAAPrismActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    prm_wall_draw_face &= _delface[prm_pos_prism]; //�v���Y���������`��s�v��
    WallActor::config(prm_pWalledSectionScene, prm_pos_prism,  prm_wall_draw_face,  prm_aColliBoxStretch);

    if (prm_aColliBoxStretch[0] == 0) {
        _pCollisionChecker->disable(0);
    } else {
        _pCollisionChecker->setColliAAPrism(0, -(_wall_dep/2)    - (_wall_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                               -(_wall_height/2) - (_wall_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                               -(_wall_width/2)  - (_wall_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                                (_wall_dep/2)    + (_wall_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                                (_wall_height/2) + (_wall_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                                (_wall_width/2)  + (_wall_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1)),
                                                _pos_prism
                                            );

         _pCollisionChecker->enable(0);
    }
	HRESULT hr;
	ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    hr = pID3DXEffect->SetFloat(_h_wall_dep, 1.0*_wall_dep/LEN_UNIT/PX_UNIT/_fRate_BoundingSphereRadius);
    checkDxException(hr, D3D_OK, "WallAAPrismActor::WallAAPrismActor() SetInt(_h_wall_dep) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_h_wall_height, 1.0*_wall_height/LEN_UNIT/PX_UNIT/_fRate_BoundingSphereRadius);
    checkDxException(hr, D3D_OK, "WallAAPrismActor::WallAAPrismActor() SetInt(_h_wall_height) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_h_wall_width, 1.0*_wall_width/LEN_UNIT/PX_UNIT/_fRate_BoundingSphereRadius);
    checkDxException(hr, D3D_OK, "WallAAPrismActor::WallAAPrismActor() SetInt(_h_wall_width) �Ɏ��s���܂����B");

}

void WallAAPrismActor::processDraw() {
    _draw_set_num = 1; //GgafDx9MeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel &&
                _pNextDrawActor->_hash_technique == _hash_technique &&
                _pNextDrawActor->isActive()
            ) {
                _draw_set_num++;
                if (_draw_set_num > _pMeshSetModel->_set_num) {
                    _draw_set_num = _pMeshSetModel->_set_num;
                    break;
                }
                _pNextDrawActor = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    if (_pWalledSectionScene->_pTarget_FrontAlpha) {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -(_pWalledSectionScene->_pTarget_FrontAlpha->_fDist_VpPlnFront));
        checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetMatrix(_h_distance_AlphaTarget) �Ɏ��s���܂����B");
    } else {
        hr = pID3DXEffect->SetFloat(_h_distance_AlphaTarget, -100.0f);
        checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetMatrix(_h_distance_AlphaTarget) �Ɏ��s���܂����B");
    }
    //VIEW�ϊ��s��
//    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_h_matView, &P_CAM->_vMatrixView);
//    checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetMatrix(_h_matView) �Ɏ��s���܂����B");

    WallActor* pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        pDrawActor->_matWorld._14 = pDrawActor->_wall_draw_face;  //�`��ʔԍ������[���h�ϊ��s���matWorld._14 �ɖ��ߍ���
        pDrawActor->_matWorld._24 = pDrawActor->_pos_prism;  //�v���Y���ʒu���������[���h�ϊ��s���matWorld._24 �ɖ��ߍ���
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
//		hr = pID3DXEffect->SetInt(_h_pos_prism, pDrawActor->_pos_prism);
//		checkDxException(hr, D3D_OK, "WallAAPrismActor::processDraw() SetInt(_h_wall_dep) �Ɏ��s���܂����B");
        pDrawActor = (WallActor*)(pDrawActor -> _pNext_TheSameDrawDepthLevel);
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}


WallAAPrismActor::~WallAAPrismActor() {
}
