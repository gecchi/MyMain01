#include "jp/ggaf/lib/scene/RotateFormationScene.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/actor/ex/Formation.h"

using namespace GgafLib;

RotateFormationScene::RotateFormationScene(const char* prm_name) :
        DefaultScene(prm_name) {
    _class_name = "RotateFormationScene";
    _max_perform_frame = 0xffffffff;
    _frame_of_current_part_began = 0;
}


GgafCore::GroupHead* RotateFormationScene::addFormation(GgafCore::Formation* prm_pFormationActor, frame prm_max_delay_offset) {
    if (prm_pFormationActor->instanceOf(Obj_ggaf_Formation)) {
        //OK
    } else {
        throwCriticalException("GgafCore::Formation 以外が登録されています。");
    }
    prm_pFormationActor->_offset_frames_end = FORMATION_END_DELAY;
    prm_pFormationActor->inactivate();
    _table.addLast(NEW FormationTblElem(prm_pFormationActor, prm_max_delay_offset), true);

    return getSceneChief()->appendGroupChild(prm_pFormationActor);
}

void RotateFormationScene::onActive() {
    if (_table.length() > 0) {
        _frame_of_current_part_began = getActiveFrame();
        _table.first();
        _table.getCurrent()->_pFormationActor->activate();
        //OK
        //_frame_of_current_part_began = getActiveFrame(); todo:絶対に０になるし。相対フレームでいいっか・・・
        _TRACE_(FUNC_NAME<<" ["<<getName()<<"] 来ました。");
    } else {
        throwCriticalException("["<<getName()<<"] テーブルにアクターが未だありません");
    }
}


void RotateFormationScene::processBehavior() {

    if (wasDeclaredEnd()) {
        //終了を待つのみ
    } else {

        if (!getSceneChief()->getChildFirst()) {
            sayonara(FORMATION_END_DELAY);
            return;
        }

        FormationTblElem* e = _table.getCurrent();
        GgafCore::Formation* pF = e->_pFormationActor;
        //全滅判定
        if (pF->_was_all_destroyed) {
            //全滅の場合
            if (_table.isLast()) {
                //最終パートだったらTABLE終了
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] end() 全パート終了！！");
                sayonara(FORMATION_END_DELAY);
            } else {
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] pActiveActor="<<pF->getName()<<" 消滅により早回しきたー！！");
                //最終パートではない場合、テーブル全体の許容フレームか判断
                if (_max_perform_frame <  getActiveFrame()) {
                    //収まらないと言うわけで、以降は全て無視されてシーン終了
                    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] end() 収まらない強制終了１！！");
                    sayonara(FORMATION_END_DELAY); //0.5分後破棄(前パートが残存しているかも知れないため余裕をもたせる)
                    //このsayonara() により、本処理先頭の wasDeclaredEnd() が真となる
                } else {
                    //余裕があるため次のパートをアクティブにする。
                    FormationTblElem* n = _table.next(); //アクティブを次のパートへ
                    n->_pFormationActor->activate();     //敵アクティブ
                    _frame_of_current_part_began = getActiveFrame();
                }
            }
        } else {
            //全滅では無い場合
            if (_table.isLast()) {
                //最終パートは次がないのでなにもしない
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] end() 全滅では無いし、最終パートで次が無いのでなにもしない");
                sayonara(FORMATION_END_DELAY); //0.5分後破棄(前パートが残存しているかも知れないため余裕をもたせる)
                //このsayonara() により、本処理先頭の wasDeclaredEnd() が真となる
            } else {
                //max_delay_offset過ぎれば次へ
                if (getActiveFrame() >= e->_max_delay_offset+_frame_of_current_part_began) {
                    if (_max_perform_frame <  getActiveFrame()) {
                        //収まらないと言うわけで、以降は全て無視され共生終了
                        _TRACE_(FUNC_NAME<<" ["<<getName()<<"] end() 収まらない強制終了２！！");
                        sayonara(FORMATION_END_DELAY); //0.5分後破棄(前パートが残存しているかも知れないため余裕をもたせる)
                        //このsayonara() により、本処理先頭の wasDeclaredEnd() が真となる
                    } else {
                        FormationTblElem* n = _table.next(); //アクティブを次のパートへ
                        n->_pFormationActor->activate();
                        _frame_of_current_part_began = getActiveFrame();
                    }

                }
            }
        }
    }
}

RotateFormationScene::~RotateFormationScene() {
}
