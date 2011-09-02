#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ActorTableScene::ActorTableScene(const char* prm_name) : GgafDx9Scene(prm_name) {
    _class_name = "ActorTableScene";
    _max_perform_frame = 0xffffffff;
}


GgafGroupHead* ActorTableScene::addToTable(FormationActor* prm_pFormationActor, frame prm_max_delay_offset) {
    if (prm_pFormationActor->_obj_class | Obj_FormationActor) {
        //OK
    } else {
        throwGgafCriticalException("ActorTableScene::processBehavior() FormationActor 以外が登録されています。")
    }
    prm_pFormationActor->_offset_frames_end = FORMATION_END_DELAY;
    prm_pFormationActor->inactivateImmediately();
    _table.addLast(NEW TblElem(prm_pFormationActor, prm_max_delay_offset), true);

    return getDirector()->addSubGroup(prm_pFormationActor);
}

void ActorTableScene::onActive() {
    if (_table.length() > 0) {
        _frame_of_current_part_began = getActivePartFrame();
        _table.first();
        _table.getCurrent()->_pFormationActor->activate();
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

        if (!getDirector()->getSubFirst()) {
            end(FORMATION_END_DELAY);
            return;
        }

        TblElem* e = _table.getCurrent();
        FormationActor* pF = e->_pFormationActor;
        //全滅判定
        bool was_destroyed = false;

        if (pF->_num_sub == 0) { //編隊破壊による全滅(画面外に逃げた場合は0にはならない)
            was_destroyed = true;
        } else {
            was_destroyed = false;
        }

        if (was_destroyed) {
            //全滅の場合
            if (_table.isLast()) {
                //最終パートだったらTABLE終了
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 全パート終了！！");
                end(FORMATION_END_DELAY);
            } else {
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] pActiveActor="<<pF->getName()<<" 消滅により早回しきたー！！");
                //最終パートではない場合、テーブル全体の許容フレームか判断
                if (_max_perform_frame <  getActivePartFrame()) {
                    //収まらないと言うわけで、以降は全て無視されてシーン終了
                    _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 収まらない強制終了１！！");
                    end(FORMATION_END_DELAY); //0.5分後破棄(前パートが残存しているかも知れないため余裕をもたせる)
                    //このend() により、本処理先頭の wasDeclaredEnd() が真となる
                } else {
                    //余裕があるため次のパートをアクティブにする。
                    TblElem* n = _table.next(); //アクティブを次のパートへ
                    n->_pFormationActor->activate();     //敵アクティブ
                    _frame_of_current_part_began = getActivePartFrame();
                }
            }
        } else {
            //全滅では無い場合
            if (_table.isLast()) {
                //最終パートは次がないのでなにもしない
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 全滅では無いし、最終パートで次が無いのでなにもしない");
                end(FORMATION_END_DELAY); //0.5分後破棄(前パートが残存しているかも知れないため余裕をもたせる)
                //このend() により、本処理先頭の wasDeclaredEnd() が真となる
            } else {
                //max_delay_offset過ぎれば次へ
                if (getActivePartFrame() >= e->_max_delay_offset+_frame_of_current_part_began) {
                    if (_max_perform_frame <  getActivePartFrame()) {
                        //収まらないと言うわけで、以降は全て無視され共生終了
                        _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() 収まらない強制終了２！！");
                        end(FORMATION_END_DELAY); //0.5分後破棄(前パートが残存しているかも知れないため余裕をもたせる)
                        //このend() により、本処理先頭の wasDeclaredEnd() が真となる
                    } else {
                        TblElem* n = _table.next(); //アクティブを次のパートへ
                        n->_pFormationActor->activate();
                        _frame_of_current_part_began = getActivePartFrame();
                    }

                }
            }
        }
    }
}

ActorTableScene::~ActorTableScene() {
}
