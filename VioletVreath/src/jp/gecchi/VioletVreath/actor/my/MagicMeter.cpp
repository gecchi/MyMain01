#include "stdafx.h"
#include "MagicMeter.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/CostDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/DamageDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MpBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/ShotMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/OptionMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/SmileMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/SpeedMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TorpedoMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/VreathMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor002.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor003.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicMeterCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicMeterStatus.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/VreathBar.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicMeter::MagicMeter(const char* prm_name, int* prm_pMP_MyShip, int* prm_pVreath_MyShip)
      : DefaultBoardSetActor(prm_name, "MagicMeter"),
width_px_(_pBoardSetModel->_fSize_BoardSetModelWidthPx),
height_px_(_pBoardSetModel->_fSize_BoardSetModelHeightPx),
width_(PX_C(width_px_)),
height_(PX_C(height_px_)) {

    _class_name = "MagicMeter";
    pTractorMagic_ = NEW TractorMagic("TRACTOR", prm_pMP_MyShip); //維持コスト有り
    pSpeedMagic_   = NEW SpeedMagic("SPEED", prm_pMP_MyShip);
    pLockonMagic_  = NEW LockonMagic("LOCKON", prm_pMP_MyShip);
    pTorpedoMagic_ = NEW TorpedoMagic("TORPEDO", prm_pMP_MyShip);
    pShotMagic_    = NEW ShotMagic("SHOT", prm_pMP_MyShip);
    pLaserMagic_   = NEW LaserMagic("LASER", prm_pMP_MyShip);
    pOptionMagic_  = NEW OptionMagic("OPTION", prm_pMP_MyShip);
    pVreathMagic_  = NEW VreathMagic("VREATH", prm_pMP_MyShip);
    pSmileMagic_   = NEW SmileMagic("SMILE", prm_pMP_MyShip); //即効魔法
    lstMagic_.addLast(pTractorMagic_);
    lstMagic_.addLast(pSpeedMagic_  );
    lstMagic_.addLast(pLockonMagic_ );
    lstMagic_.addLast(pTorpedoMagic_);
    lstMagic_.addLast(pShotMagic_  );
    lstMagic_.addLast(pLaserMagic_  );
    lstMagic_.addLast(pOptionMagic_ );
    lstMagic_.addLast(pVreathMagic_ );
    lstMagic_.addLast(pSmileMagic_  );

    int magic_num = lstMagic_.length();
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(lstMagic_.getNext(i));
    }

    papLvTgtMvCur_   = NEW MagicLvCursor001*[magic_num];
    papLvNowCur_     = NEW MagicLvCursor002*[magic_num];
    papLvCastingCur_ = NEW MagicLvCursor003*[magic_num];
    r_roll_      = NEW float[magic_num];
    r_roll_velo_ = NEW float[magic_num];
    Magic* pMagic;
    MagicList::Elem* pMagicElem = lstMagic_.getElemFirst();
    for (int i = 0; i < magic_num; i++) {
        pMagic = pMagicElem->getValue();
        papLvNowCur_[i] = NEW MagicLvCursor002("LvHilightCursor", this, pMagic); //現レベル強調カーソル
        papLvCastingCur_[i] = NEW MagicLvCursor003("LvCastMarkCursor", this, pMagic); //詠唱レベル強調カーソル
        papLvCastingCur_[i]->markOff();
        papLvTgtMvCur_[i] = NEW MagicLvCursor001("LvTargetCursor", this, pMagic); //メータ補助カーソル
        pMagicElem = pMagicElem->_pNext;
    }
    for (int i = 0; i < magic_num; i++) {
        r_roll_[i] = 0.0f;
        r_roll_velo_[i] = 0.0f;
    }

    //表示プリオリティを考慮して、addSubGroupを行う事！
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvNowCur_[i]); //現レベル強調カーソル
    }
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvCastingCur_[i]); //詠唱レベル強調カーソル
    }
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvTgtMvCur_[i]); //メータ補助カーソル
    }

    pixcoord mp_px = 800;
    int vreath_val = *prm_pVreath_MyShip; //最初が満タンだからこれを使用
    pixcoord vreath_px = mp_px;
    //MPバー設置
    pMpBar_ = NEW MpBar("MpBar");
    pMpBar_->linkVariable(prm_pMP_MyShip);
    pMpBar_->graduate(0, MY_SHIP_MAX_MP, mp_px); //現在値で画面表示は600pxとする。
    addSubGroup(pMpBar_);
    //Vreathバー設置
    pVreathBar_ = NEW VreathBar("VreathBar");
    pVreathBar_->linkVariable(prm_pVreath_MyShip);
    pVreathBar_->graduate(0, vreath_val, vreath_px); //現在値で画面表示は600pxとする。
    addSubGroup(pVreathBar_);

    //エネルギーバーのコスト表示バー
    pMpCostDispBar_ = NEW CostDispBar("CostDispBar", pMpBar_);
    pMpCostDispBar_->graduate(-MY_SHIP_MAX_MP, +MY_SHIP_MAX_MP, mp_px*2);
    addSubGroup(pMpCostDispBar_);
    //Vreathバー、コスト表示バー
    pVreathCostDispBar_ = NEW CostDispBar("CostDispBar2", pVreathBar_);
    pVreathCostDispBar_->graduate(-vreath_val, +vreath_val, vreath_px*2);
    addSubGroup(pVreathCostDispBar_);
    //Vreathバー、ダメージ表示バー
    pDamageDispBar_ = NEW DamageDispBar("DamageDispBar", pVreathBar_);
    pDamageDispBar_->graduate(-vreath_val, +vreath_val, vreath_px*2);
    addSubGroup(pDamageDispBar_);

    //残魔法効果持続時間表示
    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    addSubGroup(pMagicMeterStatus_);

    //メータ主カーソル
    pMainCur_ = NEW MagicMeterCursor001("MagicCursor", this);
    addSubGroup(pMainCur_);

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_CURSOR_MOVE_METER             , "WAVE_MM_CURSOR_MOVE_METER");  //主メーターカーソル移動時
    pSeTx->set(SE_CURSOR_MOVE_LEVEL             , "WAVE_MM_CURSOR_MOVE_LEVEL");  //上下レベル移動時
    pSeTx->set(SE_CURSOR_MOVE_LEVEL_CANCEL      , "WAVE_MM_CURSOR_MOVE_LEVEL_CANCEL");  //上下レベル移動キャンセル（）
    pSeTx->set(SE_CURSOR_BAD_MOVE               , "WAVE_MM_CURSOR_BAD_MOVE");  //ダメなカーソル移動（鳴るとうるさいので現在未使用）
    pSeTx->set(SE_EXECUTE_LEVELUP_MAGIC         , "WAVE_MM_EXECUTE_LEVELUP_MAGIC");  //レベルアップ実行時
    pSeTx->set(SE_EXECUTE_LEVELDOWN_MAGIC       , "WAVE_MM_EXECUTE_LEVELDOWN_MAGIC");  //レベルダウン実行時
    pSeTx->set(SE_EXECUTE_CANCEL_LEVELUP_MAGIC  , "WAVE_MM_EXECUTE_CANCEL_LEVELUP_MAGIC");  //（詠唱キャンセルして）レベルアップ実行時
    pSeTx->set(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC, "WAVE_MM_EXECUTE_CANCEL_LEVELDOWN_MAGIC");  //（詠唱キャンセルして）レベルダウン実行時
    pSeTx->set(SE_NG_MP_IS_SHORT                , "WAVE_MM_NG_MP_IS_SHORT");  //MPが足りないため発動あるいは効果開始できない場合
    pSeTx->set(SE_EFFECT_MAGIC                  , "WAVE_MM_EFFECT_MAGIC");  //発動が完了し、効果発生時
    pSeTx->set(SE_NOTICE_LEVELDOWN_MAGIC        , "WAVE_MM_NOTICE_LEVELDOWN_MAGIC");  //レベルダウン発生予告
    pSeTx->set(SE_BAD_OPERATION                 , "WAVE_MM_BAD_OPERATION");  //操作ミス。出来ない入力、ブブー

    pSeTx4Cast_ = NEW GgafDxSeTransmitterForActor(this);
    pSeTx4Invoke_ = NEW GgafDxSeTransmitterForActor(this);
    for (int i = 0; i < magic_num; i++) {
        pSeTx4Cast_->set(i, "WAVE_MM_CASTING", i); //詠唱中SE。チャンネル明示指定
        pSeTx4Cast_->setLooping(i, true);
        pSeTx4Invoke_->set(i, "WAVE_MM_INVOKING", i); //発動中SE。チャンネル明示指定
        pSeTx4Invoke_->setLooping(i, true);
    }
    fraeme_of_notice_remaind_ = 60*5;//残り僅か警告発生の残り時間
    alpha_velo_ = -0.01f;
}


void MagicMeter::loadStatus(int prm_saveno) {
    st_[prm_saveno].seekg(std::stringstream::beg); //頭出し
    load(st_[prm_saveno]);
}

void MagicMeter::saveStatus(int prm_saveno) {
    save(st_[prm_saveno]);
}

void MagicMeter::save(std::stringstream& sts) {
    sts << pMpBar_->getQty() << " ";
    Magic* pOrgMagic = lstMagic_.getCurrent();
    int len_magics = lstMagic_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->save(sts);
        pOrgMagic = lstMagic_.next();
    }
}

void MagicMeter::load(std::stringstream& sts) {
    int mp;
    sts >> mp;
    pMpBar_->setQty(mp);

    Magic* pOrgMagic = lstMagic_.getCurrent();
    int len_magics = lstMagic_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->load(sts);
        pOrgMagic = lstMagic_.next();
    }
}

void MagicMeter::initialize() {
    pMpBar_->position(_x, _y + height_ + PX_C(16));
    pVreathBar_->position(_x, _y + height_ + PX_C(16) + PX_C(16) );
    pMagicMeterStatus_->positionAs(this);

    getUvFlipper()->exec(FLIP_ORDER_LOOP, 10); //アニメ順序
    Magic* pMagic;
    for (int i = 0; i < lstMagic_.length(); i++) {
        pMagic = lstMagic_.getFromFirst(i);
        papLvTgtMvCur_[i]->moveTo(pMagic->level_);
        papLvNowCur_[i]->moveTo(pMagic->level_);
        papLvCastingCur_[i]->moveTo(0);
    }
}
void MagicMeter::onReset() {
    Magic* pMagic;
    for (int i = 0; i < lstMagic_.length(); i++) {
        pMagic = lstMagic_.getFromFirst(i);
        pMagic->resetTree(); //先にMagicをリセットさせる。
        papLvTgtMvCur_[i]->moveTo(pMagic->level_);
        papLvNowCur_[i]->moveTo(pMagic->level_);
        papLvCastingCur_[i]->moveTo(0);

        r_roll_[i] = 0.0f;
        r_roll_velo_[i] = 0.0f;

        pSeTx4Cast_->stop(i);
        pSeTx4Invoke_->stop(i);
    }
    pMpCostDispBar_->setQty(0);
    pVreathCostDispBar_->setQty(0);
    pDamageDispBar_->setQty(0);
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {

    ////////////////////////魔法メーターについての処理//////////////////////////
    VirtualButton* pVbPlay = VB_PLAY;
    if (pVbPlay->isBeingPressed(VB_POWERUP)) {
        alpha_velo_ = 0.05f;
        Magic* pActiveMagic = lstMagic_.getCurrent();     //アクティブな魔法
        int active_idx = lstMagic_.getCurrentIndex();     //アクティブな魔法のインデックス
        progress active_prg = pActiveMagic->getProgress()->get();  //アクティブな魔法の進捗
        if (pVbPlay->isPushedDown(VB_POWERUP)) {
            rollOpen(active_idx);
        }

        if (pVbPlay->isAutoRepeat(VB_RIGHT)) {    //「→」押下時
            //レベル表示
            if (active_prg == Magic::STATE_CASTING) {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvCastingCur_[active_idx]->point_lv_) {
                    getSeTx()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvCastingCur_[active_idx]->point_lv_); //レベルカーソルを詠唱先レベルに戻す
                }
            } else {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvNowCur_[active_idx]->point_lv_) {
                    getSeTx()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvNowCur_[active_idx]->point_lv_); //レベルカーソルをアクティブレベルに戻す
                }
            }
            rollClose(active_idx); //現在ロールクローズ

            lstMagic_.next(); //メーターを１つ進める
            pActiveMagic= lstMagic_.getCurrent();     //更新
            active_idx = lstMagic_.getCurrentIndex(); //更新
            active_prg = pActiveMagic->getProgress()->get(); //更新

            rollOpen(active_idx);  //進めた先をロールオープン
            pMainCur_->moveTo(active_idx); //メーターカーソルも１つ進める
            getSeTx()->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(VB_LEFT)) { //「←」押下時
            //レベル表示
            if (active_prg == Magic::STATE_CASTING) {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvCastingCur_[active_idx]->point_lv_) {
                    getSeTx()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvCastingCur_[active_idx]->point_lv_); //レベルカーソルを詠唱先レベルに戻す
                }
            } else {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvNowCur_[active_idx]->point_lv_) {
                    getSeTx()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvNowCur_[active_idx]->point_lv_); //レベルカーソルをアクティブレベルに戻す
                }
            }
            rollClose(active_idx); //現在ロールクローズ

            lstMagic_.prev(); //メーターを１つ戻す
            pActiveMagic= lstMagic_.getCurrent();     //更新
            active_idx = lstMagic_.getCurrentIndex(); //更新
            active_prg = pActiveMagic->getProgress()->get(); //更新

            rollOpen(active_idx); //戻した先をロールオープン
            pMainCur_->moveTo(active_idx); //メーターカーソルも１つ戻す
            getSeTx()->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(VB_UP) ) {  // 「↑」押下時
            if (pActiveMagic->max_level_ > papLvTgtMvCur_[active_idx]->point_lv_) {
                getSeTx()->play(SE_CURSOR_MOVE_LEVEL);
                papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvTgtMvCur_[active_idx]->point_lv_ + 1);
            }

        } else if (pVbPlay->isAutoRepeat(VB_DOWN)) {  //「↓」押下時
            if (0 < papLvTgtMvCur_[active_idx]->point_lv_) {
                getSeTx()->play(SE_CURSOR_MOVE_LEVEL);
                papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvTgtMvCur_[active_idx]->point_lv_ - 1);
            }
        } else {

        }
        //MPコストバー
        if (r_roll_[active_idx] > 0.01f) {
            if (papLvTgtMvCur_[active_idx]->point_lv_ == pActiveMagic->level_) {
                //カーソルがより現在と同じレベルを指している場合
                pMpCostDispBar_->setQty(0);
            } else if (papLvTgtMvCur_[active_idx]->point_lv_ > pActiveMagic->level_) {
                //カーソルが現在より高いレベルを指している場合
                //MPコストを負の赤の表示
                pMpCostDispBar_->setQty(
                  -1*pActiveMagic->level_up_cost_[pActiveMagic->level_][papLvTgtMvCur_[active_idx]->point_lv_]
                );
            } else {
                //カーソルが現在より低いレベルを指している場合
                //正の青の表示
                if (pActiveMagic->keep_cost_base_ <= 0) {
                    //維持コスト無しの場合のみMP還元バー表示
                    pMpCostDispBar_->setQty(
                      pActiveMagic->calcReduceMp(pActiveMagic->level_,  papLvTgtMvCur_[active_idx]->point_lv_)
                    );
                } else {
                    //維持コスト有りの場合、MP還元は無い
                }
            }
        } else {
            pMpCostDispBar_->setQty(0);
        }

        //Vreathバーがアクティブだった場合、Vreath増分表示
        if (pActiveMagic == pVreathMagic_) {
            VreathMagic* pVM = (VreathMagic*)pActiveMagic;
            if (r_roll_[active_idx] > 0.01f) {
                if (papLvTgtMvCur_[active_idx]->point_lv_ == pVM->level_) {
                    //カーソルがより現在と同じレベルを指している場合
                    pVreathCostDispBar_->setQty(0);
                } else if (papLvTgtMvCur_[active_idx]->point_lv_ > pVM->level_) {
                    //カーソルが現在より高いレベルを指している場合
                    //正の青の表示
                    pVreathCostDispBar_->setQty(
                            (int)(pVM->calcTotalVreath(pActiveMagic->level_,  papLvTgtMvCur_[active_idx]->point_lv_))
                    );
                } else {
                    //カーソルが現在より低いレベルを指している場合
                    pVreathCostDispBar_->setQty(0);
                }
            } else {
                pVreathCostDispBar_->setQty(0);
            }
        } else {
            pVreathCostDispBar_->setQty(0);
        }

        //「決定」時
        if (pVbPlay->isPushedDown(VB_SHOT1) || pVbPlay->isPushedDown(VB_SHOT2) || pVbPlay->isPushedDown(VB_TURBO)) {
            int r = pActiveMagic->cast(papLvTgtMvCur_[active_idx]->point_lv_);
            switch (r) {
                case MAGIC_CAST_NG_INVOKING_NOW: {
                    getSeTx()->play(SE_BAD_OPERATION);
                    break;
                }
                case MAGIC_CAST_NG_MP_IS_SHORT: {
                    getSeTx()->play(SE_NG_MP_IS_SHORT);
                    break;
                }
            }
        }
    } else  {
        alpha_velo_ = -0.02f;
        if (pVbPlay->isReleasedUp(VB_POWERUP)) {
            rollClose(lstMagic_.getCurrentIndex());
        }
        pMpCostDispBar_->setQty(0);
        pVreathCostDispBar_->setQty(0);
    }

    addAlpha(alpha_velo_);
    if (getAlpha() < 0.2f) {
        setAlpha(0.2f); //非アクティブ時のうっすら表示
    } else if (getAlpha() > 1.0f) {
        setAlpha(1.0f); //アクティブ時のハッキリ表示
    }

    ////////////////////////各魔法についての処理//////////////////////////
    GgafProgress* pMagicProg;
    Magic* pMagic = nullptr;
    int pMagic_level, pMagic_new_level;
    MagicLvCursor001* pLvTgtMvCur;
    MagicLvCursor002* pLvNowCur;
    MagicLvCursor003* pLvCastingCur;

    for (int m = 0; m < lstMagic_.length(); m++) {
        pMagic = lstMagic_.getFromFirst(m);    //魔法オブジェクト
        pMagicProg = pMagic->_pProg;           //魔法の進捗状況
        pMagic_level = pMagic->level_;         //魔法の現レベル
        pMagic_new_level = pMagic->new_level_; //魔法の新レベル（詠唱中・発動中の場合）
        pLvTgtMvCur = papLvTgtMvCur_[m];       //操作カーソルオブジェクト(↑↓移動)
        pLvNowCur = papLvNowCur_[m];           //現レベル強調表示用カーソルオブジェクト
        pLvCastingCur = papLvCastingCur_[m];   //詠唱中レベル強調表示用カーソルオブジェクト（CASTINGなどの文字）

        //ロールアップ
        r_roll_[m] += r_roll_velo_[m];
        if (r_roll_[m] < 0.0f) {
            r_roll_[m] = 0.0f;
            r_roll_velo_[m] = 0.0f;
        }
        if (r_roll_[m] > 1.0f) {
            r_roll_[m] = 1.0f;
            r_roll_velo_[m] = 0.0f;
        }

        //詠唱開始
        if (pMagicProg->isJustChangedTo(Magic::STATE_CASTING)) {
            switch (pMagic->last_cast_) {
                case MAGIC_CAST_OK_LEVELUP: {
                    getSeTx()->play(SE_EXECUTE_LEVELUP_MAGIC);
                    pSeTx4Cast_->play(m);
                    pLvTgtMvCur->blink(); //ピカピカ！
                    pLvCastingCur->markOnLevelUpCast(pMagic_new_level);
                    break;
                }
                case MAGIC_CAST_LEVELDOWN: {
                    getSeTx()->play(SE_EXECUTE_LEVELDOWN_MAGIC);
                    pLvTgtMvCur->blink(); //ピカピカ！
                    pLvNowCur->moveSmoothTo(pMagic_new_level);
                    pLvNowCur->blink();
                    if (pMagic_new_level > 0) {
                        //レベル0以外へのレベルダウンならば EFFECT エフェクト
                        pLvCastingCur->markOnLevelDownCast(pMagic_new_level);
                    }
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
                    if ( pLvCastingCur->point_lv_ ==  pLvTgtMvCur->point_lv_) {
                        //現在詠唱中のレベルで再度押下
                        //なにもしない
                    } else {
                        getSeTx()->play(SE_EXECUTE_CANCEL_LEVELUP_MAGIC);
                        pSeTx4Cast_->play(m);
                        pLvTgtMvCur->blink(); //ピカピカ！
                        pLvCastingCur->markOnLevelUpCast(pMagic_new_level);
                    }
                    break;
                }
                case MAGIC_CAST_CANCEL_AND_LEVELDOWN: {
                    getSeTx()->play(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC);
                    pLvTgtMvCur->blink(); //ピカピカ！
                    pLvNowCur->moveSmoothTo(pMagic_new_level);
                    pLvNowCur->blink();
                    if (pMagic_new_level > 0) {
                        //レベル0以外へのレベルダウンならば EFFECT エフェクト
                        pLvCastingCur->markOnLevelDownCast(pMagic_new_level);
                    } else {
                        //レベル0以外へのレベルダウンならば、おしまい。
                        pLvCastingCur->markOff();
                    }
                    break;
                }
                default: {
                    throwGgafCriticalException("MagicMeter::processBehavior() ["<<pMagic->getName()<<"] おかしい。来るはずがない。pMagic->last_cast_="<<(pMagic->last_cast_));
                }
            }
        }
        //詠唱中
        if (pMagicProg->get() == Magic::STATE_CASTING) {
            if (pMagic->new_level_ > pMagic_level) {
                //レベルアップなら音程アップ
                float r = ((float)(pMagicProg->getFrameInProgress())) / ((float)(pMagic->time_of_next_state_));
                pSeTx4Cast_->get(m)->setFrequencyRate(1.0f + (r*3.0f));
            }
        }
        //詠唱中ではなくなった
        if (pMagicProg->isJustChangedFrom(Magic::STATE_CASTING)) {
            pSeTx4Cast_->stop(m); //消音
        }

        //発動開始時
        if (pMagicProg->isJustChangedTo(Magic::STATE_INVOKING)) {
            switch (pMagic->last_invoke_) {
                case MAGIC_INVOKE_OK_LEVELUP: {
                    pSeTx4Invoke_->play(m);
                    pLvTgtMvCur->dispDisable(); //操作不可表示
                    pLvNowCur->dispDisable();
                    if (pLvTgtMvCur->point_lv_ == pMagic_level) {
                        //カーソルが現レベルを指している場合に限り
                        //新しいレベルにこっそり動かしてあげる。
                        pLvTgtMvCur->moveSmoothTo(pMagic_new_level);
                    }
                    frame time_of_invoking = (frame)(pMagic->level_up_time_of_invoking_[pMagic_level][pMagic_new_level]);
                    pLvNowCur->moveSmoothTo(pMagic_new_level, time_of_invoking); //INVOKINGに合わせて動く
                    pLvCastingCur->markOnInvoke(pMagic_new_level);
                    break;
                }
                case MAGIC_INVOKE_OK_LEVELDOWN: {
                    //レベルダウンは、詠唱開始時に現在レベル強調表示のカーソル移動が既におこなわれている。
                    //ので、ここでは何もしない。
                    break;
                }
                default: {
                    throwGgafCriticalException("MagicMeter::processBehavior() ["<<pMagic->getName()<<"] おかしい。来るはずがない。pMagic->last_invoke_="<<(pMagic->last_invoke_));
                }
            }
        }
        //発動中
        if (pMagicProg->get() == Magic::STATE_INVOKING) {
            if (pMagic->new_level_ > pMagic_level) {
                //レベルアップ時
                float r = ((float)(pMagicProg->getFrameInProgress())) / ((float)(pMagic->time_of_next_state_));
                pSeTx4Invoke_->get(m)->setFrequencyRate(1.0f + (r*3.0f));//音程を上げる
            }
        }
        //発動ではなくなった
        if (pMagicProg->isJustChangedFrom(Magic::STATE_INVOKING)) {
            pSeTx4Invoke_->stop(m); //消音
            pLvTgtMvCur->dispEnable(); //操作不可表示を解除
            pLvNowCur->dispEnable();
        }
        //効果開始時
        if (pMagicProg->isJustChangedTo(Magic::STATE_EFFECT_START)) {
            switch (pMagic->last_effect_) {
                case MAGIC_EFFECT_OK_LEVELUP: {
                    if (pMagic->time_of_effect_base_ == 0) {
                        //即効性魔法の場合
                        getSeTx()->play(SE_EFFECT_MAGIC);
                        pLvCastingCur->markOnEffect(pMagic_level);
                    } else {
                        //通常魔法の場合
                        getSeTx()->play(SE_EFFECT_MAGIC);
                        pLvCastingCur->markOnEffect(pMagic_level);
                    }
                    break;
                }
                case MAGIC_EFFECT_OK_LEVELDOWN: {
                    if (pMagic->time_of_effect_base_ == 0) {
                        //速攻魔法の終了のレベルダウン場合
                        _TRACE_("MagicMeter::processBehavior() ["<<pMagic->getName()<<"] 速攻魔法のレベルダウンのレベルダウン");
                        pLvNowCur->moveSmoothTo(pMagic_level);
                    } else {
                        //普通のレベルダウン
                        getSeTx()->play(SE_EXECUTE_LEVELDOWN_MAGIC);
                        if (pLvTgtMvCur->point_lv_ == pMagic->last_level_) {
                            //持続時間満期、あるいはMP枯渇時、
                            //カーソルがレベルダウン前の現行レベルを指していれば、
                            //こっそり、カーソルも一緒に移動
                            pLvTgtMvCur->moveSmoothTo(pMagic_level);
                        }
                        pLvNowCur->moveSmoothTo(pMagic_level);
                        pLvNowCur->blink();
                        if (pMagic_level > 0) {
                            pLvCastingCur->markOnEffect(pMagic_level);
                        }
                    }
                    break;
                }
                default: {
                    throwGgafCriticalException("MagicMeter::processBehavior() ["<<pMagic->getName()<<"] おかしい。来るはずがない。pMagic->last_effect_="<<(pMagic->last_effect_));
                }
            }
        }

        //STATE_NOTHINGへ移行した
        if (pMagicProg->isJustChangedTo(Magic::STATE_NOTHING)) {
            if (pMagicProg->isJustChangedFrom(Magic::STATE_CASTING)) { //詠唱→STATE_NOTHING
                //空詠唱（詠唱をキャンセルした or 詠唱したが詠唱完了時にMPが足りなかった）
                _TRACE_("MagicMeter::processBehavior() ["<<pMagic->getName()<<"] 詠唱→STATE_NOTHING 空詠唱乙。");
                pLvCastingCur->markOff(); //マークオフ！
                pLvNowCur->moveSmoothTo(pMagic_level);
                pLvTgtMvCur->moveSmoothTo(pMagic_level); //レベルカーソルをアクティブレベルに戻す
                if (pMagic->last_invoke_ == MAGIC_INVOKE_NG_MP_IS_SHORT) {
                    _TRACE_("MagicMeter::processBehavior() ["<<pMagic->getName()<<"] 空詠唱乙の原因は MAGIC_INVOKE_NG_MP_IS_SHORT だったため ");
                    getSeTx()->play(SE_NG_MP_IS_SHORT);
                } else {
                    getSeTx()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                }
            }
            if (pMagicProg->isJustChangedFrom(Magic::STATE_INVOKING)) {  //発動→STATE_NOTHING
                //空発動（発動したが、発動完了時、MPが足りなかったので、効果開始出来なかった）
                _TRACE_("MagicMeter::processBehavior() ["<<pMagic->getName()<<"] 発動→STATE_NOTHING 空発動乙 ");
                pLvCastingCur->markOff(); //マークオフ！
                pLvNowCur->moveSmoothTo(pMagic_level);
                pLvTgtMvCur->moveSmoothTo(pMagic_level); //レベルカーソルをアクティブレベルに戻す
                if (pMagic->last_effect_ == MAGIC_EFFECT_NG_MP_IS_SHORT) {
                    _TRACE_("MagicMeter::processBehavior() ["<<pMagic->getName()<<"] 空発動乙の原因は MAGIC_EFFECT_NG_MP_IS_SHORT だったため ");
                    getSeTx()->play(SE_NG_MP_IS_SHORT);
                } else {
                    getSeTx()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                }
            }
        }

        //もうすぐレベルダウン警告
        if (pMagic->lvinfo_[pMagic_level].remainingtime_of_effect_ == fraeme_of_notice_remaind_) {
            getSeTx()->play(SE_NOTICE_LEVELDOWN_MAGIC);
        }
    }

//    //debug -------------->
//    if (GgafDxInput::isPushedDownKey(DIK_K)) {
//        _TRACE_("MagicMeter saveStatus(0)!!!!");
//        saveStatus(0);
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_L)) {
//        _TRACE_("MagicMeter loadStatus(0)!!!!");
//        loadStatus(0);
//    }
//    //<-----------------debug
}

void MagicMeter::processJudgement() {
}

void MagicMeter::onInactive() {
}

void MagicMeter::processDraw() {
    GgafDxBoardSetEffect* const pBoardSetEffect = _pBoardSetEffect;
    ID3DXEffect* pID3DXEffect = pBoardSetEffect->_pID3DXEffect;
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();

    HRESULT hr;
    //パワーメーター
    //[====]が１つの大きさ [====][====][====]
    MagicList::Elem* pElem = lstMagic_.getElemFirst();
    Magic* pMagic;
    int pMagic_level;
    int len_magics = lstMagic_.length();
    int n = 0;
    float u,v;
    float x = float(C_PX(_x));
    float y = float(C_PX(_y));
    float z = float(C_PX(_z));
    float alpha = getAlpha();
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//一周したのでアクティブであるはず
        pMagic_level = pMagic->level_;
        n = 0;
        float wx = width_px_*i;
        //マジックメーター背景
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[n], x + wx);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_x) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_y) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_z) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[n], alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");
        if (pMagic_level > 0 && pMagic->lvinfo_[pMagic_level].remainingtime_of_effect_ <= fraeme_of_notice_remaind_) {
            pUvFlipper->getUV(1, u, v); //パターン1は赤背景、残り時間がやばい事を示す
        } else {
            pUvFlipper->getUV(0, u, v); //パターン0は通常背景
        }
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
        n++;

        //マジックメーター上の現在のマジックレベル表示
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[n], x + wx);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_x) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_y) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_z) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[n], alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");
        pUvFlipper->getUV(pMagic->lvinfo_[pMagic_level].pno_, u, v);
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
        n++;

        float rr = r_roll_[i];
        if (rr > 0.1f) {
            //各マジック要素
            int lv_slecter_num = pMagic->max_level_+1;
            for (int j = 0; j < lv_slecter_num; j++) {
                //魔法名
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[n], x + wx);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_x) に失敗しました。");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[n], y - (height_px_*(j+1)*rr));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_y) に失敗しました。");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_z[n], z);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_z) に失敗しました。");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[n], alpha*rr); //アクティブなら濃いめ
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");

                if (pMagic->chkCastAble(j) <= MAGIC_CAST_NG_MP_IS_SHORT) {
                    //MAGIC_CAST_NG_MP_IS_SHORT か MAGIC_CAST_NG_INVOKING_NOW
                    //詠唱不可表示
                    pUvFlipper->getUV(pMagic->lvinfo_[j].pno_ + 1, u, v); //右隣のテクスチャパターンが DISABLE なパターン前提
                } else {
                    //詠唱可能表示
                    pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                }
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[n], v);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
                n++;
            }
        }
        _pBoardSetModel->GgafDxBoardSetModel::draw(this, n);
        pElem = pElem->_pNext;
    }
}

void MagicMeter::rollOpen(int prm_meter_index) {
    r_roll_velo_[prm_meter_index] = 0.1f;
}

void MagicMeter::rollClose(int prm_meter_index) {
    r_roll_velo_[prm_meter_index] = -0.02f;
}

MagicMeter::~MagicMeter() {
    GGAF_DELETEARR(papLvTgtMvCur_);
    GGAF_DELETEARR(papLvNowCur_);
    GGAF_DELETEARR(papLvCastingCur_);
    GGAF_DELETEARR(r_roll_);
    GGAF_DELETEARR(r_roll_velo_);
    GGAF_DELETE(pSeTx4Cast_);
    GGAF_DELETE(pSeTx4Invoke_);
}
