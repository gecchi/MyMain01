#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ActorTableScene::ActorTableScene(const char* prm_name) : GgafDx9Scene(prm_name) {
    _class_name = "ActorTableScene";
}


GgafGroupActor* ActorTableScene::addToTable(GgafMainActor* prm_pMainActor, frame prm_max_delay_offset) {
    prm_pMainActor->inactivateImmediately();
    _table.addLast(NEW TblElem(prm_pMainActor, prm_max_delay_offset));
    return getLordActor()->addSubGroup(prm_pMainActor);
}

void ActorTableScene::initialize() {
    if (_table.length() > 0) {
        //OK
        TblElem* e = _table.get();
        e->_pActor->activateAfter(e->_max_delay_offset); //最初のアクターをアクティブ
        _prev_active_frame = getActivePartFrame()+e->_max_delay_offset;
    } else {
        throwGgafCriticalException("ActorTableScene::initialize() ["<<getName()<<"] テーブルにアクターがありません");
    }
}


void ActorTableScene::processBehavior() {
    if (wasDeclaredEnd()) {
        //終了を待つのみ
    } else {
        TblElem* e = _table.get();
        GgafMainActor* pActiveActor = e->_pActor;
        if (pActiveActor->_will_inactivate_after_flg ||
            pActiveActor->_is_active_flg_in_next_frame == false ||
            pActiveActor->_will_end_after_flg) {
            //全滅 or 全領域外は次へ
            if (_table.isLast()) {
                //TABLE終了
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 終了！！");
                end(60*60);
            } else {
                TblElem* n = _table.next(); //アクティブを次のへ
                n->_pActor->activate();
                _prev_active_frame = getActivePartFrame();
            }
        } else {
            //全滅 or 全領域外では無い場合でも
            //max_delay_offset過ぎれば次へ

            if (getActivePartFrame() >= e->_max_delay_offset+_prev_active_frame) {

                TblElem* n = _table.next(); //アクティブを次のへ
                n->_pActor->activate();
                _prev_active_frame = getActivePartFrame();
            }

        }
    }
}

ActorTableScene::~ActorTableScene() {
    _TRACE_("ActorTableScene::~ActorTableScene() ["<<getName()<<"] 解放！！！！");
}
