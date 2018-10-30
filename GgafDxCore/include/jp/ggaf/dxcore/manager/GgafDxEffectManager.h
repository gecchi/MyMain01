#ifndef GGAFDXCORE_GGAFDXEFFECTMANAGER_H_
#define GGAFDXCORE_GGAFDXEFFECTMANAGER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"


#define TYPE_MESH_EFFECT                     'X'
#define TYPE_MESHSET_EFFECT                  'x'
#define TYPE_MASSMESH_EFFECT                 't'
#define TYPE_CUBEMAPMESH_EFFECT              'G'
#define TYPE_CUBEMAPMESHSET_EFFECT           'g'
#define TYPE_D3DXANIMESH_EFFECT              'A'
#define TYPE_MORPHMESH_EFFECT                'M'
#define TYPE_MASSMORPHMESH_EFFECT            'm'
#define TYPE_CUBEMAPMORPHMESH_EFFECT         'H'
#define TYPE_WORLDBOUND_EFFECT               'W'
#define TYPE_SPRITE_EFFECT                   'S'
#define TYPE_SPRITESET_EFFECT                's'
#define TYPE_MASSSPRITE_EFFECT               'z'
#define TYPE_BOARD_EFFECT                    'B'
#define TYPE_BOARDSET_EFFECT                 'b'
#define TYPE_MASSBOARD_EFFECT                'w'
#define TYPE_POINTSPRITE_EFFECT              'P'
#define TYPE_MASSPOINTSPRITE_EFFECT          'p'
#define TYPE_POINTSPRITESET_EFFECT           'o'
#define TYPE_FRAMEDBOARD_EFFECT              'E'
#define TYPE_REGULARPOLYGONSPRITE_EFFECT     'R'
#define TYPE_REGULARPOLYGONBOARD_EFFECT      'r'

namespace GgafDxCore {

/**
 * GgafDxEffectConnection �Ǘ��N���X .
 * �����ς� GgafDxEffectConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxEffectManager : public GgafCore::GgafResourceManager<GgafDxEffect> {

public:
    static GgafDxEffect* _pEffect_active;

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDxEffectManager(const char* prm_manager_name);

    /**
     * �G�t�F�N�g����ID�ɂ��A�G�t�F�N�g�u�W�F�N�g�𐶐����� .
     * <pre>
     * ��prm_idstr�̌`��������
     * prm_idstr�́A
     * �w�G�t�F�N�g�^�C�v  + "/" + fx�t�@�C����(�g���q .fx ������������)�x
     * �Ƃ���������ɂȂ��Ă���B�G�t�F�N�g�^�C�v�͈ȉ��̒ʂ�
     *
     * ��F"x/LaserChipEffect" �̏ꍇ�B
     * "LaserChipEffect.fx"��ǂݍ��� GgafDxMeshSetEffect�C���X�^���X ��Ԃ��B
     * </pre>
     * @param prm_idstr �G�t�F�N�g����ID
     * @param prm_p ���R�p�����[�^�A���ݖ��g�p
     * @return �G�t�F�N�g�I�u�W�F�N�g
     */
    GgafDxEffect* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::GgafResourceConnection<GgafDxEffect>* processCreateConnection(const char* prm_idstr, GgafDxEffect* prm_pResource) override;

    virtual void setParamPerFrameAll();

    virtual void restoreAll();

    virtual void onDeviceLostAll();

    virtual ~GgafDxEffectManager() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXEFFECTMANAGER_H_*/
