#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshSetActor::GgafDx9MeshSetActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique,
                                         GgafDx9Checker* prm_pChecker) :
                                             GgafDx9DrawableActor(prm_name,
                                                                  prm_model_id,
                                                                  "x",
                                                                  prm_effect_id,
                                                                  "x",
                                                                  prm_technique,
                                                                  prm_pChecker) {
    _class_name = "GgafDx9MeshSetActor";
    _pMeshSetModel = (GgafDx9MeshSetModel*)_pGgafDx9Model;
    _pMeshSetEffect = (GgafDx9MeshSetEffect*)_pGgafDx9Effect;
    _pFunc_calcWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
}


void GgafDx9MeshSetActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableActor::setAlpha(prm_fAlpha);
    //GgafDx9MeshSetActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    for (DWORD i = 0; i < _pMeshSetModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}


void GgafDx9MeshSetActor::processDraw() {
    _draw_set_num = 1; //GgafDx9MeshSetActor�̓������f�����A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
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
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_hMatView) �Ɏ��s���܂����B");
    //��{���f�����_��
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetInt(_h_nVertexs) �Ɏ��s���܂����B2");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        //(*_pFunc_calcWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        //GgafDx9Util::setWorldMatrix_ScRxRzRyMv(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ahMaterialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        //�yGgafDx9MeshSetActor�̃}�e���A���J���[�ɂ��čl�����z���Y�^����
        //�{���̓}�e���A���P�I�u�W�F�N�g�ɕ����ێ����A�}�e���A�����X�g�̃O���[�v���ɐݒ肷����̂����A���s���x�œK���Ǝg�p���W�X�^���팸�ׁ̈A�e�Z�b�g��[0]�̃}�e���A����S�̂̃}�e���A���Ƃ���B
        //����������GgafDx9MeshSetActor�̓}�e���A���F��8�Z�b�g�S�Ă��ꂼ��P�F�����s�\�B
        //���Ƃ��Ɩ{�N���X�́A���ꃂ�f�������I�u�W�F�N�g���A�ő�8�Z�b�g�����Ɉ��ŕ`�悵�X�s�[�h�A�b�v��}�邱�Ƃ�ړI�Ƃ����N���X�ŁA��������}�e���A���O���[�v������I�u�W�F�N�g�ɂ͕s���Ƃ��������Ӗ��ł���B
        //�P���e�N�X�`���Ŋ撣��Ζ��Ȃ�����Ƃ������j�B�}�e���A���F�ŐF�����������ꍇ�� GgafDx9MeshActor ���g�������Ȃ��B
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_MaterialDiffuse) �Ɏ��s���܂����B");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}

GgafDx9MeshSetActor::~GgafDx9MeshSetActor() {
}
