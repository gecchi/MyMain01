#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AGgafDx::SpriteModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////
float4x4 g_matWorld;  //World�ϊ��s��
float4 g_colMaterialDiffuse;
float g_offset_u; //�e�N�X�`��U���W����
float g_offset_v; //�e�N�X�`��V���W����
float g_sin_rz;
float g_cos_rz;
float g_u_center;
float g_v_center;
//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//�X�v���C�g�W�����_�V�F�[�_�[
OUT_VS VS_DefaultRegularPolygonSprite(
      float4 prm_posModel_Local    : POSITION,     // ���f���̒��_
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;
    float x = prm_posModel_Local.x;
    float y = prm_posModel_Local.y;
    prm_posModel_Local.x = (x*g_cos_rz + y*-g_sin_rz);
    prm_posModel_Local.y = (x*g_sin_rz + y*g_cos_rz);
    //���_�v�Z
    const float4 posModel_World = mul(prm_posModel_Local, g_matWorld ); // World�ϊ�
    const float4 posModel_View = mul(posModel_World, g_matView );       // View�ϊ�
    const float4 posModel_Proj = mul(posModel_View, g_matProj);         // �ˉe�ϊ�
    out_vs.posModel_Proj = posModel_Proj;                         // �o�͂ɐݒ�
    //�������̕\�����@�B
    if (g_fog_starts_far_rate < 0.0) {
        //���̏ꍇ�A�ǂ�ȉ����ł��\������
        if (out_vs.posModel_Proj.z > g_zf*0.999) {
            //�{������O��Z�ł��A�`����������邽�߁A�ˉe���Z���W���㏑���A
            out_vs.posModel_Proj.z = g_zf*0.999; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    }
    //else {
    //    //���t�H�O
    //    out_vs.color.a *= getFogRate(out_vs.posModel_Proj.z);
    //}

    //UV�̃I�t�Z�b�g(�p�^�[���ԍ��ɂ�鑝��)���Z
    x = prm_uv.x - g_u_center;
    y = prm_uv.y - g_v_center;
    out_vs.uv.x = (x*g_cos_rz + y*g_sin_rz);
    out_vs.uv.y = (x*-g_sin_rz + y*g_cos_rz);
    out_vs.uv.x += (g_u_center + g_offset_u);
    out_vs.uv.y += (g_v_center + g_offset_v);
    
    //dot by dot�l��
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    return out_vs;
}

//�X�v���C�g�W���s�N�Z���V�F�[�_�[
float4 PS_DefaultRegularPolygonSprite(
    float2 prm_uv	  : TEXCOORD0
) : COLOR  {
    //���߂�F
    float4 colOut = tex2D( MyTextureSampler, prm_uv) ;
    //Blinker���l��
    colOut = getBlinkColor(colOut);
    colOut *= g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv)  * FLUSH_COLOR;
    colOut *= g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

//���e�N�j�b�N�FDefaultRegularPolygonSpriteTechnique��
//�y�@�\�z
//SpriteModel�p�W���V�F�[�_�[
//�y�T�v�z
//�|���i�[���X�v���C�g�j��`�悷��B���C�g�Ȃǂ̉A�e�͖����B
technique DefaultRegularPolygonSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultRegularPolygonSprite();
        PixelShader  = compile PS_VERSION PS_DefaultRegularPolygonSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultRegularPolygonSprite();
        PixelShader  = compile PS_VERSION PS_DefaultRegularPolygonSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultRegularPolygonSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
