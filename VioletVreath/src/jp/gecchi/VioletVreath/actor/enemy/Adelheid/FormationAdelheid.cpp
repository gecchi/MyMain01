#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


FormationAdelheid::FormationAdelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationAdelheid";

    pPalisana1_ = NEW EnemyPalisana("Palisana1");
    pPalisana1_->inactivateImmed();
    addSubGroup(pPalisana1_);

    pPalisana2_ = NEW EnemyPalisana("Palisana2");
    pPalisana2_->inactivateImmed();
    addSubGroup(pPalisana2_);
    _TRACE_("だんぴん1");
    dump();

    //編隊隊員デポジトリセット
    pConnection_AdelheidDepo_ = connectToDepositoryManager("EnemyAdelheid4Formation");
    setFormationMemberDepo(pConnection_AdelheidDepo_->peek());



    pConnection_ShotDepo_ = connectToDepositoryManager("EnemyAdelheidShot");

    updateRankParameter();

    pFirstAdelheid_ = nullptr;

    useProgress(PROG_LEAVE);
}

void FormationAdelheid::updateRankParameter() {
    rr_num_formation_     = 2; //RR_FormationAdelheid_Num(_RANK_);            //編隊数
    rr_interval_frames_   = 30;
    rr_mv_velo_           = RR_FormationAdelheid_MvVelo(_RANK_);         //速度
}

void FormationAdelheid::initialize() {

}

void FormationAdelheid::onActive() {
    updateRankParameter();
    _pProg->reset(PROG_INIT);
}

void FormationAdelheid::processBehavior() {

    pConnection_AdelheidDepo_->peek()->dump();


    switch (_pProg->get()) {
         case PROG_INIT: {
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT だー");

             //最初の一機
             pFirstAdelheid_ = (EnemyAdelheid*)callUpMember(rr_num_formation_);
             if (!pFirstAdelheid_) {
                 //１機目が呼び出せなかったら編隊そのものを無し
                 _pProg->changeNothing();
                 sayonara();
                 break;
             }
             pFirstAdelheid_->inactivateImmed(); //計算用に呼び出したので、活動はちょっと待って。
             pFirstAdelheid_->config(getFormationSplManuf()->createKurokoLeader(pFirstAdelheid_->_pKurokoA),
                                     pConnection_ShotDepo_->peek());
             pFirstAdelheid_->_pKurokoA->setMvVelo(rr_mv_velo_);
             onCallUpAdelheid(pFirstAdelheid_); //下位フォーメーションクラス個別実装の処理
                                                //開始座標と方向が定まる
             //出現開始位置にpPalisana1_配備
             pPalisana1_->locateAs(pFirstAdelheid_);
             coord next_X, next_Y, next_Z;
             pFirstAdelheid_->pKurokoLeader_->getPointCoord(1, next_X, next_Y, next_Z);
             pPalisana1_->_pKurokoA->setFaceAngTwd(next_X, next_Y, next_Z); //向きセット
             pPalisana1_->acitve_open(); //有効＆ハッチオープン
             //出現終了位置と、方角を求め、出現終了位置にpPalisana2_配備
             coord end_X, end_Y, end_Z;
             coord end_prev_X, end_prev_Y, end_prev_Z;
             int spl_point_num = pFirstAdelheid_->pKurokoLeader_->getPointNum();
             pFirstAdelheid_->pKurokoLeader_->getPointCoord(spl_point_num-1,
                                                            end_X, end_Y, end_Z); //最終補完点座標
             pFirstAdelheid_->pKurokoLeader_->getPointCoord(spl_point_num-2,
                                                            end_prev_X, end_prev_Y, end_prev_Z);  //最終-1 補完点座標
             pPalisana2_->locate(end_X, end_Y, end_Z);
             pPalisana2_->_pKurokoA->setFaceAngTwd(end_prev_X, end_prev_Y, end_prev_Z);
             pPalisana2_->acitve_open();//有効＆ハッチオープン
             _pProg->changeNext();
             _TRACE_("FormationAdelheid::processBehavior() PROG_INIT OK だー");
             break;
         }
         case PROG_ENTRY: {
             if (_pProg->isJustChanged()) {
                 _TRACE_("FormationAdelheid::processBehavior() PROG_ENTRY だー");
             }
             if (pPalisana1_->isOpenDone()) {
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

             if (_pProg->getFrameInProgress() == rr_interval_frames_) {
                 //最初の１機目
                 pFirstAdelheid_->activate();
             } else if (canCallUp() && (_pProg->getFrameInProgress() % rr_interval_frames_ == 0)) {
                 //２機目以降
                 EnemyAdelheid* pAdelheid = (EnemyAdelheid*)callUpMember(rr_num_formation_);
                 if (pAdelheid) {
                     SplineKurokoLeader* pKurokoLeader =
                             getFormationSplManuf()->createKurokoLeader(pAdelheid->_pKurokoA);
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
                 pPalisana1_->close_sayonara();
                 pPalisana2_->close_sayonara();
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
void FormationAdelheid::processOnSayonara() {
    //余命は FORMATION_END_DELAY フレーム
    //それ以内に閉じるアニメーションを終わらせましょう
    _TRACE_("FormationAdelheid::processOnSayonara() だー");
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

