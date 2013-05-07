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
    setFormationMemberDepo(pConnection_AdelheidDepo_->peek());

    pConnection_ShotDepo_ = connectToDepositoryManager("EnemyAdelheidShot");

    updateRankParameter();


    useProgress(PROG_LEAVE);
}

void FormationAdelheid::updateRankParameter() {
    rr_num_formation_     = 1; //RR_FormationAdelheid_Num(_RANK_);            //編隊数
    rr_interval_frames_   = 12;
    rr_mv_velo_           = PX_C(8); //RR_FormationAdelheid_MvVelo(_RANK_);         //速度
}

void FormationAdelheid::initialize() {

}

void FormationAdelheid::onActive() {
    updateRankParameter();
    _pProg->reset(PROG_INIT);
}

void FormationAdelheid::processBehavior() {

    switch (_pProg->get()) {
         case PROG_INIT: {
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT だー");

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
             pPalisana_goal->acitve_open(
                               (frame)(pDummy_->pKurokoLeader_->getTotalDistance() / rr_mv_velo_)
                             ); //遅れてハッチオープン

             pDummy_->sayonara(); //ありがとうダミー
             _pProg->changeNext();
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT OK だー");
             break;
         }

         case PROG_ENTRY: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_ENTRY だー");
             }
             if (pPalisana_start->isOpenDone()) {
                 //ハッチオープン完了
                 _pProg->changeNext();
             }
             //ハッチオープン中
             break;
         }

         case PROG_FROMATION_MOVE1: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_FROMATION_MOVE1 だー");
             }
             if (canCallUp() && (_pProg->getFrameInProgress() % rr_interval_frames_ == 0)) {
                 //２機目以降
                 EnemyAdelheid* pAdelheid = (EnemyAdelheid*)callUpMember(rr_num_formation_);
                 if (pAdelheid) {
                     SplineKurokoLeader* pKurokoLeader =
                             getSplManuf()->createKurokoLeader(pAdelheid->_pKurokoA);
                     pAdelheid->config(pKurokoLeader, pConnection_ShotDepo_->peek());
                     pAdelheid->_pKurokoA->setMvVelo(rr_mv_velo_);
                     onCallUpAdelheid(pAdelheid); //下位フォーメーションクラス個別実装の処理
                 } else {
                     _pProg->changeNext(); //規定数出現終了
                 }
             }
             break;
         }

         case PROG_FROMATION_MOVE2: {
            if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_FROMATION_MOVE2 だー");
             }
             //コールバック processOnSayonar() が起こるまで待つ。
             break;
         }

         case PROG_LEAVE: {
             if (_pProg->isJustChanged()) {
                  _TRACE_("FormationAdelheid::processBehavior() PROG_LEAVE だー");
                 pPalisana_start->close_sayonara();
                 pPalisana_goal->close_sayonara();
             }
             if (_pProg->getFrameInProgress() == 15) {
                 setHitAble(false);
             }
             break;
         }
         default:
             break;
     }
}

void FormationAdelheid::onSayonaraAll() {
    //余命は FORMATION_END_DELAY フレーム
    //それ以内に閉じるアニメーションを終わらせましょう
    _TRACE_("FormationAdelheid::onSayonaraAll() だー");
    _pProg->change(PROG_LEAVE);
}

void FormationAdelheid::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（※ボーナススコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationAdelheid::~FormationAdelheid() {
    pConnection_ShotDepo_->close();
    pConnection_AdelheidDepo_->close();
}

