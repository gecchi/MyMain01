#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundBoxActor::GroundBoxActor(const char* prm_name, const char* prm_model) :
    GgafDx9MeshSetActor(prm_name,
                         prm_model,
                         "GroundBoxEffect",
                         "GroundBoxTechnique",
                         NEW CollisionChecker(this) ) {

    _class_name = "GroundBoxActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);
}

//void GroundBoxActor::processPreDraw() {
//    _pNext_TheSameDrawDepthLevel = NULL;
//    if (_is_active_flg && _can_live_flg) {
//        //�w�i�Ȃ̂Ŕw�ʂŕ`��
//        GgafDx9Universe::setDrawDepthMaxLevel(this);
//    }
//}

void GroundBoxActor::initialize() {

}

void GroundBoxActor::onActive() {
    _box_type



}



void GroundBoxActor::processBehavior() {

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

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        //(*_pFunc_calcRotMvWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        //GgafDx9Util::setWorldMatrix_ScRxRzRyMv(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        //�yGgafDx9MeshSetActor�̃}�e���A���J���[�ɂ��čl�����z���Y�^����
        //�{���̓}�e���A���P�I�u�W�F�N�g�ɕ����ێ����A�}�e���A�����X�g�̃O���[�v���ɐݒ肷����̂����A���s���x�œK���Ǝg�p���W�X�^���팸�ׁ̈A�e�Z�b�g��[0]�̃}�e���A����S�̂̃}�e���A���Ƃ���B
        //����������GgafDx9MeshSetActor�̓}�e���A���F��8�Z�b�g�S�Ă��ꂼ��P�F�����s�\�B
        //���ꂼ��̂P�F���A�}�e���A���F�Ƃ��ăI�u�W�F�N�g�ʂɂ邽�ߒ��_�J���[�Ŏ������Ă���B
        //���Ƃ��Ɩ{�N���X�́A���ꃂ�f�������I�u�W�F�N�g���A�ő�8�Z�b�g�����Ɉ��ŕ`�悵�X�s�[�h�A�b�v��}�邱�Ƃ�ړI�Ƃ����N���X�ŁA��������}�e���A���O���[�v������I�u�W�F�N�g�ɂ͕s���Ƃ��������Ӗ��ł���B
        //�P���e�N�X�`���Ŋ撣��Ζ��Ȃ��E�E�E�Ƃ������j�B�}�e���A���F�ŐF�����������ꍇ�� GgafDx9MeshActor ���g�������Ȃ��B

        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
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

GroundBoxActor::~GroundBoxActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
