/** -1.0 / CONFIG::RENDER_TARGET_BUFFER_WIDTH */
float g_dbd_offset_x;
/** +1.0 / CONFIG::RENDER_TARGET_BUFFER_HEIGHT */
float g_dbd_offset_y;


/**
 * dot by dot çló∂
 */
float4 adjustDotByDot(float4 pos) {
    pos.x += g_dbd_offset_x*pos.w;
    pos.y += g_dbd_offset_y*pos.w;
    return pos;
}
