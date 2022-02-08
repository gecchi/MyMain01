#include "GgafEffectConst.fxh"
/**
 * GgafLib::DefaultFramedSpriteActor �p�V�F�[�_�[ .
 * �|���S���Ƀe�N�X�`����\��t�����[���X�v���C�g���P�`�悷��W���I�ȃV�F�[�_�[�B
 * ���_�o�b�t�@�t�H�[�}�b�g�́A�ȉ��̂悤�� GgafLib::FramedSpriteModel �ɒ�`����Ă�����̂�O��Ƃ��Ă��܂��B
 * {
 *     float x, y, z;             // ���W(���[�J�����W�n)
 *     float nx, ny, nz;          // �@���x�N�g��(���[�J�����W�n)
 *     DWORD color;               // ���_�J���[�i���ݖ��g�p�j
 *     float tu, tv;              // �e�N�X�`�����W
 * };
 *
 * DWORD FramedSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
 *
 * @author Masatoshi Tsuge
 * @since 2022/2/8
 */

/** ���f����World�ϊ��s�� */
float4x4 g_matWorldRotMv;
/** ���f����View�ϊ��s�� */
float4x4 g_matView;
/** ���f���̎ˉe�ϊ��s�� */
float4x4 g_matProj;
/** ���f���̃}�e���A���F(���C�g�ɂ��g�U���ˎ��̃��f���̐F) */
float4 g_colMaterialDiffuse;

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

/** �e�N�X�`��U���W�����i�p�^�[��No�ɂ�葝���j */
float g_offset_u001;
float g_offset_u002;
float g_offset_u003;
float g_offset_u004;
float g_offset_u005;
float g_offset_u006;
float g_offset_u007;
float g_offset_u008;
float g_offset_u009;
/** �e�N�X�`��V���W�����i�p�^�[��No�ɂ�葝���j */
float g_offset_v001;
float g_offset_v002;
float g_offset_v003;
float g_offset_v004;
float g_offset_v005;
float g_offset_v006;
float g_offset_v007;
float g_offset_v008;
float g_offset_v009;

float g_center_width;
float g_center_height;

float g_frame_width;
float g_frame_height;

float g_frame_sx;
float g_center_sy;

float g_frame_sy;
float g_center_sx;

float g_local_offset_x;
float g_local_offset_y;

float g_alpha;
/** �e�N�X�`���̃T���v���[(s0 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler MyTextureSampler : register(s0);
sampler MyTextureSampler_frame : register(s1);

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
OUT_VS VS_DefaultFramedSprite(
      float4 prm_posModel_Local : POSITION, // ���f���̒��_
      float  prm_index          : PSIZE ,       // ���f���ԍ�
      float2 prm_uv             : TEXCOORD0 // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = (int)prm_index;
    float offsetU; //�e�N�X�`��U���W����
    float offsetV; //�e�N�X�`��V���W����
    float x; //X���W(dxcoord)
    float y; //Y���W(dxcoord)
    float center_flg = 0.0f;
//center_flg = 1.0f; 
    //    ��������������
    //    ���O���P���Q��
    //    ��������������
    //    ���R���S���T��
    //    ��������������
    //    ���U���V���W��
    //    ��������������
    float center_width = g_center_width * g_center_sx;
    float center_height = g_center_height * g_center_sy;
    float frame_width = g_frame_width * g_frame_sx;
    float frame_height = g_frame_height * g_frame_sy;
    if (index < 3) {
        y = (center_height + frame_height) * 0.5;
        prm_posModel_Local.y *= g_frame_sy;
        if (index == 0) {
            x = -(center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u001;
            offsetV = g_offset_v001;
        } else if (index == 1) {
            x = 0;
            prm_posModel_Local.x *= g_center_sx;
            offsetU = g_offset_u002;
            offsetV = g_offset_v002;
        } else { //index == 2
            x = (center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u003;
            offsetV = g_offset_v003;
        }
    } else if (index < 6) {
        y = 0;
        prm_posModel_Local.y *= g_center_sy;
        if (index == 3) {
            x = -(center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u004;
            offsetV = g_offset_v004;
        } else if (index == 4) {
            x = 0;
            center_flg = 1.0f; //���S�p�l���ł��邱�Ƃ̃t���O
            prm_posModel_Local.x *= g_center_sx;
            offsetU = g_offset_u005;
            offsetV = g_offset_v005;
        } else { //index == 5
            x = (center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u006;
            offsetV = g_offset_v006;
        }
    } else { // index >= 6
        y = -(center_height + frame_height) * 0.5;
        prm_posModel_Local.y *= g_frame_sy;
        if (index == 6) {
            x = -(center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u007;
            offsetV = g_offset_v007;
        } else if (index == 7) {
            x = 0;
            prm_posModel_Local.x *= g_center_sx;
            offsetU = g_offset_u008;
            offsetV = g_offset_v008;
        } else { // index == 8
            x = (center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u009;
            offsetV = g_offset_v009;
        }
    }

	prm_posModel_Local.x += x;
	prm_posModel_Local.y += y;
	//World*View*�ˉe�ϊ�
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, g_matWorldRotMv ), g_matView ), g_matProj);  // �o�͂ɐݒ�
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
    out_vs.uv.x = prm_uv.x + offsetU;
    out_vs.uv.y = prm_uv.y + offsetV;

    //�}�e���A���F�Ƃ��Ē��_�J���[�ɐݒ�
    out_vs.color.r = center_flg;  //���S�p�l���ł��鎖�̏��� color.r �i���_�J���[��ׂ��āj���ߍ���
    out_vs.color.a = g_alpha;
    return out_vs;
}

/**
 * GgafLib::DefaultFramedSpriteActor �p�̋^���X�v���C�g�W���s�N�Z���V�F�[�_�[ .
 * @param prm_uv    UV���W
 * @param prm_color �F�i�}�e���A���A���t�H�O�l���ς݁j
 */
float4 PS_DefaultFramedSprite(
    float2 prm_uv    : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    float4 colOut;
    if (prm_color.r == 0.0f) { //color.r�͒��S�p�l�����
        colOut = tex2D( MyTextureSampler_frame, prm_uv);
    } else {
        colOut = tex2D( MyTextureSampler, prm_uv);
    } 
	
    //���߂�F
    //float4 colTex = tex2D( MyTextureSampler, prm_uv); //�e�N�X�`������F�擾
    //�e�N�X�`���F�Ƀ}�e���A���J���[�ƃX�y�L�����[���l��
    colOut = colOut * g_colMaterialDiffuse;
    //Blinker���l��
    if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
    }

    //�}�X�^�[��
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv    : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    float4 colOut;
    if (prm_color.r == 0.0f) { //color.r�͒��S�p�l�����
        colOut = tex2D( MyTextureSampler_frame, prm_uv)* FLUSH_COLOR;
    } else {
        colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
    } 
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

//���e�N�j�b�N�FDefaultFramedSpriteTechnique��
//�y�@�\�z
//FramedSpriteModel�p�W���V�F�[�_�[
//�y�T�v�z
//�|���i�[���X�v���C�g�j��`�悷��B���C�g�Ȃǂ̉A�e�͖����B
technique DefaultFramedSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultFramedSprite();
        PixelShader  = compile PS_VERSION PS_DefaultFramedSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultFramedSprite();
        PixelShader  = compile PS_VERSION PS_DefaultFramedSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultFramedSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
