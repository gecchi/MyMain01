#include "jp/ggaf/lib/actor/SpriteMeshWorldBoundActor.h"

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SpriteMeshWorldBoundActor::SpriteMeshWorldBoundActor(const char* prm_name,
                                                     const char* prm_model,
                                                     GgafStatus* prm_pStat) :
        GgafDxSpriteMeshActor(prm_name,
                               prm_model,
                               prm_pStat,
                               nullptr) {

    _class_name = "SpriteMeshWorldBoundActor";
    changeEffectTechnique("NoLight"); //NoLight�Ńx�^�h��e�N�j�b�N
    setSpecialRenderDepthIndex(RENDER_DEPTH_INDEX_SP_BACK(1));
}

void SpriteMeshWorldBoundActor::processSettlementBehavior() {
    DefaultCamera* pCam = pGOD->getSpacetime()->getCamera();
    //��ʊO���薳���ɔ��Ȃ������ȗ����B
    //���̏����𖳎����Ă��܂�
    //�E���g���{�[�����̍l��
    //�E�����ؓo�^
    //�E�����䂩��̋����v�Z
    //GgafDxGeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    setPositionAt(pCam);
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    UTIL::setWorldMatrix_ScMv(this, _matWorld); //���[���h�ϊ�
}
//void SpriteMeshWorldBoundActor::processPreDraw() {
//    //��ʊO���薳���ɔ��Ȃ������ȗ���
//    //���̏����𖳎����Ă��܂�
//    //�E�i�K�����_�����O�̐[�x�v�Z
//    //�E�ꎞ�e�N�j�b�N�l��
//    //GgafDxFigureActor::processPreDraw() �Ɠ�������鎖�I
//    if (_pModel->_is_init_model == false) {
//        onCreateModel(); //���f���쐬���̏�������
//        _pModel->_is_init_model = true;
//    }
//    GgafDxSpacetime::registerFigureActor(REGULAR_RENDER_DEPTH_INDEXS_NUM,this); //�Ő[��
//}

SpriteMeshWorldBoundActor::~SpriteMeshWorldBoundActor() {
}

