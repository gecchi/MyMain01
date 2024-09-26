#include "jp/ggaf/lib/util/WorldCollisionChecker2D.h"

#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

WorldCollisionChecker2D::WorldCollisionChecker2D(GgafDx::GeometricActor* prm_pActor) : WorldCollisionChecker(prm_pActor)
{
}

void WorldCollisionChecker2D::updateHitArea() {
    GgafDx::CollisionArea* const pActiveCollisionArea = _pCollisionArea;
    if (pActiveCollisionArea == nullptr) {
        return;
    }
    GgafDx::GeometricActor* const pActor = _pColliActor;
    if (pActor->isActiveInTheTree()) {
        //�l���؂ɓo�^�I
#ifdef MY_DEBUG
        if (_kind == 0) {
            _TRACE_("�y�x���z WorldCollisionChecker2D::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")�̎�ʂ�0�ɂ�������炸�A�����؂ɓo�^���悤�Ƃ��Ă��܂��B�Ȃ��ł����H�B");
        }
#endif
        pActiveCollisionArea->updateAABB(pActor->_rx, pActor->_ry, pActor->_rz); //�ŊO��̋��EAABB�X�V
        DefaultSpacetime::_pWorldQuadtree->registerElem(this, pActor->_x + pActiveCollisionArea->_aabb_x1,
                                                                pActor->_y + pActiveCollisionArea->_aabb_y1,
                                                                pActor->_x + pActiveCollisionArea->_aabb_x2,
                                                                pActor->_y + pActiveCollisionArea->_aabb_y2);
#ifdef MY_DEBUG
        WorldCollisionChecker::_num_check_actors++;
#endif

    }
}

bool WorldCollisionChecker2D::isHit(const GgafDx::CollisionChecker* const prm_pOppChecker) {
    GgafDx::CollisionArea* const pActiveCollisionArea = _pCollisionArea;
    GgafDx::CollisionArea* const pOppActiveCollisionArea = prm_pOppChecker->_pCollisionArea; //����̓����蔻��̈�
    const GgafDx::GeometricActor* const pActor = _pColliActor;                //����̃A�N�^�[
    const GgafDx::GeometricActor* const pOppActor = prm_pOppChecker->_pColliActor;                //����̃A�N�^�[
    const int colli_part_num = pActiveCollisionArea->_colli_part_num;
    const int opp_colli_part_num = pOppActiveCollisionArea->_colli_part_num; //����̓����蔻��v�f��
    const coord pActor_x = pActor->_x;
    const coord pActor_y = pActor->_y;
    const coord pOppActor_x = pOppActor->_x;
    const coord pOppActor_y = pOppActor->_y;
    //�����̓����蔻��v�f�����A�N�^�[���m�̏ꍇ�A
    //�܂��ŊO���EAABox�œ����蔻����s���āA�q�b�g����Ό����ɓ����蔻����s���B
    if (colli_part_num > 2 && opp_colli_part_num > 2) {
#ifdef MY_DEBUG
        WorldCollisionChecker::_num_check++;
#endif
        if (pActor_x + pActiveCollisionArea->_aabb_x2 >= pOppActor_x + pOppActiveCollisionArea->_aabb_x1) {
            if (pActor_x + pActiveCollisionArea->_aabb_x1 <= pOppActor_x + pOppActiveCollisionArea->_aabb_x2) {
                if (pActor_y + pActiveCollisionArea->_aabb_y2 >= pOppActor_y + pOppActiveCollisionArea->_aabb_y1) {
                    if (pActor_y + pActiveCollisionArea->_aabb_y1 <= pOppActor_y + pOppActiveCollisionArea->_aabb_y2) {
#ifdef MY_DEBUG
                        WorldCollisionChecker::_num_zannen_check++;
#endif
                        goto CNT;
                    }
                }
            }
        }
#ifdef MY_DEBUG
        WorldCollisionChecker::_num_otoku_check++;
        WorldCollisionChecker::_num_otoku_check_actors += (colli_part_num*opp_colli_part_num);
#endif
        return false;
    }

CNT:

    for (int i = 0; i < colli_part_num; i++) {
        const GgafDx::CollisionPart* const pColliPart = pActiveCollisionArea->_papColliPart[i];
        const int shape_kind = pColliPart->_shape_kind;

        if (shape_kind == COLLI_AABOX) {

            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //�������` �� �����`��
                    if (UTIL::isHit2D(pActor   , (ColliAABox*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart)) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //�������` �� �~��
                     if (UTIL::isHit2D(pActor   , (ColliAABox*)pColliPart,
                                       pOppActor, (ColliSphere*)pOppColliPart)) {
                         pActiveCollisionArea->_hit_colli_part_index = i;
                         pOppActiveCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //�������` �� ���p�O�p�`��
                     if (UTIL::isHit2D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                       pActor   , (ColliAABox*)pColliPart        )) {
                         pActiveCollisionArea->_hit_colli_part_index = i;
                         pOppActiveCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                     //�������` �� AAPyramid��
                    _TRACE_("�y�x���z2D�� AAB �� AAPyramid �̓����蔻�菈�������݂��܂��BAAPyramid��2D�����蔻��͂���܂��� "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                 }
            }
        } else if (shape_kind == COLLI_SPHERE) {
            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //���~ �� �����`��
                    if (UTIL::isHit2D(pOppActor, (ColliAABox*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart )) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //���~ �� �~��
                    if (UTIL::isHit2D(pActor  , (ColliSphere*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //���~ �� ���p�O�p�`��
                    if (UTIL::isHit2D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart     )) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //���~ �� ���p�O�p�`��
                    _TRACE_("�y�x���z2D�� �� �� AAPyramid �̓����蔻�菈�������݂��܂��BAAPyramid��2D�����蔻��͂���܂��� "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                }
            }
        } else if (shape_kind == COLLI_AAPRISM) {
            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //�����p�O�p�` �� �����`��
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart  )) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //�����p�O�p�` �� �~��
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }  else if (opp_shape_kind == COLLI_AAPRISM) {
                    //�����p�O�p�` �� ���p�O�p�`��
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliAAPrism*)pOppColliPart)) {
                        pActiveCollisionArea->_hit_colli_part_index = i;
                        pOppActiveCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //�����p�O�p�` �� AAPyramid��
                    _TRACE_("�y�x���z2D�� AAPrism �� AAPyramid �̓����蔻�菈�������݂��܂��BAAPyramid��2D�����蔻��͂���܂��� "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                 }
            }
        } else if (shape_kind == COLLI_AAPYRAMID) {
            _TRACE_("�y�x���z2D�� AAPyramid �̓����蔻�菈�������݂��܂��BAAPyramid��2D�����蔻��͂���܂��� "<<
                    pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
            return false;
        }
    }
    return false;
}


WorldCollisionChecker2D::~WorldCollisionChecker2D() {
}
