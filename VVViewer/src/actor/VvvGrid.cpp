#include "VvvGrid.h"

#include "VvvCaretaker.h"
#include "scene/VvvSpacetime.h"
#include "actor/VvvCamera.h"

using namespace GgafLib;
using namespace VVViewer;

VvvGrid::VvvGrid(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Grid2") {
}

void VvvGrid::initialize() {
    setAlpha(0.6);
    setPosition(0,0);
}

void VvvGrid::processBehavior() {
//    _TRACE_("-------------------");
//    DefaultCamera* pCam = pCARETAKER->getSpacetime()->getCamera();
//    double Zorg = -pCam->getZOrigin();
//    _TRACE_("Zorg="<<Zorg);
//    double H = CONFIG::GAME_BUFFER_HEIGHT;
//    _TRACE_("H="<<H);
//    double Zf = pCam->getZFar();
//    _TRACE_("Zf="<<Zf);
//    double Hf = (H*Zf)/Zorg;
//    _TRACE_("Hf="<<Hf);
//    double dz = C_DX(UTIL::getDistance(pCam, this));
//    _TRACE_("dz="<<dz);
//    double Hdz = (H*dz)/Zorg;
//    _TRACE_("Hdz="<<Hdz);
//    double rate = (H/Hdz);
//    _TRACE_("rate="<<rate);
//    double sr0 = 1.0/rate;
//    _TRACE_("sr0="<<sr0);
//    double sr1 = 1.0/(H/((H*(Zf - (-_dest_from_vppln_back)))/Zorg));
//    _TRACE_("sr1="<<sr1);
//    double sr2 = (_dest_from_vppln_back+Zf)/Zorg;
//    _TRACE_("sr2="<<sr1);
//   setScaleR(sr2);
//
//   /** [r]視錐台奥面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
//   //dxcoord _dest_from_vppln_back;
//   double d2 = Zf - (-_dest_from_vppln_back);
//   _TRACE_("d2="<<d2);
//
//

}

VvvGrid::~VvvGrid() {
}
