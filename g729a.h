#define  L_FRAME_COMPRESSED 10
#define  L_FRAME            80
extern "C" void va_g729a_init_encoder(encoder_state *state);
extern "C" void va_g729a_encoder(encoder_state *state, short *speech, unsigned char *bitstream);
extern "C" void va_g729a_init_decoder(decoder_state *state);
extern "C" void va_g729a_decoder(decoder_state *state, unsigned char *bitstream, short *synth_short, int bfi);
