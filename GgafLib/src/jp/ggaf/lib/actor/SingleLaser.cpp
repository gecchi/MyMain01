#include "jp/ggaf/lib/actor/SingleLaser.h"

#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/effect/SingleLaserEffect.h"


using namespace GgafLib;

//���ӁFSingleLaser SetNum �̍ő�� 26 �Ɉ����グ����B��`����26��ݒ萄��
SingleLaser::SingleLaser(const char* prm_name, const char* prm_model) :
             GgafDx::MeshSetActor(prm_name,
                                  prm_model,
                                  TYPE_MESHSET_MODEL,
                                  "SingleLaserEffect",
                                  TYPE_SINGLELASER_EFFECT,
                                  "SingleLaserTechnique",
                                  UTIL::createChecker(this) ) {
//    _pMeshSetModel->_draw_set_num = 26; //���݂̃V���O�����[�U�[�̍ő�Z�b�g�������㏑���B
    _class_name = "SingleLaser";
    _pColliChecker = (CollisionChecker*)_pChecker;

    setZEnableDraw(true);    //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
}

void SingleLaser::processDraw() {
    int draw_set_num = 0; //MeshSetActor�̓������f���œ����e�N�j�b�N��
                          //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    SingleLaserEffect* pSingleLaserEffect = (SingleLaserEffect*)_pMeshSetEffect;
    ID3DXEffect* const pID3DXEffect = pSingleLaserEffect->_pID3DXEffect;
    HRESULT hr;
    //��{���f�����_��
    GgafDx::FigureActor* pDrawActor = this;
    SingleLaser* pSingleLaserChip = nullptr;
    int model_Set_num = _pMeshSetModel->_draw_set_num;

    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pSingleLaserChip = (SingleLaser*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(pSingleLaserEffect->_ah_matWorld[draw_set_num], &(pSingleLaserChip->_matWorld));
            checkDxException(hr, D3D_OK, "pDrawActor->_matWorld="<<pDrawActor->_matWorld<<" pDrawActor="<<pDrawActor->getName()<<" draw_set_num="<<draw_set_num<<" �Ɏ��s���܂����B");
            draw_set_num++;
            if (draw_set_num >= model_Set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    GgafDx::Spacetime::_pActor_draw_active = pSingleLaserChip; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pMeshSetModel->GgafDx::MeshSetModel::draw(this, draw_set_num);
}

void SingleLaser::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

SingleLaser::~SingleLaser() {
    GGAF_DELETE(_pColliChecker);
}
