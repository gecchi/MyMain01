#include "TitleBoard.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/Colorist.h"



using namespace GgafLib;
using namespace VioletVreath;

TitleBoard::TitleBoard(const char* prm_name) : DefaultMassBoardActor(prm_name, "Title") {
    _class_name = "TitleBoard";
    useZBufferDrawing(false);
    setZBufferWriteEnable(false);

    _z = 10; //メニューを表に出すために、タイトルは奥へ・・・

    //インスタンスデータ初期化
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    float u, v;
    aInstancedata_title_[0].px_x = C_PX(_x);
    aInstancedata_title_[0].px_y = C_PX(_y);
    aInstancedata_title_[0].depth_z = C_PX(_z);
    aInstancedata_title_[0].local_px_x = 0.0f;
    aInstancedata_title_[0].local_px_y = 0.0f;
    aInstancedata_title_[0].r_sx = SC_R(_sx);
    aInstancedata_title_[0].r_sy = SC_R(_sy);
    aInstancedata_title_[0].rad_rz = ANG_RAD(_rz);
    pUvFlipper->getUV(0, u, v);
    aInstancedata_title_[0].offset_u = u;
    aInstancedata_title_[0].offset_v = v;
    memcpy(&(aInstancedata_title_[0].r), &(_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);

    aInstancedata_title_[1] = aInstancedata_title_[0];

    pUvFlipper->getUV(1, u, v);
    aInstancedata_title_[1].offset_u = u;
    aInstancedata_title_[1].offset_v = v;
}

void TitleBoard::onCreateModel() {
}

void TitleBoard::initialize() {
}

void TitleBoard::onActive() {
}

void TitleBoard::processBehavior() {

}

void TitleBoard::processJudgement() {
}

void TitleBoard::processDraw() {
    aInstancedata_title_[0].px_x = C_PX(_x);
    aInstancedata_title_[0].px_y = C_PX(_y);
    aInstancedata_title_[1].px_x = C_PX(_x + PX_C(600));
    aInstancedata_title_[1].px_y = C_PX(_y);
    _pMassBoardModel->GgafDx::MassBoardModel::draw(this, 2, aInstancedata_title_);
}

TitleBoard::~TitleBoard() {
}
