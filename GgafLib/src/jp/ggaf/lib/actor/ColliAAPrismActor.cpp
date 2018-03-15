#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"

#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliAAPrismActor* ColliAAPrismActor::_pObj = nullptr;

ColliAAPrismActor::ColliAAPrismActor(const char* prm_name, GgafStatus* prm_pStat) : GgafDxAAPrismActor(prm_name, prm_pStat, nullptr) {
    _class_name = "ColliAAPrismActor";
    setAlpha(0.8);
}

ColliAAPrismActor* ColliAAPrismActor::get() {
    if (ColliAAPrismActor::_pObj == nullptr) {
        ColliAAPrismActor::_pObj = NEW ColliAAPrismActor("HITAREA", nullptr);
    }
    return ColliAAPrismActor::_pObj;
}

void ColliAAPrismActor::release() {
    //�����蔻������I�u�W�F�N�g����x���g�p����Ȃ���nullptr��������Ȃ�
    GGAF_DELETE_NULLABLE(ColliAAPrismActor::_pObj);
}

void ColliAAPrismActor::drawHitarea(CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != nullptr &&
        prm_pColliChecker->_pCollisionArea != nullptr &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDxGeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDxCollisionArea* pCollisionArea = prm_pColliChecker->_pCollisionArea;
        int iAreaNum = pCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            getEffect()->setAlphaMaster(1.0); //�V�[���ɏ������Ȃ��̂ŌŒ�l�̐ݒ肪�K�v
            for (int i = 0; i < iAreaNum; i++) {
                if (pCollisionArea->_papColliPart[i]->_is_valid_flg && pCollisionArea->_papColliPart[i]->_shape_kind == COLLI_AAPRISM) {
                    ColliAAPrism* prism = (ColliAAPrism*)pCollisionArea->_papColliPart[i];
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
                    GgafGod::_num_drawing--; //�����蔻��\���͕\���I�u�W�F�N�g���ɃJ�E���g���Ȃ�
#endif
                }
            }
        }

    }
}

ColliAAPrismActor::~ColliAAPrismActor() {
}
