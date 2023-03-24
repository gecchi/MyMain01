#ifndef GGAF_DX_EFFECT_H_
#define GGAF_DX_EFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif
#include <string>

#define Obj_GgafDx_Effect                      (0x2U)            //0b 00000000 00000000 00000000 00000010
#define Obj_GgafDx_MeshEffect                  (0x4U)            //0b 00000000 00000000 00000000 00000100
#define Obj_GgafDx_D3DXAniMeshEffect           (0x8U)            //0b 00000000 00000000 00000000 00001000
#define Obj_GgafDx_MeshSetEffect               (0x10U)           //0b 00000000 00000000 00000000 00010000
#define Obj_GgafDx_MassMeshEffect              (0x20U)           //0b 00000000 00000000 00000000 00100000
#define Obj_GgafDx_MorphMeshEffect             (0x40U)           //0b 00000000 00000000 00000000 01000000
#define Obj_GgafDx_CubeMapMeshEffect           (0x80U)           //0b 00000000 00000000 00000000 10000000
#define Obj_GgafDx_CubeMapMeshSetEffect        (0x100U)          //0b 00000000 00000000 00000001 00000000
#define Obj_GgafDx_CubeMapMorphMeshEffect      (0x200U)          //0b 00000000 00000000 00000010 00000000
#define Obj_GgafDx_WorldBoundEffect            (0x400U)          //0b 00000000 00000000 00000100 00000000
#define Obj_GgafDx_SpriteEffect                (0x800U)          //0b 00000000 00000000 00001000 00000000
#define Obj_GgafDx_SpriteSetEffect             (0x1000U)         //0b 00000000 00000000 00010000 00000000
#define Obj_GgafDx_BoardEffect                 (0x2000U)         //0b 00000000 00000000 00100000 00000000
#define Obj_GgafDx_BoardSetEffect              (0x4000U)         //0b 00000000 00000000 01000000 00000000
#define Obj_GgafDx_MassEffect                  (0x8000U)         //0b 00000000 00000000 10000000 00000000
#define Obj_GgafDx_MassBoardEffect             (0x10000U)        //0b 00000000 00000001 00000000 00000000
#define Obj_GgafDx_PointSpriteEffect           (0x20000U)        //0b 00000000 00000010 00000000 00000000
#define Obj_GgafDx_MassSpriteEffect            (0x40000U)        //0b 00000000 00000100 00000000 00000000
#define Obj_GgafDx_MassMorphMeshEffect         (0x80000U)        //0b 00000000 00001000 00000000 00000000
#define Obj_GgafDx_MassPointSpriteEffect       (0x100000U)       //0b 00000000 00010000 00000000 00000000
#define Obj_GgafDx_PointSpriteSetEffect        (0x200000U)       //0b 00000000 00100000 00000000 00000000
#define Obj_GgafDx_FramedBoardEffect           (0x400000U)       //0b 00000000 01000000 00000000 00000000
#define Obj_GgafDx_RegularPolygonSpriteEffect  (0x800000U)       //0b 00000000 10000000 00000000 00000000
#define Obj_GgafDx_RegularPolygonBoardEffect   (0x1000000U)      //0b 00000001 00000000 00000000 00000000
#define Obj_GgafDx_BoneAniMeshEffect           (0x2000000U)      //0b 00000010 00000000 00000000 00000000
#define Obj_GgafDx_SkinAniMeshEffect           (0x4000000U)      //0b 00000100 00000000 00000000 00000000
#define Obj_GgafDx_FramedSpriteEffect          (0x8000000U)      //0b 00001000 00000000 00000000 00000000

namespace GgafDx {

/**
 * �G�t�F�N�g���N���X.
 * �L����(�A�N�^�[)�̃G�t�F�N�g��ێ�����N���X�ł��B<BR>
 * @version 1.00
 * @since 2018/10/30
 * @author Masatoshi Tsuge
 */
class Effect : public GgafCore::Object {
    friend class EffectManager;

    static std::string getEffectFileName(std::string prm_file);

//protected:
//    static D3DXMACRO _aD3DXMacro_Defines[3];

public:
    D3DXHANDLE _h_alpha_master;

    D3DXHANDLE _h_dbd_offset_x;
    D3DXHANDLE _h_dbd_offset_y;
    /** [r]�G�t�F�N�g��`�̎��ʖ��B(50�����܂�) */
    char* _effect_name;
    /** [r]�G�t�F�N�g */
    ID3DXEffect* _pID3DXEffect;

#ifdef MY_DEBUG
    bool _begin;
#endif

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g��`�̎��ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     */
    explicit Effect(const char* prm_effect_name);

    char* getName() {
        return _effect_name;
    }

    /**
     * 1�t���[����1����s���邾���ŗǂ��G�t�F�N�g�p�����[�^��
     * ���̃��\�b�h�ɋL�q����B
     */
    virtual void setParamPerFrame() = 0;

    void setAlphaMaster(float prm_scene_alpha);

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�EffectManager�ł���<BR>
     */
    virtual ~Effect();
};

}
#endif /*GGAF_DX_EFFECT_H_*/
