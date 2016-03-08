#include "jp/ggaf/lib/actor/wall/MassWallActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/DefaultGod.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

MassWallActor::MassWallActor(const char* prm_name,
                               const char* prm_model_id,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               GgafStatus* prm_pStat) :

                        GgafDxMassMeshActor(prm_name,
                                           prm_model_id,
                                           prm_effect_id,
                                           prm_technique,
                                           prm_pStat,
                                           NEW CollisionChecker3D(this) ) {
    _class_name = "MassWallActor";
    _obj_class |= Obj_MassWallActor;
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _wall_draw_face = 0;
    _pos_info = 0;
    _pWalledSectionScene = nullptr;

    _wall_dep = 0;
    _wall_width = 0;
    _wall_height = 0;
    setHitAble(true);
}

void MassWallActor::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->instanceOf(Obj_LaserChip)) { //���肪���[�U�[
        LaserChip* pLaserChip = (LaserChip*)prm_pOtherActor;
        if (pLaserChip->getInfrontChip() == nullptr || pLaserChip->_can_chikei_hit) {
            //���肪��[�`�b�v���A1/16 �̒n�`�����蔻��L��`�b�v
            GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}



void MassWallActor::initialize() {

}

void MassWallActor::onActive() {

}

void MassWallActor::processBehavior() {
}

void MassWallActor::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MassWallActor::processPreDraw() {
    if (_wall_draw_face > 0) {
        //�`��ʂ�����ꍇ�͕\���Ώۂɂ���
        GgafDxFigureActor::processPreDraw();
    }
}

bool MassWallActor::isOutOfSpacetime() const {
    GgafDxSpacetime* pSpacetime =  P_GOD->getSpacetime();
    if (pSpacetime->_x_bound_left <= _x+_wall_dep) {
        return false;
    }
    return true;
}

int MassWallActor::isOutOfView() {
    if (_offscreen_kind == -1) {
        dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*2.0f;//�|����2�͋��E����傫�����āA��ʋ��E�̃`���c�L��}����
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_infront < bound) {
                            //if (_dest_from_vppln_back < bound) {
                            //    //Viewport�͈͓�
                            //    _offscreen_kind = 0;
                            //} else {
                            //    //�����ʂ�艜�Ŕ͈͊O
                            //    _offscreen_kind = 6;
                            //}

                            //�����ʔ���͖���
                            _offscreen_kind = 0;
                        } else {
                            //��O���ʂ���O�Ŕ͈͊O
                            _offscreen_kind = 5;
                        }
                    } else {
                        //�E���ʂ��E�Ŕ͈͊O
                        _offscreen_kind = 4;
                    }
                } else {
                    //�����ʂ�荶�Ŕ͈͊O
                    _offscreen_kind = 3;
                }
            } else {
                //�����ʂ�艺�Ŕ͈͊O
                _offscreen_kind = 2;
            }
        } else {
            //�㕽�ʂ���Ŕ͈͊O
            _offscreen_kind = 1;
        }
    }
    return _offscreen_kind;
}


void MassWallActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    _pWalledSectionScene =prm_pWalledSectionScene;
    _wall_dep = _pWalledSectionScene->_wall_dep;
    _wall_width = _pWalledSectionScene->_wall_width;
    _wall_height = _pWalledSectionScene->_wall_height;
    _wall_draw_face = prm_wall_draw_face;
    _pos_info = prm_pos_info;
}

void MassWallActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

MassWallActor::~MassWallActor() {
    GGAF_DELETE(_pColliChecker);
}
