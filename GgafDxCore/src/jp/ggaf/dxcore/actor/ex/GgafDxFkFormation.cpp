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
void GgafDxFkFormation::registerFormationFkBase(GgafDxGeometricActor* prm_pFkBase) {
    if (_pSubFirst == nullptr) { //最初の１つ目
        //本フォーメーションオブジェクト自体の種別を確定
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND,
                      prm_pFkBase->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND) != prm_pFkBase->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("異なる種別のFKベースアクターを登録しようとしています。 \n"<<
                                       "想定="<<getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pFkBase->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pFkBase->getName()<<"]");
        }
#endif
    }
    GgafFormation::addSubLast(prm_pFkBase);
}

void GgafDxFkFormation::addFormationMember(GgafDxGeometricActor* prm_pMember,
                                           int prm_x_init_local,
                                           int prm_y_init_local,
                                           int prm_z_init_local,
                                           int prm_rx_init_local,
                                           int prm_ry_init_local,
                                           int prm_rz_init_local) {

#ifdef MY_DEBUG
    if (wasDeclaredEnd() || willInactivateAfter()) {
        //終了を待つのみ
        throwGgafCriticalException(": "<<
                                   "既に死にゆく定めのFormationです。サブに追加することはおかしいでしょう。this="<<getName());
    }
    if (getSubFirst() == nullptr) {
        throwGgafCriticalException(": "<<
                                   "FKベースアクターがいません。addFormationBase() してください。this="<<getName());
    }
#endif
    GgafDxGeometricActor* pFkBase = (GgafDxGeometricActor*)(getSubFirst());
    ++_num_formation_member;
    prm_pMember->_pFormation = this; //メンバーへフォーメーションを設定
    pFkBase->addSubGroupAsFk(prm_pMember,
                             prm_x_init_local,
                             prm_y_init_local,
                             prm_z_init_local,
                             prm_rx_init_local,
                             prm_ry_init_local,
                             prm_rz_init_local);
    prm_pMember->inactivate(); //フォーメーションなのでCallUpを待つため
}

void GgafDxFkFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || willInactivateAfter()) {
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
    if (wasDeclaredEnd() || willInactivateAfter()) {
        //終了を待つのみ
        return nullptr;
    }
    if (_can_call_up) {
                                 //FkBase     -> GroupHead   ->Actor
        GgafActor* pFirstActor = getSubFirst()->getSubFirst()->getSubFirst(); //今の先頭アクター
        if (_pIte) {
            _pIte = _pIte->getNext();
            if (_pIte == pFirstActor) { //１周した
                _can_call_up = false;
                return nullptr;
            }
        } else {
            //初回
            _pIte = pFirstActor;
        }
        _pIte->activate();
        if (_pIte->getNext() == pFirstActor) {
            //次が今の先頭アクターなら、これ(_pIte)は最後の一つ
            _can_call_up = false;
        }
        return (GgafDxGeometricActor*)_pIte;
    } else {
        return nullptr;
    }
}

GgafDxFkFormation::~GgafDxFkFormation() {

}
