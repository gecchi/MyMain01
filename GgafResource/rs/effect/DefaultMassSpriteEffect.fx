#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AGgafDx::MassSpriteModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2016/02/25
////////////////////////////////////////////////////////////////////////////////
//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float4 color            : COLOR0;
    float2 uv               : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//�X�v���C�g�W�����_�V�F�[�_�[
OUT_VS VS_DefaultMassSprite(
      float4 prm_posModel_Local   : POSITION,      // ���f���̒��_
      float3 prm_vecNormal_Local  : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv               : TEXCOORD0,     // ���f���̒��_��UV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float2 prm_offset_uv        : TEXCOORD5,     // offset_u, offset_v
      float4 prm_color            : TEXCOORD6      // r, g, b, a
) {
    OUT_VS out_vs = (OUT_VS)0;
    //���_�v�Z
    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};

 //   prm_posModel_Local.x += prm_local.x;
 //   prm_posModel_Local.y += prm_local.y;

    //World*View*�ˉe�ϊ�
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);  // �o�͂ɐݒ�

    //UV�̃I�t�Z�b�g(�p�^�[���ԍ��ɂ�鑝��)���Z
    out_vs.uv.x = prm_uv.x + prm_offset_uv.x;
    out_vs.uv.y = prm_uv.y + prm_offset_uv.y;
    out_vs.color = prm_color;
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
    //dot by dot�l��
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    return out_vs;
}

//�X�v���C�g�W���s�N�Z���V�F�[�_�[
float4 PS_DefaultMassSprite(
    float2 prm_uv	  : TEXCOORD0 ,
    float4 prm_color  : COLOR0
) : COLOR  {

    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color;
    //Blinker���l��
    colOut = getBlinkColor(colOut);
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0 ,
    float4 prm_color  : COLOR0
) : COLOR  {
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR * prm_color;
    //���v�Z�A�e�N�X�`�����ƃI�u�W�F�N�g���̍��Z
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

//���e�N�j�b�N�FDefaultMassSpriteTechnique��
//�y�@�\�z
//MassSpriteModel�p�W���V�F�[�_�[
//�y�T�v�z
//�|���i�[���X�v���C�g�j��`�悷��B���C�g�Ȃǂ̉A�e�͖����B
technique DefaultMassSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassSprite();
        PixelShader  = compile PS_VERSION PS_DefaultMassSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultMassSprite();
        PixelShader  = compile PS_VERSION PS_DefaultMassSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultMassSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}