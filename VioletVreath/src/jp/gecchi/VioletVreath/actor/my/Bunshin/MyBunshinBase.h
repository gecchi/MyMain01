#ifndef MYBUNSHINCONTROLLER_H_
#define MYBUNSHINCONTROLLER_H_
#include "VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * ���g�y�� .
 * @version 1.00
 * @since 2015/04/17
 * @author Masatoshi Tsuge
 */
class MyBunshinBase : public GgafLib::DefaultGeometricActor {

private:
    class Pos {
    public:
        coord x, y, z;
        Pos() : x(0), y(0), z(0) {}
        void set(coord prm_x, coord prm_y, coord prm_z) {
            x = prm_x;   y = prm_y;   z = prm_z;
        }
        void set(const GgafDxCore::GgafDxGeometricActor* p) {
            x = p->_x;   y = p->_y;   z = p->_z;
        }
        void add(coord prm_x, coord prm_y, coord prm_z) {
            x += prm_x;  y += prm_y;  z += prm_z;
        }
    };
    class PosTrace {
    public:
        Pos* _paPos;
        int _num;
        int _p;
        PosTrace(int n) {
            _p = 0;
            _num = n;
            _paPos = NEW Pos[_num];
        }
        /**
         * �J�����g�v�f����i�߁A�i�߂����Pos�𓾂� .
         * @return
         */
        Pos* next() {
            if (_p == _num-1) {
                _p = 0;
            } else {
                _p++;
            }
            return &(_paPos[_p]);
        }
        Pos* getPrev() {
            return &(_paPos[ (_p == 0 ? _num-1 : _p-1) ]);
        }
        Pos* getNext() {
            return &(_paPos[ (_p == _num-1 ? 0 : _p+1) ]);
        }
        Pos* get2Next() {
            return &(_paPos[ (_p == _num-1 ? 1 : (_p == _num-2 ? 0 : _p+2) ) ]);
        }
        ~PosTrace() {
            GGAF_DELETEARR(_paPos);
        }
    };
    inline void positionAs(Pos *pPos) {
         position(pPos->x, pPos->y, pPos->z);
    }

public:
    /** �ő啪�g�� */
    static const int MAX_BUNSHIN_NUM;
    /** [r]���g�ƕ��g�̊Ԋu */
    static const frame BUNSHIN_D;
    /** [r]���g�̌����̊p���x */
    static const angvelo ANGVELO_TURN;
    /** [r]���g�����̍L�����]�p���x */
    static const angvelo ANGVELO_EXPANSE;
    /** [r]���g���߂��Ă��鎞��MAX���� */
    static const int RENGE;
    /** ���g�t���[�ړ����̕��g�̈ړ����x */
    static const velo VELO_BUNSHIN_FREE_MV;

    static int now_bunshin_num_;


    /** [r]���g�{�� */
    MyBunshin* pBunshin_;
    /** ���g�p�̃g���[�X���W�̗��j�i��΍��W�j�B�J�����g�����@���W�B */
    PosTrace* pPosTrace_;
    /** ���@�g���[�X�̍��W����̃I�t�Z�b�g(�t���[�łȂ��ꍇ��0) */
    GgafDxCore::GgafDxGeoElem trace_offset_;
    /** ���g�ԍ�(1�`) */
    unsigned int no_;
    /** ���g�ԍ�1�`MAX�ɂ���āA�o�����鉉�o�̂��߂̏悸�銄�������� */
    double delay_r_;
    /** [r]���g�𒆐S�Ƃ����A���g�̔��a�����̈ʒu(�����l) */
    coord bunshin_default_radius_position_;
    /** [r]���g�𒆐S�Ƃ����A���g�̌��]�O����̈ʒu(�����l) */
    angle bunshin_default_ang_position_;
    /** [r]���g�̍L����p�x(�����l) */
    angle bunshin_default_expanse_;
    /** [r]���g�𒆐S�Ƃ����A���g�̌��]�̊p���x(�����l) */
    angvelo bunshin_default_angvelo_mv_;
    /** [r]���g�ʒu�̍L����ړ����x */
    velo bunshin_velo_mv_radius_pos_;
    /** [r]���g�𒆐S�Ƃ����A���g�̔��a�����̈ʒu(�W�����) */
    velo bunshin_radius_pos_;

    /** [r]���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** */
    frame moving_frames_since_default_pos_;
    int trace_mode_;
    enum {
        TRACE_TWINBEE,
        TRACE_GRADIUS,
        TRACE_FREEZE,
    };

    enum {
        PROG_INIT,
        PROG_BUNSHIN_NOMAL_TRACE,
        PROG_BUNSHIN_FREE_MODE_IGNITED,
        PROG_BUNSHIN_FREE_MODE_READY,
        PROG_BUNSHIN_FREE_MODE_MOVE,
        PROG_BUNSHIN_FREE_MODE_STOP,
        PROG_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS,
        PROG_BANPEI,
    };
    frame return_default_pos_frames_;
    bool is_free_mode_;
    bool is_isolate_mode_;
    float c_ax_x_,c_ax_y_,c_ax_z_;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_no ���g�ԍ� (1�`)
     */
    MyBunshinBase(const char* prm_name, unsigned int prm_no);

    void config(
            coord prm_radius_position,
            angle prm_ang_position,
            angle prm_expanse,
            angvelo prm_angvelo_mv);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor���ŕ\���������ꍇ�̓R�����g�ɂ��邱��
//GgafDxGeometricActor�̏ꍇ�̓R�����g���O������
    //virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {}

    virtual ~MyBunshinBase();

    void resetBunshin(int prm_mode);

    void addTurnAngleAroundAx(float prm_ax_x, float prm_ax_y, float prm_ax_z);


    static void setBunshinNum(int prm_num);


};

}
#endif /*MYBUNSHINCONTROLLER_H_*/

