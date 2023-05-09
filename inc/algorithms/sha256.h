#ifndef INC_42_FT_SSL_MD5_SHA256_H
#define INC_42_FT_SSL_MD5_SHA256_H

#define SHA256_SHR(x, n) ((x) >> (n))
#define SHA256_ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define SHA256_DELTA0(x) (SHA256_ROTR(x,7) ^ SHA256_ROTR(x,18) ^ SHA256_SHR(x, 3))
#define SHA256_DELTA1(x) (SHA256_ROTR(x,17) ^ SHA256_ROTR(x,19) ^ SHA256_SHR(x, 10))
#define SHA256_SIG0(x) (SHA256_ROTR(x,2) ^ SHA256_ROTR(x,13) ^ SHA256_ROTR(x,22))
#define SHA256_SIG1(x) (SHA256_ROTR(x,6) ^ SHA256_ROTR(x,11) ^ SHA256_ROTR(x,25))
#define SHA256_CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define SHA256_MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define SHA256_MAX_BLOCK_BYTES				64
#define SHA256_HASH_SIZE					64
#define SHA256_MAX_BLOCK_BITS				512
#define SHA256_MAX_BYTES_BFR_ADDING_SIZE	56

typedef struct {
	uint32_t		hash[8];
	unsigned char	data[SHA256_MAX_BLOCK_BYTES];
	uint32_t		data_len;
	uint64_t		bit_len;
} sha256_context_t;


char *sha256_start(const unsigned char *data, size_t len);

#endif //INC_42_FT_SSL_MD5_SHA256_H
