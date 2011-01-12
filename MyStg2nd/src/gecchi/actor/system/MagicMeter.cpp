#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MagicMeter::MagicMeter(const char* prm_name)
: GgafDx9BoardSetActor(prm_name, prm_model, "MagicMeterEffect", "MagicMeterTechnique") {
    _class_name = "MagicMeter";
    //_z = 0.99;//たぶん最背面 （0 <= _z < 1.0）Z=(0～+1)
    //_z = 0.9999999f;
    _z = 0.00000001f;
    _width = _pBoardSetModel->_fSize_BoardSetModelWidthPx;
    _height = _pBoardSetModel->_fSize_BoardSetModelHeightPx/9;
    _x = 100;
    _h_active_magic = _pID3DXEffect->GetParameterByName( NULL, "_g_active_magic" ); //マスターα



//    [0][0]  [1][0]  [2][0]  [3][0]
//    [0][1]  [1][1]  [2][1]  [3][1]
//    [0][2]  [1][2]  [2][2]  [3][2]
//    [0][3]  [1][3]  [2][3]  [3][3]
//    [0][4]  [1][4]  [2][4]  [3][4]
//    [0][5]  [1][5]  [2][5]  [3][5]
//    [0][6]  [1][6]  [2][6]  [3][6]
//    [0][7]  [1][7]  [2][7]  [3][7]
//    [0][8]  [1][8]  [2][8]  [3][8]
//
//    [4][0]  [5][0]  [6][0]  [7][0]
//    [4][1]  [5][1]  [6][1]  [7][1]
//    [4][2]  [5][2]  [6][2]  [7][2]
//    [4][3]  [5][3]  [6][3]  [7][3]
//    [4][4]  [5][4]  [6][4]  [7][4]
//    [4][5]  [5][5]  [6][5]  [7][5]
//    [4][6]  [5][6]  [6][6]  [7][6]
//    [4][7]  [5][7]  [6][7]  [7][7]
//    [4][8]  [5][8]  [6][8]  [7][8]
//

    int pno[9][8] = { { 0,  1,   2,   3},
                      { 4,  5,   6,   7},
                      { 8,  9,  10,  11},
                      {12, 13,  14,  15},
                      {16, 17,  18,  19},
                      {20, 21,  22,  23},
                      {24, 25,  26,  27},
                      {28, 29,  30,  31},
                      {32, 33,  34,  35},
                      {36, 37,  38,  39},
                      {40, 41,  42,  43},
                      {44, 45,  46,  47},
                      {48, 49,  50,  51},
                      {52, 53,  54,  55},
                      {56, 57,  58,  59},
                      {60, 61,  62,  63},
                      {64, 65,  66,  67},
                      {68, 69,  70,  71} };
    for (int i = 0; i < MMETER_MAX_LEVEL_Y; i++) {
        for(int j = 0; j < 8; j++) {
            _pos_pattern_no[i][j] = pno[i][j];
        }
    }

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
    _pUvFlipper->behave();
}

void MagicMeter::processJudgement() {
}

void MagicMeter::onInactive() {
}
void MagicMeter::processDraw() {
    _draw_set_num = _ringMagics.length(); //同一描画深度に、GgafDx9BoardSetActorの同じモデルかつ同じテクニックが
//                       //連続しているカウント数
//    GgafDx9DrawableActor* _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
//    while (true) {
//        if (_pNextDrawActor != NULL)  {
//            if (_pNextDrawActor->_pGgafDx9Model == _pBoardSetModel &&
//                _pNextDrawActor->_hash_technique == _hash_technique &&
//                _pNextDrawActor->isActive()
//            ) {
//                _draw_set_num++;
//                if (_draw_set_num > _pBoardSetModel->_set_num) {
//                    _draw_set_num = _pBoardSetModel->_set_num;
//                    break;
//                }
//                _pNextDrawActor = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
//            } else {
//                break;
//            }
//        } else {
//            break;
//        }
//    }
//
//    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
//    HRESULT hr;
//
//    GgafDx9DrawableActor *pDrawActor;
//    GgafDx9RectUV* pRectUV_Active;


    Magic* pMagic;
    GgafLinkedListRing<Magic>::Elem* pElem = _ringMagics.getElemFirst();
    hr = pID3DXEffect->SetFloat(_h_active_magic, _ringMagics->ge);
    checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) に失敗しました。");
    for (int i = 0; i < _draw_set_num; i++) {
        pMagic = pElem->_pValue;
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], _x+_width*i);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[i], _y - (_height*MMETER_MAX_LEVEL_Y) + (_height*pMagic->_flevel));
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedY) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[i], _z);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[i], _fAlpha);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahAlpha) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], _pBoardSetModel->_paRectUV[i]->_aUV[0].tu);
        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], _pBoardSetModel->_paRectUV[i]->_aUV[0].tv);
        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) に失敗しました。");
        if (pMagic != _ringMagics.getCurrent()) {
            hr = pID3DXEffect->SetInt(_h_active_magic, i);
            checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetInt(_h_active_magic) に失敗しました。");
        }
        hr = pID3DXEffect->SetInt(_h_magic_no, i);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetInt(_h_magic_no) に失敗しました。");
        pElem = pElem->_pNext;
    }


    _pBoardSetModel->draw(this);
}

MagicMeter::~MagicMeter() {
}
