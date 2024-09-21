/** (1.0 / CONFIG::RENDER_TARGET_BUFFER_WIDTH) / 2.0 */
float g_dbd_offset_x;
/** (1.0 / CONFIG::RENDER_TARGET_BUFFER_HEIGHT) / 2.0 */
float g_dbd_offset_y;


/**
 * dot by dot l—¶
 */
float4 adjustDotByDot(float4 pos) {
    float w = pos.w;
    pos /= w; //w‚ÅŠ„‚Á‚Ä -1 ` 1 x -1 ` 1 ‚ÌÀ•WŒn‚É–ß‚·
    pos.x -= g_dbd_offset_x; // -0.5px •ª‚¸‚ç‚·
    pos.y += g_dbd_offset_x; // +0.5px •ª‚¸‚ç‚·
    pos *= w; //w‚ğæ‚¶ ‚à‚Æ‚Ì’l‚É–ß‚·
    return pos;
}
