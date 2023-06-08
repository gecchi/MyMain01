#include "GgafDx_World3DimEffect.fxh"
// author : Masatoshi Tsuge
// date:2009/03/06

//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam_World;
float g_specular;
float g_specular_power;
float g_tex_blink_power;
float g_tex_blink_threshold;

// ���C�g�̕���
float3 g_vecLightFrom_World;
// Ambien���C�g�F�i���ːF�j
float4 g_colLightAmbient;
// Diffuse���C�g�F�i���ːF�j
float4 g_colLightDiffuse;
//���[���h�ϊ��s��
float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
float4x4 g_matWorld009;
float4x4 g_matWorld010;
float4x4 g_matWorld011;
float4x4 g_matWorld012;
float4x4 g_matWorld013;
float4x4 g_matWorld014;
float4x4 g_matWorld015;
//float4x4 g_matWorld016;
//�I�u�W�F�N�g�̃}�e���A���F�iDiffuse���ːF�ƁAAmbien���ːF���ʁj
float4 g_colMaterialDiffuse001;
float4 g_colMaterialDiffuse002;
float4 g_colMaterialDiffuse003;
float4 g_colMaterialDiffuse004;
float4 g_colMaterialDiffuse005;
float4 g_colMaterialDiffuse006;
float4 g_colMaterialDiffuse007;
float4 g_colMaterialDiffuse008;
float4 g_colMaterialDiffuse009;
float4 g_colMaterialDiffuse010;
float4 g_colMaterialDiffuse011;
float4 g_colMaterialDiffuse012;
float4 g_colMaterialDiffuse013;
float4 g_colMaterialDiffuse014;
float4 g_colMaterialDiffuse015;
//float4 g_colMaterialDiffuse016;

float g_offset_u001;
float g_offset_u002;
float g_offset_u003;
float g_offset_u004;
float g_offset_u005;
float g_offset_u006;
float g_offset_u007;
float g_offset_u008;
float g_offset_u009;
float g_offset_u010;
float g_offset_u011;
float g_offset_u012;
float g_offset_u013;
float g_offset_u014;
float g_offset_u015;
//float g_offset_u016;

float g_offset_v001;
float g_offset_v002;
float g_offset_v003;
float g_offset_v004;
float g_offset_v005;
float g_offset_v006;
float g_offset_v007;
float g_offset_v008;
float g_offset_v009;
float g_offset_v010;
float g_offset_v011;
float g_offset_v012;
float g_offset_v013;
float g_offset_v014;
float g_offset_v015;
//float g_offset_v016;

//�e�N�X�`���̃T���v��(s0���W�X�^)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float2 uv     : TEXCOORD0;
    float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS VS_SpriteMeshSet(
    float4 prm_posModel_Local  : POSITION,  // ���f���̒��_
    float  prm_index           : PSIZE ,    // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���H�j
    float3 prm_vecNormal_Local : NORMAL,    // ���f���̒��_�̖@��
    float2 prm_uv              : TEXCOORD0  // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = (int)prm_index;

    //���_�v�Z
    float4x4 matWorld;
    float offsetU;
    float offsetV;
    float4 colMaterialDiffuse;

    if (index == 0) {
        matWorld = g_matWorld001;
        colMaterialDiffuse = g_colMaterialDiffuse001;
        offsetU  = g_offset_u001;
        offsetV  = g_offset_v001;
    } else if (index == 1) {
        matWorld = g_matWorld002;
        colMaterialDiffuse = g_colMaterialDiffuse002;
        offsetU  = g_offset_u002;
        offsetV  = g_offset_v002;
    } else if (index == 2) {
        matWorld = g_matWorld003;
        colMaterialDiffuse = g_colMaterialDiffuse003;
        offsetU  = g_offset_u003;
        offsetV  = g_offset_v003;
    } else if (index == 3) {
        matWorld = g_matWorld004;
        colMaterialDiffuse = g_colMaterialDiffuse004;
        offsetU  = g_offset_u004;
        offsetV  = g_offset_v004;
    } else if (index == 4) {
        matWorld = g_matWorld005;
        colMaterialDiffuse = g_colMaterialDiffuse005;
        offsetU  = g_offset_u005;
        offsetV  = g_offset_v005;
    } else if (index == 5) {
        matWorld = g_matWorld006;
        colMaterialDiffuse = g_colMaterialDiffuse006;
        offsetU  = g_offset_u006;
        offsetV  = g_offset_v006;
    } else if (index == 6) {
        matWorld = g_matWorld007;
        colMaterialDiffuse = g_colMaterialDiffuse007;
        offsetU  = g_offset_u007;
        offsetV  = g_offset_v007;
    } else if (index == 7) {
        matWorld = g_matWorld008;
        colMaterialDiffuse = g_colMaterialDiffuse008;
        offsetU  = g_offset_u008;
        offsetV  = g_offset_v008;
    } else if (index == 8) {
        matWorld = g_matWorld009;
        colMaterialDiffuse = g_colMaterialDiffuse009;
        offsetU  = g_offset_u009;
        offsetV  = g_offset_v009;
    } else if (index == 9) {
        matWorld = g_matWorld010;
        colMaterialDiffuse = g_colMaterialDiffuse010;
        offsetU  = g_offset_u010;
        offsetV  = g_offset_v010;
    } else if (index == 10) {
        matWorld = g_matWorld011;
        colMaterialDiffuse = g_colMaterialDiffuse011;
        offsetU  = g_offset_u011;
        offsetV  = g_offset_v011;
    } else if (index == 11) {
        matWorld = g_matWorld012;
        colMaterialDiffuse = g_colMaterialDiffuse012;
        offsetU  = g_offset_u012;
        offsetV  = g_offset_v012;
    } else if (index == 12) {
        matWorld = g_matWorld013;
        colMaterialDiffuse = g_colMaterialDiffuse013;
        offsetU  = g_offset_u013;
        offsetV  = g_offset_v013;
    } else if (index == 13) {
        matWorld = g_matWorld014;
        colMaterialDiffuse = g_colMaterialDiffuse014;
        offsetU  = g_offset_u014;
        offsetV  = g_offset_v014;
    } else { //if (index == 14) {
        matWorld = g_matWorld015;
        colMaterialDiffuse = g_colMaterialDiffuse015;
        offsetU  = g_offset_u015;
        offsetV  = g_offset_v015;
    }
//	else {
//		matWorld = g_matWorld016;
//		colMaterialDiffuse = g_colMaterialDiffuse016;
//		offsetU  = g_offset_u016;
//		offsetV  = g_offset_v016;
//	}
    //World*View*�ˉe�ϊ�
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);
    //�@���v�Z
    //out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld)); 	//�@���� World �ϊ����Đ��K��
    //UV�͂��̂܂�
    out_vs.uv.x = prm_uv.x + offsetU;
    out_vs.uv.y = prm_uv.y + offsetV;
    //���_�J���[�v�Z

    //�@���� World �ϊ����Đ��K��
    const float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld));
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
    float refl_power = dot(vecNormal_World, -g_vecLightFrom_World);
    //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g�����A�}�e���A���F ���l�������J���[�쐬�B
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * colMaterialDiffuse;
    //���t�H�O
    out_vs.color.a = colMaterialDiffuse.a;
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
    return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 PS_SpriteMeshSet(
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
    float2 prm_uv	 : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    const float4 colOut = colTex * prm_color * FLUSH_COLOR;
    return colOut;
}

technique SpriteMeshSetTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_SpriteMeshSet();
        PixelShader  = compile PS_VERSION PS_SpriteMeshSet();
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
        VertexShader = compile VS_VERSION VS_SpriteMeshSet();
        PixelShader  = compile PS_VERSION PS_SpriteMeshSet();
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
        VertexShader = compile VS_VERSION VS_SpriteMeshSet();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
