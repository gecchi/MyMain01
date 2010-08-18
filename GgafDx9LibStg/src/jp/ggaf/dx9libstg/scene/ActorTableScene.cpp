#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ActorTableScene::ActorTableScene(const char* prm_name) : GgafDx9Scene(prm_name) {
    _class_name = "ActorTableScene";
}


GgafGroupActor* ActorTableScene::addToTable(GgafMainActor* prm_pMainActor) {
    prm_pMainActor->inactivateImmediately();
    _table.addLast(prm_pMainActor, false);
    return getLordActor()->addSubGroup(prm_pMainActor);
}

GgafGroupActor* ActorTableScene::addToTable(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    prm_pMainActor->inactivateImmediately();
    _table.addLast(prm_pMainActor, false);
    return getLordActor()->addSubGroup(prm_kind, prm_pMainActor);
}

void ActorTableScene::initialize() {
    if (_table.length() > 0) {
        //OK
        GgafMainActor* p = _table.get();
        p->activate(); //最初のアクターをアクティブ
    } else {
        throwGgafCriticalException("ActorTableScene::initialize() ["<<getName()<<"] テーブルにアクターがありません");
    }
}


void ActorTableScene::processBehavior() {
    if (wasDeclaredEnd()) {
        //終了を待つのみ
    } else {
        GgafMainActor* pActiveActor = _table.get();
        if (pActiveActor->_will_inactivate_after_flg ||
            pActiveActor->_is_active_flg_in_next_frame == false ||
            pActiveActor->_will_end_after_flg) {
            if (_table.isLast()) {
                //TABLE終了
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 終了！！");
                end(60*60);
            } else {
                GgafMainActor* p = _table.next(); //アクティブを次のアクターへ
                p->activate();
            }
        }
    }
}

ActorTableScene::~ActorTableScene() {
    _TRACE_("ActorTableScene::~ActorTableScene() ["<<getName()<<"] 解放！！！！");
}
