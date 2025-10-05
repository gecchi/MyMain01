#include "MgrSpacetime.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/lib/util/VirtualButton.h"

#include "actor/camera/MgrCameraWorker.h"
#include "actor/PointerTest.h"
#include "MgrCaretaker.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "util/MgrUtil.h"

using namespace GgafCore;
using namespace GgafDx;
using namespace GgafLib;
using namespace Mogera;


std::ofstream pOs_("C:/gnuplot/xxxxxx.txt");


MgrSpacetime::MgrSpacetime(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;
    UTIL::left_top_x_ = CONFIG::NUMBER_OF_SCREENS_USED > 1 ? PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].left) :
                                            PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].left);
    UTIL::left_top_y_ = CONFIG::NUMBER_OF_SCREENS_USED > 1 ? PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].top) :
                                            PX_C(pCARETAKER->_aRectRenderBufferSource[SCREEN01].top);
    UTIL::center_x_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_WIDTH / 2);
    UTIL::center_y_ = PX_C(CONFIG::RENDER_TARGET_BUFFER_HEIGHT / 2);

    pActiveCamWorker_ = NEW MgrCameraWorker("MgrCameraWorker", prm_pCam);
    getSceneChief()->appendChild(pActiveCamWorker_); //���f�t�H���g�J�������[�N

    pVb_ = NEW VirtualButton();
    pVb_->remapK(0, VB_UI_DEBUG, VBK_Q     );
    pVb_->remapK(0, VB_PAUSE   , VBK_ESCAPE);
    pVb_->remap(0, VB_UP     , VBK_UP   , VBJ_P1_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
    pVb_->remap(0, VB_DOWN   , VBK_DOWN , VBJ_P1_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
    pVb_->remap(0, VB_LEFT   , VBK_LEFT , VBJ_P1_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
    pVb_->remap(0, VB_RIGHT  , VBK_RIGHT, VBJ_P1_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
    pVb_->remap(0, VB_BUTTON1, VBK_SPACE, VBJ_P1_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");
}
struct MagneticLine {
    std::vector<D3DXVECTOR3> points;
};

// ���K��
D3DXVECTOR3 normalize(const D3DXVECTOR3& v) {
    float len = D3DXVec3Length(&v);
    if (len < 1e-6f) return D3DXVECTOR3(0,0,0);
    return v / len;
}

// ���C���C������
MagneticLine GenerateMagneticLine(
    const D3DXVECTOR3& start,       // N�� (���˓_)
    const D3DXVECTOR3& end,         // S�� (�G)
    const D3DXVECTOR3& initDir,     // �������[�U�[����
    int sampleCount,                // �T���v�����W��
    float fieldStrength = 5.0f,     // ���E�����W��
    float dt = 0.05f                // 1�X�e�b�v����
) {
    MagneticLine line;
    line.points.reserve(sampleCount);

    D3DXVECTOR3 pos = start;
    D3DXVECTOR3 vel = normalize(initDir);

    for (int i = 0; i < sampleCount; i++) {
        line.points.push_back(pos);

        // S�ɂ���̈��́i���E���ۂ��j
        D3DXVECTOR3 dir = end - pos;
        float dist2 = D3DXVec3LengthSq(&dir) + 1e-6f;
        D3DXVECTOR3 force = normalize(dir) * (fieldStrength / dist2);

        // �i�s�������X�V
        vel += force * dt;
        vel = normalize(vel);

        // ���W���X�V
        pos += vel * dt;
    }
    return line;
}

void MgrSpacetime::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    pWorld_ = desireScene(Mogera::MgrWorld);
    appendChild(pWorld_);


    // ���˓_�ƓG���W
    D3DXVECTOR3 start(0, 0, 0);
    D3DXVECTOR3 end(1, -1, 0);

    // ���������x�N�g���i������Ɍ��j
    D3DXVECTOR3 initDir(0, 3, 0);

    // ���C���C������
    MagneticLine line = GenerateMagneticLine(start, end, initDir, 200);

//    // GNUPLOT �`���ŏo��
//    for (std::vector<D3DXVECTOR3>::const_iterator it = curve.begin(); it != curve.end(); ++it)
//    {
//        _TRACE_( it->x << " " << it->y << " " << it->z );
//        pOs_ << it->x << " " << it->y << " " << it->z << std::endl;
//    }
    for (size_t i = 0; i < line.points.size(); ++i) {
        const D3DXVECTOR3& p = line.points[i];
        _TRACE_( p.x << " " << p.y << " " << p.z );
        pOs_ << p.x << " " << p.y << " " << p.z << std::endl;
        //std::cout << p.x << " " << p.y << " " << p.z << "\n";
    }
    pOs_.close();
}

//set xrange[-10:10]
//set yrange[-10:10]
//set zrange[-10:10]
//set view 60, 30, 1, 1  # zscale�𒲐����Ď��̔䗦�����킹��
//splot 'xxxxxx.txt' using 1:2 : 3 with points

void MgrSpacetime::processBehavior() {
    pVb_->update(); //���͏󋵍X�V

//    bool b1 = pVb_->isPressed(0, VB_UP);
//    bool b2 = pVb_->wasPressedAtLeastOnce(0, VB_UP, 10);
//    bool b3 = pVb_->wasPressedAtLeastOnce(0, VB_UP, 3);
//    _TRACE_(getBehaveingFrame() <<":"<<b1<<":"<<b2<<":"<<b3);
    bool b1 = pVb_->arePushedDownAtOnce3(0, VB_LEFT, VB_UP, VB_RIGHT, 1);
//    bool b2 = pVb_->arePushedDownAtOnce(0, VB_LEFT, VB_UP, VB_RIGHT, 10);
//    bool b3 = pVb_->arePushedDownAtOnce(0, VB_LEFT, VB_UP, VB_RIGHT, 60);
//    _TRACE_(getBehaveingFrame() <<":"<<b1<<":"<<b2<<":"<<b3);
    if (b1) {
        _TRACE_(getBehaveingFrame() <<":"<<b1);
    }

}
void MgrSpacetime::processJudgement() {
}
void MgrSpacetime::processHitCheck() {
    //�����蔻��`�F�b�N
    executeWorldHitCheck(MGR_MIKATA, MGR_TEKI);
    executeViewHitCheck(MGR_MIKATA, MGR_TEKI);
}

MgrSpacetime::~MgrSpacetime() {
    GGAF_DELETE(pVb_);
}

