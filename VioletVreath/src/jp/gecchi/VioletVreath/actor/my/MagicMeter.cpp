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
      : DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    width_px_ = _pBoardSetModel->_fSize_BoardSetModelWidthPx;
    height_px_ = _pBoardSetModel->_fSize_BoardSetModelHeightPx;
    width_ = PX_C(width_px_);
    height_ = PX_C(height_px_);

//    pMP_MyShip_ = prm_pMP_MyShip;
//    cost_disp_mp_.graduate(pMP_MyShip_->_max_val_px, pMP_MyShip_->_max_val);
//    cost_disp_mp_.set(0);
//    pVreath_MyShip_ = prm_pVreath_MyShip;
//    cost_disp_vreath.graduate(pVreath_MyShip_->_max_val_px, pVreath_MyShip_->_max_val);
//    cost_disp_vreath.set(0);
//    damage_disp_vreath.graduate(pVreath_MyShip_->_max_val_px, pVreath_MyShip_->_max_val);
//    damage_disp_vreath.set(0);

    pTractorMagic_ = NEW TractorMagic("TRACTOR", prm_pMP_MyShip);
    pSpeedMagic_   = NEW SpeedMagic("SPEED", prm_pMP_MyShip);
    pLockonMagic_  = NEW LockonMagic("LOCKON", prm_pMP_MyShip);
    pTorpedoMagic_ = NEW TorpedoMagic("TORPEDO", prm_pMP_MyShip);
    pLaserMagic_   = NEW LaserMagic("LASER", prm_pMP_MyShip);
    pOptionMagic_  = NEW OptionMagic("OPTION", prm_pMP_MyShip);
    pVreathMagic_  = NEW VreathMagic("VREATH", prm_pMP_MyShip);
    pSmileMagic_   = NEW SmileMagic("SMILE", prm_pMP_MyShip); //即効魔法
    lstMagic_.addLast(pTractorMagic_);
    lstMagic_.addLast(pSpeedMagic_  );
    lstMagic_.addLast(pLockonMagic_ );
    lstMagic_.addLast(pTorpedoMagic_);
    lstMagic_.addLast(pLaserMagic_  );
    lstMagic_.addLast(pOptionMagic_ );
    lstMagic_.addLast(pVreathMagic_ );
    lstMagic_.addLast(pSmileMagic_  );

    int magic_num = lstMagic_.length();

    for (int i = 0; i < magic_num; i++) {
        addSubGroup(lstMagic_.getNext(i));
    }

    papLvTargetCursor_      = NEW MagicLvCursor001*[magic_num];
    papLvHilightCursor_     = NEW MagicLvCursor002*[magic_num];
    papLvCastingMarkCursor_ = NEW MagicLvCursor003*[magic_num];
    paFloat_rr_      = NEW float[magic_num];
    paFloat_velo_rr_ = NEW float[magic_num];
    Magic* pMagic;
    MagicList::Elem* pMagicElem = lstMagic_.getElemFirst();
    for (int i = 0; i < magic_num; i++) {
        pMagic = pMagicElem->getValue();
        papLvHilightCursor_[i] = NEW MagicLvCursor002("LvHilightCursor", this, pMagic); //現レベル強調カーソル
        papLvCastingMarkCursor_[i] = NEW MagicLvCursor003("LvCastMarkCursor_", this, pMagic); //詠唱レベル強調カーソル
        papLvCastingMarkCursor_[i]->markOff();
        papLvTargetCursor_[i] = NEW MagicLvCursor001("LvTargetCursor", this, pMagic); //メータ補助カーソル
        pMagicElem = pMagicElem->_pNext;
    }
    for (int i = 0; i < magic_num; i++) {
        paFloat_rr_[i] = 0.0f;
        paFloat_velo_rr_[i] = 0.0f;
    }

    //表示プリオリティを考慮して、addSubGroupを行う事！
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvHilightCursor_[i]); //現レベル強調カーソル
    }
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvCastingMarkCursor_[i]); //詠唱レベル強調カーソル
    }
    for (int i = 0; i < magic_num; i++) {
        addSubGroup(papLvTargetCursor_[i]); //メータ補助カーソル
    }


    //エネルギーバー設置
    pMpBar_ = NEW MpBar("MpBar");
    pMpBar_->_pPxQuantity->link(prm_pMP_MyShip);
    pMpBar_->graduatePxQty(600, pMpBar_->getQty()); //現在値で画面表示は600pxとする。
    addSubGroup(pMpBar_);
    //Vreathバー設置
    pVreathBar_ = NEW VreathBar("VreathBar");
    pVreathBar_->_pPxQuantity->link(prm_pVreath_MyShip);
    pVreathBar_->graduatePxQty(600, pVreathBar_->getQty()); //現在値で画面表示は600pxとする。
    addSubGroup(pVreathBar_);

    //エネルギーバーのコスト表示バー
    pMpCostDispBar_ = NEW CostDispBar("CostDispBar", pMpBar_);
    pMpCostDispBar_->graduatePxQty(600, pMpBar_->getQty()); //上と合わせる事
    addSubGroup(pMpCostDispBar_);
    //Vreathバー、コスト表示バー
    pVreathCostDispBar_ = NEW CostDispBar("CostDispBar2", pVreathBar_);
    pVreathCostDispBar_->graduatePxQty(600, pVreathBar_->getQty());  //上と合わせる事
    addSubGroup(pVreathCostDispBar_);
    //Vreathバー、ダメージ表示バー
    pDamageDispBar_ = NEW DamageDispBar("DamageDispBar", pVreathBar_);
    pDamageDispBar_->graduatePxQty(600, pVreathBar_->getQty());  //上と合わせる事
    addSubGroup(pDamageDispBar_);


    //残魔法効果持続時間表示
    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    addSubGroup(pMagicMeterStatus_);

    //メータ主カーソル
    pMagicCursor_ = NEW MagicMeterCursor001("MagicCursor", this);
    addSubGroup(pMagicCursor_);


    _pSeTx->set(SE_CURSOR_MOVE_METER             , "WAVE_MM_CURSOR_MOVE_METER");  //主メーターカーソル移動時
    _pSeTx->set(SE_CURSOR_MOVE_LEVEL             , "WAVE_MM_CURSOR_MOVE_LEVEL");  //上下レベル移動時
    _pSeTx->set(SE_CURSOR_MOVE_LEVEL_CANCEL      , "WAVE_MM_CURSOR_MOVE_LEVEL_CANCEL");  //上下レベル移動キャンセル（）
    _pSeTx->set(SE_CURSOR_BAD_MOVE               , "WAVE_MM_CURSOR_BAD_MOVE");  //ダメなカーソル移動（鳴るとうるさいので現在未使用）
    _pSeTx->set(SE_EXECUTE_LEVELUP_MAGIC         , "WAVE_MM_EXECUTE_LEVELUP_MAGIC");  //レベルアップ実行時
    _pSeTx->set(SE_EXECUTE_LEVELDOWN_MAGIC       , "WAVE_MM_EXECUTE_LEVELDOWN_MAGIC");  //レベルダウン実行時
    _pSeTx->set(SE_EXECUTE_CANCEL_LEVELUP_MAGIC  , "WAVE_MM_EXECUTE_CANCEL_LEVELUP_MAGIC");  //（詠唱キャンセルして）レベルアップ実行時
    _pSeTx->set(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC, "WAVE_MM_EXECUTE_CANCEL_LEVELDOWN_MAGIC");  //（詠唱キャンセルして）レベルダウン実行時
    _pSeTx->set(SE_CANT_INVOKE_MAGIC             , "WAVE_MM_CANT_INVOKE_MAGIC");  //詠唱完了時、MPが足りないため発動できない場合
    _pSeTx->set(SE_EFFECT_MAGIC                  , "WAVE_MM_EFFECT_MAGIC");  //発動が完了し、効果発生時
    _pSeTx->set(SE_NOTICE_LEVELDOWN_MAGIC        , "WAVE_MM_NOTICE_LEVELDOWN_MAGIC");  //レベルダウン発生予告
    _pSeTx->set(SE_BAD_OPERATION                 , "WAVE_MM_BAD_OPERATION");  //操作ミス。出来ない入力、ブブー

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
    pMpBar_->position(_X, _Y + height_ + PX_C(16));
    pVreathBar_->position(_X, _Y + height_ + PX_C(16) + PX_C(16) );
    pMagicMeterStatus_->positionAs(this);

    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //アニメ順序
    Magic* pMagic;
    for (int i = 0; i < lstMagic_.length(); i++) {
        pMagic = lstMagic_.getFromFirst(i);
        papLvTargetCursor_[i]->moveTo(pMagic->level_);
        papLvHilightCursor_[i]->moveTo(pMagic->level_);
        papLvCastingMarkCursor_[i]->moveTo(0);
    }
}
void MagicMeter::onReset() {
    Magic* pMagic;
    for (int i = 0; i < lstMagic_.length(); i++) {
        pMagic = lstMagic_.getFromFirst(i);
        pMagic->resetTree(); //先にMagicをリセットさせる。
        papLvTargetCursor_[i]->moveTo(pMagic->level_);
        papLvHilightCursor_[i]->moveTo(pMagic->level_);
        papLvCastingMarkCursor_[i]->moveTo(0);

        paFloat_rr_[i] = 0.0f;
        paFloat_velo_rr_[i] = 0.0f;

        pSeTx4Cast_->stop(i);
        pSeTx4Invoke_->stop(i);
    }
    //主メーターカーソル
    lstMagic_.current(0);
    int active_idx = lstMagic_.getCurrentIndex();
    pMagicCursor_->moveTo(active_idx);
}
void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    VirtualButton* pVbPlay = VB_PLAY;

    if (pVbPlay->isBeingPressed(VB_POWERUP)) {
        alpha_velo_ = 0.05f;
        Magic* pActiveMagic = lstMagic_.getCurrent();     //アクティブな魔法
        int active_idx = lstMagic_.getCurrentIndex();     //アクティブな魔法のインデックス
        progress active_prg = pActiveMagic->_pProg->get();  //アクティブな魔法の進捗
        if (pVbPlay->isPushedDown(VB_POWERUP)) {
            rollOpen(active_idx);
        }

        if (pVbPlay->isAutoRepeat(VB_RIGHT)) {    //「→」押下時
            //レベル表示
            if (active_prg == Magic::STATE_CASTING) {
                if (papLvTargetCursor_[active_idx]->point_lv_ != papLvCastingMarkCursor_[active_idx]->point_lv_) {
                    _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTargetCursor_[active_idx]->moveSmoothTo(papLvCastingMarkCursor_[active_idx]->point_lv_); //レベルカーソルを詠唱先レベルに戻す
                }
            } else {
                if (papLvTargetCursor_[active_idx]->point_lv_ != papLvHilightCursor_[active_idx]->point_lv_) {
                    _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTargetCursor_[active_idx]->moveSmoothTo(papLvHilightCursor_[active_idx]->point_lv_); //レベルカーソルをアクティブレベルに戻す
                }
            }
            rollClose(active_idx); //現在ロールクローズ

            lstMagic_.next(); //メーターを１つ進める
            pActiveMagic= lstMagic_.getCurrent();     //更新
            active_idx = lstMagic_.getCurrentIndex(); //更新
            active_prg = pActiveMagic->_pProg->get();   //更新

            rollOpen(active_idx);  //進めた先をロールオープン
            pMagicCursor_->moveTo(active_idx); //メーターカーソルも１つ進める
            _pSeTx->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(VB_LEFT)) { //「←」押下時
            //レベル表示
            if (active_prg == Magic::STATE_CASTING) {
                if (papLvTargetCursor_[active_idx]->point_lv_ != papLvCastingMarkCursor_[active_idx]->point_lv_) {
                    _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTargetCursor_[active_idx]->moveSmoothTo(papLvCastingMarkCursor_[active_idx]->point_lv_); //レベルカーソルを詠唱先レベルに戻す
                }
            } else {
                if (papLvTargetCursor_[active_idx]->point_lv_ != papLvHilightCursor_[active_idx]->point_lv_) {
                    _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTargetCursor_[active_idx]->moveSmoothTo(papLvHilightCursor_[active_idx]->point_lv_); //レベルカーソルをアクティブレベルに戻す
                }
            }
            rollClose(active_idx); //現在ロールクローズ

            lstMagic_.prev(); //メーターを１つ戻す
            pActiveMagic= lstMagic_.getCurrent();     //更新
            active_idx = lstMagic_.getCurrentIndex(); //更新
            active_prg = pActiveMagic->_pProg->get();   //更新

            rollOpen(active_idx); //戻した先をロールオープン
            pMagicCursor_->moveTo(active_idx); //メーターカーソルも１つ戻す
            _pSeTx->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(VB_UP) ) {  // 「↑」押下時
            if (pActiveMagic->max_level_ > papLvTargetCursor_[active_idx]->point_lv_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(papLvTargetCursor_[active_idx]->point_lv_ + 1);
            }

        } else if (pVbPlay->isAutoRepeat(VB_DOWN)) {  //「↓」押下時
            if (0 < papLvTargetCursor_[active_idx]->point_lv_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(papLvTargetCursor_[active_idx]->point_lv_ - 1);
            }
        } else {

        }
        //MPコストバー
        if (paFloat_rr_[active_idx] > 0.01f) {
            if (papLvTargetCursor_[active_idx]->point_lv_ == pActiveMagic->level_) {
                //カーソルがより現在と同じレベルを指している場合
                pMpCostDispBar_->setQty(0);
            } else if (papLvTargetCursor_[active_idx]->point_lv_ > pActiveMagic->level_) {
                //カーソルが現在より高いレベルを指している場合
                //負の赤の表示
                pMpCostDispBar_->setQty(
                  -1*pActiveMagic->interest_cost_[papLvTargetCursor_[active_idx]->point_lv_ - pActiveMagic->level_]
                );
            } else {
                //カーソルが現在より低いレベルを指している場合
                //正の青の表示
                pMpCostDispBar_->setQty(
                  pActiveMagic->calcReduceMp(pActiveMagic->level_,  papLvTargetCursor_[active_idx]->point_lv_)
                );
            }
        } else {
            pMpCostDispBar_->setQty(0);
        }

        //Vreathバー
        if (active_idx == 6) {
            VreathMagic* pVM = (VreathMagic*)pActiveMagic;
            if (paFloat_rr_[active_idx] > 0.01f) {
                if (papLvTargetCursor_[active_idx]->point_lv_ == pVM->level_) {
                    //カーソルがより現在と同じレベルを指している場合
                    pVreathCostDispBar_->setQty(0);
                } else if (papLvTargetCursor_[active_idx]->point_lv_ > pVM->level_) {
                    //カーソルが現在より高いレベルを指している場合
                    //正の青の表示
                    pVreathCostDispBar_->setQty(
                            (int)(pVM->calcTotalVreath(pActiveMagic->level_,  papLvTargetCursor_[active_idx]->point_lv_))
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
            int r = pActiveMagic->cast(papLvTargetCursor_[active_idx]->point_lv_);

            switch (r) {
                case MAGIC_CAST_NG_INVOKING_NOW: {
                    _pSeTx->play(SE_BAD_OPERATION);
                    break;
                }
                case MAGIC_CAST_NG_MP_IS_SHORT: {
                    _pSeTx->play(SE_BAD_OPERATION);
                    break;
                }
                case MAGIC_CAST_NOTHING: {
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_CANCEL: {
                    _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTargetCursor_[active_idx]->blink(); //ピカピカ！
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELUP: {
                    pSeTx4Cast_->play(active_idx);

                    _pSeTx->play(SE_EXECUTE_LEVELUP_MAGIC);
                    papLvTargetCursor_[active_idx]->blink(); //ピカピカ！
                    //LEVELUP 時は既にpActiveMagic->new_level_ がアップ予定レベル
                    papLvCastingMarkCursor_[active_idx]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELDOWN: {
                    _pSeTx->play(SE_EXECUTE_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[active_idx]->blink(); //ピカピカ！
                    //LEVELDOWN 時は既に effect(new_lv) 実行済みのため、現レベル pActiveMagic->level_ となる
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->blink();
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
                    pSeTx4Cast_->play(active_idx);

                    _pSeTx->play(SE_EXECUTE_CANCEL_LEVELUP_MAGIC);
                    papLvTargetCursor_[active_idx]->blink(); //ピカピカ！
                    //LEVELUP 時は既にpActiveMagic->new_level_ がアップ予定レベル
                    papLvCastingMarkCursor_[active_idx]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN: {
                    _pSeTx->play(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[active_idx]->blink(); //ピカピカ！
                    //LEVELDOWN 時は既に effect(new_lv) 実行済みのため、現レベル pActiveMagic->level_ となる
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->blink();
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
    //毎フレームの各魔法表示についての処理
    GgafProgress* pMagicProg = nullptr;
    Magic* pMagic = nullptr;
    int pMagic_level, pMagic_new_level;
    for (int m = 0; m < lstMagic_.length(); m++) {
        pMagic = lstMagic_.getFromFirst(m);
        pMagicProg = pMagic->_pProg;
        pMagic_level = pMagic->level_;
        pMagic_new_level = pMagic->new_level_;

        paFloat_rr_[m] += paFloat_velo_rr_[m];
        if (paFloat_rr_[m] < 0.0f) {
            paFloat_rr_[m] = 0.0f;
            paFloat_velo_rr_[m] = 0.0f;
        }
        if (paFloat_rr_[m] > 1.0f) {
            paFloat_rr_[m] = 1.0f;
            paFloat_velo_rr_[m] = 0.0f;
        }

        //INVOKING開始時
        if (pMagicProg->isJustChangedTo(Magic::STATE_INVOKING)) {
            if (pMagic_new_level > pMagic_level) {
                //レベルアップ時
                pSeTx4Invoke_->play(m);
            }
            papLvTargetCursor_[m]->dispDisable();
            papLvHilightCursor_[m]->dispDisable();
            if (papLvTargetCursor_[m]->point_lv_ == pMagic_level) {
                //カーソルが現レベルを指している場合に限り
                //新しいレベルにこっそり動かしてあげる。
                papLvTargetCursor_[m]->moveSmoothTo(pMagic_new_level);
            }
            if (pMagic_new_level > pMagic_level) {
                //レベルアップ時
                papLvHilightCursor_[m]->moveSmoothTo(pMagic_new_level, (frame)(pMagic->interest_time_of_invoking_[pMagic_new_level - pMagic_level]));
            } else {
                //レベルダウン時
                papLvHilightCursor_[m]->moveSmoothTo(pMagic_new_level, 1); //即効で動く
            }
            papLvCastingMarkCursor_[m]->markOnInvoke(pMagic_new_level);
        }
        //INVOKING中
        if (pMagicProg->get() == Magic::STATE_INVOKING) {
            if (pMagic->new_level_ > pMagic_level) {
                //レベルアップ時
                float f = ((float)(pMagicProg->getFrameInProgress())) / ((float)(pMagic->time_of_next_state_));
                pSeTx4Invoke_->get(m)->setFrequencyRate(1.0f + (f*3.0f));//音程を上げる
            }
        }
        //INVOKING完
        if (pMagicProg->isJustChangedFrom(Magic::STATE_INVOKING)) {
            pSeTx4Invoke_->stop(m);
            papLvTargetCursor_[m]->dispEnable();
            papLvHilightCursor_[m]->dispEnable();
            papLvHilightCursor_[m]->blink();
        }

        //EFFECTING開始時
        if (pMagicProg->isJustChangedTo(Magic::STATE_EFFECTING)) {
            if (pMagic->last_level_ < pMagic->level_) {
                //レベルアップSTATE_EFFECTINGだったならば
                _pSeTx->play(SE_EFFECT_MAGIC);
                papLvCastingMarkCursor_[m]->markOnEffect(pMagic_level);
            } else {
                //レベルダウンEFFECT_BEGEINだったならば
                //markOnLevelDownCast() した直後である。
                //「CASTING」１ループのアニメーションがある為、何もしない。
            }
        }

        //満期レベルダウン時
        if (pMagic->prev_frame_level_ != pMagic_level && pMagic->prev_frame_level_ > pMagic_level) {
            _pSeTx->play(SE_EXECUTE_LEVELDOWN_MAGIC);
            if (papLvTargetCursor_[m]->point_lv_ == pMagic->prev_frame_level_) {
                papLvTargetCursor_[m]->moveSmoothTo(pMagic_level);
            }
            papLvHilightCursor_[m]->moveSmoothTo(pMagic_level);
            papLvHilightCursor_[m]->blink();
        }

        //空詠唱（詠唱したが、詠唱完了時、MPが足りなかった）
        if (pMagicProg->get() == Magic::STATE_NOTHING && pMagicProg->isJustChangedFrom(Magic::STATE_CASTING)) {
            papLvCastingMarkCursor_[m]->markOff(); //マークオフ！
            _pSeTx->play(SE_CANT_INVOKE_MAGIC);
        }

        //即効性魔法終了時
        if (pMagic->time_of_effect_base_ == 0 &&
            pMagicProg->get() == Magic::STATE_NOTHING &&
            pMagicProg->isJustChangedFrom(Magic::STATE_INVOKING)) {
            //メモ
            //STATE_INVOKING
            //↓
            //effect(new_level_)(chenge(STATE_EFFECT_BEGIN))
            //↓
            //chenge(STATE_NOTHING) と上書きされるので
            // pMagicProg->isJustChangedFrom(Magic::STATE_INVOKING) の判定となる
            //このタイミングで
//            papLvCastingMarkCursor_[m]->markOff(); //マークオフ！
            papLvCastingMarkCursor_[m]->markOnEffect(pMagic_level);
            papLvHilightCursor_[m]->moveSmoothTo(pMagic_level);
        }

        //詠唱中
        if (pMagicProg->get() == Magic::STATE_CASTING) {
            if (pMagic->new_level_ > pMagic_level) {
                //レベルアップなら音程アップ
                float f = ((float)(pMagicProg->getFrameInProgress())) / ((float)(pMagic->time_of_next_state_));
                pSeTx4Cast_->get(m)->setFrequencyRate(1.0f + (f*3.0f));
            }
        }
        //詠唱完
        if (pMagicProg->isJustChangedFrom(Magic::STATE_CASTING)) {
            pSeTx4Cast_->stop(m);
        }

        //もうすぐレベルダウン警告
        if (pMagic->lvinfo_[pMagic_level].remainingtime_of_effect_ == fraeme_of_notice_remaind_) {
            _pSeTx->play(SE_NOTICE_LEVELDOWN_MAGIC);
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
    GgafDxBoardSetEffect* pBoardSetEffect = _pBoardSetEffect;
    ID3DXEffect* pID3DXEffect = pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    //パワーメーター
    //[====]が１つの大きさ [====][====][====]
    MagicList::Elem* pElem = lstMagic_.getElemFirst();
    Magic* pMagic;
    int pMagic_level;
    int len_magics = lstMagic_.length();
    int n = 0;
    float u,v;
    float x = float(C_PX(_X));
    float y = float(C_PX(_Y));
    float z = float(C_PX(_Z));
    float alpha = getAlpha();
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//一周したのでアクティブであるはず
        pMagic_level = pMagic->level_;
        n = 0;
        float wx = width_px_*i;
        //マジックメーター背景
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_X[n], x + wx);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_Y[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[n], alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");
        if (pMagic_level > 0 && pMagic->lvinfo_[pMagic_level].remainingtime_of_effect_ <= fraeme_of_notice_remaind_) {
            _pUvFlipper->getUV(1, u, v); //パターン1は赤背景、残り時間がやばい事を示す
        } else {
            _pUvFlipper->getUV(0, u, v); //パターン0は通常背景
        }
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
        n++;

        //マジックメーター上の現在のマジックレベル表示
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_X[n], x + wx);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_Y[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[n], alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");
        _pUvFlipper->getUV(pMagic->lvinfo_[pMagic_level].pno_, u, v);
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
        n++;

        float rr = paFloat_rr_[i];
        if (rr > 0.1f) {
            //各マジック要素
            int lv_slecter_num = pMagic->max_level_+1;
            for (int j = 0; j < lv_slecter_num; j++) {
                //魔法名
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_X[n], x + wx);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) に失敗しました。");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_Y[n], y - (height_px_*(j+1)*rr));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) に失敗しました。");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_Z[n], z);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) に失敗しました。");
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[n], alpha*rr); //アクティブなら濃いめ
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");

                if (pMagic->chkCastAble(j) <= MAGIC_CAST_NG_MP_IS_SHORT) {
                    //MAGIC_CAST_NG_MP_IS_SHORT か MAGIC_CAST_NG_INVOKING_NOW
                    //詠唱不可表示
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_ + 1, u, v); //右隣のテクスチャパターンが DISABLE なパターン前提
                } else {
                    //詠唱可能表示
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
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
    paFloat_velo_rr_[prm_meter_index] = 0.1f;
}

void MagicMeter::rollClose(int prm_meter_index) {
    paFloat_velo_rr_[prm_meter_index] = -0.02f;
}

MagicMeter::~MagicMeter() {
    GGAF_DELETEARR(papLvTargetCursor_);
    GGAF_DELETEARR(papLvHilightCursor_);
    GGAF_DELETEARR(papLvCastingMarkCursor_);
    GGAF_DELETEARR(paFloat_rr_);
    GGAF_DELETEARR(paFloat_velo_rr_);
    GGAF_DELETE(pSeTx4Cast_);
    GGAF_DELETE(pSeTx4Invoke_);
}
