#include "jp/ggaf/lib/actor/debug/ColliAAPyramidActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"

using namespace GgafLib;

ColliAAPyramidActor* ColliAAPyramidActor::_pObj = nullptr;

ColliAAPyramidActor::ColliAAPyramidActor(const char* prm_name) : GgafDx::AAPyramidActor(prm_name) {
    _class_name = "ColliAAPyramidActor";
    setAlpha(0.8);
    useZBufferDrawing(false);      //�`�掞�AZ�o�b�t�@�l�͍l�����Ȃ�
    setZBufferWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    setCullingDraw(false);
}

ColliAAPyramidActor* ColliAAPyramidActor::get() {
    if (ColliAAPyramidActor::_pObj == nullptr) {
        ColliAAPyramidActor::_pObj = NEW ColliAAPyramidActor("HITAREA");
    }
    return ColliAAPyramidActor::_pObj;
}

void ColliAAPyramidActor::release() {
    //�����蔻������I�u�W�F�N�g����x���g�p����Ȃ���nullptr��������Ȃ�
    GGAF_DELETE_NULLABLE(ColliAAPyramidActor::_pObj);
}

void ColliAAPyramidActor::drawHitarea(GgafDx::CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != nullptr &&
        prm_pColliChecker->_pCollisionArea != nullptr &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDx::GeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDx::CollisionArea* pActiveCollisionArea = prm_pColliChecker->_pCollisionArea;
        int iAreaNum = pActiveCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            getEffect()->setAlphaMaster(1.0); //�V�[���ɏ������Ȃ��̂ŌŒ�l�̐ݒ肪�K�v
            for (int i = 0; i < iAreaNum; i++) {
                if (pActiveCollisionArea->_papColliPart[i]->_shape_kind == COLLI_AAPYRAMID) {
                    ColliAAPyramid* pyramid = (ColliAAPyramid*)pActiveCollisionArea->_papColliPart[i];
                    if (pyramid->_pos_info < 0) {
                        _TRACE_("�y�x���zColliAAPyramidActor::drawHitarea BADPOS i="<<i<<" Target="<<pActor->getName()<<" �v����");
                    } else {
                        drawPyramid(pActor->_x + pyramid->_x1,
                                    pActor->_y + pyramid->_y1,
                                    pActor->_z + pyramid->_z1,
                                    pActor->_x + pyramid->_x2,
                                    pActor->_y + pyramid->_y2,
                                    pActor->_z + pyramid->_z2,
                                    pyramid->_pos_info);
                    }
#ifdef MY_DEBUG
                    GgafCore::Caretaker::_num_draw--; //�����蔻��\���͕\���I�u�W�F�N�g���ɃJ�E���g���Ȃ�
#endif
                }
            }
        }

    }
}

ColliAAPyramidActor::~ColliAAPyramidActor() {
}
