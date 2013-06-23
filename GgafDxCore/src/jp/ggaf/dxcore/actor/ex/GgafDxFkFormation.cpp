#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxFkFormation.h"
#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxFkFormation::GgafDxFkFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafDxFkFormation";
    _pIte = nullptr;
    _can_call_up = true;
}
void GgafDxFkFormation::setFkBase(GgafDxGeometricActor* prm_pFkBase) {
    if (_pSubFirst == nullptr) { //最初の１つ目
        //本フォーメーションオブジェクト自体の種別を確定
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND,
                      prm_pFkBase->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND) != prm_pFkBase->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafDxFkFormation::addFormationBase 異なる種別のFKベースアクターを登録しようとしています。 \n"<<
                                       "想定="<<_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pFkBase->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pFkBase->getName()<<"]");
        }
#endif
    }
    GgafFormation::addSubLast(prm_pFkBase);
}

void GgafDxFkFormation::addFormationMemberAsFk(GgafDxGeometricActor* prm_pMember,
                                               int prm_X_init_local,
                                               int prm_Y_init_local,
                                               int prm_Z_init_local,
                                               int prm_RX_init_local,
                                               int prm_RY_init_local,
                                               int prm_RZ_init_local) {

#ifdef MY_DEBUG
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        throwGgafCriticalException("GgafDxFkFormation::addFormationMemberAsFk() : "<<
                                   "既に死にゆく定めのFormationです。サブに追加することはおかしいでしょう。this="<<getName());
    }
    if (getSubFirst() == nullptr) {
        throwGgafCriticalException("GgafDxFkFormation::addFormationMemberAsFk() : "<<
                                   "FKベースアクターがいません。addFormationBase() してください。this="<<getName());
    }
#endif
    GgafDxGeometricActor* pFkBase = (GgafDxGeometricActor*)(getSubFirst());
    _num_formation_member++;
    prm_pMember->_pFormation = this; //メンバーへフォーメーションを設定
    pFkBase->addSubGroupAsFk(prm_pMember,
                             prm_X_init_local,
                             prm_Y_init_local,
                             prm_Z_init_local,
                             prm_RX_init_local,
                             prm_RY_init_local,
                             prm_RZ_init_local);
    prm_pMember->inactivateImmed(); //フォーメーションなのでCallUpを待つため
}

void GgafDxFkFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
    } else {
        GgafMainActor* pFkBase = (GgafMainActor*)(getSubFirst()); //FKベース
        if (pFkBase) {
            if (pFkBase->getSubFirst() == nullptr) { //FKベースの配下がなければ
                pFkBase->sayonara(); //FKベースを開放
            }
        } else {
            //配下のFKベースがない場合、フォーメーションはなかったことになり、自身を終了
            onSayonaraAll(); //コールバック
            sayonara(_offset_frames_end);
            _was_all_sayonara = true;
        }
    }
}

void GgafDxFkFormation::onEnd() {
    GgafFormation::onEnd();
}

GgafDxGeometricActor* GgafDxFkFormation::callUpMember() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        return nullptr;
    }
    if (_can_call_up) {
        if (_pIte) {
            _pIte = _pIte->getNext();
                         //FkBase     -> GroupHead   ->Actor
            if (_pIte == getSubFirst()->getSubFirst()->getSubFirst()) { //１周した
                _can_call_up = false;
                return nullptr;
            }
        } else {
                  //FkBase       -> GroupHead   ->Actor
            _pIte = getSubFirst()->getSubFirst()->getSubFirst();
        }
        _pIte->activate();
        return (GgafDxGeometricActor*)_pIte;
    } else {
        return nullptr;
    }
}

GgafDxFkFormation::~GgafDxFkFormation() {

}
