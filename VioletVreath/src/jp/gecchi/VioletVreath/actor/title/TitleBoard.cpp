#include "TitleBoard.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TitleBoard::VERTEX_instancedata TitleBoard::_aInstancedata_title[2];

TitleBoard::TitleBoard(const char* prm_name) : DefaultMassBoardActor(prm_name, "Title") {
    _class_name = "TitleBoard";
    setZEnableDraw(false);
    setZWriteEnable(false);
}
void TitleBoard::onCreateModel() {
    _pMassBoardModel->_pInstancedata = TitleBoard::_aInstancedata_title;
    //���C���X�^���X�f�[�^�̓ǂݍ��݃A�h���X�������㏑��
    //���̎�@�͒��ӂ��K�v�ł���B
    //���f���ɃC���X�^���X�f�[�^��R�t���Ă��邽�߁A��{�́A���f���ɑ΂��ėB��̃A�N�^�[�̏ꍇ�Ƃ��邱�Ƃ��O��B
    //�������f���ŕ����A�N�^�[�̃C���X�^���X������ꍇ�A���ʂ̃C���X�^���X�f�[�^���w���̂ŁA
    //�Q�ڈȍ~NEW���ꂽ�A�N�^�[���A�A���`��i�[�x���ׂ荇���Ĉ�C�ɕ`�悷��j�ΏۂɂȂ��Ă��܂����ꍇ�A
    //����̃C���X�^���X�f�[�^�ŕ`�悳��Ă��܂����낤�B
    //�����"TitleBoard"�̓��f��"Title"�ŁAGamePreTitleScene , GameTitleScene �ł��ꂼ��NEW����Ă��邪�A
    //���ۂɓ����Ɂi�A���Łj�\�����邱�Ƃ��������Ƃ��\�ߕ������Ă���̂ŁA���܂��܂��܂������Ă���B

    static const size_t size_of_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    float u, v;

    TitleBoard::_aInstancedata_title[0].transformed_x = C_PX(_x);
    TitleBoard::_aInstancedata_title[0].transformed_y = C_PX(_y);
    TitleBoard::_aInstancedata_title[0].depth_z = C_PX(_z);
    TitleBoard::_aInstancedata_title[0].local_left_top_x = 0.0f;
    TitleBoard::_aInstancedata_title[0].local_left_top_y = 0.0f;
    TitleBoard::_aInstancedata_title[0].r_sx = SC_R(_sx);
    TitleBoard::_aInstancedata_title[0].r_sy = SC_R(_sy);
    TitleBoard::_aInstancedata_title[0].rad_rz = ANG_RAD(_rz);
    pUvFlipper->getUV(0, u, v);
    TitleBoard::_aInstancedata_title[0].offset_u = u;
    TitleBoard::_aInstancedata_title[0].offset_v = v;
    memcpy(&(TitleBoard::_aInstancedata_title[0].r), &(_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);

    TitleBoard::_aInstancedata_title[1].transformed_x = C_PX(_x + PX_C(600));
    TitleBoard::_aInstancedata_title[1].transformed_y = C_PX(_y);
    TitleBoard::_aInstancedata_title[1].depth_z = C_PX(_z);
    TitleBoard::_aInstancedata_title[1].local_left_top_x = 0.0f;
    TitleBoard::_aInstancedata_title[1].local_left_top_y = 0.0f;
    TitleBoard::_aInstancedata_title[1].r_sx = SC_R(_sx);
    TitleBoard::_aInstancedata_title[1].r_sy = SC_R(_sy);
    TitleBoard::_aInstancedata_title[1].rad_rz = ANG_RAD(_rz);
    pUvFlipper->getUV(1, u, v);
    TitleBoard::_aInstancedata_title[1].offset_u = u;
    TitleBoard::_aInstancedata_title[1].offset_v = v;
    memcpy(&(TitleBoard::_aInstancedata_title[1].r), &(_paMaterial[0].Diffuse), size_of_D3DCOLORVALUE);

}
void TitleBoard::initialize() {
    _z = 10; //���j���[��\�ɏo�����߂ɁA�^�C�g���͉��ցE�E�E
}

void TitleBoard::onActive() {
}

void TitleBoard::processBehavior() {
    TitleBoard::_aInstancedata_title[0].transformed_x = C_PX(_x);
    TitleBoard::_aInstancedata_title[0].transformed_y = C_PX(_y);
    TitleBoard::_aInstancedata_title[1].transformed_x = C_PX(_x + PX_C(600));
    TitleBoard::_aInstancedata_title[1].transformed_y = C_PX(_y);
}

void TitleBoard::processJudgement() {
}

void TitleBoard::processDraw() {

    _pMassBoardModel->GgafDxMassBoardModel::draw(this, 2);
}

TitleBoard::~TitleBoard() {
}
