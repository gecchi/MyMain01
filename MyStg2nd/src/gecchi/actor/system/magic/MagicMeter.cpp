#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MagicMeter::MagicMeter(const char* prm_name)
: DefaultBoardSetActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeter";
    //_z = 0.99;//たぶん最背面 （0 <= _z < 1.0）Z=(0～+1)
    //_z = 0.9999999f;
    _z = 0.00000001f;
    _width = _pBoardSetModel->_fSize_BoardSetModelWidthPx;
    _height = _pBoardSetModel->_fSize_BoardSetModelHeightPx;
    _x = 100;
    _y = 400;



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

//    int pno[9][8] = { { 0,  1,   2,   3},
//                      { 4,  5,   6,   7},
//                      { 8,  9,  10,  11},
//                      {12, 13,  14,  15},
//                      {16, 17,  18,  19},
//                      {20, 21,  22,  23},
//                      {24, 25,  26,  27},
//                      {28, 29,  30,  31},
//                      {32, 33,  34,  35},
//                      {36, 37,  38,  39},
//                      {40, 41,  42,  43},
//                      {44, 45,  46,  47},
//                      {48, 49,  50,  51},
//                      {52, 53,  54,  55},
//                      {56, 57,  58,  59},
//                      {60, 61,  62,  63},
//                      {64, 65,  66,  67},
//                      {68, 69,  70,  71} };
//    for (int i = 0; i < MMETER_MAX_LEVEL_Y; i++) {
//        for(int j = 0; j < 8; j++) {
//            _pos_pattern_no[i][j] = pno[i][j];
//        }
//    }

//    MagicKind* pMagicKind = NEW MagicKind("SPEEDUP");
//    MagicKind* pMagicKind = NEW MagicKind("MISSALE");
//    MagicKind* pMagicKind = NEW MagicKind("LASER");
//    MagicKind* pMagicKind = NEW MagicKind("OPTION");
//    MagicKind* pMagicKind = NEW MagicKind("FF");


//    SpeedMagic*  pSpeedMagic  = NEW SpeedMagic();
//    PhotonMagic* pPhotonMagic = NEW PhotonMagic();
//    LockonMagic* pLockonMagic = NEW LockonMagic();

//    addSubLast(pSpeedMagic);
//    addSubLast(pPhotonMagic);
//    addSubLast(pLockonMagic);


    _ringMagics.addLast(NEW OptionMagic("OPTION"));
    _ringMagics.addLast(NEW LaserMagic("LASER"));
}

void MagicMeter::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //アニメ順序
}

void MagicMeter::onActive() {
}

void MagicMeter::processBehavior() {
    //_pUvFlipper->behave();
}

void MagicMeter::processJudgement() {
    if (VB_PLAY->isBeingPressed(VB_POWERUP)) {

        if (VB_PLAY->isPushedDown(VB_RIGHT)) {
            _ringMagics.next();
        } else if (VB_PLAY->isPushedDown(VB_LEFT)) {
            _ringMagics.prev();
        } else if (VB_PLAY->isPushedDown(VB_UP)) {
            _ringMagics.getCurrent()->incLevel();
        } else if (VB_PLAY->isPushedDown(VB_DOWN)) {
            _ringMagics.getCurrent()->decLevel();
        }
    } else if (VB_PLAY->isReleasedUp(VB_POWERUP)) {

    }
}

void MagicMeter::onInactive() {
}
void MagicMeter::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    GgafDx9RectUV* pRectUV_Active;
    HRESULT hr;
    //パワーメーター
    //[====]が１つの大きさ [====][====][====]
    for (int i = 0; i < _ringMagics.length(); i++) {
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], _x +_width*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[i], _y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[i], _z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[i], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
        pRectUV_Active = _pBoardSetModel->_paRectUV + 3 + i; //3番目のパターンを式つけろ！
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) に失敗しました。");
    }
    _pBoardSetModel->draw(this, _ringMagics.length());

    GgafLinkedListRing<Magic>::Elem* pElem = _ringMagics.getElemFirst();
    //パワーメーターアクティブカーソル
    for (int i = 0; i < 1; i++) {
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], _x+_width*_ringMagics.indexOf(_ringMagics.getCurrent()));
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[i], _y) ;
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[i], _z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[i], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
        pRectUV_Active = _pBoardSetModel->_paRectUV + 0; //パターン0がパワーメーターアクティブカーソル
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) に失敗しました。");
    }
    _pBoardSetModel->draw(this, 1);
    //メーター要素


    Magic* pMagic;
    for (int i = 0; i < _ringMagics.length(); i++) {
        pMagic = pElem->_pValue;
        int draw_set_num = 0;
        for (int j = 0; j < pMagic->_max_level; j++) {
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[j], _x + _width*i);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[j], _y - _height*(j+1));
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[j], _z);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[j], _fAlpha); //アクティブなら濃いめ
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
            pRectUV_Active = _pBoardSetModel->_paRectUV + pMagic->_lvinfo[j]._pno;
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[j], pRectUV_Active->_aUV[0].tu);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[j], pRectUV_Active->_aUV[0].tv);
            checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) に失敗しました。");
            draw_set_num++;
        }
        _pBoardSetModel->draw(this, draw_set_num);
        pElem = pElem->_pNext;
    }

    //各メーター要素アクティブ
    pMagic = pElem->_pValue;//一周したのでアクティブであるはず
    for (int i = 0; i < _ringMagics.length(); i++) {
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], _x + _width*i);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedX) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[i], _y - (_height*(pMagic->_level+1)));
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahTransformedY) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[i], _z);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[i], _fAlpha);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw SetFloat(_ahAlpha) に失敗しました。");
        pRectUV_Active = _pBoardSetModel->_paRectUV + 1; //パターン1がメーター要素アクティブ
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetU) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
        checkDxException(hr, D3D_OK, "MagicMeter::processDraw() SetFloat(_hOffsetV) に失敗しました。");
    }

}

MagicMeter::~MagicMeter() {
}
