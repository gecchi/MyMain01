#include "jp/ggaf/lib/util/DirectionUtil.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

#define V3E (0.57735026918963)    // éŒÇﬂÇÃíPà ÉxÉNÉgÉãäeóvëf(t = (1.0 / Å„(1*1+1*1+1*1)) * 1 )
#define V2E (0.70710678118655)    // t = (1.0 / Å„(1*1+1*1)) * 1
DirectionUtil::FaceVec DirectionUtil::_vec[3*3*3] = {
        {-V3E, -V3E, -V3E},      //FACE_NNN,     //TN(-1,-1,-1)
        {-V2E, -V2E,    0},      //FACE_NNZ,     //TN(-1,-1, 0)
        {-V3E, -V3E, +V3E},      //FACE_NNP,     //TN(-1,-1, 1)
        {-V2E,    0, -V2E},      //FACE_NZN,     //TN(-1, 0,-1)
        {  -1,    0,    0},      //FACE_NZZ,     //TN(-1, 0, 0)
        {-V2E,    0, +V2E},      //FACE_NZP,     //TN(-1, 0, 1)
        {-V3E, +V3E, -V3E},      //FACE_NPN,     //TN(-1, 1,-1)
        {-V2E, +V2E,    0},      //FACE_NPZ,     //TN(-1, 1, 0)
        {-V3E, +V3E, +V3E},      //FACE_NPP,     //TN(-1, 1, 1)
        {   0, -V2E, -V2E},      //FACE_ZNN,     //TN( 0,-1,-1)
        {   0,   -1,    0},      //FACE_ZNZ,     //TN( 0,-1, 0)
        {   0, -V2E, +V2E},      //FACE_ZNP,     //TN( 0,-1, 1)
        {   0,    0,   -1},      //FACE_ZZN,     //TN( 0, 0,-1)
        {   0,    0,    0},      //FACE_ZZZ,     //TN( 0, 0, 0)
        {   0,    0,   +1},      //FACE_ZZP,     //TN( 0, 0, 1)
        {   0, +V2E, -V2E},      //FACE_ZPN,     //TN( 0, 1,-1)
        {   0,   +1,    0},      //FACE_ZPZ,     //TN( 0, 1, 0)
        {   0, +V2E, +V2E},      //FACE_ZPP,     //TN( 0, 1, 1)
        {+V3E, -V3E, -V3E},      //FACE_PNN,     //TN( 1,-1,-1)
        {+V2E, -V2E,    0},      //FACE_PNZ,     //TN( 1,-1, 0)
        {+V3E, -V3E, +V3E},      //FACE_PNP,     //TN( 1,-1, 1)
        {+V2E,    0, -V2E},      //FACE_PZN,     //TN( 1, 0,-1)
        {  +1,    0,    0},      //FACE_PZZ,     //TN( 1, 0, 0)
        {+V2E,    0, +V2E},      //FACE_PZP,     //TN( 1, 0, 1)
        {+V3E, +V3E, -V3E},      //FACE_PPN,     //TN( 1, 1,-1)
        {+V2E, +V2E,    0},      //FACE_PPZ,     //TN( 1, 1, 0)
        {+V3E, +V3E, +V3E}       //FACE_PPP      //TN( 1, 1, 1)

};
DirectionUtil::FaceVec* DirectionUtil::_face2vec = &(DirectionUtil::_vec[13]); //13 ÇÕ 3*3*3=27 ÇÃê^ÇÒíÜÇÃóvëfÅB_face2vec[-13Å`13]Ç≈ÉAÉNÉZÉXÇ∑ÇÈà◊

DirectionUtil::FaceSgn DirectionUtil::_sgn[3*3*3] = {
         {-1,-1,-1 },      //FACE_NNN,
         {-1,-1, 0 },      //FACE_NNZ,
         {-1,-1, 1 },      //FACE_NNP,
         {-1, 0,-1 },      //FACE_NZN,
         {-1, 0, 0 },      //FACE_NZZ,
         {-1, 0, 1 },      //FACE_NZP,
         {-1, 1,-1 },      //FACE_NPN,
         {-1, 1, 0 },      //FACE_NPZ,
         {-1, 1, 1 },      //FACE_NPP,
         { 0,-1,-1 },      //FACE_ZNN,
         { 0,-1, 0 },      //FACE_ZNZ,
         { 0,-1, 1 },      //FACE_ZNP,
         { 0, 0,-1 },      //FACE_ZZN,
         { 0, 0, 0 },      //FACE_ZZZ,
         { 0, 0, 1 },      //FACE_ZZP,
         { 0, 1,-1 },      //FACE_ZPN,
         { 0, 1, 0 },      //FACE_ZPZ,
         { 0, 1, 1 },      //FACE_ZPP,
         { 1,-1,-1 },      //FACE_PNN,
         { 1,-1, 0 },      //FACE_PNZ,
         { 1,-1, 1 },      //FACE_PNP,
         { 1, 0,-1 },      //FACE_PZN,
         { 1, 0, 0 },      //FACE_PZZ,
         { 1, 0, 1 },      //FACE_PZP,
         { 1, 1,-1 },      //FACE_PPN,
         { 1, 1, 0 },      //FACE_PPZ,
         { 1, 1, 1 }       //FACE_PPP
};
DirectionUtil::FaceSgn* DirectionUtil::_face2sgn = &(DirectionUtil::_sgn[13]); //13 ÇÕ 3*3*3=27 ÇÃê^ÇÒíÜÇÃóvëfÅB_face2sgn[-13Å`13]Ç≈ÉAÉNÉZÉXÇ∑ÇÈà◊

int DirectionUtil::_relation_up_vec[3*3*3][3*3*3];
int (*DirectionUtil::_relation_up_by_vec)[3*3*3];

bool DirectionUtil::is_init = false;


void DirectionUtil::init() {
    if (DirectionUtil::is_init) {
        return;
    }
    _TRACE_("DirectionUtil::init()");
    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 3*3*3; j++) {
            DirectionUtil::_relation_up_vec[i][j] = FACE_XXX;
        }
    }
    _relation_up_by_vec =  (int (*)[3*3*3])(&(DirectionUtil::_relation_up_vec[13][13])); //13 ÇÕ 3*3*3=27 ÇÃê^ÇÒíÜÇÃóvëfÅA_relation_up_vec[-13Å`13][-13Å`13]Ç≈ÉAÉNÉZÉXÇ∑ÇÈà◊


//    for (int j = 0; j < 3*3*3; j++) {
//        DirectionUtil::_relation_up_vec[TN(0, 0, 0)][j] = TN( 0, 1, 0); //è„
//    }
//    DirectionUtil::_relation_up_vec[TN(0, 0, 0)][TN(0, 0, 0)] = TN(0, 0, 0);

    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN( 1,-1,-1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN( 1,-1, 0)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN( 1,-1, 1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN( 1, 0,-1)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN( 1, 0, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN( 1, 0, 1)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN( 1, 1,-1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN( 1, 1, 0)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN( 1, 1, 1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN(-1,-1,-1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN(-1,-1, 0)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN(-1,-1, 1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN(-1, 0,-1)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN(-1, 0, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN(-1, 0, 1)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN(-1, 1,-1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN(-1, 1, 0)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 0)][TN(-1, 1, 1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN(-1,-1,-1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN(-1,-1, 0)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN(-1,-1, 1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN(-1, 0,-1)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN(-1, 0, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN(-1, 0, 1)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN(-1, 1,-1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN(-1, 1, 0)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN(-1, 1, 1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN( 1,-1,-1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN( 1,-1, 0)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN( 1,-1, 1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN( 1, 0,-1)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN( 1, 0, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN( 1, 0, 1)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN( 1, 1,-1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN( 1, 1, 0)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 0)][TN( 1, 1, 1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN(-1, 1,-1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN(-1, 1, 0)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN(-1, 1, 1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 0, 1,-1)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 0, 1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 0, 1, 1)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 1, 1,-1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 1, 1, 0)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 1, 1, 1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN(-1,-1,-1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN(-1,-1, 0)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN(-1,-1, 1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 0,-1,-1)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 0,-1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 0,-1, 1)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 1,-1,-1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 1,-1, 0)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 0)][TN( 1,-1, 1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN(-1,-1,-1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN(-1,-1, 0)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN(-1,-1, 1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 0,-1,-1)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 0,-1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 0,-1, 1)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 1,-1,-1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 1,-1, 0)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 1,-1, 1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN(-1, 1,-1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN(-1, 1, 0)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN(-1, 1, 1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 0, 1,-1)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 0, 1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 0, 1, 1)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 1, 1,-1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 1, 1, 0)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 0)][TN( 1, 1, 1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN(-1,-1, 1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN(-1, 0, 1)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN(-1, 1, 1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 0,-1, 1)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 0, 0, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 0, 1, 1)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 1,-1, 1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 1, 0, 1)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 1, 1, 1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN(-1,-1,-1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN(-1, 0,-1)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN(-1, 1,-1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 0,-1,-1)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 0, 0,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 0, 1,-1)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 1,-1,-1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 1, 0,-1)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0, 1)][TN( 1, 1,-1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN(-1,-1,-1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN(-1, 0,-1)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN(-1, 1,-1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 0,-1,-1)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 0, 0,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 0, 1,-1)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 1,-1,-1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 1, 0,-1)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 1, 1,-1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN(-1,-1, 1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN(-1, 0, 1)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN(-1, 1, 1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 0,-1, 1)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 0, 0, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 0, 1, 1)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 1,-1, 1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 1, 0, 1)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 0,-1)][TN( 1, 1, 1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 0, 1,-1)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 0, 1, 0)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 0, 1, 1)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 1, 0,-1)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 1, 0, 0)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 1, 0, 1)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 1, 1,-1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 1, 1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 1, 1, 1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN(-1,-1,-1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN(-1,-1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN(-1,-1, 1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN(-1, 0,-1)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN(-1, 0, 0)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN(-1, 0, 1)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 0,-1,-1)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 0,-1, 0)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 0)][TN( 0,-1, 1)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN(-1,-1,-1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN(-1,-1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN(-1,-1, 1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN(-1, 0,-1)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN(-1, 0, 0)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN(-1, 0, 1)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 0,-1,-1)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 0,-1, 0)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 0,-1, 1)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 0, 1,-1)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 0, 1, 0)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 0, 1, 1)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 1, 0,-1)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 1, 0, 0)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 1, 0, 1)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 1, 1,-1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 1, 1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 0)][TN( 1, 1, 1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 0,-1, 1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 0, 0, 1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 0, 1, 1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 1,-1, 0)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 1, 0, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 1, 1, 0)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 1,-1, 1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 1, 0, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 1, 1, 1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN(-1,-1,-1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN(-1, 0,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN(-1, 1,-1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN(-1,-1, 0)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN(-1, 0, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN(-1, 1, 0)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 0,-1,-1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 0, 0,-1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0, 1)][TN( 0, 1,-1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN(-1,-1,-1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN(-1, 0,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN(-1, 1,-1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN(-1,-1, 0)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN(-1, 0, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN(-1, 1, 0)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 0,-1,-1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 0, 0,-1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 0, 1,-1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 0,-1, 1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 0, 0, 1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 0, 1, 1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 1,-1, 0)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 1, 0, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 1, 1, 0)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 1,-1, 1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 1, 0, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0,-1)][TN( 1, 1, 1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN(-1, 0, 1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 0, 0, 1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 1, 0, 1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN(-1, 1, 0)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 0, 1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 1, 1, 0)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN(-1, 1, 1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 0, 1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 1, 1, 1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN(-1,-1,-1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 0,-1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 1,-1,-1)] = TN( 1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN(-1,-1, 0)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 0,-1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 1,-1, 0)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN(-1, 0,-1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 0, 0,-1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1, 1)][TN( 1, 0,-1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN(-1,-1,-1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 0,-1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 1,-1,-1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN(-1,-1, 0)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 0,-1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 1,-1, 0)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN(-1, 0,-1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 0, 0,-1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 1, 0,-1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN(-1, 0, 1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 0, 0, 1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 1, 0, 1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN(-1, 1, 0)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 0, 1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 1, 1, 0)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN(-1, 1, 1)] = TN(-1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 0, 1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1,-1)][TN( 1, 1, 1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 0, 1,-1)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 0, 1, 0)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 0, 1, 1)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN(-1, 0,-1)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN(-1, 0, 0)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN(-1, 0, 1)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN(-1, 1,-1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN(-1, 1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN(-1, 1, 1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 1,-1,-1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 1,-1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 1,-1, 1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 1, 0,-1)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 1, 0, 0)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 1, 0, 1)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 0,-1,-1)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 0,-1, 0)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 0)][TN( 0,-1, 1)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 1, 0,-1)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 1, 0, 0)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 1, 0, 1)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 0,-1,-1)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 0,-1, 0)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 0,-1, 1)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 1,-1,-1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 1,-1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 1,-1, 1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN(-1, 1,-1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN(-1, 1, 0)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN(-1, 1, 1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 0, 1,-1)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 0, 1, 0)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN( 0, 1, 1)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN(-1, 0,-1)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN(-1, 0, 0)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 0)][TN(-1, 0, 1)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 0,-1, 1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 0, 0, 1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 0, 1, 1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN(-1,-1, 0)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN(-1, 0, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN(-1, 1, 0)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN(-1,-1, 1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN(-1, 0, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN(-1, 1, 1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 1,-1,-1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 1, 0,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 1, 1,-1)] = TN(-1, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 1,-1, 0)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 1, 0, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 1, 1, 0)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 0,-1,-1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 0, 0,-1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 0, 1)][TN( 0, 1,-1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 1,-1, 0)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 1, 0, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 1, 1, 0)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 0,-1,-1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 0, 0,-1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 0, 1,-1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 1,-1,-1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 1, 0,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 1, 1,-1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN(-1,-1, 1)] = TN( 1,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN(-1, 0, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN(-1, 1, 1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 0,-1, 1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 0, 0, 1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN( 0, 1, 1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN(-1,-1, 0)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN(-1, 0, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 0,-1)][TN(-1, 1, 0)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN(-1, 0, 1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 0, 0, 1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 1, 0, 1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN(-1,-1, 0)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 0,-1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 1,-1, 0)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN(-1,-1, 1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 0,-1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 1,-1, 1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN(-1, 1,-1)] = TN(-1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 0, 1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 1, 1,-1)] = TN( 1,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN(-1, 1, 0)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 0, 1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 1, 1, 0)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN(-1, 0,-1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 0, 0,-1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0,-1, 1)][TN( 1, 0,-1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN(-1, 1, 0)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 0, 1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 1, 1, 0)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN(-1, 0,-1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 0, 0,-1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 1, 0,-1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN(-1, 1,-1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 0, 1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 1, 1,-1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN(-1,-1, 1)] = TN(-1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 0,-1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 1,-1, 1)] = TN( 1, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN(-1, 0, 1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 0, 0, 1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 1, 0, 1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN(-1,-1, 0)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 0,-1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 0, 1,-1)][TN( 1,-1, 0)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN( 0, 0, 1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN( 0, 1, 0)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN( 0, 1, 1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN( 1, 0, 0)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN( 1, 0, 1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN( 1, 1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN( 1, 1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN( 0,-1, 0)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN( 0,-1,-1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN(-1, 0, 0)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN(-1, 0,-1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN(-1,-1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1, 1)][TN(-1,-1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN( 0, 0,-1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN( 0,-1,-1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN(-1, 0, 0)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN(-1, 0,-1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN(-1,-1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN(-1,-1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN( 0, 0, 1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN( 0, 1, 0)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN( 1, 0, 0)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN( 1, 0, 1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN( 1, 1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1,-1)][TN( 1, 1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN( 0, 0,-1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN( 0, 1, 0)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN( 0, 1,-1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN( 1, 0,-1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN( 1, 1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN( 1, 1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN( 0, 0, 1)] = TN( 1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN( 0,-1, 0)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN( 0,-1, 1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN(-1, 0, 0)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN(-1,-1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1, 1,-1)][TN(-1,-1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 0, 0, 1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 0,-1, 0)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 0,-1, 1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN(-1, 0, 0)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN(-1, 0, 1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN(-1,-1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 0, 0,-1)] = TN(-1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 0, 1, 0)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 0, 1,-1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 1, 0, 0)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 1, 0,-1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 1, 1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1,-1, 1)][TN( 1, 1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 0, 0, 1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 0,-1, 0)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 0,-1, 1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 1, 0, 0)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 1, 0, 1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 1,-1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 1,-1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 0, 0,-1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 0, 1, 0)] = TN( 1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN( 0, 1,-1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN(-1, 0, 0)] = TN( 0,-1, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN(-1, 0,-1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN(-1, 1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1, 1)][TN(-1, 1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 0, 0,-1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 0, 1, 0)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 0, 1,-1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN(-1, 0, 0)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN(-1, 0,-1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN(-1, 1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN(-1, 1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 0, 0, 1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 0,-1, 0)] = TN(-1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 0,-1, 1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 1, 0, 0)] = TN( 0, 1,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 1, 0, 1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 1,-1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1,-1)][TN( 1,-1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 0, 0,-1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 0,-1, 0)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 0,-1,-1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 1, 0, 0)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 1, 0,-1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 1,-1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 1,-1,-1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 0, 0, 1)] = TN( 1,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 0, 1, 0)] = TN( 1, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN( 0, 1, 1)] = TN( 1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN(-1, 0, 0)] = TN( 0,-1,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN(-1, 0, 1)] = TN( 0,-1, 0);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN(-1, 1, 0)] = TN( 0, 0,-1);
    DirectionUtil::_relation_up_by_vec[TN( 1,-1,-1)][TN(-1, 1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 0, 0, 1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 0, 1, 0)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 0, 1, 1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN(-1, 0, 0)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN(-1, 0, 1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN(-1, 1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN(-1, 1, 1)] = TN( 0, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 0, 0,-1)] = TN(-1, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 0,-1, 0)] = TN(-1, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 0,-1,-1)] = TN(-1, 0, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 1, 0, 0)] = TN( 0, 1, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 1, 0,-1)] = TN( 0, 1, 0);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 1,-1, 0)] = TN( 0, 0, 1);
    DirectionUtil::_relation_up_by_vec[TN(-1, 1, 1)][TN( 1,-1,-1)] = TN( 0, 0, 0);

    DirectionUtil::is_init = true;
}
face26 DirectionUtil::cnvVec2FaceNo(float prm_vx, float prm_vy, float prm_vz) {
    int sgn_x, sgn_y, sgn_z;
    DirectionUtil::cnvVec2Sgn(prm_vx, prm_vy, prm_vz,
                              sgn_x, sgn_y, sgn_z);
    return TN(sgn_x, sgn_y, sgn_z);
}

void DirectionUtil::cnvVec2Sgn(float prm_vx, float prm_vy, float prm_vz,
                                int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
    //îºåaÇPÇ…ì‡ê⁄Ç∑ÇÈê≥î™äpå`ÇÃÇPï”ÇÕ 2Å„2 - 2
    //                  y
    //                  ^
    //                  |
    //              ____|____
    //            Å^   ^|   /Å_
    //          Å^   v || 1/:  Å_
    //        Å^       || / :    Å_
    //       |         v|/  :      | É∆=3/8ÉŒ
    //      -+----------+---+------+---------> x
    //       |         0|<->       |
    //        Å_        | u      Å^
    //          Å_      |      Å^
    //            Å_ÅQÅQ|ÅQÅQÅ^
    //                  |
    // u = cos(3/8ÉŒ)  = 0.38268343236509
    // v = sin(3/8ÉŒ)  = 0.92387953251129

    static const float u = 0.38268343236509f;
    static const float v = 0.92387953251129f;

    float nvx, nvy, nvz;
    UTIL::getNormalizeVector(prm_vx, prm_vy, prm_vz,
                             nvx, nvy, nvz);

    //
    //     ^
    //     | u
    //     |____
    //    ^|   :Å_
    //   v||   :  Å_
    //    ||...:....Å_
    //    v|   :      | u
    //-----+---+------+--------->
    //     |<--------->
    //     |     v

    if (nvx < -u) {
        out_sgn_x = -1;
    } else if (u < nvx) {
        out_sgn_x = +1;
    } else {
        out_sgn_x = 0;
    }

    if (nvy < -u) {
        out_sgn_y = -1;
    } else if (u < nvy) {
        out_sgn_y = +1;
    } else {
        out_sgn_y = 0;
    }

    if (nvz < -u) {
        out_sgn_z = -1;
    } else if (u < nvz) {
        out_sgn_z = +1;
    } else {
        out_sgn_z = 0;
    }
}


void DirectionUtil::cnvFaceNo2Vec(face26 prm_face_no, float& out_vx, float& out_vy, float& out_vz) {
    out_vx = DirectionUtil::_face2vec[prm_face_no].vx;
    out_vy = DirectionUtil::_face2vec[prm_face_no].vy;
    out_vz = DirectionUtil::_face2vec[prm_face_no].vz;
}

void DirectionUtil::cnvFaceNo2Sgn(face26 prm_face_no, int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
    out_sgn_x = DirectionUtil::_face2sgn[prm_face_no].sgn_x;
    out_sgn_y = DirectionUtil::_face2sgn[prm_face_no].sgn_y;
    out_sgn_z = DirectionUtil::_face2sgn[prm_face_no].sgn_z;
}
