#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MagicMeter::MagicMeter(const char* prm_name)
: DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    _width_px = _pBoardSetModel->_fSize_BoardSetModelWidthPx + 1.0f;
    _height_px = _pBoardSetModel->_fSize_BoardSetModelHeightPx + 1.0f;
    _X = 100*LEN_UNIT;
    _Y = (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - (_height_px*2)) * LEN_UNIT;
//    AmountGraph _qu;
//    _qu.set(1.0);
//    _qu.config(400.0, 1.0);
//    float _value = 1000;
//    _qu.config(400.0f, _value);
//    AmountGraph _qu();
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
    _ringMagics.addLast(NEW TractorMagic("TRACTOR"));
    _ringMagics.addLast(NEW SpeedMagic("SPEED"));
    _ringMagics.addLast(NEW LockonMagic("LOCKON"));
    _ringMagics.addLast(NEW TorpedoMagic("TORPEDO"));
    _ringMagics.addLast(NEW LaserMagic("LASER"));
    _ringMagics.addLast(NEW OptionMagic("OPTION"));
    for (int i = 0; i < _ringMagics.length(); i++) {
        addSubGroup(_ringMagics.getNext(i));
    }


    _paLevelCursor = NEW int[_ringMagics.length()];
    for (int i = 0; i < _ringMagics.length(); i++) {
        _paLevelCursor[i] = _ringMagics.getNextFromFirst(i)->_level;
    }
    _pSeTransmitter->useSe(4);
    _pSeTransmitter->set(0, "click07_2"); //メーター移動
    _pSeTransmitter->set(1, "G_EFC5");  //レベル移動
    _pSeTransmitter->set(2, "warp");  //決定
    _pSeTransmitter->set(3, "SwingA@11"); //キャンセル
}

void MagicMeter::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //アニメ順序
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    //_pUvFlipper->behave();
    GgafLinkedListRing<Magic>::Elem* pElem = _ringMagics.getElemFirst();
    for (int i = 0; i < _ringMagics.length(); i++) {
        pElem->_pValue->behave();
        pElem = pElem->_pNext;
    }
    //updatePanVolume3D しないため _pSeTransmitter->behave(); は不要
}

void MagicMeter::processJudgement() {


    if (VB_PLAY->isBeingPressed(VB_POWERUP)) {
        Magic* pActiveMagic = _ringMagics.getCurrent();
        int i = _ringMagics.indexOf(pActiveMagic);
        if (VB_PLAY->isPushedDown(VB_POWERUP)) {
            pActiveMagic->rollOpen();
        }

        if (VB_PLAY->isAutoRepeat(VB_RIGHT)) {
            _paLevelCursor[i] = pActiveMagic->_level;
            _pSeTransmitter->playImmediately(0);
            pActiveMagic->rollClose();
            _ringMagics.next();
            _ringMagics.getCurrent()->rollOpen();
        } else if (VB_PLAY->isAutoRepeat(VB_LEFT)) {
            _paLevelCursor[i] = pActiveMagic->_level;
            _pSeTransmitter->playImmediately(0);
            pActiveMagic->rollClose();
            _ringMagics.prev();
            _ringMagics.getCurrent()->rollOpen();
        } else if (VB_PLAY->isAutoRepeat(VB_UP)) {
            if (pActiveMagic->_max_level > _paLevelCursor[i]) {
                _pSeTransmitter->playImmediately(0);
                _paLevelCursor[i] ++;
            }
        } else if (VB_PLAY->isAutoRepeat(VB_DOWN)) {
            if (0 < _paLevelCursor[i]) {
                _pSeTransmitter->playImmediately(0);
                _paLevelCursor[i] --;
            }
        }
    } else if (VB_PLAY->isReleasedUp(VB_POWERUP)) {
        Magic* pActiveMagic = _ringMagics.getCurrent();
        int i = _ringMagics.indexOf(pActiveMagic);
        if (pActiveMagic->_level < _paLevelCursor[i]) {
            _pSeTransmitter->playImmediately(2);
            pActiveMagic->execute(_paLevelCursor[i]);
                 //レベルアップ魔法実行！

        } else if (pActiveMagic->_level > _paLevelCursor[i]) {
            _pSeTransmitter->playImmediately(3);
            pActiveMagic->execute(_paLevelCursor[i]);
                //レベルダウン魔法実行！

        } else if (pActiveMagic->_level == _paLevelCursor[i]) {
            //同じレベル実行＝何もしない
        }
        pActiveMagic->rollClose();
    }
}

void MagicMeter::onInactive() {
}

void MagicMeter::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    //GgafDx9RectUV* pRectUV_Active;
    HRESULT hr;
    //パワーメーター
    //[====]が１つの大きさ [====][====][====]
    GgafLinkedListRing<Magic>::Elem* pElem = _ringMagics.getElemFirst();
    Magic* pMagic;
    int len_magics = _ringMagics.length();
    int n = 0;
    float u,v;
    float x = float(App2Pix(_X));
    float y = float(App2Pix(_Y));
    float z = float(App2Pix(_Z));
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//一周したのでアクティブであるはず
        //各マジック要素
        n = 0;
        if (pMagic->_rr > 0.1) {
            for (int j = 0; j < pMagic->_max_level+1; j++) {
                n++;
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - (_height_px*(j+1)*pMagic->_rr));
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000002f);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->_rr); //アクティブなら濃いめ
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
//                pRectUV_Active = _pBoardSetModel->_paRectUV + pMagic->_lvinfo[j]._pno;
               // pRectUV_Active = _pUvFlipper->_paRectUV + pMagic->_lvinfo[j]._pno;
                _pUvFlipper->getUV(pMagic->_lvinfo[j]._pno, u, v);

                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
                checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) に失敗しました。");
            }

            //各マジックのカーソル
            n++;
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y - ((_height_px*(_paLevelCursor[i]+1))*pMagic->_rr));
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000001f);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], pMagic->_rr*2);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
            //pRectUV_Active = _pUvFlipper->_paRectUV + 1; //パターン1がメーター要素アクティブ
            _pUvFlipper->getUV(1, u, v);
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) に失敗しました。");

        }


        //マジックメーター背景
        n++;
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x +_width_px*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
        //pRectUV_Active = _pUvFlipper->_paRectUV + 2; //3番目のパターンを式つけろ！
        _pUvFlipper->getUV(2, u, v);

        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) に失敗しました。");

        //現在のマジックレベル表示
        n++;
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], 0.00000001f);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
        //pRectUV_Active = _pUvFlipper->_paRectUV + pMagic->_lvinfo[pMagic->_level]._pno;
        _pUvFlipper->getUV(pMagic->_lvinfo[pMagic->_level]._pno, u, v);

        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) に失敗しました。");

        _pBoardSetModel->draw(this, n+1);
        pElem = pElem->_pNext;
    }




    //パワーメーターアクティブカーソル
    n = 0;
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[n], x + _width_px*_ringMagics.indexOf(_ringMagics.getCurrent()));
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[n], y) ;
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[n], z);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[n], _fAlpha);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
    //pRectUV_Active = _pUvFlipper->_paRectUV + 0; //パターン0が
    _pUvFlipper->getUV(0, u, v);

    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[n], u);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[n], v);
    checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) に失敗しました。");
    _pBoardSetModel->draw(this, n+1);
}

MagicMeter::~MagicMeter() {
    DELETEARR_IMPOSSIBLE_NULL(_paLevelCursor);
}
