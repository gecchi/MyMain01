#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicMeter::MagicMeter(const char* prm_name, GgafLib::AmountGraph* prm_pMP_MyShip, GgafLib::AmountGraph* prm_pVreath_MyShip)
      : DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    width_px_ = _pBoardSetModel->_fSize_BoardSetModelWidthPx;
    height_px_ = _pBoardSetModel->_fSize_BoardSetModelHeightPx;
    width_ = PX_C(width_px_);
    height_ = PX_C(height_px_);

//    _X = PX_C(100);
//    _Y = PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - (height_px_*2));
    _Z = 5;
//    AmountGraph qu_;
//    qu_.set(1.0);
//    qu_.config(400.0, 1.0);
//    float value_ = 1000;
//    qu_.config(400.0f, value_);
//    AmountGraph qu_();
//    [0][0]  [1][0]  [2][0]  [3][0]
//    [0][1]  [1][1]  [2][1]  [3][1]
//    [0][2]  [1][2]  [2][2]  [3][2]
//    [0][3]  [1][3]  [2][3]  [3][3]
//    [0][4]  [1][4]  [2][4]  [3][4]
//    [0][5]  [1][5]  [2][5]  [3][5]
//    [0][6]  [1][6]  [2][6]  [3][6]
//    [0][7]  [1][7]  [2][7]  [3][7]
//
//    [4][0]  [5][0]  [6][0]  [7][0]
//    [4][1]  [5][1]  [6][1]  [7][1]
//    [4][2]  [5][2]  [6][2]  [7][2]
//    [4][3]  [5][3]  [6][3]  [7][3]
//    [4][4]  [5][4]  [6][4]  [7][4]
//    [4][5]  [5][5]  [6][5]  [7][5]
//    [4][6]  [5][6]  [6][6]  [7][6]
//    [4][7]  [5][7]  [6][7]  [7][7]
//

    pMP_MyShip_ = prm_pMP_MyShip;

    cost_disp_.config(pMP_MyShip_->_max_val_px, pMP_MyShip_->_max_val); //値 10000 で表示は600pxとする。
    cost_disp_.set(0);

    ringMagics_.addLast(NEW TractorMagic("TRACTOR", pMP_MyShip_));
    ringMagics_.addLast(NEW SpeedMagic("SPEED", pMP_MyShip_));
    ringMagics_.addLast(NEW LockonMagic("LOCKON", pMP_MyShip_));
    ringMagics_.addLast(NEW TorpedoMagic("TORPEDO", pMP_MyShip_));
    ringMagics_.addLast(NEW LaserMagic("LASER", pMP_MyShip_));
    ringMagics_.addLast(NEW OptionMagic("OPTION", pMP_MyShip_));
    ringMagics_.addLast(NEW VreathMagic("VREATH", pMP_MyShip_));
    for (int i = 0; i < ringMagics_.length(); i++) {
        addSubGroup(ringMagics_.getNext(i));
    }

    pMagicCursor_ = NEW MagicMeterCursor001("MagicCursor", this); //メータ主カーソル
    pMagicCursor_->_Z = _Z - 3; //最も手前に表示したい
    addSubGroup(pMagicCursor_);

    papLvTargetCursor_ = NEW MagicLvCursor001*[ringMagics_.length()];
    papLvHilightCursor_ = NEW MagicLvCursor002*[ringMagics_.length()];
    papLvCastingMarkCursor_ = NEW MagicLvCursor003*[ringMagics_.length()];
    paFloat_rr_ = NEW float[ringMagics_.length()];
    paFloat_velo_rr_ = NEW float[ringMagics_.length()];
    Magic* pMagic;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);

        papLvTargetCursor_[i] = NEW MagicLvCursor001("LvTargetCursor", this, pMagic); //メータ副カーソル
        papLvTargetCursor_[i]->_Z = _Z - 3;
        addSubGroup(papLvTargetCursor_[i]);

        papLvHilightCursor_[i] = NEW MagicLvCursor002("LvHilightCursor", this, pMagic); //現レベル強調カーソル
        papLvHilightCursor_[i]->_Z = _Z - 1;
        addSubGroup(papLvHilightCursor_[i]);

        papLvCastingMarkCursor_[i] = NEW MagicLvCursor003("LvCastMarkCursor_", this, pMagic); //詠唱レベル強調カーソル
        papLvCastingMarkCursor_[i]->_Z = _Z - 2;
        papLvCastingMarkCursor_[i]->markOff();
        addSubGroup(papLvCastingMarkCursor_[i]);

        paFloat_rr_[i] = 0.0f;
        paFloat_velo_rr_[i] = 0.0f;
    }

    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    pMagicMeterStatus_->locatedBy(this);
    addSubGroup(pMagicMeterStatus_);

    //エネルギーバー設置
    pEnergyBar_ = NEW EnergyBar("EnergyBar", pMP_MyShip_);
    pEnergyBar_->locate(PX_C(100), PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 50.0f), _Z);
    addSubGroup(pEnergyBar_);
    //コスト表示バー
    pCostDispBar_ = NEW CostDispBar("CostDispBar", pEnergyBar_, &cost_disp_);
    pCostDispBar_->locate(pEnergyBar_->_X, pEnergyBar_->_Y, _Z-1);
    addSubGroup(pCostDispBar_);






    _pSeTx->useSe(SE_BAD_OPERATION+1);
    _pSeTx->set(SE_CURSOR_MOVE_METER             , "click07"      );  //メーター移動
    _pSeTx->set(SE_CURSOR_MOVE_LEVEL             , "G_EFC5"       );  //レベル移動
    _pSeTx->set(SE_CURSOR_MOVE_LEVEL_CANCEL      , "yume_ashi_022");  //レベル移動キャンセル
    _pSeTx->set(SE_CURSOR_BAD_MOVE               , "break_glass01");  //ダメな移動
    _pSeTx->set(SE_EXECUTE_LEVELUP_MAGIC         , "warp"         );  //レベルダウンアップ
    _pSeTx->set(SE_EXECUTE_LEVELDOWN_MAGIC       , "SwingA@11"    );  //レベルダウン実行
    _pSeTx->set(SE_EXECUTE_CANCEL_LEVELUP_MAGIC  , "warp"         );  //レベルダウンアップ
    _pSeTx->set(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC, "SwingA@11"    );  //レベルダウン実行
    _pSeTx->set(SE_CANT_INVOKE_MAGIC             , "yume_organ_01");  //詠唱完了時、MPが足りないため発動できない場合
    _pSeTx->set(SE_BAD_OPERATION                 , "yume_SUZU"    );  //ブブー
}

void MagicMeter::loadStatus(int prm_saveno) {
    st_[prm_saveno].seekg(std::stringstream::beg); //頭出し
    load(st_[prm_saveno]);
}

void MagicMeter::saveStatus(int prm_saveno) {
    save(st_[prm_saveno]);
}

void MagicMeter::save(std::stringstream& sts) {
    sts << pMP_MyShip_->get() << " ";
    Magic* pOrgMagic = ringMagics_.getCurrent();
    int len_magics = ringMagics_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->save(sts);
        pOrgMagic = ringMagics_.next();
    }
}

void MagicMeter::load(std::stringstream& sts) {
    int mp;
    sts >> mp;
    pMP_MyShip_->set(mp);

    Magic* pOrgMagic = ringMagics_.getCurrent();
    int len_magics = ringMagics_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->load(sts);
        pOrgMagic = ringMagics_.next();
    }
}

void MagicMeter::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //アニメ順序
    Magic* pMagic;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);
        papLvTargetCursor_[i]->moveTo(pMagic->level_);
        papLvHilightCursor_[i]->moveTo(pMagic->level_);
        papLvCastingMarkCursor_[i]->moveTo(0);
    }
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    if (VB_PLAY->isBeingPressed(VB_POWERUP)) {

        Magic* pActiveMagic = ringMagics_.getCurrent();     //アクティブな魔法
        int active_idx = ringMagics_.getCurrentIndex();     //アクティブな魔法のインデックス
        progress active_prg = pActiveMagic->_pProg->get();  //アクティブな魔法の進捗
        if (VB_PLAY->isPushedDown(VB_POWERUP)) {
            rollOpen(active_idx);
        }

        if (VB_PLAY->isAutoRepeat(VB_RIGHT)) {    //「→」押下時
            //レベル表示
            if (papLvTargetCursor_[active_idx]->point_lv_ != pActiveMagic->level_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_); //実行されなかった為、レベルカーソルもアクティブレベルに戻す
            }
            rollClose(active_idx); //現在ロールクローズ

            ringMagics_.next(); //メーターを１つ進める
            pActiveMagic= ringMagics_.getCurrent();     //更新
            active_idx = ringMagics_.getCurrentIndex(); //更新
            active_prg = pActiveMagic->_pProg->get();   //更新

            rollOpen(active_idx);  //進めた先をロールオープン
            pMagicCursor_->moveTo(active_idx); //メーターカーソルも１つ進める
            _pSeTx->play(SE_CURSOR_MOVE_METER);

        } else if (VB_PLAY->isAutoRepeat(VB_LEFT)) { //「←」押下時
            //レベル表示
            if (papLvTargetCursor_[active_idx]->point_lv_ != pActiveMagic->level_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL_CANCEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_); //実行されなかった為、レベルカーソルもアクティブレベルに戻す
            }
            rollClose(active_idx); //現在ロールクローズ

            ringMagics_.prev(); //メーターを１つ戻す
            pActiveMagic= ringMagics_.getCurrent();     //更新
            active_idx = ringMagics_.getCurrentIndex(); //更新
            active_prg = pActiveMagic->_pProg->get();   //更新

            rollOpen(active_idx); //戻した先をロールオープン
            pMagicCursor_->moveTo(active_idx); //メーターカーソルも１つ戻す
            _pSeTx->play(SE_CURSOR_MOVE_METER);

        } else if (VB_PLAY->isAutoRepeat(VB_UP) ) {  // 「↑」押下時
            if (pActiveMagic->max_level_ > papLvTargetCursor_[active_idx]->point_lv_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(papLvTargetCursor_[active_idx]->point_lv_ + 1);
            }

        } else if (VB_PLAY->isAutoRepeat(VB_DOWN)) {  //「↓」押下時
            if (0 < papLvTargetCursor_[active_idx]->point_lv_) {
                _pSeTx->play(SE_CURSOR_MOVE_LEVEL);
                papLvTargetCursor_[active_idx]->moveSmoothTo(papLvTargetCursor_[active_idx]->point_lv_ - 1);
            }
        } else {

        }
        //コストバー
        if (paFloat_rr_[active_idx] > 0.01f) {
            if (papLvTargetCursor_[active_idx]->point_lv_ == pActiveMagic->level_) {
                cost_disp_.set(0);
            } else if (papLvTargetCursor_[active_idx]->point_lv_ > pActiveMagic->level_) {
                cost_disp_.set(
                  pActiveMagic->interest_cost_[papLvTargetCursor_[active_idx]->point_lv_ - pActiveMagic->level_]
                );
            } else {
                cost_disp_.set(
                    -1*pActiveMagic->calcReduceMp(pActiveMagic->level_,  papLvTargetCursor_[active_idx]->point_lv_)
                );
            }
        } else {
            cost_disp_.set(0);
        }

        //「決定」時
        if (VB_PLAY->isPushedDown(VB_SHOT1)) {
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
                    papLvTargetCursor_[active_idx]->beginBlinking(); //ピカピカ！
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELUP: {
                    _pSeTx->play(SE_EXECUTE_LEVELUP_MAGIC);
                    papLvTargetCursor_[active_idx]->beginBlinking(); //ピカピカ！
                    //LEVELUP 時は既にpActiveMagic->new_level_ がアップ予定レベル
                    papLvCastingMarkCursor_[active_idx]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_LEVELDOWN: {
                    _pSeTx->play(SE_EXECUTE_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[active_idx]->beginBlinking(); //ピカピカ！
                    //LEVELDOWN 時は既に effect(new_lv) 実行済みのため、現レベル pActiveMagic->level_ となる
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->beginBlinking();
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
                    _pSeTx->play(SE_EXECUTE_CANCEL_LEVELUP_MAGIC);
                    papLvTargetCursor_[active_idx]->beginBlinking(); //ピカピカ！
                    //LEVELUP 時は既にpActiveMagic->new_level_ がアップ予定レベル
                    papLvCastingMarkCursor_[active_idx]->markOnLevelUpCast(pActiveMagic->new_level_);
                    break;
                }
                case MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN: {
                    _pSeTx->play(SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC);
                    papLvTargetCursor_[active_idx]->beginBlinking(); //ピカピカ！
                    //LEVELDOWN 時は既に effect(new_lv) 実行済みのため、現レベル pActiveMagic->level_ となる
                    papLvCastingMarkCursor_[active_idx]->markOnLevelDownCast(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->moveSmoothTo(pActiveMagic->level_);
                    papLvHilightCursor_[active_idx]->beginBlinking();
                    break;
                }
            }
        }
    } else  {
        if (VB_PLAY->isReleasedUp(VB_POWERUP)) {
            rollClose(ringMagics_.getCurrentIndex());
        }
    }

    //毎フレームの各魔法表示についての処理
    GgafProgress* pMagicProg = NULL;
    Magic* pMagic = NULL;
    for (int m = 0; m < ringMagics_.length(); m++) {
        pMagic = ringMagics_.getFromFirst(m);
        pMagicProg = pMagic->_pProg;

        paFloat_rr_[m] += paFloat_velo_rr_[m];
        if (paFloat_rr_[m] < 0.0f) {
            paFloat_rr_[m] = 0.0f;
            paFloat_velo_rr_[m] = 0.0f;
        }
        if (paFloat_rr_[m] > 1.0f) {
            paFloat_rr_[m] = 1.0f;
            paFloat_velo_rr_[m] = 0.0f;
        }

        //レベルアップINVOKING時
        if (pMagicProg->isJustChangedTo(Magic::STATE_INVOKE_BEGIN)) {
            papLvTargetCursor_[m]->dispDisable();
            papLvHilightCursor_[m]->dispDisable();
            if (papLvTargetCursor_[m]->point_lv_ == pMagic->level_) {
                //現レベルを指している場合
                //新しいレベルにこっそり動かしてあげる。
                papLvTargetCursor_[m]->moveSmoothTo(pMagic->new_level_);
            }
            papLvHilightCursor_[m]->moveSmoothTo(pMagic->new_level_, (frame)(pMagic->interest_time_of_invoking_[pMagic->new_level_-pMagic->level_]));
            papLvCastingMarkCursor_[m]->markOnInvoke(pMagic->new_level_);
        }
        //レベルアップINVOKING完了時
        if (pMagicProg->isJustChangedFrom(Magic::STATE_INVOKING)) {
            papLvTargetCursor_[m]->dispEnable();
            papLvHilightCursor_[m]->dispEnable();
            papLvHilightCursor_[m]->beginBlinking();
        }

        //効果開始時
        if (pMagicProg->isJustChangedTo(Magic::STATE_EFFECT_BEGIN)) {
            if (pMagic->last_level_ < pMagic->level_) {
                //レベルアップEFFECT_BEGEINだったならば
                papLvCastingMarkCursor_[m]->markOff(); //マークオフ！
            } else {
                //レベルダウンEFFECT_BEGEINだったならば
                //markOnLevelDownCast() した直後である。何もしない。
            }
        }

        //満期レベルダウン時
        if (pMagic->prev_frame_level_ != pMagic->level_ && pMagic->prev_frame_level_ > pMagic->level_) {
            if (papLvTargetCursor_[m]->point_lv_ == pMagic->prev_frame_level_) {
                papLvTargetCursor_[m]->moveSmoothTo(pMagic->level_);
            }
            papLvHilightCursor_[m]->moveSmoothTo(pMagic->level_);
            papLvHilightCursor_[m]->beginBlinking();
        }

        //空詠唱（詠唱したが、詠唱完了時、MPが足りなかった）
        if (pMagicProg->get() == Magic::STATE_NOTHING && pMagicProg->isJustChangedFrom(Magic::STATE_CASTING)) {
            papLvCastingMarkCursor_[m]->markOff(); //マークオフ！
            _pSeTx->play(SE_CANT_INVOKE_MAGIC);
        }
    }

    if (GgafDxInput::isPushedDownKey(DIK_K)) {
        saveStatus(0);
    }

    if (GgafDxInput::isPushedDownKey(DIK_L)) {
        loadStatus(0);
    }
}

void MagicMeter::processJudgement() {
}

void MagicMeter::onInactive() {
}

void MagicMeter::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    //GgafDxRectUV* pRectUV_Active;
    HRESULT hr;
    //パワーメーター
    //[====]が１つの大きさ [====][====][====]
    GgafLinkedListRing<Magic>::Elem* pElem = ringMagics_.getElemFirst();
    Magic* pMagic;
    int len_magics = ringMagics_.length();
    int n = 0;
    float u,v;
    float x = C_PX(_X);
    float y = C_PX(_Y);
    float z = C_PX(_Z);
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//一周したのでアクティブであるはず
        n = 0;

        //マジックメーター背景
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x +width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], _alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");
        _pUvFlipper->getUV(0, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
        n++;

        //マジックメーター上の現在のマジックレベル表示
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x + width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], _alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");
        _pUvFlipper->getUV(pMagic->lvinfo_[pMagic->level_].pno_, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
        n++;

        if (paFloat_rr_[i] > 0.1) {
            //各マジック要素
            for (int j = 0; j < pMagic->max_level_+1; j++) {
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x + width_px_*i);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y - (height_px_*(j+1)*paFloat_rr_[i]));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], paFloat_rr_[i]); //アクティブなら濃いめ
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");

                if (pMagic->chkCastAble(j) <= MAGIC_CAST_NG_MP_IS_SHORT) {
                    //MAGIC_CAST_NG_MP_IS_SHORT か MAGIC_CAST_NG_INVOKING_NOW
                    //詠唱不可表示
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_ + 1, u, v); //右隣のテクスチャパターンが DISABLE なパターン前提
                } else {
                    //詠唱可能表示
                    _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                }
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
                n++;
            }

//            //各マジックの現レベル強調表示
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_X[n], x + width_px_*i);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_X) に失敗しました。");
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_transformed_Y[n], y - ((height_px_*(pMagic->level_+1))*paFloat_rr_[i]));
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_transformed_Y) に失敗しました。");
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_depth_Z[n], z);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_depth_Z) に失敗しました。");
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_alpha[n], paFloat_rr_[i]*2);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ah_alpha) に失敗しました。");
//            _pUvFlipper->getUV(1, u, v);
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_u[n], u);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
//            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ah_offset_v[n], v);
//            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
//            n++;
        }

        _pBoardSetModel->draw(this, n);
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
    DELETEARR_IMPOSSIBLE_NULL(papLvTargetCursor_);
    DELETEARR_IMPOSSIBLE_NULL(papLvHilightCursor_);
    DELETEARR_IMPOSSIBLE_NULL(papLvCastingMarkCursor_);
    DELETEARR_IMPOSSIBLE_NULL(paFloat_rr_);
    DELETEARR_IMPOSSIBLE_NULL(paFloat_velo_rr_);
}
