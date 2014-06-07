#include "stdafx.h"
#include "LabelRankFont.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

char LabelRankFont::RANK_1stDeg[10][6] = {
                                      ""     ,
                                      "!"    ,
                                      "!!"   ,
                                      "!!!"  ,
                                      "!!!!" ,
                                      "\""    ,
                                      "\"!"   ,
                                      "\"!!"  ,
                                      "\"!!!" ,
                                      "\"!!!!"
            };

char LabelRankFont::RANK_10thDeg[10][5] = {
                                       ""    ,
                                       "#$"  ,
                                       "%&"  ,
                                       "'("  ,
                                       ")*"  ,
                                       "+,"  ,
                                       "+,#$",
                                       "+,%&",
                                       "+,'(",
                                       "+,)*"
            };

char LabelRankFont::RANK_100thDeg[10][7] = {
                                        ""      ,
                                        "-./"   ,
                                        "012"   ,
                                        "345"   ,
                                        "678"   ,
                                        "9:;"   ,
                                        "9:;-./",
                                        "9:;012",
                                        "9:;345",
                                        "9:;678"
                                 };



char LabelRankFont::RANK_1000thDeg[10][9] = {
                                         ""        ,
                                         "<=>?"    ,
                                         "@ABC"    ,
                                         "DEFG"    ,
                                         "HIJK"    ,
                                         "LMNO"    ,
                                         "LMNO<=>?",
                                         "LMNO@ABC",
                                         "LMNODEFG",
                                         "LMNOHIJK"
                                  };


char LabelRankFont::RANK_10000thDeg[10][46] = {
                                           ""    ,
                                           "PQRST"                                        ,
                                           "PQRSTPQRST"                                   ,
                                           "PQRSTPQRSTPQRST"                              ,
                                           "PQRSTPQRSTPQRSTPQRST"                         ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRST"                    ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRST"               ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST"          ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST"     ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST"
            };

char LabelRankFont::RANK_INF[] = "UVWXYZ";


void LabelRankFont::cnvRankStr(int prm_rank, char* out) {
    out[0] = '\0';
    if (prm_rank <= 0) {
        strcat(out, "");
        return;
    }
    if (prm_rank > 100000) {
        strcat(out, RANK_INF);
        return;
    }
    int idx_rank_10000thDeg = prm_rank/10000;
    if (idx_rank_10000thDeg > 0) {
        strcat(out, RANK_10000thDeg[idx_rank_10000thDeg]);
        prm_rank -= idx_rank_10000thDeg*10000;
    }
    int idx_rank_1000thDeg = prm_rank/1000;
    if (idx_rank_1000thDeg > 0) {
        strcat(out, RANK_1000thDeg[idx_rank_1000thDeg]);
        prm_rank -= idx_rank_1000thDeg*1000;
    }
    int idx_rank_100thDeg = prm_rank/100;
    if (idx_rank_100thDeg > 0) {
        strcat(out, RANK_100thDeg[idx_rank_100thDeg]);
        prm_rank -= idx_rank_100thDeg*100;
    }
    int idx_rank_10thDeg = prm_rank/10;
    if (idx_rank_10thDeg > 0) {
        strcat(out, RANK_10thDeg[idx_rank_10thDeg]);
        prm_rank -= idx_rank_10thDeg*10;
    }
    int idx_rank_1stDeg = prm_rank;
    if (idx_rank_1stDeg > 0) {
        strcat(out, RANK_1stDeg[idx_rank_1stDeg]);
        prm_rank -= idx_rank_1stDeg;
    }

//    1     !    10   #$    100    -./    1000     ,-./    10000                                         PQRST
//    2    !!    20   %&    200    012    2000     @ABC    20000                                    PQRSTPQRST
//    3   !!!    30   '(    300    345    3000     DEFG    30000                               PQRSTPQRSTPQRST
//    4  !!!!    40   )*    400    678    4000     HIJK    40000                          PQRSTPQRSTPQRSTPQRST
//    5     "    50   +,    500    9:;    5000     LMNO    50000                     PQRSTPQRSTPQRSTPQRSTPQRST
//    6    "!    60 +,#$    600 9:;-./    6000 LMNO,-./    60000                PQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//    7   "!!    70 +,%&    700 9:;012    7000 LMNO@ABC    70000           PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//    8  "!!!    80 +,'(    800 9:;345    8000 LMNODEFG    80000      PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//    9 "!!!!    90 +,)*    900 9:;678    9000 LMNOHIJK    90000 PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//–³ŒÀ‘å UVWXYZ
}


LabelRankFont::LabelRankFont(const char* prm_name) :
        StringBoardActor(prm_name, "RankFont")
{
    _class_name = "LabelRankFont";
    tmp_rank_ = 0;
    setAlign(ALIGN_RIGHT, VALIGN_BOTTOM);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_RANK_UP  , "WAVE_RANK_UP");
    useProgress(PROG_BANPEI);
}

void LabelRankFont::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->getTexBlinker()->forceRange(0.5, 5.0);
    pModel->setBlinkPower(1.0, 0.01);
}

void LabelRankFont::initialize() {
    tmp_rank_ = G_RANK_DISP;
    getProgress()->reset(PROG_NOMALDISP);
}

void LabelRankFont::processBehavior() {
//    //<---- debug
    GgafProgress* pProg = getProgress();

    int rank_level = G_RANK_DISP;
    if (rank_level != tmp_rank_) {
        char c[65];
        cnvRankStr(rank_level, c);
        update(c);
        pProg->change(PROG_RANKUP);
        tmp_rank_ = rank_level;
    }


    switch (pProg->get()) {
        case PROG_NOMALDISP: {
            if (pProg->isJustChanged()) {
                getModel()->getTexBlinker()->transitionLinerUntil(1.0, 5);
            }
            break;
        }

        case PROG_RANKUP: {
            if (pProg->isJustChanged()) {
                getSeTx()->play(SE_RANK_UP);
                getModel()->getTexBlinker()->beat(30, 15, 0, 15, 3);
            }
            if (!getModel()->getTexBlinker()->isTransitioning()) {
                pProg->change(PROG_NOMALDISP);
            }
            break;
        }

        default: {
            break;
        }
    }
}

LabelRankFont::~LabelRankFont() {
}

