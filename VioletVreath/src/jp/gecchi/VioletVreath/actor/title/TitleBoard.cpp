#include "TitleBoard.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TitleBoard::TitleBoard(const char* prm_name) : DefaultMassBoardActor(prm_name, "2/Title") {
    _class_name = "TitleBoard";
    setZEnableDraw(false);
    setZWriteEnable(false);

    _z = 10; //���j���[��\�ɏo�����߂ɁA�^�C�g���͉��ցE�E�E

    //�C���X�^���X�f�[�^������
    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
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
    _pMassBoardModel->GgafDxMassBoardModel::draw(this, 2, aInstancedata_title_);
}

TitleBoard::~TitleBoard() {
}
