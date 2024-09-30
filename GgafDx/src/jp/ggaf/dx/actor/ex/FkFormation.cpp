#include "jp/ggaf/dx/actor/ex/FkFormation.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"


using namespace GgafDx;

FkFormation::FkFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafCore::Formation(prm_name, prm_offset_frames_end)
{
    _class_name = "FkFormation";
    _pIte = nullptr;
    _can_called_up = true;
}
void FkFormation::registerFormationFkBase(GeometricActor* prm_pFkBase) {
    if (_pChildFirst == nullptr) { //最初の１つ目
        //本フォーメーションオブジェクト自体の種別を確定
//        getStatus()->set(STAT_DEFAULT_ACTOR_KIND,
//                      prm_pFkBase->getCheckerKind());
        setDefaultKind(prm_pFkBase->getCheckerKind());
    } else {
#ifdef MY_DEBUG
        if (getCheckerKind() != prm_pFkBase->getCheckerKind()) {
            throwCriticalException("異なる種別のFKベースアクターを登録しようとしています。 \n"
                                       "想定="<<getCheckerKind()<<"[_pChildFirst="<<_pChildFirst->getName()<<"] \n"
                                       "引数="<<prm_pFkBase->getCheckerKind()<<"["<<prm_pFkBase->getName()<<"]");
        }
#endif
    }
    GgafCore::Formation::appendChild(prm_pFkBase);
}

void FkFormation::appendFormationMember(GeometricActor* prm_pMember,
                                        int prm_x_init_local,
                                        int prm_y_init_local,
                                        int prm_z_init_local,
                                        int prm_rx_init_local,
                                        int prm_ry_init_local,
                                        int prm_rz_init_local) {

#ifdef MY_DEBUG
    if (wasDeclaredEnd() || isInactivateScheduled()) {
        //終了を待つのみ
        throwCriticalException(": 既に死にゆく定めのFormationです。子に追加することはおかしいでしょう。this="<<getName());
    }
    if (getChildFirst() == nullptr) {
        throwCriticalException(": FKベースアクターがいません。addFormationBase() してください。this="<<getName());
    }
#endif
    GeometricActor* pFkBase = (GeometricActor*)(getChildFirst());
    _num_formation_member++;
    prm_pMember->_pFormation = this; //メンバーへフォーメーションを設定
    pFkBase->appendChildAsFk(prm_pMember,
                              prm_x_init_local,
                              prm_y_init_local,
                              prm_z_init_local,
                              prm_rx_init_local,
                              prm_ry_init_local,
                              prm_rz_init_local);
    prm_pMember->inactivate(); //フォーメーションなのでCalledUpを待つため
}

void FkFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || isInactivateScheduled()) {
        //終了を待つのみ
    } else {
        GgafCore::MainActor* pFkBase = (GgafCore::MainActor*)(getChildFirst()); //FKベース
        if (pFkBase) {
            if (pFkBase->getChildFirst() == nullptr) { //FKベースの配下がなければ
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

void FkFormation::onEnd() {
    GgafCore::Formation::onEnd();
}

GeometricActor* FkFormation::calledUpMember(int prm_formation_child_num) {
    if (wasDeclaredEnd() || isInactivateScheduled()) {
        //終了を待つのみ
        return nullptr;
    }
    if (_can_called_up) {
                                 //FkBase      ->Actor
        GgafCore::Actor* pFirstActor = getChildFirst()->getChildFirst(); //今の先頭アクター
        if (_pIte) {
            _pIte = _pIte->getNext();
        } else {
            //初回
            _pIte = pFirstActor;
            if (!_pIte) {
                //メンバーが追加されてない
                _TRACE_("【警告】 FkFormation::calledUpMember() メンバーが追加されてません。おかしいのでは？。this="<<NODE_INFO);
                _can_called_up = false; //次回から calledUpMember() 不可
                _num_formation_member = 0;
                return nullptr;
            }
        }
        _num_called_up++;
        _pIte->activate();
        if (_pIte->getNext() == pFirstActor) {
            //次が今の先頭アクターなら、これ(_pIte)は最後の一つ
            _can_called_up = false;
        }

        if (_pIte->getNext() == pFirstActor) {
            //最後の１つ
            _can_called_up = false; //次回から calledUpMember() 不可
            _num_formation_member = _num_called_up; //destroyedFollower 編隊全滅判定の為再設定
        }
        if (prm_formation_child_num <= _num_called_up) {
            //上限数に達した
            _can_called_up = false; //次回から calledUpMember() 不可
            _num_formation_member = _num_called_up; //destroyedFollower 編隊全滅判定の為再設定
        }
        return (GeometricActor*)_pIte;
    } else {
        return nullptr;
    }
}

FkFormation::~FkFormation() {

}
