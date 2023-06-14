#include "GgafDx_World3DimEffect.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AGgafDx::MeshModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////
//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam_World;
float g_specular;
float g_specular_power;

float4x4 g_matWorld;  //World�ϊ��s��

float3 g_vecLightFrom_World; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_colMaterialDiffuse;  //�}�e���A���̐F
float g_tex_blink_power;
float g_tex_blink_threshold;

float g_offset_u;
float g_offset_v;

//s0���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float2 uv     : TEXCOORD0;
    float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���b�V���W�����_�V�F�[�_�[
OUT_VS VS_SpriteMesh(
    float4 prm_posModel_Local  : POSITION, // ���f���̒��_
    float3 prm_vecNormal_Local : NORMAL,   // ���f���̒��_�̖@��
    float2 prm_uv              : TEXCOORD0 // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_�v�Z
    out_vs.posModel_Proj = mul( mul( mul(prm_posModel_Local, g_matWorld), g_matView), g_matProj);  //World*View*�ˉe�ϊ�
    //UV
    out_vs.uv.x = prm_uv.x + g_offset_u;
    out_vs.uv.y = prm_uv.y + g_offset_v;

    //�@���� World �ϊ����Đ��K��
    const float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, g_matWorld));
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
    float refl_power = dot(vecNormal_World, -g_vecLightFrom_World);
    //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g�����A�}�e���A���F ���l�������J���[�쐬�B
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * g_colMaterialDiffuse;
    //���t�H�O
    out_vs.color.a = g_colMaterialDiffuse.a;
    //�������̕\�����@�B
    if (g_fog_starts_far_rate < 0.0) {
        //���̏ꍇ�A�ǂ�ȉ����ł��\������
        if (out_vs.posModel_Proj.z > g_zf*0.999) {
            //�{������O��Z�ł��A�`����������邽�߁A�ˉe���Z���W���㏑���A
            out_vs.posModel_Proj.z = g_zf*0.999; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    } else {
        //���t�H�O
        out_vs.color.a *= getFogRate(out_vs.posModel_Proj.z);
    }

    return out_vs;
}

OUT_VS VS_NoLight(
    float4 prm_posModel_Local  : POSITION,  // ���f���̒��_
    float3 prm_vecNormal_Local : NORMAL,    // ���f���̒��_�̖@��
    float2 prm_uv              : TEXCOORD0  // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;
    //���_�v�Z
    out_vs.posModel_Proj = mul( mul( mul(prm_posModel_Local, g_matWorld), g_matView), g_matProj);  //World*View*�ˉe�ϊ�
    //UV
    out_vs.uv.x = prm_uv.x + g_offset_u;
    out_vs.uv.y = prm_uv.y + g_offset_v;
    //�A�}�e���A���F ���l�������J���[�쐬�B
    out_vs.color = g_colMaterialDiffuse;
    return out_vs;
}


//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 PS_SpriteMesh(
    float2 prm_uv	 : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color;
    //Blinker���l��
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
    }
    //�}�X�^�[��
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_NoLight(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color;
    //Blinker���l��
//	if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
//		colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
//	}
    colOut.a *= g_alpha_master;
    return colOut;
}

technique SpriteMeshTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_SpriteMesh();
        PixelShader  = compile PS_VERSION PS_SpriteMesh();
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
        VertexShader = compile VS_VERSION VS_SpriteMesh();
        PixelShader  = compile PS_VERSION PS_SpriteMesh();
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
        VertexShader = compile VS_VERSION VS_SpriteMesh();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

technique NoLight
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_NoLight();
        PixelShader  = compile PS_VERSION PS_NoLight();
    }
}

