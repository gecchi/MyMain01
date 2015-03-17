#include "jp/ggaf/lib/actor/WallPartsActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallPartsActor::WallPartsActor(const char* prm_name,
                               const char* prm_model_id,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               GgafStatus* prm_pStat) :

                        GgafDxMeshSetActor(prm_name,
                                           prm_model_id,
                                           prm_effect_id,
                                           prm_technique,
                                           prm_pStat,
                                           NEW CollisionChecker3D(this) ) {
    _class_name = "WallPartsActor";
    _obj_class |= Obj_WallPartsActor;
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _wall_draw_face = 0;
    _pos_prism = 0;
    _pWalledSectionScene = nullptr;

    _wall_dep = 0;
    _wall_width = 0;
    _wall_height = 0;
    setHitAble(true);
}

void WallPartsActor::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->instanceOf(Obj_LaserChip)) {
        LaserChip* pLaserChip = (LaserChip*)prm_pOtherActor;
        if (pLaserChip->_chip_kind == 3 || pLaserChip->_can_chikei_hit) {
            //���肪 3:���Ԑ擪�`�b�v ���A1/8�̒n�`�����蔻��L��`�b�v
            GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}



void WallPartsActor::initialize() {

}

void WallPartsActor::onActive() {

}

void WallPartsActor::processBehavior() {
}

void WallPartsActor::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void WallPartsActor::processPreDraw() {
    if (_wall_draw_face > 0) {
        //�`��ʂ�����ꍇ�͕\���Ώۂɂ���
        GgafDxFigureActor::processPreDraw();
    }
}

bool WallPartsActor::isOutOfUniverse() const {
    if (_x+_wall_dep < GgafDxUniverse::_x_gone_left) {
        return true;
    } else {
        return false;
    }
}

int WallPartsActor::isOutOfView() {
    if (_offscreen_kind == -1) {
        dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*2.0f;//�|����2�͋��E����傫�����āA��ʋ��E�̃`���c�L��}����
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_front < bound) {
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


void WallPartsActor::config(WalledSectionScene* prm_pWalledSectionScene, int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) {
    _pWalledSectionScene =prm_pWalledSectionScene;
    _wall_dep = _pWalledSectionScene->_wall_dep;
    _wall_width = _pWalledSectionScene->_wall_width;
    _wall_height = _pWalledSectionScene->_wall_height;
    _wall_draw_face = prm_wall_draw_face;
    _pos_prism = prm_pos_prism;
}

void WallPartsActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

WallPartsActor::~WallPartsActor() {
    GGAF_DELETE(_pColliChecker);
}
