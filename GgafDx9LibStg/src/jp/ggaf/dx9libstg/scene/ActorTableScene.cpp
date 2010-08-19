#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ActorTableScene::ActorTableScene(const char* prm_name) : GgafDx9Scene(prm_name) {
    _class_name = "ActorTableScene";
    _max_perform_frame = 0xffffffff;
}


GgafGroupActor* ActorTableScene::addToTable(GgafMainActor* prm_pMainActor, frame prm_max_delay_offset) {
    prm_pMainActor->inactivateImmediately();
    _table.addLast(NEW TblElem(prm_pMainActor, prm_max_delay_offset));
    return getLordActor()->addSubGroup(prm_pMainActor);
}

void ActorTableScene::initialize() {
}

void ActorTableScene::onActive() {
    if (_table.length() > 0) {
        //OK
        _frame_of_current_part_began = getActivePartFrame(); todo:絶対に０になるし。相対フレームでいいっか・・・
        _TRACE_("ActorTableScene::onActive() ["<<getName()<<"] 来ました。_frame_of_current_part_began="<<_frame_of_current_part_began);
    } else {
        throwGgafCriticalException("ActorTableScene::onActive() ["<<getName()<<"] テーブルにアクターが未だありません");
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
                //最終パートだったらTABLE終了
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 全パート終了！！");
                end(60*60);
            } else {
                TblElem* n = _table.next(); //アクティブを次のパートへ
                if (_max_perform_frame <  getActivePartFrame() + n->_max_delay_offset) {
                    //収まらないと言うわけで、以降は全て無視され共生終了
                    _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 収まらない強制終了１！！");
                    end(60*60);
                } else {
                    //余裕があるため次のパートをアクティブにする。
                    n->_pActor->activate();
                    _frame_of_current_part_began = getActivePartFrame();
                }
            }
        } else {
            //全滅 or 全領域外では無い場合でも
            //max_delay_offset過ぎれば次へ
            if (_table.isLast()) {
                //最終パートは次がないのでなにもしない
                //全滅 or 全領域外まで待つ
            } else {
                if (getActivePartFrame() >= e->_max_delay_offset+_frame_of_current_part_began) {
                    TblElem* n = _table.next(); //アクティブを次のパートへ
                    if (_max_perform_frame <  getActivePartFrame() + n->_max_delay_offset) {
                        //収まらないと言うわけで、以降は全て無視され共生終了
                        _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 収まらない強制終了２！！");
                        end(60*60);
                    } else {
                        n->_pActor->activate();
                        _frame_of_current_part_began = getActivePartFrame();
                    }

                }
            }

        }
    }
}

ActorTableScene::~ActorTableScene() {
    _TRACE_("ActorTableScene::~ActorTableScene() ["<<getName()<<"] 解放！！！！");
}
