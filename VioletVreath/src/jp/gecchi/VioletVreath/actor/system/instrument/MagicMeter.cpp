#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_CURSOR_MOVE_METER = 0   ,
    SE_CURSOR_MOVE_LEVEL       ,
    SE_CURSOR_MOVE_LEVEL_CANCEL,
    SE_CURSOR_BAD_MOVE,
    SE_EXECUTE_LEVELUP_MAGIC   ,
    SE_EXECUTE_LEVELDOWN_MAGIC ,
};

MagicMeter::MagicMeter(const char* prm_name)
: DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    width_px_ = _pBoardSetModel->_fSize_BoardSetModelWidthPx + 1.0f;
    height_px_ = _pBoardSetModel->_fSize_BoardSetModelHeightPx + 1.0f;
    width_ = PX2CO(width_px_);
    height_ = PX2CO(height_px_);

    _X = 100*LEN_UNIT;
    _Y = (GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - (height_px_*2)) * LEN_UNIT;
    _Z = 10;
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


    mp_.config(600, 10000); //値 10000 で表示は400pxとする。
    mp_.set(10000);           //初期値は5000
    ringMagics_.addLast(NEW TractorMagic("TRACTOR", &mp_));
    ringMagics_.addLast(NEW SpeedMagic("SPEED", &mp_));
    ringMagics_.addLast(NEW LockonMagic("LOCKON", &mp_));
    ringMagics_.addLast(NEW TorpedoMagic("TORPEDO", &mp_));
    ringMagics_.addLast(NEW LaserMagic("LASER", &mp_));
    ringMagics_.addLast(NEW OptionMagic("OPTION", &mp_));
    for (int i = 0; i < ringMagics_.length(); i++) {
        addSubGroup(ringMagics_.getNext(i));
    }
    pMagicCursor_ = NEW MagicMeterCursor001("MagicCursor", this);
    addSubGroup(pMagicCursor_);

    paCursorLv_ = NEW int[ringMagics_.length()];
    papLvCursor_ = NEW MagicMeterCursor002*[ringMagics_.length()];
    Magic* pMagic;
    for (int i = 0; i < ringMagics_.length(); i++) {
        pMagic = ringMagics_.getFromFirst(i);
        paCursorLv_[i] = pMagic->level_;
        papLvCursor_[i] = NEW MagicMeterCursor002("LvCursor", this, pMagic);
        addSubGroup(papLvCursor_[i]);
    }

    pMagicMeterStatus_ = NEW MagicMeterStatus("MagicMeterStatus", this);
    pMagicMeterStatus_->locateAs(this);
    addSubGroup(pMagicMeterStatus_);

    //エネルギーバー設置
    pEnagyBar_ = NEW EnagyBar("EnagyBar", &mp_);
    pEnagyBar_->locate(PX2CO(100), PX2CO(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 50.0f), 0.00000001f );
    addSubGroup(pEnagyBar_);

    _pSeTransmitter->useSe(SE_EXECUTE_LEVELDOWN_MAGIC+1);
    _pSeTransmitter->set(SE_CURSOR_MOVE_METER, "click07"); //メーター移動
    _pSeTransmitter->set(SE_CURSOR_MOVE_LEVEL, "G_EFC5");    //レベル移動
    _pSeTransmitter->set(SE_CURSOR_MOVE_LEVEL_CANCEL, "yume_ashi_022"); //レベル移動キャンセル
    _pSeTransmitter->set(SE_CURSOR_BAD_MOVE, "break_glass01"); //ダメな移動
    _pSeTransmitter->set(SE_EXECUTE_LEVELUP_MAGIC, "warp");      //レベルダウンアップ
    _pSeTransmitter->set(SE_EXECUTE_LEVELDOWN_MAGIC, "SwingA@11"); //レベルダウン実行
}
void MagicMeter::loadStatus(int prm_saveno) {
    st_[prm_saveno].seekg(stringstream::beg); //頭出し
    load(st_[prm_saveno]);
}
void MagicMeter::saveStatus(int prm_saveno) {
    save(st_[prm_saveno]);
}

void MagicMeter::save(stringstream& sts) {
    sts << mp_.get() << " ";
    Magic* pOrgMagic = ringMagics_.getCurrent();
    int len_magics = ringMagics_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->save(sts);
        pOrgMagic = ringMagics_.next();
    }
}

void MagicMeter::load(stringstream& sts) {
    int mp;
    sts >> mp;
    mp_.set(mp);

    Magic* pOrgMagic = ringMagics_.getCurrent();
    int len_magics = ringMagics_.length();
    for (int i = 0; i < len_magics; i++) {
        pOrgMagic->load(sts);
        pOrgMagic = ringMagics_.next();
    }
}
void MagicMeter::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //アニメ順序
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    if (VB_PLAY->isBeingPressed(VB_POWERUP)) {

        Magic* pActiveMagic = ringMagics_.getCurrent();
        int i = ringMagics_.indexOf(pActiveMagic);
        if (VB_PLAY->isPushedDown(VB_POWERUP)) {
            pActiveMagic->rollOpen();
        }

        progress prg = pActiveMagic->_pProg->get();
        if (VB_PLAY->isAutoRepeat(VB_RIGHT)) {    //「→」押下時
            //レベル表示
            if (paCursorLv_[i] != pActiveMagic->level_) {
                _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL_CANCEL);
            }
            if (MAGIC_STATE_CASTING <= prg && prg <=  MAGIC_STATE_INVOKING) {
                //詠唱～発動中は、アクティブレベルに戻さない
            } else {
                paCursorLv_[i] = pActiveMagic->level_; //実行されなかった為、アクティブレベルに戻す
                papLvCursor_[i]->moveToLv(paCursorLv_[i]); //レベルカーソルもアクティブレベルに戻す
            }
            pActiveMagic->rollClose();
            //メータ表示
            ringMagics_.next(); //メーターを１つ進める
            ringMagics_.getCurrent()->rollOpen();
            _pSeTransmitter->playImmed(SE_CURSOR_MOVE_METER);
            pMagicCursor_->moveTo(ringMagics_.indexOf(ringMagics_.getCurrent())); //メーターカーソルも１つ進める

        } else if (VB_PLAY->isAutoRepeat(VB_LEFT)) { //「←」押下時
            //レベル表示
            if (paCursorLv_[i] != pActiveMagic->level_) {
                _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL_CANCEL);
            }
            if (MAGIC_STATE_CASTING <= prg && prg <=  MAGIC_STATE_INVOKING) {
                //詠唱～発動中は、アクティブレベルに戻さない
            } else {
                paCursorLv_[i] = pActiveMagic->level_; //実行されなかった為、アクティブレベルに戻す
                papLvCursor_[i]->moveToLv(paCursorLv_[i]); //レベルカーソルもアクティブレベルに戻す
            }
            pActiveMagic->rollClose();
            //メータ表示
            ringMagics_.prev(); //メーターを１つ戻す
            ringMagics_.getCurrent()->rollOpen();
            _pSeTransmitter->playImmed(SE_CURSOR_MOVE_METER);
            pMagicCursor_->moveTo(ringMagics_.indexOf(ringMagics_.getCurrent())); //メーターカーソルも１つ戻す

        } else if (VB_PLAY->isAutoRepeat(VB_UP)) {  // 「↑」押下時
            if (pActiveMagic->max_level_ > paCursorLv_[i] ) {
                if (prg != MAGIC_STATE_INVOKING) { //但し発動中は操作不可
                    _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL);
                    paCursorLv_[i] ++;
                    papLvCursor_[i]->moveToLv(paCursorLv_[i]);
                } else {
                    _pSeTransmitter->playImmed(SE_CURSOR_BAD_MOVE); //ブッブーサウンド
                }
            }

        } else if (VB_PLAY->isAutoRepeat(VB_DOWN) && prg != MAGIC_STATE_INVOKING) {  //「↓」押下時
            if (prg != MAGIC_STATE_INVOKING) { //但し発動中は操作不可
                if (0 < paCursorLv_[i]) {
                    _pSeTransmitter->playImmed(SE_CURSOR_MOVE_LEVEL);
                    paCursorLv_[i] --;
                    papLvCursor_[i]->moveToLv(paCursorLv_[i]);
                }
            } else {
                _pSeTransmitter->playImmed(SE_CURSOR_BAD_MOVE); //ブッブーサウンド
            }
        }

    } else if (VB_PLAY->isReleasedUp(VB_POWERUP)) { //決定

        Magic* pActiveMagic = ringMagics_.getCurrent();
        progress prg = pActiveMagic->_pProg->get();
        int i = ringMagics_.indexOf(pActiveMagic);
        if (pActiveMagic->level_ < paCursorLv_[i]) {
            _pSeTransmitter->playImmed(SE_EXECUTE_LEVELUP_MAGIC);
            pActiveMagic->cast(paCursorLv_[i]); //レベルアップ魔法実行！
            papLvCursor_[i]->beginBlinking(); //ピカピカ！
        } else if (pActiveMagic->level_ > paCursorLv_[i]) {
            _pSeTransmitter->playImmed(SE_EXECUTE_LEVELDOWN_MAGIC);
            pActiveMagic->cast(paCursorLv_[i]);  //レベルダウン魔法実行！
            papLvCursor_[i]->beginBlinking(); //ピカピカ！
        } else if (pActiveMagic->level_ == paCursorLv_[i]) {
            if (MAGIC_STATE_CASTING <= prg && prg < MAGIC_STATE_INVOKING) {
                //詠唱～発動前までの場合は、キャンセルを意味する。
            } else {
                //同じレベル実行＝何もしない
            }
        }
        pActiveMagic->rollClose();
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
    float x = float(CO2PX(_X));
    float y = float(CO2PX(_Y));
    float z = float(CO2PX(_Z));
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//一周したのでアクティブであるはず
        n = 0;

        //マジックメーター背景
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x +width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.010f);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
        _pUvFlipper->getUV(2, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
        n++;

        //マジックメーター上の現在のマジックレベル表示
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + width_px_*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.009f);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _alpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
        _pUvFlipper->getUV(pMagic->lvinfo_[pMagic->level_].pno_, u, v);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
        n++;

        if (pMagic->rr_ > 0.1) {
            //各マジック要素
            for (int j = 0; j < pMagic->max_level_+1; j++) {
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + width_px_*i);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - (height_px_*(j+1)*pMagic->rr_));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.015f+(0.001f*(j+1)));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->rr_); //アクティブなら濃いめ
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
                _pUvFlipper->getUV(pMagic->lvinfo_[j].pno_, u, v);
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
                n++;
            }

            //各マジックの現レベル強調表示
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + width_px_*i);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - ((height_px_*(pMagic->level_+1))*pMagic->rr_));
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.012f);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->rr_*2);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
            _pUvFlipper->getUV(1, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetU_) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(hOffsetV_) に失敗しました。");
            n++;
        }

        _pBoardSetModel->draw(this, n);
        pElem = pElem->_pNext;
    }
}

MagicMeter::~MagicMeter() {
    DELETEARR_IMPOSSIBLE_NULL(paCursorLv_);
    DELETEARR_IMPOSSIBLE_NULL(papLvCursor_);
}
