#include "jp/ggaf/lib/actor/SingleLaser.h"

#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/effect/SingleLaserEffect.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


SingleLaser::SingleLaser(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
             GgafDxMeshSetActor(prm_name,
                                 std::string("26/" + std::string(prm_model_id)).c_str(),
                                 TYPE_MESHSET_MODEL,
                                 "SingleLaserEffect",
                                 TYPE_SINGLELASER_EFFECT,
                                 "SingleLaserTechnique",
                                 prm_pStat,
                                 UTIL::createChecker(this) ) {

    _pMeshSetModel->_set_num = 26; //���݂̃V���O�����[�U�[�̍ő�Z�b�g�������㏑���B

    _class_name = "SingleLaser";
    _pColliChecker = (CollisionChecker*)_pChecker;

    setZEnableDraw(true);    //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
}

void SingleLaser::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActor�̓������f���œ����e�N�j�b�N��
                          //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    SingleLaserEffect* pSingleLaserEffect = (SingleLaserEffect*)_pMeshSetEffect;
    ID3DXEffect* const pID3DXEffect = pSingleLaserEffect->_pID3DXEffect;
    HRESULT hr;
    //��{���f�����_��
    GgafDxFigureActor* pDrawActor = this;
    SingleLaser* pSingleLaserChip = nullptr;
    int model_Set_num = _pMeshSetModel->_set_num;

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
    GgafDxSpacetime::_pActor_draw_active = pSingleLaserChip; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pMeshSetModel->GgafDxMeshSetModel::draw(this, draw_set_num);
}

void SingleLaser::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

SingleLaser::~SingleLaser() {
    GGAF_DELETE(_pColliChecker);
}
