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
    if (prm_pMainActor->_obj_class | Obj_GgafDx9FormationActor) {
        //OK
    } else if (prm_pMainActor->_obj_class | Obj_GgafDx9DrawableActor) {
        //OK
    } else {
        _TRACE_("ActorTableScene::processBehavior() GgafDx9FormationActor,Obj_GgafDx9DrawableActor 以外が登録されています。")
    }
    prm_pMainActor->inactivateImmediately();
    _table.addLast(NEW TblElem(prm_pMainActor, prm_max_delay_offset), true);
    return getLordActor()->addSubGroup(prm_pMainActor);
}

void ActorTableScene::onActive() {
    if (_table.length() > 0) {
        _frame_of_current_part_began = getActivePartFrame();
        _table.first();
        _table.getCurrent()->_pActor->activate();
        //OK
        //_frame_of_current_part_began = getActivePartFrame(); todo:絶対に０になるし。相対フレームでいいっか・・・
        _TRACE_("ActorTableScene::onActive() ["<<getName()<<"] 来ました。");
    } else {
        throwGgafCriticalException("ActorTableScene::onActive() ["<<getName()<<"] テーブルにアクターが未だありません");
    }
}


void ActorTableScene::processBehavior() {

    if (wasDeclaredEnd()) {
        //終了を待つのみ
    } else {

        if (!getLordActor()->getSubFirst()) {
            end(30*60);
            return;
        }

        TblElem* e = _table.getCurrent();
        GgafMainActor* pActiveActor = e->_pActor;
        //全滅判定
        bool was_destroyed = false;
        if (pActiveActor->_obj_class | Obj_GgafDx9FormationActor) {
            GgafDx9FormationActor* pF = (GgafDx9FormationActor*)pActiveActor;
            if (pF->_num_sub == 0) {
                was_destroyed = true;
            } else {
                was_destroyed = false;
            }
        } else if (pActiveActor->_obj_class | Obj_GgafDx9DrawableActor) {
            if (pActiveActor->isDisappear()) {
                was_destroyed = true;
            } else {
                was_destroyed = false;
            }
        } else {
            was_destroyed = false;
        }

        if (was_destroyed) {
            //全滅 or 全領域外は次へ
            if (_table.isLast()) {
                //最終パートだったらTABLE終了
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 全パート終了！！");
                end(30*60);
            } else {
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] pActiveActor="<<pActiveActor->getName()<<" 消滅により早回しきたー！！");
                //最終パートではない場合、テーブル全体の許容フレームか判断
                if (_max_perform_frame <  getActivePartFrame()) {
                    //収まらないと言うわけで、以降は全て無視されてシーン終了
                    _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 収まらない強制終了１！！");
                    end(30*60); //0.5分後破棄(前パートが残存しているかも知れないため余裕をもたせる)
                } else {
                    //余裕があるため次のパートをアクティブにする。
                    TblElem* n = _table.next(); //アクティブを次のパートへ
                    n->_pActor->activate();     //敵アクティブ
                    _frame_of_current_part_began = getActivePartFrame();
                }
            }
        } else {
            //全滅 or 全領域外では無い場合
            if (_table.isLast()) {
                //最終パートは次がないのでなにもしない
                //上の全滅 or 全領域外判定に引っかかるまで待つ
            } else {
                //max_delay_offset過ぎれば次へ
                if (getActivePartFrame() >= e->_max_delay_offset+_frame_of_current_part_began) {
                    if (_max_perform_frame <  getActivePartFrame()) {
                        //収まらないと言うわけで、以降は全て無視され共生終了
                        _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 収まらない強制終了２！！");
                        end(30*60); //0.5分後破棄(前パートが残存しているかも知れないため余裕をもたせる)
                    } else {
                        TblElem* n = _table.next(); //アクティブを次のパートへ
                        n->_pActor->activate();
                        _frame_of_current_part_began = getActivePartFrame();
                    }

                }
            }
        }
    }
}

ActorTableScene::~ActorTableScene() {
}
