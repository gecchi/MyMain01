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

    GgafDx9Texture* pTexture = _pMeshSetModel->_papTextureCon[0]->refer();
    _pUvFlipper = NEW GgafDx9UvFlipper(pTexture);
    _pUvFlipper->setRotation(1, 1);
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
}


void GgafDx9SpriteMeshSetActor::processDraw() {

    _draw_set_num = 0; //GgafDx9SpriteMeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDx9DrawableActor* pDrawActor = this;
    GgafDx9SpriteMeshSetActor* pSpriteMeshSetActor = NULL;
    float u = 0;
    float v = 0;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pGgafDx9Model == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pSpriteMeshSetActor = (GgafDx9SpriteMeshSetActor*)pDrawActor;

                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[_draw_set_num], &(pSpriteMeshSetActor->_matWorld));
                checkDxException(hr, D3D_OK, "GgafDx9SpriteMeshSetActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[_draw_set_num], &(pSpriteMeshSetActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
                checkDxException(hr, D3D_OK, "GgafDx9SpriteMeshSetActor::processDraw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
        #ifdef MY_DEBUG
                if (pDrawActor->_obj_class & Obj_GgafDx9SpriteMeshSetActor) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDx9SpriteMeshSetActor::processDraw() pDrawActor["<<pDrawActor->getName()<<"] ��GgafDx9SpriteMeshSetActor�ł͂���܂���B");
                }
        #endif
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
                pSpriteMeshSetActor->_pUvFlipper->getUV(u, v);
                hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetU[_draw_set_num], u);
                checkDxException(hr, D3D_OK, "GgafDx9SpriteMeshSetActor::processDraw() SetMatrix(_h_offset_u) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetV[_draw_set_num], v);
                checkDxException(hr, D3D_OK, "GgafDx9SpriteMeshSetActor::processDraw() SetMatrix(_h_offset_v) �Ɏ��s���܂����B");


                _draw_set_num++;
                if (_draw_set_num >= _pMeshSetModel->_set_num) {
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
    GgafDx9Universe::_pActor_DrawActive = pSpriteMeshSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pMeshSetModel->draw(this, _draw_set_num);
}


GgafDx9SpriteMeshSetActor::~GgafDx9SpriteMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
