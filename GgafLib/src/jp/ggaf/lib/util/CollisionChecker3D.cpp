#include "jp/ggaf/lib/util/CollisionChecker3D.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/util/LinearOctree.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

CollisionChecker3D::CollisionChecker3D(GgafDx::GeometricActor* prm_pActor) : CollisionChecker(prm_pActor) ,
        _pLinearOctree(pGOD->getSpacetime()->getLinearOctree()),
        _pElem(NEW GgafCore::TreeElem<3u>(_pLinearOctree->_paOctant, prm_pActor))
{
}

void CollisionChecker3D::updateHitArea() {
    GgafDx::CollisionArea* const pCollisionArea = _pCollisionArea;
    if (pCollisionArea == nullptr) {
        return;
    }
    GgafDx::GeometricActor* const pActor = _pActor;
    if (pActor->isActiveInTheTree()) {
        //�����؂ɓo�^�I
        _pElem->_kind = pActor->lookUpKind();
#ifdef MY_DEBUG
        if (_pElem->_kind == 0) {
            _TRACE_("���x���� CollisionChecker3D::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")�̎�ʂ�0�ɂ�������炸�A�����؂ɓo�^���悤�Ƃ��Ă��܂��B�Ȃ��ł����H�B");
        }
#endif
        pCollisionArea->updateAABB(pActor->_rx, pActor->_ry, pActor->_rz); //�ŊO��̋��EAABB�X�V
        _pLinearOctree->registerElem(_pElem, pActor->_x + pCollisionArea->_aabb_x1,
                                             pActor->_y + pCollisionArea->_aabb_y1,
                                             pActor->_z + pCollisionArea->_aabb_z1,
                                             pActor->_x + pCollisionArea->_aabb_x2,
                                             pActor->_y + pCollisionArea->_aabb_y2,
                                             pActor->_z + pCollisionArea->_aabb_z2);

    }
}

bool CollisionChecker3D::isHit(const GgafDx::Checker* const prm_pOppChecker) {
    GgafDx::CollisionArea* const pCollisionArea = _pCollisionArea;
    GgafDx::CollisionArea* const pOppCollisionArea = prm_pOppChecker->_pCollisionArea; //����̓����蔻��̈�
    const GgafDx::GeometricActor* const pActor = _pActor;                //����̃A�N�^�[
    const GgafDx::GeometricActor* const pOppActor = prm_pOppChecker->_pActor;                //����̃A�N�^�[
    const int colli_part_num = pCollisionArea->_colli_part_num;
    const int opp_colli_part_num = pOppCollisionArea->_colli_part_num; //����̓����蔻��v�f��

    //�����̓����蔻��v�f�����A�N�^�[���m�̏ꍇ�A
    //�܂��ŊO���EAABox�œ����蔻����s���āA�q�b�g����Ό����ɓ����蔻����s���B
    if (colli_part_num > 3 || opp_colli_part_num > 3) {
#ifdef MY_DEBUG
        CollisionChecker::_num_check++;
#endif
        if (pActor->_x + pCollisionArea->_aabb_x2 >= pOppActor->_x + pOppCollisionArea->_aabb_x1) {
            if (pActor->_x + pCollisionArea->_aabb_x1 <= pOppActor->_x + pOppCollisionArea->_aabb_x2) {
                if (pActor->_z + pCollisionArea->_aabb_z2 >= pOppActor->_z + pOppCollisionArea->_aabb_z1) {
                    if (pActor->_z + pCollisionArea->_aabb_z1 <= pOppActor->_z + pOppCollisionArea->_aabb_z2) {
                        if (pActor->_y + pCollisionArea->_aabb_y2 >= pOppActor->_y + pOppCollisionArea->_aabb_y1) {
                            if (pActor->_y + pCollisionArea->_aabb_y1 <= pOppActor->_y + pOppCollisionArea->_aabb_y2) {
                                goto CNT;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

CNT:
    for (int i = 0; i < colli_part_num; i++) {
        const GgafDx::CollisionPart* const pColliPart = pCollisionArea->_papColliPart[i];
        if (!pColliPart->_is_valid_flg) { continue; }
        for (int j = 0; j < opp_colli_part_num; j++) {
            const GgafDx::CollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
            if (!pOppColliPart->_is_valid_flg) { continue; }
#ifdef MY_DEBUG
            CollisionChecker::_num_check++;
#endif
            bool is_hit = (*UTIL::hit_check3d_func_table[pColliPart->_shape_kind | pOppColliPart->_shape_kind])(
                    pActor, pColliPart, pOppActor, pOppColliPart);
            if (is_hit) {
                pCollisionArea->_hit_colli_part_index = i;
                pOppCollisionArea->_hit_colli_part_index = j;
                return true;
            }
        }
    }
    return false;
}


CollisionChecker3D::~CollisionChecker3D() {
    delete _pElem;
    //�����蔻��͂Ȃ���������Ȃ��B���̏ꍇ_pElem�͖��ʂȐ����Ɖ�������邱�ƂɂȂ�B�B
}
