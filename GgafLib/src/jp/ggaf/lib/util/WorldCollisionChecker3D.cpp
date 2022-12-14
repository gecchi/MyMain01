#include "jp/ggaf/lib/util/WorldCollisionChecker3D.h"

#include "jp/ggaf/core/actor/GroupHead.h"
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

WorldCollisionChecker3D::WorldCollisionChecker3D(GgafDx::GeometricActor* prm_pActor) : WorldCollisionChecker(prm_pActor) ,
        _pWorldLinearOctree(pCARETAKER->getSpacetime()->getLinearOctree()),
        _pNodeElem(NEW GgafCore::LinearOctree<GgafCore::Actor>::NodeElem(prm_pActor))
{
}

void WorldCollisionChecker3D::updateHitArea() {
    GgafDx::CollisionArea* const pCollisionArea = _pCollisionArea;
    if (pCollisionArea == nullptr) {
        return;
    }
    GgafDx::GeometricActor* const pActor = _pActor;
    if (pActor->isActiveInTheTree()) {
        //八分木に登録！
        _pNodeElem->_kind = pActor->lookUpKind();
#ifdef MY_DEBUG
        if (_pNodeElem->_kind == 0) {
            _TRACE_("【警告】 WorldCollisionChecker3D::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")の種別が0にもかかわらず、八分木に登録しようとしています。なぜですか？。");
        }
#endif
        pCollisionArea->updateAABB(pActor->_rx, pActor->_ry, pActor->_rz); //最外域の境界AABB更新
        _pWorldLinearOctree->registerElem(_pNodeElem, pActor->_x + pCollisionArea->_aabb_x1,
                                                      pActor->_y + pCollisionArea->_aabb_y1,
                                                      pActor->_z + pCollisionArea->_aabb_z1,
                                                      pActor->_x + pCollisionArea->_aabb_x2,
                                                      pActor->_y + pCollisionArea->_aabb_y2,
                                                      pActor->_z + pCollisionArea->_aabb_z2);
    }
}

bool WorldCollisionChecker3D::isHit(const GgafDx::CollisionChecker* const prm_pOppChecker) {
    GgafDx::CollisionArea* const pCollisionArea = _pCollisionArea;
    GgafDx::CollisionArea* const pOppCollisionArea = prm_pOppChecker->_pCollisionArea; //相手の当たり判定領域
    const GgafDx::GeometricActor* const pActor = _pActor;                //相手のアクター
    const GgafDx::GeometricActor* const pOppActor = prm_pOppChecker->_pActor;                //相手のアクター
    const int colli_part_num = pCollisionArea->_colli_part_num;
    const int opp_colli_part_num = pOppCollisionArea->_colli_part_num; //相手の当たり判定要素数
    const coord pActor_x = pActor->_x;
    const coord pActor_y = pActor->_y;
    const coord pActor_z = pActor->_z;
    const coord pOppActor_x = pOppActor->_x;
    const coord pOppActor_y = pOppActor->_y;
    const coord pOppActor_z = pOppActor->_z;
    //複数の当たり判定要素をもつアクター同士の場合、
    //まず最外境界AABoxで当たり判定を行って、ヒットすれば厳密に当たり判定を行う。
    if (colli_part_num > 2 || opp_colli_part_num > 2) {
#ifdef MY_DEBUG
        WorldCollisionChecker::_num_check++;
#endif
        if (pActor_x + pCollisionArea->_aabb_x2 >= pOppActor_x + pOppCollisionArea->_aabb_x1) {
            if (pActor_x + pCollisionArea->_aabb_x1 <= pOppActor_x + pOppCollisionArea->_aabb_x2) {
                if (pActor_z + pCollisionArea->_aabb_z2 >= pOppActor_z + pOppCollisionArea->_aabb_z1) {
                    if (pActor_z + pCollisionArea->_aabb_z1 <= pOppActor_z + pOppCollisionArea->_aabb_z2) {
                        if (pActor_y + pCollisionArea->_aabb_y2 >= pOppActor_y + pOppCollisionArea->_aabb_y1) {
                            if (pActor_y + pCollisionArea->_aabb_y1 <= pOppActor_y + pOppCollisionArea->_aabb_y2) {
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


    for (int i = 0; i < colli_part_num; i++) {
        const GgafDx::CollisionPart* const pColliPart = pCollisionArea->_papColliPart[i];
        if (!pColliPart->_is_valid_flg) { continue; }
        const int shape_kind = pColliPart->_shape_kind;

        if (shape_kind == COLLI_AABOX) {

            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
                if (!pOppColliPart->_is_valid_flg) { continue; }
                const int opp_shape_kind = pOppColliPart->_shape_kind;


//                int shape_kind_bit = (shape_kind << 4) | opp_shape_kind;
//                pFunc_isHit3D[shape_kind_bit](.....);


#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif

                if (opp_shape_kind == COLLI_AABOX) {
                    //＜AAB と AAB＞
                    coord max_dx = pColliPart->_hdx + pOppColliPart->_hdx;
                    if ((ucoord)( (pOppActor_x + pOppColliPart->_cx) - (pActor_x + pColliPart->_cx) + max_dx ) < (ucoord)(2*max_dx)) {
                        //↑左辺計算が0より小さい場合 unsigned キャストにより正の大きな数になるので条件成立しない事を利用し、ABSの判定を一つ除去してる。
                        //BOX vs BOX の当たり判定頻度はパフォーマンスに大きな影響を与えるため、わずかでも高速化したいため。
                        coord max_dz = pColliPart->_hdz + pOppColliPart->_hdz;
                        if ((ucoord)( (pOppActor_z + pOppColliPart->_cz) - (pActor_z + pColliPart->_cz) + max_dz ) < (ucoord)(2*max_dz)) {
                            coord max_dy = pColliPart->_hdy + pOppColliPart->_hdy;
                            if ((ucoord)( (pOppActor_y + pOppColliPart->_cy) - (pActor_y + pColliPart->_cy) + max_dy ) < (ucoord)(2*max_dy)) {
                                pCollisionArea->_hit_colli_part_index = i;
                                pOppCollisionArea->_hit_colli_part_index = j;
                                return true;
                            }
                        }
                    }
//                    if (UTIL::isHit3D(pActor   , (ColliAABox*)pColliPart,
//                                      pOppActor, (ColliAABox*)pOppColliPart)) {
//                        pCollisionArea->_hit_colli_part_index = i;
//                        pOppCollisionArea->_hit_colli_part_index = j;
//                        return true;
//                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //＜AAB と 球＞
                     if (UTIL::isHit3D(pActor   , (ColliAABox*)pColliPart,
                                       pOppActor, (ColliSphere*)pOppColliPart)) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //＜AAB と AAPrism＞
                     if (UTIL::isHit3D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                       pActor   , (ColliAABox*)pColliPart        )) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                     //＜AAB と AAPyramid＞
                     if (UTIL::isHit3D(pOppActor, (ColliAAPyramid*)pOppColliPart,
                                       pActor   , (ColliAABox*)pColliPart        )) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 }
            }

        } else if (shape_kind == COLLI_SPHERE) {

            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
                if (!pOppColliPart->_is_valid_flg) { continue; }
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //＜球 と AAB＞
                    if (UTIL::isHit3D(pOppActor, (ColliAABox*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜球 と 球＞
                    //球1 ： 中心点の座標P1(x1, y1, z1), 半径r1
                    //球2 ： 中心点の座標P2(x2, y2, z2), 半径r2
                    //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
                    double dx = (double)( (pActor_x+pColliPart->_cx) - (pOppActor_x+pOppColliPart->_cx) );
                    double dy = (double)( (pActor_y+pColliPart->_cy) - (pOppActor_y+pOppColliPart->_cy) );
                    double dz = (double)( (pActor_z+pColliPart->_cz) - (pOppActor_z+pOppColliPart->_cz) );
                    double dd = dx*dx + dy*dy + dz*dz;
                    if (dd <= (double)(((ColliSphere*)pColliPart)->_r + ((ColliSphere*)pOppColliPart)->_r) *
                              (double)(((ColliSphere*)pColliPart)->_r + ((ColliSphere*)pOppColliPart)->_r)
                    ) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
//                    if (UTIL::isHit3D(pActor  , (ColliSphere*)pColliPart,
//                                      pOppActor, (ColliSphere*)pOppColliPart)) {
//                        pCollisionArea->_hit_colli_part_index = i;
//                        pOppCollisionArea->_hit_colli_part_index = j;
//                        return true;
//                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //＜球 と AAPrism＞
                    if (UTIL::isHit3D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart     )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //＜球 と AAPyramid＞
                    if (UTIL::isHit3D(pOppActor, (ColliAAPyramid*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart     )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }
            }

        } else if (shape_kind == COLLI_AAPRISM) {

            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
                if (!pOppColliPart->_is_valid_flg) { continue; }
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //＜AAPrism と AAB＞
                    if (UTIL::isHit3D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart  )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜AAPrism と 球＞
                    if (UTIL::isHit3D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }  else if (opp_shape_kind == COLLI_AAPRISM) {
                    //＜AAPrism と AAPrism＞
                    //TODO:未対応。 考えるだけで重たくなりそう、というかめんどくさそうな感じがする；。
                    //時間があれば考えよう・・・
                    _TRACE_("【警告】AAPrism と AAPrism の当たり判定処理が存在します。そんな処理は未だ作ってません。 "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //＜AAPrism と AAPyramid＞
                    //TODO: 今は未対応。
                    _TRACE_("【警告】AAPrism と AAPyramid の当たり判定処理が存在します。そんな処理は未だ作ってません。 "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                }
            }

        } else if (shape_kind == COLLI_AAPYRAMID) {

            for (int j = 0; j < opp_colli_part_num; j++) {
                const GgafDx::CollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
                if (!pOppColliPart->_is_valid_flg) { continue; }
                const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
                WorldCollisionChecker::_num_check++;
#endif
                if (opp_shape_kind == COLLI_AABOX) {
                    //＜AAPyramid と AAB＞
                    if (UTIL::isHit3D(pActor  , (ColliAAPyramid*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart  )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //＜AAPyramid と 球＞
                    if (UTIL::isHit3D(pActor  , (ColliAAPyramid*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //＜AAPyramid と AAPrism＞
                    //TODO: 今は未対応。
                    _TRACE_("【警告】AAPyramid と AAPrism の当たり判定処理が存在します。そんな処理は未だ作ってません。 "<<
                            pActor <<"["<<_pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //＜AAPyramid と AAPyramid＞
                    //TODO: 今は未対応。
                    _TRACE_("【警告】AAPyramid と AAPyramid の当たり判定処理が存在します。そんな処理は未だ作ってません。 "<<
                            pActor <<"["<<_pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                }
            }
        }
    }
    return false;
}


WorldCollisionChecker3D::~WorldCollisionChecker3D() {
    delete _pNodeElem;
    //当たり判定はないかもしれない。この場合_pElemは無駄な生成と解放をすることになる。。
}
