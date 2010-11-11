#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteMeshSetActor::GgafDx9SpriteMeshSetActor(const char* prm_name,
                                       const char* prm_model,
                                       GgafDx9Checker* prm_pChecker) :

                                        GgafDx9MeshSetActor(prm_name,
                                                           prm_model,
                                                           "SpriteMeshSetEffect",
                                                           "SpriteMeshSetTechnique",
                                                           prm_pChecker) {

    _obj_class |= Obj_GgafDx9SpriteMeshSetActor;
    _class_name = "GgafDx9SpriteMeshSetActor";
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
    _pUvFlipper->forcePtnNoRange(0, 1);
    _pUvFlipper->setPtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
}


void GgafDx9SpriteMeshSetActor::processDraw() {

    _draw_set_num = 1; //GgafDx9MeshSetModel�C���X�^���X���A�����Ă���J�E���g���B
                       //����`��[�x�͈�x�ɕ`�悷��B
    GgafDx9DrawableActor* _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
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
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_h_matView, &P_CAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_h_matView) �Ɏ��s���܂����B");
    //��{���f�����_��
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_vertexs_num, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetInt(_h_vertexs_num) �Ɏ��s���܂����B2");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    GgafDx9SpriteMeshSetActor* pA;
    float u = 0;
    float v = 0;
    for (int i = 0; i < _draw_set_num; i++) {
        //(*_pFunc_calcRotMvWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
#ifdef MY_DEBUG
        if (pDrawActor->_obj_class & Obj_GgafDx9SpriteMeshSetActor) {
            //OK
        } else {
            throwGgafCriticalException("GgafDx9SpriteMeshSetActor::processDraw() pDrawActor["<<pDrawActor->getName()<<"] ��GgafDx9SpriteMeshSetActor�ł͂���܂���B");
        }
#endif
        pA = (GgafDx9SpriteMeshSetActor*)pDrawActor; //TODO:���̃L���X�g�͊댯�ł���B
        //[MEMO]
        //GgafDx9SpriteMeshSetActor �́AGgafDx9MeshSetActor ����h�����Ă��邽�߁A���f���N���X�͓���GgafDx9MeshSetModel�ł���B
        //GgafDx9SpriteMeshSetActor���g�p���郂�f����("x/10/Flora"��)�ƁAGgafDx9MeshSetActor���g�p���郂�f������
        //�������̂����݂���ꍇ�ApDrawActor �́AGgafDx9MeshSetActor �̉\��������B
        //����́A_draw_set_num �����߂郍�W�b�N�͓���[�x�ŘA���̓���(�A�h���X)���f���ł���B�Ƃ������肵���s���Ă��Ȃ����߁B
        //���͂����ŁAGgafDx9SpriteMeshSetActor �� GgafDx9MeshSetActor �œ��ꃂ�f�������g�p���邱�Ƃ͋֎~�ɂ������̂ł���B
        //�{���� Actor �̎�ނɊ֌W�Ȃ��A���� Model �ŘA���Ȃ�΁A�X�e�[�g�؂�ւ��������������邱�Ƃ��E���ł���̂����A
        //GgafDx9SpriteMeshSetActor �́AGgafDx9MeshSetActor ����h�����Ă���ɂ�������炸�A�������G�t�F�N�g���̂�ύX���Ă���B
        //�����Ɏ�������Ȃ�΁A�ʕ��Ƃ��Ă��ꂼ��ʂ� Model �N���X���쐬����ׂ���������Ȃ����AModel�N���X�Ƃ��Ă̏������̂�
        //GgafDx9SpriteMeshSetActor�AGgafDx9MeshSetActor ���ɑS�������ŗǂ��B
        //�Y�񂾌��ʁAModel �N���X�𕪂��Ď��������A���댯�ȃL���X�g���s�����ƂƂ���B
        //�Ƃ肠����GgafDx9SpriteMeshSetActor �ƁAGgafDx9MeshSetActor �̃��f�����d�������Ȃ��悤�Ђ�����ӎ����邱�Ƃɂ���B
        //�f�o�b�N���[�h�ŏ\���e�X�g����B
        //Actor �͔h�����Ă���̂ɁAModel��Effect�́A�e��Actor�ƈႤ�A������Set�n�B����Ȋ֌W�ɒ��ӂ���B�i���[�U�[�`�b�v�Ƃ��E�E�E�j
        //TODO:�d�����Ȃ��悤�ɂ���d�g�݂��Ȃ�Ƃ�����

        //UV�I�t�Z�b�g�ݒ�
        pA->_pUvFlipper->getUV(u, v);
        hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetU[i], u);
        checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_u) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetV[i], v);
        checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_v) �Ɏ��s���܂����B");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);
}


GgafDx9SpriteMeshSetActor::~GgafDx9SpriteMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
