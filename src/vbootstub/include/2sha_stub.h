#include <stddef.h>

/* Stub prototypes */
int vb2_digest_buffer(const uint8_t *buf,
		      uint32_t size,
		      enum vb2_hash_algorithm hash_alg,
		      uint8_t *digest,
		      uint32_t digest_size);

struct vb2_digest_context {
	uint8_t *dontuse;
};

int vb2_digest_extend(struct vb2_digest_context *ctx,
		      void *buf,
		      size_t sz);

int vb2_digest_init(struct vb2_digest_context *ctx,
		    enum vb2_hash_algorithm hash_alg);

int vb2_digest_finalize(struct vb2_digest_context *ctx,
			void *digest,
			size_t digest_sz);
