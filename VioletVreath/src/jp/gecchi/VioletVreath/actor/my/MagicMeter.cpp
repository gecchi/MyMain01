#include "MagicMeter.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/MassBoardEffect.h"
#include "jp/ggaf/dx/model/MassBoardModel.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/CostDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/DamageDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MpBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/ShotMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
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
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/dx/sound/Se.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/BunshinMagic.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_CURSOR_MOVE_METER       ,
    SE_CURSOR_MOVE_LEVEL       ,
    SE_CURSOR_MOVE_LEVEL_CANCEL,
    SE_CURSOR_BAD_MOVE         ,
    SE_EXECUTE_LEVELUP_MAGIC   ,
    SE_EXECUTE_LEVELDOWN_MAGIC ,
    SE_EXECUTE_CANCEL_LEVELUP_MAGIC   ,
    SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC ,
    SE_NG_MP_IS_SHORT       ,
    SE_EFFECT_MAGIC    ,
    SE_NOTICE_LEVELDOWN_MAGIC,
    SE_BAD_OPERATION   ,
};

MagicMeter::MagicMeter(const char* prm_name, int* prm_pMP_MyShip, int* prm_pVreath_MyShip)
      : DefaultMassBoardActor(prm_name, "MagicMeter"),
width_px_(_pMassBoardModel->_model_width_px),
height_px_(_pMassBoardModel->_model_height_px),
width_(PX_C(width_px_)),
height_(PX_C(height_px_)) {

    _class_name = "MagicMeter";
    pTractorMagic_ = NEW TractorMagic("TRACTOR", prm_pMP_MyShip); //維持コスト有り
    pSpeedMagic_   = NEW SpeedMagic("SPEED", prm_pMP_MyShip);
    pLockonMagic_  = NEW LockonMagic("LOCKON", prm_pMP_MyShip);
    pTorpedoMagic_ = NEW TorpedoMagic("TORPEDO", prm_pMP_MyShip);
    pShotMagic_    = NEW ShotMagic("SHOT", prm_pMP_MyShip);
    pLaserMagic_   = NEW LaserMagic("LASER", prm_pMP_MyShip);
    pBunshinMagic_ = NEW BunshinMagic("BUNSHIN", prm_pMP_MyShip);
    pVreathMagic_  = NEW VreathMagic("VREATH", prm_pMP_MyShip);
    pSmileMagic_   = NEW SmileMagic("SMILE", prm_pMP_MyShip); //即効魔法
    lstMagic_.addLast(pTractorMagic_);
    lstMagic_.addLast(pSpeedMagic_  );
    lstMagic_.addLast(pLockonMagic_ );
    lstMagic_.addLast(pTorpedoMagic_);
    lstMagic_.addLast(pShotMagic_   );
    lstMagic_.addLast(pLaserMagic_  );
    lstMagic_.addLast(pBunshinMagic_);
    lstMagic_.addLast(pVreathMagic_ );
    lstMagic_.addLast(pSmileMagic_  );
    lstMagic_.createIndex();

    int magic_num = lstMagic_.length();
    for (int i = 0; i < magic_num; i++) {
        appendGroupChild(lstMagic_.getNext(i));
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

    //表示プリオリティを考慮して、appendGroupChildを行う事！
    for (int i = 0; i < magic_num; i++) {
        appendGroupChild(papLvNowCur_[i]); //現レベル強調カーソル
    }
    for (int i = 0; i < magic_num; i++) {
        appendGroupChild(papLvCastingCur_[i]); //詠唱レベル強調カーソル
    }
    for (int i = 0; i < magic_num; i++) {
        appendGroupChild(papLvTgtMvCur_[i]); //メータ補助カーソル
    }

    const int mp_max_val = MY_SHIP_MAX_MP;
    const coord mp_disp_width = PX_C(800); //画面表示上の横幅800ピクセル。
    const int vreath_max_val = *prm_pVreath_MyShip; //最初が満タンだからこれを使用
    const coord vreath_disp_width = PX_C(800);  //画面表示上の横幅ピクセル数。
    //MPバー設置
    pMpBar_ = NEW MpBar("MpBar");
    pMpBar_->linkVariable(prm_pMP_MyShip);
    pMpBar_->scale(0, mp_max_val, mp_disp_width);
    appendGroupChild(pMpBar_);
    //Vreathバー設置
    pVreathBar_ = NEW VreathBar("VreathBar");
    pVreathBar_->linkVariable(prm_pVreath_MyShip);
    pVreathBar_->scale(0, vreath_max_val, vreath_disp_width);
    appendGroupChild(pVreathBar_);

    //エネルギーバーのコスト表示バー
    pMpCostDispBar_ = NEW CostDispBar("CostDispBar", pMpBar_);
    pMpCostDispBar_->scale(-mp_max_val, +mp_max_val, mp_disp_width*2);
    appendGroupChild(pMpCostDispBar_);
    //Vreathバー、コスト表示バー
    pVreathCostDispBar_ = NEW CostDispBar("CostDispBar2", pVreathBar_);
    pVreathCostDispBar_->scale(-vreath_max_val, +vreath_max_val, vreath_disp_width*2);
    appendGroupChild(pVreathCostDispBar_);
    //Vreathバー、ダメージ表示バー
    pDamageDispBar_ = NEW DamageDispBar("DamageDispBar", pVreathBar_);
    pDamageDispBar_->scale(-vreath_max_val, +vreath_max_val, vreath_disp_width*2);
    appendGroupChild(pDamageDispBar_);

    //残魔法効果持続時間表示
    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    appendGroupChild(pMagicMeterStatus_);

    //メータ主カーソル
    pMainCur_ = NEW MagicMeterCursor001("MagicCursor", this);
    appendGroupChild(pMainCur_);

    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_CURSOR_MOVE_METER             , "SE_MM_CURSOR_MOVE_METER");  //主メーターカーソル移動時
    pSeTx->set(SE_CURSOR_MOVE_LEVEL             , "SE_MM_CURSOR_MOVE_LEVEL");  //上下レベル移動時
    pSeTx->set(SE_CURSOR_MOVE_LEVEL_CANCEL      , "SE_MM_CURSOR_MOVE_LEVEL_CANCEL");  //上下レベル移動キャンセル（）
    pSeTx->set(SE_CURSOR_BAD_MOVE               , "SE_MM_CURSOR_BAD_MOVE");  //ダメなカーソル移動（鳴るとうるさいので現在未使用）
    pSeTx->set(SE_EXECUTE_LEVELUP_MAGIC         , "SE_MM_EXECUTE_LEVELUP_MAGIC");  //レベルアップ実行時
    pSeTx->set(SE_EXECUTE_LEVELDOWN_MAGIC       , "SE_MM_EXECUTE_LEVELDOWN_MAGIC");  //レベルダウン実行時
    pSeTx->set(SE_EXECUTE_CANCEL_LEVELUP_MAGIC  , "SE_MM_EXECUTE_CANCEL_LEVELUP_MAGIC");  //（詠唱キャンセルして）レベルアップ実行時
    pSeTx->set(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC, "SE_MM_EXECUTE_CANCEL_LEVELDOWN_MAGIC");  //（詠唱キャンセルして）レベルダウン実行時
    pSeTx->set(SE_NG_MP_IS_SHORT                , "SE_MM_NG_MP_IS_SHORT");  //MPが足りないため発動あるいは効果開始できない場合
    pSeTx->set(SE_EFFECT_MAGIC                  , "SE_MM_EFFECT_MAGIC");  //発動が完了し、効果発生時
    pSeTx->set(SE_NOTICE_LEVELDOWN_MAGIC        , "SE_MM_NOTICE_LEVELDOWN_MAGIC");  //レベルダウン発生予告
    pSeTx->set(SE_BAD_OPERATION                 , "SE_MM_BAD_OPERATION");  //操作ミス。出来ない入力、ブブー

    pSeTx4Cast_ = NEW GgafDx::SeTransmitterForActor(this);
    pSeTx4Invoke_ = NEW GgafDx::SeTransmitterForActor(this);
    for (int i = 0; i < magic_num; i++) {
        pSeTx4Cast_->set(i, "SE_MM_CASTING", i); //詠唱中SE。チャンネル明示指定
        pSeTx4Invoke_->set(i, "SE_MM_INVOKING", i); //発動中SE。チャンネル明示指定
    }
    fraeme_of_notice_remaind_ = 60*5;//残り僅か警告発生の残り時間
    alpha_velo_ = -0.01f;

    //インスタンスデータ初期化
    max_draw_num_ = 0;
    int len_magics = lstMagic_.length();
    MagicList::Elem* pElem = lstMagic_.getElemFirst();
    for (int i = 0; i < len_magics; i++) {
        max_draw_num_++; //マジックメーター背景
        max_draw_num_++; //マジックメーター上の現在のマジックレベル表示
        pMagic = pElem->getValue();//一周したのでアクティブであるはず
        int lv_slecter_num = pMagic->max_level_+1;
        for (int j = 0; j < lv_slecter_num; j++) {
            max_draw_num_++;  //各マジック要素
        }
        pElem = pElem->_pNext;
    }
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    paInstancedata_MM_ = NEW VERTEX_instancedata[max_draw_num_];
    paInstancedata_MM_[0].px_x = C_PX(_x);
    paInstancedata_MM_[0].px_y = C_PX(_y);
    paInstancedata_MM_[0].depth_z = C_PX(_z);
    paInstancedata_MM_[0].local_px_x = 0.0f;
    paInstancedata_MM_[0].local_px_y = 0.0f;
    paInstancedata_MM_[0].r_sx = SC_R(_sx);
    paInstancedata_MM_[0].r_sy = SC_R(_sy);
    paInstancedata_MM_[0].rad_rz = ANG_RAD(_rz);
    paInstancedata_MM_[0].offset_u = 0;
    paInstancedata_MM_[0].offset_v = 0;
    memcpy(&(paInstancedata_MM_[0].r), &(_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);
    for (int i = 1; i < max_draw_num_; i++) {
        paInstancedata_MM_[i] = paInstancedata_MM_[0]; //コピーして初期化
    }
}

void MagicMeter::loadStatus(int prm_saveno) {
    st_[prm_saveno].seekg(std::stringstream::beg); //頭出し
    loadProperties(st_[prm_saveno]);
}

void MagicMeter::saveStatus(int prm_saveno) {
    save(st_[prm_saveno]);
}

void MagicMeter::save(std::stringstream& sts) {
    sts << pMpBar_->getVal() << " ";
    Magic* pOrgMagic = lstMagic_.getCurrent();
    int len_magics = lstMagic_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->save(sts);
        pOrgMagic = lstMagic_.next();
    }
}

void MagicMeter::loadProperties(std::stringstream& sts) {
    int mp;
    sts >> mp;
    pMpBar_->setVal(mp);

    Magic* pOrgMagic = lstMagic_.getCurrent();
    int len_magics = lstMagic_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->loadProperties(sts);
        pOrgMagic = lstMagic_.next();
    }
}

void MagicMeter::initialize() {
    pMpBar_->setPosition(_x, _y + height_ + PX_C(16));
    pVreathBar_->setPosition(pMpBar_->_x, pMpBar_->_y + PX_C(16));
    pMagicMeterStatus_->setPositionAt(this);

    getUvFlipper()->exec(FLIP_ORDER_LOOP, 10); //アニメ順序
    Magic* pMagic;
    for (int i = 0; i < lstMagic_.length(); i++) {
        pMagic = lstMagic_.getFromFirst(i);
        papLvTgtMvCur_[i]->moveTo(pMagic->level_);
        papLvNowCur_[i]->moveTo(pMagic->level_);
        papLvCastingCur_[i]->moveTo(0);
        papLvCastingCur_[i]->markOff();
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
        papLvCastingCur_[i]->markOff();

        r_roll_[i] = 0.0f;
        r_roll_velo_[i] = 0.0f;

        pSeTx4Cast_->stop(i);
        pSeTx4Invoke_->stop(i);
    }
    pMpCostDispBar_->setVal(0);
    pVreathCostDispBar_->setVal(0);
    pDamageDispBar_->setVal(0);
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    ////////////////////////各魔法についての処理//////////////////////////
    GgafCore::Phase* pMagicPhase;
    Magic* pMagic = nullptr;
    int pMagic_level, pMagic_new_level;
    MagicLvCursor001* pLvTgtMvCur;
    MagicLvCursor002* pLvNowCur;
    MagicLvCursor003* pLvCastingCur;

    for (int m = 0; m < lstMagic_.length(); m++) {
        pMagic = lstMagic_.getFromFirst(m);    //魔法オブジェクト
        pMagicPhase = pMagic->_pPhase;         //魔法のフェーズ状況
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
        if (pMagicPhase->hasJustChangedTo(Magic::PHASE_CASTING)) {
            switch (pMagic->last_cast_) {
                case MAGIC_CAST_OK_LEVELUP: {
                    getSeTransmitter()->play(SE_EXECUTE_LEVELUP_MAGIC);
                    pSeTx4Cast_->play(m, true);
                    pLvTgtMvCur->blink(); //ピカピカ！
                    pLvCastingCur->markOnLevelUpCast(pMagic_new_level);
                    break;
                }
                case MAGIC_CAST_LEVELDOWN: {
                    getSeTransmitter()->play(SE_EXECUTE_LEVELDOWN_MAGIC);
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
                        getSeTransmitter()->play(SE_EXECUTE_CANCEL_LEVELUP_MAGIC);
                        pSeTx4Cast_->play(m);
                        pLvTgtMvCur->blink(); //ピカピカ！
                        pLvCastingCur->markOnLevelUpCast(pMagic_new_level);
                    }
                    break;
                }
                case MAGIC_CAST_CANCEL_AND_LEVELDOWN: {
                    getSeTransmitter()->play(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC);
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
                    throwCriticalException("["<<pMagic->getName()<<"] おかしい。来るはずがない。pMagic->last_cast_="<<(pMagic->last_cast_));
                    break;
                }
            }
        }
        //詠唱中
        if (pMagicPhase->getCurrent() == Magic::PHASE_CASTING) {
            if (pMagic->new_level_ > pMagic_level) {
                //レベルアップなら音程アップ
                float r = ((float)(pMagicPhase->getFrame())) / ((float)(pMagic->time_of_next_state_));
                pSeTx4Cast_->getSe(m)->setFrequencyRate(1.0f + (r*3.0f));
            }
        }
        //詠唱中ではなくなった
        if (pMagicPhase->hasJustChangedFrom(Magic::PHASE_CASTING)) {
            pSeTx4Cast_->stop(m); //消音
        }

        //発動開始時
        if (pMagicPhase->hasJustChangedTo(Magic::PHASE_INVOKING)) {
            switch (pMagic->last_invoke_) {
                case MAGIC_INVOKE_OK_LEVELUP: {
                    pSeTx4Invoke_->play(m, true);
                    pLvTgtMvCur->dispDisable(); //操作不可表示
                    pLvNowCur->dispDisable();
                    if (pLvTgtMvCur->point_lv_ == pMagic_level) {
                        //カーソルが現レベルを指している場合に限り
                        //新しいレベルにこっそり動かしてあげる。
                        pLvTgtMvCur->moveSmoothTo(pMagic_new_level);
                    }
                    frame invoking_frames = (frame)(pMagic->level_up_invoking_frames_[pMagic_level][pMagic_new_level]);
                    pLvNowCur->moveSmoothTo(pMagic_new_level, invoking_frames); //INVOKINGに合わせて動く
                    pLvCastingCur->markOnInvoke(pMagic_new_level);
                    break;
                }
                case MAGIC_INVOKE_OK_LEVELDOWN: {
                    //レベルダウンは、詠唱開始時に現在レベル強調表示のカーソル移動が既におこなわれている。
                    //ので、ここでは何もしない。
                    break;
                }
                default: {
                    throwCriticalException("["<<pMagic->getName()<<"] おかしい。来るはずがない。pMagic->last_invoke_="<<(pMagic->last_invoke_));
                    break;
                }
            }
        }
        //発動中
        if (pMagicPhase->getCurrent() == Magic::PHASE_INVOKING) {
            if (pMagic->new_level_ > pMagic_level) {
                //レベルアップ時
                float r = ((float)(pMagicPhase->getFrame())) / ((float)(pMagic->time_of_next_state_));
                pSeTx4Invoke_->getSe(m)->setFrequencyRate(1.0f + (r*3.0f));//音程を上げる
            }
        }
        //発動ではなくなった
        if (pMagicPhase->hasJustChangedFrom(Magic::PHASE_INVOKING)) {
            pSeTx4Invoke_->stop(m); //消音
            pLvTgtMvCur->dispEnable(); //操作不可表示を解除
            pLvNowCur->dispEnable();
        }
        //効果開始時
        if (pMagicPhase->hasJustChangedTo(Magic::PHASE_EFFECT_START)) {
            switch (pMagic->last_effect_) {
                case MAGIC_EFFECT_OK_LEVELUP: {
                    if (pMagic->effecting_frames_base_ == 0) {
                        //即効性魔法の場合
                        getSeTransmitter()->play(SE_EFFECT_MAGIC);
                        pLvCastingCur->markOnEffect(pMagic_level);
                    } else {
                        //通常魔法の場合
                        getSeTransmitter()->play(SE_EFFECT_MAGIC);
                        pLvCastingCur->markOnEffect(pMagic_level);
                    }
                    break;
                }
                case MAGIC_EFFECT_OK_LEVELDOWN: {
                    if (pMagic->effecting_frames_base_ == 0) {
                        //速攻魔法の終了のレベルダウン場合
                        _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] 速攻魔法のレベルダウンのレベルダウン");
                        pLvNowCur->moveSmoothTo(pMagic_level);
                    } else {
                        //普通のレベルダウン
                        getSeTransmitter()->play(SE_EXECUTE_LEVELDOWN_MAGIC);
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
                    throwCriticalException("["<<pMagic->getName()<<"] おかしい。来るはずがない。pMagic->last_effect_="<<(pMagic->last_effect_));
                    break;
                }
            }
        }

        //PHASE_NOTHINGへ移行した
        if (pMagicPhase->hasJustChangedTo(Magic::PHASE_NOTHING)) {
            if (pMagicPhase->hasJustChangedFrom(Magic::PHASE_CASTING)) { //詠唱→PHASE_NOTHING
                //空詠唱（詠唱をキャンセルした or 詠唱したが詠唱完了時にMPが足りなかった）
                _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] 詠唱→PHASE_NOTHING 空詠唱乙。");
                pLvCastingCur->markOff(); //マークオフ！
                pLvNowCur->moveSmoothTo(pMagic_level);
                pLvTgtMvCur->moveSmoothTo(pMagic_level); //レベルカーソルをアクティブレベルに戻す
                if (pMagic->last_invoke_ == MAGIC_INVOKE_NG_MP_IS_SHORT) {
                    _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] 空詠唱乙の原因は MAGIC_INVOKE_NG_MP_IS_SHORT だったため ");
                    getSeTransmitter()->play(SE_NG_MP_IS_SHORT);
                } else {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                }
            }
            if (pMagicPhase->hasJustChangedFrom(Magic::PHASE_INVOKING)) {  //発動→PHASE_NOTHING
                //空発動（発動したが、発動完了時、MPが足りなかったので、効果開始出来なかった）
                _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] 発動→PHASE_NOTHING 空発動乙 ");
                pLvCastingCur->markOff(); //マークオフ！
                pLvNowCur->moveSmoothTo(pMagic_level);
                pLvTgtMvCur->moveSmoothTo(pMagic_level); //レベルカーソルをアクティブレベルに戻す
                if (pMagic->last_effect_ == MAGIC_EFFECT_NG_MP_IS_SHORT) {
                    _TRACE_(FUNC_NAME<<" ["<<pMagic->getName()<<"] 空発動乙の原因は MAGIC_EFFECT_NG_MP_IS_SHORT だったため ");
                    getSeTransmitter()->play(SE_NG_MP_IS_SHORT);
                } else {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                }
            }
        }

        //もうすぐレベルダウン警告
        if (pMagic->lvinfo_[pMagic_level].remained_frame_of_effecting == fraeme_of_notice_remaind_) {
            getSeTransmitter()->play(SE_NOTICE_LEVELDOWN_MAGIC);
        }
    }

//    //debug -------------->
//    if (GgafDx::Input::isPushedDownKey(DIK_K)) {
//        _TRACE_("MagicMeter saveStatus(0)!!!!");
//        saveStatus(0);
//    }
//    if (GgafDx::Input::isPushedDownKey(DIK_L)) {
//        _TRACE_("MagicMeter loadStatus(0)!!!!");
//        loadStatus(0);
//    }
//    //<-----------------debug

    ////////////////////////魔法メーターについての処理//////////////////////////
    VirtualButton* pVbPlay = VVB_PLAY;
    MyShip* pMyShip = pMYSHIP;
    if (pMyShip->canControl() && pVbPlay->isPressed(0, VVB_POWERUP)) {
        alpha_velo_ = 0.05f;
        Magic* pActiveMagic = lstMagic_.getCurrent();     //アクティブな魔法
        int active_idx = lstMagic_.getCurrentIndex();     //アクティブな魔法のインデックス
        int active_phase = pActiveMagic->getPhase()->getCurrent();  //アクティブな魔法のフェーズ
        if (pMyShip->canControl() && pVbPlay->isPushedDown(0, VVB_POWERUP)) {
            rollOpen(active_idx);
        }

        if (pVbPlay->isAutoRepeat(0, VVB_RIGHT)) {    //「→」押下時
            //レベル表示
            if (active_phase == Magic::PHASE_CASTING) {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvCastingCur_[active_idx]->point_lv_) {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvCastingCur_[active_idx]->point_lv_); //レベルカーソルを詠唱先レベルに戻す
                }
            } else {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvNowCur_[active_idx]->point_lv_) {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvNowCur_[active_idx]->point_lv_); //レベルカーソルをアクティブレベルに戻す
                }
            }
            rollClose(active_idx); //現在ロールクローズ

            lstMagic_.next(); //メーターを１つ進める
            pActiveMagic= lstMagic_.getCurrent();     //更新
            active_idx = lstMagic_.getCurrentIndex(); //更新
            active_phase = pActiveMagic->getPhase()->getCurrent(); //更新

            rollOpen(active_idx);  //進めた先をロールオープン
            pMainCur_->moveTo(active_idx); //メーターカーソルも１つ進める
            getSeTransmitter()->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(0, VVB_LEFT)) { //「←」押下時
            //レベル表示
            if (active_phase == Magic::PHASE_CASTING) {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvCastingCur_[active_idx]->point_lv_) {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvCastingCur_[active_idx]->point_lv_); //レベルカーソルを詠唱先レベルに戻す
                }
            } else {
                if (papLvTgtMvCur_[active_idx]->point_lv_ != papLvNowCur_[active_idx]->point_lv_) {
                    getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                    papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvNowCur_[active_idx]->point_lv_); //レベルカーソルをアクティブレベルに戻す
                }
            }
            rollClose(active_idx); //現在ロールクローズ

            lstMagic_.prev(); //メーターを１つ戻す
            pActiveMagic= lstMagic_.getCurrent();     //更新
            active_idx = lstMagic_.getCurrentIndex(); //更新
            active_phase = pActiveMagic->getPhase()->getCurrent(); //更新

            rollOpen(active_idx); //戻した先をロールオープン
            pMainCur_->moveTo(active_idx); //メーターカーソルも１つ戻す
            getSeTransmitter()->play(SE_CURSOR_MOVE_METER);

        } else if (pVbPlay->isAutoRepeat(0, VVB_UP) ) {  // 「↑」押下時
            if (pActiveMagic->max_level_ > papLvTgtMvCur_[active_idx]->point_lv_) {
                getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL);
                papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvTgtMvCur_[active_idx]->point_lv_ + 1);
            }

        } else if (pVbPlay->isAutoRepeat(0, VVB_DOWN)) {  //「↓」押下時
            if (0 < papLvTgtMvCur_[active_idx]->point_lv_) {
                getSeTransmitter()->play(SE_CURSOR_MOVE_LEVEL);
                papLvTgtMvCur_[active_idx]->moveSmoothTo(papLvTgtMvCur_[active_idx]->point_lv_ - 1);
            }
        } else {

        }
        //MPコストバー
        if (r_roll_[active_idx] > 0.01f) {
            if (papLvTgtMvCur_[active_idx]->point_lv_ == pActiveMagic->level_) {
                //カーソルがより現在と同じレベルを指している場合
                pMpCostDispBar_->setVal(0);
            } else if (papLvTgtMvCur_[active_idx]->point_lv_ > pActiveMagic->level_) {
                //カーソルが現在より高いレベルを指している場合
                //MPコストを負の赤の表示
                pMpCostDispBar_->setVal(
                  -1*pActiveMagic->level_up_cost_[pActiveMagic->level_][papLvTgtMvCur_[active_idx]->point_lv_]
                );
            } else {
                //カーソルが現在より低いレベルを指している場合
                //正の青の表示
                if (pActiveMagic->keep_cost_base_ <= 0) {
                    //維持コスト無しの場合のみMP還元バー表示
                    pMpCostDispBar_->setVal(
                      pActiveMagic->calcReduceMp(pActiveMagic->level_,  papLvTgtMvCur_[active_idx]->point_lv_)
                    );
                } else {
                    //維持コスト有りの場合、MP還元は無い
                }
            }
        } else {
            pMpCostDispBar_->setVal(0);
        }

        //Vreathバーがアクティブだった場合、Vreath増分表示
        if (pActiveMagic == pVreathMagic_) {
            VreathMagic* pVM = (VreathMagic*)pActiveMagic;
            if (r_roll_[active_idx] > 0.01f) {
                if (papLvTgtMvCur_[active_idx]->point_lv_ == pVM->level_) {
                    //カーソルがより現在と同じレベルを指している場合
                    pVreathCostDispBar_->setVal(0);
                } else if (papLvTgtMvCur_[active_idx]->point_lv_ > pVM->level_) {
                    //カーソルが現在より高いレベルを指している場合
                    //正の青の表示
                    pVreathCostDispBar_->setVal(
                            (int)(pVM->calcTotalVreath(pActiveMagic->level_,  papLvTgtMvCur_[active_idx]->point_lv_))
                    );
                } else {
                    //カーソルが現在より低いレベルを指している場合
                    pVreathCostDispBar_->setVal(0);
                }
            } else {
                pVreathCostDispBar_->setVal(0);
            }
        } else {
            pVreathCostDispBar_->setVal(0);
        }

        //「決定」時
        if (pVbPlay->isPushedDown(0, VVB_SHOT1) || pVbPlay->isPushedDown(0, VVB_SHOT2) || pVbPlay->isPushedDown(0, VVB_TURBO)) {
            int r = pActiveMagic->cast(papLvTgtMvCur_[active_idx]->point_lv_);
            switch (r) {
                case MAGIC_CAST_NG_INVOKING_NOW: {
                    getSeTransmitter()->play(SE_BAD_OPERATION);
                    break;
                }
                case MAGIC_CAST_NG_MP_IS_SHORT: {
                    getSeTransmitter()->play(SE_NG_MP_IS_SHORT);
                    break;
                }
            }
        }
    } else  {
        alpha_velo_ = -0.02f;
        if (!pMyShip->canControl() || pVbPlay->isReleasedUp(0, VVB_POWERUP)) {
            rollClose(lstMagic_.getCurrentIndex());
        }
        pMpCostDispBar_->setVal(0);
        pVreathCostDispBar_->setVal(0);
    }

    addAlpha(alpha_velo_);
    if (getAlpha() < 0.3f) {
        setAlpha(0.3f); //非アクティブ時のうっすら表示
    } else if (getAlpha() > 1.0f) {
        setAlpha(1.0f); //アクティブ時のハッキリ表示
    }
}

void MagicMeter::onInactive() {
}

void MagicMeter::processDraw() {
    GgafDx::MassBoardEffect* const pMassBoardEffect = _pMassBoardEffect;
    ID3DXEffect* pID3DXEffect = pMassBoardEffect->_pID3DXEffect;
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();

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
    VERTEX_instancedata* p = paInstancedata_MM_;

    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->getValue();//一周したのでアクティブであるはず
        pMagic_level = pMagic->level_;
        float wx = width_px_*i;

        //マジックメーター背景
        p->px_x = x + wx;
        p->px_y = y;
        p->depth_z = z;

        if (pMagic_level > 0 && pMagic->lvinfo_[pMagic_level].remained_frame_of_effecting <= fraeme_of_notice_remaind_) {
            p->r = 2.0;   p->g = 0.5;   p->b = 0.5;
//            pUvFlipper->getUV(1, u, v); //パターン1は赤背景、残り時間がやばい事を示す
        } else {
            p->r = 1.0;   p->g = 1.0;   p->b = 1.0;
//            pUvFlipper->getUV(0, u, v); //パターン0は通常背景
        }
        p->a = alpha;
        pUvFlipper->getUV(0, u, v);
        p->offset_u = u;
        p->offset_v = v;
        ++p; n++;

        //マジックメーター上の現在のマジックレベル表示
        p->px_x = x + wx;
        p->px_y = y;
        p->depth_z = z;
        p->r = 1.0;   p->g = 1.0;   p->b = 1.0;
        p->a = alpha*3; //強調表示
        pUvFlipper->getUV(pMagic->lvinfo_[pMagic_level].pno_, u, v);
        p->offset_u = u;
        p->offset_v = v;
        ++p; n++;

        float rr = r_roll_[i];
        if (rr > 0.1f) {
            //各マジック要素
            int lv_slecter_num = pMagic->max_level_+1;
            for (int j = 0; j < lv_slecter_num; j++) {

                //魔法名
                p->px_x = x + wx;
                p->px_y = y - (height_px_*(j+1)*rr);
                p->depth_z = z;
                p->a = alpha*rr; //アクティブな列は表示
                if (pMagic->chkCastAble(j) <= MAGIC_CAST_NG_MP_IS_SHORT) {
                    //詠唱不可表示 (MAGIC_CAST_NG_MP_IS_SHORT か MAGIC_CAST_NG_INVOKING_NOW)
//                    pUvFlipper->getUV(pMagic->lvinfo_[j].pno_ + 1, u, v); //右隣のテクスチャパターンが DISABLE なパターン前提
                    p->r = 0.3;  p->g = 0.3;  p->b = 0.3;
                } else {
                    //詠唱可能表示
//                    pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                    p->r = 1.0;  p->g = 1.0;  p->b = 1.0;
                }
                pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                p->offset_u = u;
                p->offset_v = v;
                p++; n++;
            }
        }
        pElem = pElem->_pNext;
    }
    _pMassBoardModel->GgafDx::MassBoardModel::draw(this, n, paInstancedata_MM_);
}

void MagicMeter::rollOpen(int prm_meter_index) {
    r_roll_velo_[prm_meter_index] = 0.1f;
}

void MagicMeter::rollClose(int prm_meter_index) {
    r_roll_velo_[prm_meter_index] = -0.1f;
}

MagicMeter::~MagicMeter() {
    GGAF_DELETEARR(papLvTgtMvCur_);
    GGAF_DELETEARR(papLvNowCur_);
    GGAF_DELETEARR(papLvCastingCur_);
    GGAF_DELETEARR(r_roll_);
    GGAF_DELETEARR(r_roll_velo_);
    GGAF_DELETE(pSeTx4Cast_);
    GGAF_DELETE(pSeTx4Invoke_);

    GGAF_DELETEARR(paInstancedata_MM_);
}
