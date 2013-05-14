#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


FormationAdelheid::FormationAdelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationAdelheid";

    pPalisana_start = NEW EnemyPalisana("Palisana1");
    pPalisana_start->inactivateImmed();
    addSubGroup(pPalisana_start);

    pPalisana_goal = NEW EnemyPalisana("Palisana2");
    pPalisana_goal->inactivateImmed();
    addSubGroup(pPalisana_goal);

    //軌道計算用のダミー
    pDummy_ = NEW EnemyAdelheid("DammyEnemyAdelheid");;
    pDummy_->inactivateImmed();
    addSubGroup(pDummy_);

    //編隊隊員デポジトリセット
    pConnection_AdelheidDepo_ = connectToDepositoryManager("EnemyAdelheid4Formation");
    setFormationMember(pConnection_AdelheidDepo_->peek());

    pConnection_ShotDepo_ = connectToDepositoryManager("EnemyAdelheidShot");

    updateRankParameter();


    useProgress(PROG_LEAVE);
}

void FormationAdelheid::updateRankParameter() {
    rr_num_formation_     = 21;  //調査 20 で両方開くが、21で一つしかひらかないのは何故。  //RR_FormationAdelheid_Num(_RANK_);            //編隊数
    rr_interval_frames_   = 25;
    rr_mv_velo_           = PX_C(40); //RR_FormationAdelheid_MvVelo(_RANK_);         //速度
    mv_velo_member_ = rr_mv_velo_;
}

void FormationAdelheid::initialize() {

}

void FormationAdelheid::onActive() {
    updateRankParameter();
    _pProg->reset(PROG_INIT);
}

void FormationAdelheid::processBehavior() {
    //pPalisana_start が破壊されているかチェック
    if (pPalisana_start) {
        if (pPalisana_start->onChangeToInactive()) {
            pPalisana_start = nullptr;
        }
    }
    //pPalisana_goal が破壊されているかチェック
    if (pPalisana_goal) {
        if (pPalisana_goal->onChangeToInactive()) {
            pPalisana_goal = nullptr;
        }
    }

    switch (_pProg->get()) {
         case PROG_INIT: {
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT です");

             //最初の一機
             pDummy_->config(getSplManuf()->createKurokoLeader(pDummy_->_pKurokoA),
                                     pConnection_ShotDepo_->peek());
             pDummy_->_pKurokoA->setMvVelo(rr_mv_velo_);
             onCallUpAdelheid(pDummy_); //下位フォーメーションクラス個別実装の処理
                                        //開始座標と方向が定まる
             pDummy_->pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //座標計算のためスタート＆オプション指定
                                                                                     //オプションはEnemyAdelheidと合わせること
             //出現開始位置にpPalisana_start配備
             pPalisana_start->locateAs(pDummy_);
             coord next_X, next_Y, next_Z;
             pDummy_->pKurokoLeader_->getPointCoord(1, next_X, next_Y, next_Z);//[0] or [1] を気をつけよ
             pPalisana_start->_pKurokoA->setFaceAngTwd(next_X, next_Y, next_Z); //向きセット
             pPalisana_start->acitve_open(); //有効＆ハッチオープン
             //出現終了位置と、方角を求め、出現終了位置にpPalisana_goal配備
             coord end_X, end_Y, end_Z;
             coord end_prev_X, end_prev_Y, end_prev_Z;
             int spl_point_num = pDummy_->pKurokoLeader_->getPointNum();
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-1,
                                                    end_X, end_Y, end_Z); //最終補完点座標
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-2,
                                                    end_prev_X, end_prev_Y, end_prev_Z);  //最終-1 補完点座標
             pPalisana_goal->locate(end_X, end_Y, end_Z);
             pPalisana_goal->_pKurokoA->setFaceAngTwd(end_prev_X, end_prev_Y, end_prev_Z);
             //pPalisana_goal->acitve_open(
             //                  (frame)(pDummy_->pKurokoLeader_->getTotalDistance() / rr_mv_velo_)
             //                ); //遅れてハッチオープン

             pPalisana_goal->acitve_open();

             pDummy_->sayonara(); //ありがとうダミー
             _pProg->changeNext();
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT OK です");
             break;
         }

         case PROG_ENTRY: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_ENTRY です");
             }
             if (pPalisana_start) {
                 if (pPalisana_start->isOpenDone()) {
                     //ハッチオープン完了
                     _pProg->changeNext();
                 }
             } else {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_ENTRY pPalisana_startオープン完了前に破壊された！");
                 callUpMember(0); //招集打ち切り（これにより、本フォーメションオブジェクトは解放体制に入る）
                 _pProg->changeNothing(); //編隊処理自体終了
             }
             //ハッチオープン中
             break;
         }

         case PROG_FROMATION_MOVE1: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_FROMATION_MOVE1 です");
             }
             if (pPalisana_start) {
                 if (canCallUp()) {
                     if (_pProg->getFrameInProgress() % rr_interval_frames_ == 0) {
                         //２機目以降
                         EnemyAdelheid* pAdelheid = (EnemyAdelheid*)callUpMember(rr_num_formation_);
                         if (pAdelheid) {
                             SplineKurokoLeader* pKurokoLeader =
                                     getSplManuf()->createKurokoLeader(pAdelheid->_pKurokoA);
                             pAdelheid->config(pKurokoLeader, pConnection_ShotDepo_->peek());
                             pAdelheid->_pKurokoA->setMvVelo(rr_mv_velo_);
                             onCallUpAdelheid(pAdelheid); //下位フォーメーションクラス個別実装の処理
                         }
                     }
                 } else {
                    pPalisana_start->close_sayonara();
                    _pProg->changeNext(); //出現終了！
                 }
             } else {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_ENTRY pPalisana_start callUpMember完了前に破壊された！");
                 callUpMember(0); //招集打ち切り（これにより、本フォーメションオブジェクトは解放体制に入る）
                 _pProg->changeNext(); //出現終了！
             }
             break;
         }

         //メンバー減速
         case PROG_FROMATION_MOVE2: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_FROMATION_MOVE2 です");
             }

             if (mv_velo_member_ < -(rr_mv_velo_/8) ) {
                 mv_velo_member_ = -(rr_mv_velo_/8);
                 _pProg->changeNext(); //減速終了！
             } else {
                 mv_velo_member_ -= 2000;
             }
             break;
         }

         //メンバー停滞&発射
         case PROG_FROMATION_MOVE3: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_FROMATION_MOVE3 です");

                 GgafActor* pFollower = _listFollower.getCurrent();
                 int num_follwer = _listFollower.length();
                 for (int i = 0; i < num_follwer; i++) {
                     ((EnemyAdelheid*)pFollower)->open_shot();
                     pFollower = _listFollower.next();
                 }

             }

             if (_pProg->getFrameInProgress() == 360) {
                 _pProg->changeNext(); //停滞終了！
             }
             break;
         }

         //メンバー再始動
         case PROG_FROMATION_MOVE4: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_FROMATION_MOVE4 です");
             }
             if (mv_velo_member_ > rr_mv_velo_)  {
                 mv_velo_member_ = rr_mv_velo_;
                 _pProg->changeNext(); //再始動終了！
             } else {
                 mv_velo_member_ += 500;
             }
             break;
         }

         //待機
         case PROG_FROMATION_MOVE5: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_FROMATION_MOVE5 です");
             }
             break;
         }

//----------------------------------------------
         case PROG_LEAVE: {
             if (_pProg->isJustChanged()) {
                  _TRACE_("FormationAdelheid::processBehavior() PROG_LEAVE です");
                  if (pPalisana_goal) {
                      pPalisana_goal->close_sayonara();
                  }
             }

             break;
         }
         default:
             break;
     }
}

void FormationAdelheid::onSayonaraAll() {
    //このコールバックが呼び出された時点で、余命は FORMATION_END_DELAY フレームのはず
    _TRACE_("FormationAdelheid::onSayonaraAll() です");
    _pProg->change(PROG_LEAVE);
    //解放を待つ
}

void FormationAdelheid::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationAdelheid::~FormationAdelheid() {
    pConnection_ShotDepo_->close();
    pConnection_AdelheidDepo_->close();
}

