#include "ft_ssl.h"

static const uint32_t k[64] = {
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
		0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
		0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
		0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
		0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
		0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static void sha256_transform_block(sha256_context_t *ctx) {
	uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, w[64];
	
	for (i = 0, j = 0; i < 16; i++, j += 4)
		w[i] = (ctx->data[j] << 24) | (ctx->data[j + 1] << 16) | (ctx->data[j + 2] << 8) | (ctx->data[j + 3]);
	for ( ; i < 64; i++)
		w[i] = SHA256_DELTA1(w[i - 2]) + w[i - 7] + SHA256_DELTA0(w[i - 15]) + w[i - 16];

	a = ctx->hash[0];
	b = ctx->hash[1];
	c = ctx->hash[2];
	d = ctx->hash[3];
	e = ctx->hash[4];
	f = ctx->hash[5];
	g = ctx->hash[6];
	h = ctx->hash[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + SHA256_SIG1(e) + SHA256_CH(e, f, g) + k[i] + w[i];
		t2 = SHA256_SIG0(a) + SHA256_MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	ctx->hash[0] += a;
	ctx->hash[1] += b;
	ctx->hash[2] += c;
	ctx->hash[3] += d;
	ctx->hash[4] += e;
	ctx->hash[5] += f;
	ctx->hash[6] += g;
	ctx->hash[7] += h;
}

static void sha256_reduce_to_one_block(sha256_context_t *ctx, const uchar *data, size_t len) {
	for (size_t i = 0; i < len; i++) {
		ctx->data[ctx->data_len++] = data[i];
		if (ctx->data_len == SHA256_MAX_BLOCK_BYTES) {
			sha256_transform_block(ctx);
			ctx->data_len = 0;
			ctx->bit_len += SHA256_MAX_BLOCK_BITS;
		}
	}
}


static void sha256_transform_last(sha256_context_t *ctx) {
	uint32_t i = ctx->data_len;

	if (i < SHA256_MAX_BYTES_BFR_ADDING_SIZE) {
		ctx->data[i++] = 0x80;
		for (; i < SHA256_MAX_BYTES_BFR_ADDING_SIZE; i++) {
			ctx->data[i] = 0x00;
		}
	} else {
		ctx->data[i++] = 0x80;
		while (i < SHA256_MAX_BLOCK_BYTES)
			ctx->data[i++] = 0x00;
		sha256_transform_block(ctx);
		memset(ctx->data, 0, 56);
	}


	ctx->bit_len += ctx->data_len * 8;
	ctx->data[63] = ctx->bit_len;
	ctx->data[62] = ctx->bit_len >> 8;
	ctx->data[61] = ctx->bit_len >> 16;
	ctx->data[60] = ctx->bit_len >> 24;
	ctx->data[59] = ctx->bit_len >> 32;
	ctx->data[58] = ctx->bit_len >> 40;
	ctx->data[57] = ctx->bit_len >> 48;
	ctx->data[56] = ctx->bit_len >> 56;

	sha256_transform_block(ctx);
}

char *sha256_start(const uchar *data, size_t len) {
	sha256_context_t	ctx;
	char				*res;
	size_t				res_idx;

	ctx.bit_len = 0;
	ctx.data_len = 0;

	ctx.hash[0] = 0x6a09e667;
	ctx.hash[1] = 0xbb67ae85;
	ctx.hash[2] = 0x3c6ef372;
	ctx.hash[3] = 0xa54ff53a;
	ctx.hash[4] = 0x510e527f;
	ctx.hash[5] = 0x9b05688c;
	ctx.hash[6] = 0x1f83d9ab;
	ctx.hash[7] = 0x5be0cd19;

	sha256_reduce_to_one_block(&ctx, data, len);
	sha256_transform_last(&ctx);

	res_idx = 0;
	res = (char *) malloc(SHA256_HASH_SIZE + 1);
	if (!res)
		return (NULL);
	for (size_t i = 0; i < 8; i++) {
		char *converted = ft_convert_base(ctx.hash[i], BASE_HEX_LOWER);
		if (!converted) {
			free(res);
			return NULL;
		}
		size_t conv_len = ft_strlen(converted);
		while (conv_len++ < 8)
			res[res_idx++] = '0';
		ft_strcpy(&res[res_idx], converted);
		res_idx += ft_strlen(converted);
		free(converted);
	}

	return res;
}
