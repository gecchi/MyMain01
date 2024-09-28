#ifndef GGAF_DX_AAPRISMACTOR_H_
#define GGAF_DX_AAPRISMACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafDx {

/**
 * AA�v���Y��.
 * �v���Y����\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A�����Ppx�����̗�����(���S��(0,0,0))�̃v���Y����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class AAPrismActor : public MeshActor {
public:

    /**
     * ����]���̍\����
     */
    class RotPosPrism : public GgafCore::Object {
    public:
        angle _rx;
        angle _rz;
        angle _ry;
    public:
        RotPosPrism() : _rx(0), _rz(0), _ry(0) {
        };
        RotPosPrism(angle rx, angle rz, angle ry) :
            GgafCore::Object(), _rx(rx), _rz(rz), _ry(ry) {
        }
    };

    /** �v���Y���̎p���}�b�v�iAABB�̃v���Y���ʒu�F�Ή����鎲��]�j */
    static std::map<int, AAPrismActor::RotPosPrism> pos2r;

public:
    AAPrismActor(const char* prm_name);

    /**
     * �v���Y���̎p���}�b�v��ݒ�
     * @return
     */
    static bool initStatic();

    void drawPrism(coord prm_x1, coord prm_y1, coord prm_z1,
                   coord prm_x2, coord prm_y2, coord prm_z2, pos_t pos_info);

    virtual ~AAPrismActor();
};

}
#endif /*GGAF_DX_AAPRISMACTOR_H_*/
