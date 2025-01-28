#include "jp/ggaf/lib/actor/debug/ColliAAPrismActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"



using namespace GgafLib;

ColliAAPrismActor* ColliAAPrismActor::_pObj = nullptr;

ColliAAPrismActor::ColliAAPrismActor(const char* prm_name) : GgafDx::AAPrismActor(prm_name) {
    _class_name = "ColliAAPrismActor";
    setAlpha(0.8);
    useZBufferDrawing(false);      //�`�掞�AZ�o�b�t�@�l�͍l�����Ȃ�
    setZBufferWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    setCullingDraw(false);
}

ColliAAPrismActor* ColliAAPrismActor::get() {
    if (ColliAAPrismActor::_pObj == nullptr) {
        ColliAAPrismActor::_pObj = NEW ColliAAPrismActor("HITAREA");
    }
    return ColliAAPrismActor::_pObj;
}

void ColliAAPrismActor::release() {
    //�����蔻������I�u�W�F�N�g����x���g�p����Ȃ���nullptr��������Ȃ�
    GGAF_DELETE_NULLABLE(ColliAAPrismActor::_pObj);
}

void ColliAAPrismActor::drawHitarea(GgafDx::CollisionChecker* prm_pColliChecker) {
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
                if (pActiveCollisionArea->_papColliPart[i]->_shape_kind == COLLI_AAPRISM) {
                    ColliAAPrism* prism = (ColliAAPrism*)pActiveCollisionArea->_papColliPart[i];
                    if (prism->_pos_info == 0) {
                        _TRACE_("�y�x���zColliAAPrismActor::drawHitarea BADPOS i="<<i<<" Target="<<pActor->getName()<<" �v����");
                    } else {
                        drawPrism(pActor->_x + prism->_x1,
                                  pActor->_y + prism->_y1,
                                  pActor->_z + prism->_z1,
                                  pActor->_x + prism->_x2,
                                  pActor->_y + prism->_y2,
                                  pActor->_z + prism->_z2,
                                  prism->_pos_info); //TODO:prism->_pos_info �� 0 �� pos2r[pos_info]._ry ���������Ȓl�ŗ�����
                    }
#ifdef MY_DEBUG
                    GgafCore::Caretaker::_num_draw--; //�����蔻��\���͕\���I�u�W�F�N�g���ɃJ�E���g���Ȃ�
#endif
                }
            }
        }

    }
}

ColliAAPrismActor::~ColliAAPrismActor() {
}
