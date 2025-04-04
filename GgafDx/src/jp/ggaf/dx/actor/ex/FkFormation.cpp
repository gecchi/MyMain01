#include "jp/ggaf/dx/actor/ex/FkFormation.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"


using namespace GgafDx;

FkFormation::FkFormation(const char* prm_name, frame prm_offset_frames_end) :
        Formation(prm_name, prm_offset_frames_end)
{
    _class_name = "FkFormation";
    _pIte = nullptr;
}
void FkFormation::registerFormationFkBase(GeometricActor* prm_pFkBase) {
    if (_pChildFirst == nullptr) { //最初の１つ目
        //本フォーメーションオブジェクト自体の種別を確定
    } else {
#ifdef MY_DEBUG
        throwCriticalException("registerFormationFkBase 既に FkBase 追加されてます！\n"<<
                "_pChildFirst="<<_pChildFirst->getName()<<"   prm_pFkBase="<<prm_pFkBase->getName() );
#endif
    }
    Formation::appendChild(prm_pFkBase);
}

void FkFormation::appendFormationMember(GgafCore::Actor* prm_pMember,
                                        int prm_x_init_local,
                                        int prm_y_init_local,
                                        int prm_z_init_local,
                                        int prm_rx_init_local,
                                        int prm_ry_init_local,
                                        int prm_rz_init_local) {

#ifdef MY_DEBUG
    if (wasDeclaredEnd() || isInactivateScheduled()) {
        //終了を待つのみ
        throwCriticalException("FkFormation::appendFormationMember() 既に死にゆく定めのFormationです。子に追加することはおかしいでしょう。this="<<getName());
    }
    if (getChildFirst() == nullptr) {
        throwCriticalException("FkFormation::appendFormationMember() FKベースアクターがいません。addFormationBase() してください。this="<<getName());
    }
#endif
    //TODO:GeometricActor チェックをいれる？
    GeometricActor* pMember = (GeometricActor*)prm_pMember;
    GeometricActor* pFkBase = (GeometricActor*)(getChildFirst());
    _num_formation_member++;
    pMember->_pFormation = this; //メンバーへフォーメーションを設定
    //this > pFkBase > pMember
    //               > pMember
    //               ...
    pFkBase->appendChildAsFk(pMember,
                             prm_x_init_local,
                             prm_y_init_local,
                             prm_z_init_local,
                             prm_rx_init_local,
                             prm_ry_init_local,
                             prm_rz_init_local);
    pMember->inactivate(); //フォーメーションなのでSummonを待つため
}

void FkFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || isInactivateScheduled()) {
        //終了を待つのみ
    } else {
        GgafCore::MainActor* pFkBase = (GgafCore::MainActor*)(getChildFirst()); //FKベース
        if (pFkBase) {
            if (pFkBase->getChildFirst() == nullptr) { //FKベースの配下がなければ
                pFkBase->sayonara(); //FKベースを開放
                //TODO:イベントを作るか？FKベースだけ残された場合、FKベースが先に倒された場合、全消失とか
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
    Formation::onEnd();
}

GeometricActor* FkFormation::summonMember(int prm_formation_child_num) {
    if (wasDeclaredEnd() || isInactivateScheduled()) {
        //終了を待つのみ
        return nullptr;
    }
    if (_can_summon) {
                                 //FkBase      ->Actor
        GeometricActor* pFirstActor = (GeometricActor*)(getChildFirst()->getChildFirst()); //今の先頭アクター
        if (_pIte) {
            _pIte = _pIte->getNext();
        } else {
            //初回
            _pIte = pFirstActor;
            if (!_pIte) {
                //メンバーが追加されてない
                _TRACE_("【警告】 FkFormation::summonMember() メンバーが追加されてません。おかしいのでは？。this="<<NODE_INFO);
                _can_summon = false; //次回から summonMember() 不可
                _num_formation_member = 0;
                return nullptr;
            }
        }
        _num_summon++;
        _pIte->activate();
        if (_pIte->getNext() == pFirstActor) {
            //次が今の先頭アクターなら、これ(_pIte)は最後の一つ
            _can_summon = false;
        }

        if (_pIte->getNext() == pFirstActor) {
            //最後の１つ
            _can_summon = false; //次回から summonMember() 不可
            _num_formation_member = _num_summon; //onDestroyMember 編隊全滅判定の為再設定
        }
        if (prm_formation_child_num <= _num_summon) {
            //上限数に達した
            _can_summon = false; //次回から summonMember() 不可
            _num_formation_member = _num_summon; //onDestroyMember 編隊全滅判定の為再設定
        }
        return (GeometricActor*)_pIte;
    } else {
        return nullptr;
    }
}

FkFormation::~FkFormation() {

}
