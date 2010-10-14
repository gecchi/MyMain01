#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundBoxActor::GroundBoxActor(const char* prm_name, const char* prm_model, int prm_box_dep, int prm_box_width, int prm_box_height) :
    GgafDx9MeshSetActor(prm_name,
                        string(string("16/") + string(prm_model)).c_str(),
                         "GroundBoxEffect",
                         "GroundBoxTechnique",
                         NEW CollisionChecker(this) ) {
    _pMeshSetModel->_set_num = 16; //GroundBoxActor�ő�Z�b�g����16�B
    _class_name = "GroundBoxActor";
    setHitAble(true);
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);
    _ground_speed = 0;
    _box_draw_face = 0;

    _box_dep = prm_box_dep;
    _box_width = prm_box_width;
    _box_height = prm_box_height;

    _ahDrawFace[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face001" );
    _ahDrawFace[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face002" );
    _ahDrawFace[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face003" );
    _ahDrawFace[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face004" );
    _ahDrawFace[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face005" );
    _ahDrawFace[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face006" );
    _ahDrawFace[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face007" );
    _ahDrawFace[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face008" );
    _ahDrawFace[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face009" );
    _ahDrawFace[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face010" );
    _ahDrawFace[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face011" );
    _ahDrawFace[11] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face012" );
    _ahDrawFace[12] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face013" );
    _ahDrawFace[13] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face014" );
    _ahDrawFace[14] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face015" );
    _ahDrawFace[15] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_draw_face016" );
    _h_box_dep = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_box_dep" );
    _h_box_width = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_box_width" );
    _h_box_height = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_box_height" );



    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(true);  //Z�o�b�t�@�͏������ݗL��
}

//void GroundBoxActor::processPreDraw() {
//    _pNext_TheSameDrawDepthLevel = NULL;
//    if (_is_active_flg && _can_live_flg) {
//        //�w�i�Ȃ̂Ŕw�ʂŕ`��
//        GgafDx9Universe::setDrawDepthMaxLevel(this);
//    }
//}

void GroundBoxActor::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -_box_dep/2, -_box_height/2, -_box_width/2,
                                        _box_dep/2,  _box_height/2,  _box_width/2);
    _SX=_SY=_SZ = 4000;
    setBoundingSphereRadiusRate(4.0);
}

void GroundBoxActor::onActive() {
    //_box_type



}



void GroundBoxActor::processBehavior() {
    _X = _X - _ground_speed;
}
void GroundBoxActor::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void GroundBoxActor::processDraw() {
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

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW�ϊ��s��
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_h_matView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_h_matView) �Ɏ��s���܂����B");
    //��{���f�����_��
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_vertexs_num, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetInt(_h_vertexs_num) �Ɏ��s���܂����B2");

    hr = pID3DXEffect->SetFloat(_h_box_dep, 1.0*_box_dep/LEN_UNIT/PX_UNIT);
    checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetFloat(_h_box_dep) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_h_box_width, 1.0*_box_width/LEN_UNIT/PX_UNIT);
    checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetFloat(_h_box_width) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_h_box_height, 1.0*_box_height/LEN_UNIT/PX_UNIT);
    checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetFloat(_h_box_height) �Ɏ��s���܂����B");


    GroundBoxActor* pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        //(*_pFunc_calcRotMvWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        //GgafDx9Util::setWorldMatrix_ScRxRzRyMv(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
        //hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        //�yGgafDx9MeshSetActor�̃}�e���A���J���[�ɂ��čl�����z���Y�^����
        //�{���̓}�e���A���P�I�u�W�F�N�g�ɕ����ێ����A�}�e���A�����X�g�̃O���[�v���ɐݒ肷����̂����A���s���x�œK���Ǝg�p���W�X�^���팸�ׁ̈A�e�Z�b�g��[0]�̃}�e���A����S�̂̃}�e���A���Ƃ���B
        //����������GgafDx9MeshSetActor�̓}�e���A���F��8�Z�b�g�S�Ă��ꂼ��P�F�����s�\�B
        //���ꂼ��̂P�F���A�}�e���A���F�Ƃ��ăI�u�W�F�N�g�ʂɂ邽�ߒ��_�J���[�Ŏ������Ă���B
        //���Ƃ��Ɩ{�N���X�́A���ꃂ�f�������I�u�W�F�N�g���A�ő�8�Z�b�g�����Ɉ��ŕ`�悵�X�s�[�h�A�b�v��}�邱�Ƃ�ړI�Ƃ����N���X�ŁA��������}�e���A���O���[�v������I�u�W�F�N�g�ɂ͕s���Ƃ��������Ӗ��ł���B
        //�P���e�N�X�`���Ŋ撣��Ζ��Ȃ��E�E�E�Ƃ������j�B�}�e���A���F�ŐF�����������ꍇ�� GgafDx9MeshActor ���g�������Ȃ��B

        //checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetValue(_ah_materialDiffuse) �Ɏ��s���܂����B");

        //�`��ʔԍ�
        hr = pID3DXEffect->SetInt(this->_ahDrawFace[i], pDrawActor->_box_draw_face);
        checkDxException(hr, D3D_OK, "GroundBoxActor::processDraw() SetInt(_ahDrawFace) �Ɏ��s���܂����B");



        pDrawActor = (GroundBoxActor*)(pDrawActor -> _pNext_TheSameDrawDepthLevel);
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            //���̃L���X�g�͊댯�ł���B���g�̃I�u�W�F�N�g���f�����B��̃��f���łȂ���Ζ\�����Ă��܂��B
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}















//
//void GroundBoxActor::processDraw() {
//    static ID3DXEffect* pID3DXEffect;
//    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
//    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matView, &pCAM->_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matView) �Ɏ��s���܂����B");
//    GgafDx9Util::setWorldMatrix_RxRzRyMv(this, _matWorld);
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
//    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
//
////    // Z�o�b�t�@�𖳌���
////    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
////    // Z�o�b�t�@�������ݕs��
////    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�J�����OOFF
//    _pMeshModel->draw(this);
//
////    // Z�o�b�t�@��L����
////    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
////    // Z�o�b�t�@�������݉�
////    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//
//}



void GroundBoxActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

void GroundBoxActor::config(int prm_box_draw_face, int* prm_aColliBoxStretch) {
    _box_draw_face = prm_box_draw_face;

    _pCollisionChecker->setColliAAB(0, -(_box_dep/2)    - (_box_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1)),
                                       -(_box_height/2) - (_box_height * (prm_aColliBoxStretch[FACE_D_IDX]-1)),
                                       -(_box_width/2)  - (_box_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1)),
                                        (_box_dep/2)    + (_box_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1)),
                                        (_box_height/2) + (_box_height * (prm_aColliBoxStretch[FACE_A_IDX]-1)),
                                        (_box_width/2)  + (_box_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1))
                                   );




//                                        _box_dep/2,  _box_height/2,  _box_width/2);
//
//    GgafDx9CollisionPart* pColliPart = _pCollisionChecker->_pCollisionArea->_papColliPart[0];
//    //pColliPart->_aab_x1 -= _box_dep    * (prm_aColliBoxStretch[FACE_B_IDX]-1);
//    pColliPart->_aab_x2 += _box_dep    * (prm_aColliBoxStretch[FACE_F_IDX]-1);
//    //pColliPart->_aab_y1 -= _box_height * (prm_aColliBoxStretch[FACE_D_IDX]-1);
//    pColliPart->_aab_y2 += _box_height * (prm_aColliBoxStretch[FACE_A_IDX]-1);
//    //pColliPart->_aab_z1 -= _box_width  * (prm_aColliBoxStretch[FACE_E_IDX]-1);
//    pColliPart->_aab_z2 += _box_width  * (prm_aColliBoxStretch[FACE_C_IDX]-1);

}

GroundBoxActor::~GroundBoxActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
