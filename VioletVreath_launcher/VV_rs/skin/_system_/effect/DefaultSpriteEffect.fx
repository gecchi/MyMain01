#include "GgafEffectConst.fxh"
/**
 * GgafLib::DefaultSpriteActor �p�V�F�[�_�[ .
 * �|���S���Ƀe�N�X�`����\��t�����[���X�v���C�g���P�`�悷��W���I�ȃV�F�[�_�[�B
 * ���_�o�b�t�@�t�H�[�}�b�g�́A�ȉ��̂悤�� GgafLib::SpriteModel �ɒ�`����Ă�����̂�O��Ƃ��Ă��܂��B
 * {
 *     float x, y, z;             // ���W(���[�J�����W�n)
 *     float nx, ny, nz;          // �@���x�N�g��(���[�J�����W�n)
 *     DWORD color;               // ���_�J���[�i���ݖ��g�p�j
 *     float tu, tv;              // �e�N�X�`�����W
 * };
 *
 * DWORD SpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
 *
 * @author Masatoshi Tsuge
 * @since 2009/03/06
 */

/** ���f����World�ϊ��s�� */
float4x4 g_matWorld;
/** ���f����View�ϊ��s�� */
float4x4 g_matView;
/** ���f���̎ˉe�ϊ��s�� */
float4x4 g_matProj;
/** ���f���̃}�e���A���F(���C�g�ɂ��g�U���ˎ��̃��f���̐F) */
float4 g_colMaterialDiffuse;
/** �e�N�X�`��U���W�����i�p�^�[��No�ɂ�葝���j */
float g_offset_u;
/** �e�N�X�`��V���W�����i�p�^�[��No�ɂ�葝���j */
float g_offset_v;
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDx::TextureBlinker�Q��)�̓_�ŋ��x */
float g_tex_blink_power;
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDx::TextureBlinker�Q��)�̑ΏۂƂȂ�RGB�̂������l(0.0�`1.0) */
float g_tex_blink_threshold;
/** �t�F�[�h�C���E�A�E�g�@�\(GgafDx::AlphaCurtain�Q��)�̂��߂̃}�X�^�[�A���t�@�l(0.0�`1.0) */
float g_alpha_master;
/** ���݂̎ˉe�ϊ��s��v�f��zf�B�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
float g_zf;
/** -1.0 or 0.999 �B�����ł��\���������������ꍇ��0.999 ����������B*/
float g_far_rate;

/** �e�N�X�`���̃T���v���[(s0 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler MyTextureSampler : register(s0);

/** ���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS
{
    float4 posModel_Proj : POSITION;  //�ŏI�I�Ȓ��_���W(���[���h�E�r���[�E�ˉe�ϊ���)
    float4 color         : COLOR0;    //���_�J���[
    float2 uv            : TEXCOORD0; //���_�e�N�X�`��UV
};


/**
 * GgafLib::DefaultMeshActor �p�̋^���X�v���C�g�W�����_�V�F�[�_�[ .
 * ���_�� World > View > �ˉe �ϊ�����B
 * ���f���̃}�e���A���F�t�𒸓_�J���[�̐ݒ�ōs���B
 * �e�N�X�`���̃p�^�[���ԍ��ɔ����ݒ肳�ꂽUV���W��ݒ�B
 * @param prm_posModel_Local  ���_�̃��[�J�����W�B����A�E��A�����A�E���̏���4���_���n���Ă���
 * @param prm_uv              ���_��UV���W
 */
OUT_VS VS_DefaultSprite(
      float4 prm_posModel_Local : POSITION, // ���f���̒��_
      float2 prm_uv             : TEXCOORD0 // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;

    //World*View*�ˉe�ϊ�
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, g_matWorld ), g_matView ), g_matProj);  // �o�͂ɐݒ�
    //�������̕\�����@�B
    if (g_far_rate > 0.0) {
        if (out_vs.posModel_Proj.z > g_zf*g_far_rate) {
            //�{������O��Z�ł��A�`����������邽�߁A�ˉe���Z���W���㏑���A
            out_vs.posModel_Proj.z = g_zf*g_far_rate;
        }
    }
    //dot by dot�l��
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);

    //UV�̃I�t�Z�b�g�i�p�^�[���ԍ��ɂ�鑝���j�����Z
    out_vs.uv.x = prm_uv.x + g_offset_u;
    out_vs.uv.y = prm_uv.y + g_offset_v;

    //�}�e���A���F�Ƃ��Ē��_�J���[�ɐݒ�
    out_vs.color = g_colMaterialDiffuse;

    return out_vs;
}

/**
 * GgafLib::DefaultSpriteActor �p�̋^���X�v���C�g�W���s�N�Z���V�F�[�_�[ .
 * @param prm_uv    UV���W
 * @param prm_color �F�i�}�e���A���A���t�H�O�l���ς݁j
 */
float4 PS_DefaultSprite(
    float2 prm_uv    : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    //���߂�F
    float4 colTex = tex2D( MyTextureSampler, prm_uv); //�e�N�X�`������F�擾
    //�e�N�X�`���F�Ƀ}�e���A���J���[�ƃX�y�L�����[���l��
    float4 colOut = colTex * prm_color;
    //Blinker���l��
    if (colTex.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
    }

    //�}�X�^�[��
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv : TEXCOORD0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv)  * FLUSH_COLOR;
//    colOut *= g_colMaterialDiffuse;
//    colOut.a *= g_alpha_master;
    return colOut;
}

//���e�N�j�b�N�FDefaultSpriteTechnique��
//�y�@�\�z
//SpriteModel�p�W���V�F�[�_�[
//�y�T�v�z
//�|���i�[���X�v���C�g�j��`�悷��B���C�g�Ȃǂ̉A�e�͖����B
technique DefaultSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultSprite();
        PixelShader  = compile PS_VERSION PS_DefaultSprite();
    }
}

technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultSprite();
        PixelShader  = compile PS_VERSION PS_DefaultSprite();
    }
}

technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
