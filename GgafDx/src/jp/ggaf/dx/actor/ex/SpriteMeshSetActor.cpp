#include "jp/ggaf/dx/actor/ex/SpriteMeshSetActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name,
                                       const char* prm_model,
                                       CollisionChecker* prm_pChecker) :

                                               MeshSetActor(prm_name,
                                                            prm_model,
                                                            "SpriteMeshSetEffect",
                                                            "SpriteMeshSetTechnique",
                                                            prm_pChecker) {

    _obj_class |= Obj_GgafDx_SpriteMeshSetActor;
    _class_name = "SpriteMeshSetActor";

    Texture* pTexture = getModel()->getDefaultTextureConnection()->peek();
    _pUvFlipper = NEW UvFlipper(pTexture);
    _pUvFlipper->locatePatternNo(1, 1);
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
}


void SpriteMeshSetActor::processDraw() {

    int draw_set_num = 0; //SpriteMeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* const pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    FigureActor* pDrawActor = this;
    SpriteMeshSetActor* pSpriteMeshSetActor = nullptr;
    int model_draw_set_num = _pMeshSetModel->_draw_set_num;
    float u = 0;
    float v = 0;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pSpriteMeshSetActor = (SpriteMeshSetActor*)pDrawActor;

            hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pSpriteMeshSetActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[draw_set_num], &(pSpriteMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
            checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pDrawActor->instanceOf(Obj_GgafDx_SpriteMeshSetActor)) {
                //OK
            } else {
                throwCriticalException("pDrawActor["<<pDrawActor->getName()<<"] ��SpriteMeshSetActor�ł͂���܂���B");
            }
#endif
            //[MEMO]
            //SpriteMeshSetActor �́AMeshSetActor ����h�����Ă��邽�߁A���f���N���X�͓���MeshSetModel�ł���B
            //SpriteMeshSetActor���g�p���郂�f����("x,10,Flora"��)�ƁAMeshSetActor���g�p���郂�f������
            //�������̂����݂���ꍇ�ApDrawActor �́AMeshSetActor �̉\��������B
            //����́Adraw_set_num �����߂郍�W�b�N�͓���[�x�ŘA���̓���(�A�h���X)���f���ł���B�Ƃ������肵���s���Ă��Ȃ����߁B
            //���͂����ŁASpriteMeshSetActor �� MeshSetActor �œ��ꃂ�f�������g�p���邱�Ƃ͋֎~�ɂ������̂ł���B
            //�{���� Actor �̎�ނɊ֌W�Ȃ��A���� Model �ŘA���Ȃ�΁A�X�e�[�g�؂�ւ��������������邱�Ƃ��E���ł���̂����A
            //SpriteMeshSetActor �́AMeshSetActor ����h�����Ă���ɂ�������炸�A�������G�t�F�N�g���̂�ύX���Ă���B
            //�����Ɏ�������Ȃ�΁A�ʕ��Ƃ��Ă��ꂼ��ʂ� Model �N���X���쐬����ׂ���������Ȃ����AModel�N���X�Ƃ��Ă̏������̂�
            //SpriteMeshSetActor�AMeshSetActor ���ɑS�������ŗǂ��B
            //�Y�񂾌��ʁAModel �N���X�𕪂��Ď��������A���댯�ȃL���X�g���s�����ƂƂ���B
            //�Ƃ肠����SpriteMeshSetActor �ƁAMeshSetActor �̃��f�����d�������Ȃ��悤�Ђ�����ӎ����邱�Ƃɂ���B
            //�f�o�b�N���[�h�ŏ\���e�X�g����B
            //Actor �͔h�����Ă���̂ɁAModel��Effect�́A�e��Actor�ƈႤ�A������Set�n�B����Ȋ֌W�ɒ��ӂ���B�i���[�U�[�`�b�v�Ƃ��E�E�E�j
            //TODO:�d�����Ȃ��悤�ɂ���d�g�݂��Ȃ�Ƃ�����

            //UV�I�t�Z�b�g�ݒ�
            pSpriteMeshSetActor->_pUvFlipper->getUV(u, v);
            hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ah_offset_u[draw_set_num], u);
            checkDxException(hr, D3D_OK, "SetMatrix(_h_offset_u) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ah_offset_v[draw_set_num], v);
            checkDxException(hr, D3D_OK, "SetMatrix(_h_offset_v) �Ɏ��s���܂����B");

            draw_set_num++;
            if (draw_set_num >= model_draw_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    Spacetime::_pActor_draw_active = pSpriteMeshSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pMeshSetModel->MeshSetModel::draw(this, draw_set_num);
}


SpriteMeshSetActor::~SpriteMeshSetActor() {
    GGAF_DELETE(_pUvFlipper);
}
