#include "jp/ggaf/lib/actor/debug/ColliSphereActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliSphere.h"



using namespace GgafLib;

ColliSphereActor* ColliSphereActor::_pObj = nullptr;

ColliSphereActor::ColliSphereActor(const char* prm_name) : GgafDx::SphereActor(prm_name, nullptr) {
    _class_name = "ColliSphereActor";
    setAlpha(0.8);
}

ColliSphereActor* ColliSphereActor::get() {
    if (ColliSphereActor::_pObj == nullptr) {
        ColliSphereActor::_pObj = NEW ColliSphereActor("HITAREA");
    }
    return ColliSphereActor::_pObj;
}

void ColliSphereActor::release() {
    //�����蔻������I�u�W�F�N�g����x���g�p����Ȃ���nullptr��������Ȃ�
    GGAF_DELETE_NULLABLE(ColliSphereActor::_pObj);
}

void ColliSphereActor::drawHitarea(GgafDx::CollisionChecker* prm_pChecker) {
    if (prm_pChecker != nullptr &&
        prm_pChecker->_pActiveCollisionArea != nullptr &&
        prm_pChecker->getTargetActor()->canHit() &&
        prm_pChecker->getTargetActor()->isActiveInTheTree()) {
        GgafDx::GeometricActor* pActor = prm_pChecker->getTargetActor();
        GgafDx::CollisionArea* pActiveCollisionArea = prm_pChecker->_pActiveCollisionArea;

        int iAreaNum = pActiveCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            getEffect()->setAlphaMaster(1.0); //�V�[���ɏ������Ȃ��̂ŌŒ�l�̐ݒ肪�K�v
            for (int i = 0; i < iAreaNum; i++) {
                if (pActiveCollisionArea->_papColliPart[i]->_shape_kind == COLLI_SPHERE) {
                    ColliSphere* sphere = (ColliSphere*)pActiveCollisionArea->_papColliPart[i];
                    drawSphere(pActor->_x + sphere->_cx,
                               pActor->_y + sphere->_cy,
                               pActor->_z + sphere->_cz,
                               sphere->_r);
#ifdef MY_DEBUG
                    GgafCore::Caretaker::_num_draw--; //�����蔻��\���͕\���I�u�W�F�N�g���ɃJ�E���g���Ȃ�
#endif
                }
            }
        }

    }
}

ColliSphereActor::~ColliSphereActor() {
}
