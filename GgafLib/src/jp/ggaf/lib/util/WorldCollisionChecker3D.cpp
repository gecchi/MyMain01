#include "jp/ggaf/lib/util/WorldCollisionChecker3D.h"

#include "jp/ggaf/core/util/lineartree/LinearOctree.hpp"
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

WorldCollisionChecker3D::WorldCollisionChecker3D(GgafDx::GeometricActor* prm_pActor, kind_t prm_kind) : WorldCollisionChecker(prm_pActor, prm_kind)
{
}

void WorldCollisionChecker3D::updateHitArea() {
    GgafDx::CollisionArea* const pActiveCollisionArea = _pCollisionArea;
    if (pActiveCollisionArea == nullptr) {
        return;
    }
    GgafDx::GeometricActor* const pActor = _pColliActor;
    if (pActor->isActiveInTheTree()) {
#ifdef MY_DEBUG
        if (_kind == 0) {
            _TRACE_("�y�x���z WorldCollisionChecker3D::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")�̎�ʂ�0�ɂ�������炸�A�����؂ɓo�^���悤�Ƃ��Ă��܂��B�Ȃ��ł����H�B");
        }
#endif
        pActiveCollisionArea->updateAABB(pActor->_rx, pActor->_ry, pActor->_rz); //�ŊO��̋��EAABB�X�V
        DefaultSpacetime::_pWorldOctree->registerElem(this, pActor->_x + pActiveCollisionArea->_aabb_x1,
                                                            pActor->_y + pActiveCollisionArea->_aabb_y1,
                                                            pActor->_z + pActiveCollisionArea->_aabb_z1,
                                                            pActor->_x + pActiveCollisionArea->_aabb_x2,
                                                            pActor->_y + pActiveCollisionArea->_aabb_y2,
                                                            pActor->_z + pActiveCollisionArea->_aabb_z2);
#ifdef MY_DEBUG
        WorldCollisionChecker::_num_check_actors++;
#endif
    }
}



//StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
//                     const GgafDx::GeometricActor* const pActor02, const ColliSphere*    const pSphere02

//bool (*pFunc_isHit3D)(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*) = &(StgUtil::isHit3D);


//bool (*pFunc_isHit3D_2)(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//
//
//bool (*pFunc_isHit3D)(const GgafDx::GeometricActor*, const ColliAAPyramid* ,const GgafDx::GeometricActor* , const ColliSphere* ) = &(StgUtil::isHit3D);

//bool (*pFunc_isHit3D_2)(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*) = &(StgUtil::isHit3D);
//pFunc_isHit3D = &(StgUtil::isHit3D)(GgafDx::GeometricActor*, ColliAAPyramid* ,GgafDx::GeometricActor* , ColliSphere* );

//void (*prm_pFuncFeature)(GgafCore::Object*, void*, void*, void*) = &(CommonScene::scrollX);


//bool StgUtil::isHit3D_Box_Box(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Box_Sphere(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Box_Prism(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Sphere_Sphere(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Sphere_Prism(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Prism_Prism(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);

//bool StgUtil::isHit3D_Box_Box(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Box_Sphere(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Box_Prism(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Sphere_Box(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Sphere_Sphere(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Sphere_Prism(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Pris_Box(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Pris_Sphere(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);
//bool StgUtil::isHit3D_Pris_Prism(const GgafDx::GeometricActor*, const GgafDx::CollisionPart*, const GgafDx::GeometricActor*, const GgafDx::CollisionPart*);

//bool (*pFunc_isHit3D[])(const GgafDx::GeometricActor*, const ColliAAPyramid* ,const GgafDx::GeometricActor* , const ColliSphere* ) = {
//        &(StgUtil::isHit3D_Box_Box),
//        &(StgUtil::isHit3D_Box_Sphere),
//        ...
//
//};

//                int shape_kind_bit = (shape_kind << 4) | opp_shape_kind;
//                pFunc_isHit3D[shape_kind_bit](.....);

bool WorldCollisionChecker3D::isHit(const GgafDx::CollisionChecker* const prm_pOppChecker) {
    GgafDx::CollisionArea* const pActiveCollisionArea = _pCollisionArea;
    GgafDx::CollisionArea* const pOppActiveCollisionArea = prm_pOppChecker->_pCollisionArea; //����̓����蔻��̈�
    const GgafDx::GeometricActor* const pActor = _pColliActor;                //����̃A�N�^�[
    const GgafDx::GeometricActor* const pOppActor = prm_pOppChecker->_pColliActor;                //����̃A�N�^�[
    const int colli_part_num = pActiveCollisionArea->_colli_part_num;
    const int opp_colli_part_num = pOppActiveCollisionArea->_colli_part_num; //����̓����蔻��v�f��
    const coord pActor_x = pActor->_x;
    const coord pActor_y = pActor->_y;
    const coord pActor_z = pActor->_z;
    const coord pOppActor_x = pOppActor->_x;
    const coord pOppActor_y = pOppActor->_y;
    const coord pOppActor_z = pOppActor->_z;
    //�����̓����蔻��v�f�����A�N�^�[���m�̏ꍇ�A
    //�܂��ŊO���EAABox�œ����蔻����s���āA�q�b�g����Ό����ɓ����蔻����s���B
    if (colli_part_num > 1 || opp_colli_part_num > 1) {
#ifdef MY_DEBUG
        WorldCollisionChecker::_num_check++;
#endif
        if (pActor_x + pActiveCollisionArea->_aabb_x2 >= pOppActor_x + pOppActiveCollisionArea->_aabb_x1 &&
            pActor_x + pActiveCollisionArea->_aabb_x1 <= pOppActor_x + pOppActiveCollisionArea->_aabb_x2 &&
            pActor_z + pActiveCollisionArea->_aabb_z2 >= pOppActor_z + pOppActiveCollisionArea->_aabb_z1 &&
            pActor_z + pActiveCollisionArea->_aabb_z1 <= pOppActor_z + pOppActiveCollisionArea->_aabb_z2 &&
            pActor_y + pActiveCollisionArea->_aabb_y2 >= pOppActor_y + pOppActiveCollisionArea->_aabb_y1 &&
            pActor_y + pActiveCollisionArea->_aabb_y1 <= pOppActor_y + pOppActiveCollisionArea->_aabb_y2
        ) {
#ifdef MY_DEBUG
            WorldCollisionChecker::_num_zannen_check++;
#endif
            goto CNT;
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
        pActiveCollisionArea->_hit_colli_part_index = i;
        if (shape_kind == COLLI_AABOX) {

            for (int j = 0; j < opp_colli_part_num; j++) {
                pOppActiveCollisionArea->_hit_colli_part_index = j;
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;

#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //��AAB �� AAB��
                    coord max_dx = pColliPart->_hdx + pOppColliPart->_hdx;
                    if ((ucoord)( (pOppActor_x + pOppColliPart->_cx) - (pActor_x + pColliPart->_cx) + max_dx ) < (ucoord)(max_dx<<1)) {
                        //�����ӌv�Z��0��菬�����ꍇ unsigned �L���X�g�ɂ�萳�̑傫�Ȑ��ɂȂ�̂ŏ����������Ȃ����𗘗p���AABS�̔������������Ă�B
                        //BOX vs BOX �̓����蔻��p�x�̓p�t�H�[�}���X�ɑ傫�ȉe����^���邽�߁A�킸���ł����������������߁B
                        coord max_dz = pColliPart->_hdz + pOppColliPart->_hdz;
                        if ((ucoord)( (pOppActor_z + pOppColliPart->_cz) - (pActor_z + pColliPart->_cz) + max_dz ) < (ucoord)(max_dz<<1)) {
                            coord max_dy = pColliPart->_hdy + pOppColliPart->_hdy;
                            if ((ucoord)( (pOppActor_y + pOppColliPart->_cy) - (pActor_y + pColliPart->_cy) + max_dy ) < (ucoord)(max_dy<<1)) {
                                return true;
                            }
                        }
                    }
//                    if (UTIL::isHit3D(pActor   , (ColliAABox*)pColliPart,
//                                      pOppActor, (ColliAABox*)pOppColliPart)) {
//                        pActiveCollisionArea->_hit_colli_part_index = i;
//                        pOppActiveCollisionArea->_hit_colli_part_index = j;
//                        return true;
//                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //��AAB �� ����
                     if (UTIL::isHit3D(pActor   , (ColliAABox*)pColliPart,
                                       pOppActor, (ColliSphere*)pOppColliPart)) {
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //��AAB �� AAPrism��
                     if (UTIL::isHit3D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                       pActor   , (ColliAABox*)pColliPart        )) {
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                     //��AAB �� AAPyramid��
                     if (UTIL::isHit3D(pOppActor, (ColliAAPyramid*)pOppColliPart,
                                       pActor   , (ColliAABox*)pColliPart        )) {
                         return true;
                     }
                 }
            }
        } else if (shape_kind == COLLI_SPHERE) {
            for (int j = 0; j < opp_colli_part_num; j++) {
                pOppActiveCollisionArea->_hit_colli_part_index = j;
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //���� �� AAB��
                    if (UTIL::isHit3D(pOppActor, (ColliAABox*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart )) {
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //���� �� ����
                    //��1 �F ���S�_�̍��WP1(x1, y1, z1), ���ar1
                    //��2 �F ���S�_�̍��WP2(x2, y2, z2), ���ar2
                    //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
                    double dx = (double)( (pActor_x+pColliPart->_cx) - (pOppActor_x+pOppColliPart->_cx) );
                    double dy = (double)( (pActor_y+pColliPart->_cy) - (pOppActor_y+pOppColliPart->_cy) );
                    double dz = (double)( (pActor_z+pColliPart->_cz) - (pOppActor_z+pOppColliPart->_cz) );
                    double dd = dx*dx + dy*dy + dz*dz;
                    if (dd <= (double)(((ColliSphere*)pColliPart)->_r + ((ColliSphere*)pOppColliPart)->_r) *
                              (double)(((ColliSphere*)pColliPart)->_r + ((ColliSphere*)pOppColliPart)->_r)
                    ) {
                        return true;
                    }
//                    if (UTIL::isHit3D(pActor  , (ColliSphere*)pColliPart,
//                                      pOppActor, (ColliSphere*)pOppColliPart)) {
//                        pActiveCollisionArea->_hit_colli_part_index = i;
//                        pOppActiveCollisionArea->_hit_colli_part_index = j;
//                        return true;
//                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //���� �� AAPrism��
                    if (UTIL::isHit3D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart     )) {
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //���� �� AAPyramid��
                    if (UTIL::isHit3D(pOppActor, (ColliAAPyramid*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart     )) {
                        return true;
                    }
                }
            }
        } else if (shape_kind == COLLI_AAPRISM) {
            for (int j = 0; j < opp_colli_part_num; j++) {
                pOppActiveCollisionArea->_hit_colli_part_index = j;
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //��AAPrism �� AAB��
                    if (UTIL::isHit3D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart  )) {
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //��AAPrism �� ����
                    if (UTIL::isHit3D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        return true;
                    }
                }  else if (opp_shape_kind == COLLI_AAPRISM) {
                    //��AAPrism �� AAPrism��
                    //TODO:���Ή��B �l���邾���ŏd�����Ȃ肻���A�Ƃ������߂�ǂ��������Ȋ���������G�B
                    //���Ԃ�����΍l���悤�E�E�E
                    _TRACE_("�y�x���zAAPrism �� AAPrism �̓����蔻�菈�������݂��܂��B����ȏ����͖�������Ă܂���B "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //��AAPrism �� AAPyramid��
                    //TODO: ���͖��Ή��B
                    _TRACE_("�y�x���zAAPrism �� AAPyramid �̓����蔻�菈�������݂��܂��B����ȏ����͖�������Ă܂���B "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                }
            }
        } else if (shape_kind == COLLI_AAPYRAMID) {
            for (int j = 0; j < opp_colli_part_num; j++) {
                pOppActiveCollisionArea->_hit_colli_part_index = j;
                const GgafDx::CollisionPart* const pOppColliPart = pOppActiveCollisionArea->_papColliPart[j];
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //��AAPyramid �� AAB��
                    if (UTIL::isHit3D(pActor   , (ColliAAPyramid*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart  )) {
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //��AAPyramid �� ����
                    if (UTIL::isHit3D(pActor   , (ColliAAPyramid*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //��AAPyramid �� AAPrism��
                    //TODO: ���͖��Ή��B
                    _TRACE_("�y�x���zAAPyramid �� AAPrism �̓����蔻�菈�������݂��܂��B����ȏ����͖�������Ă܂���B "<<
                            pActor <<"["<<_pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //��AAPyramid �� AAPyramid��
                    //TODO: ���͖��Ή��B
                    _TRACE_("�y�x���zAAPyramid �� AAPyramid �̓����蔻�菈�������݂��܂��B����ȏ����͖�������Ă܂���B "<<
                            pActor <<"["<<_pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                }
            }
        }
    }
    return false;
}


WorldCollisionChecker3D::~WorldCollisionChecker3D() {
}
