#ifndef FUZZY_H
#define FUZZY_H

/// These functions allow a programmer to compute the fuzzy hashes
/// (also called the context-triggered piecewise hashes)


#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief fuzzy_digest flag indicating to eliminate sequences of more than
 *        three identical characters
 */
#define FUZZY_FLAG_ELIMSEQ 0x1u
/**
 * @brief fuzzy_digest flag indicating not to truncate the second part to
 *        SPAMSUM_LENGTH/2 characters.
 */
#define FUZZY_FLAG_NOTRUNC 0x2u

struct fuzzy_state;

/**
 * @brief Construct a fuzzy_state object and return it.
 *
 * To use it call fuzzy_update and fuzzy_digest on it. It must be disposed
 * with fuzzy_free.
 * @return the constructed fuzzy_state or NULL on failure
 */
extern /*@only@*/ /*@null@*/ struct fuzzy_state *fuzzy_new(void);

/**
 * @brief Create a copy of a fuzzy_state object and return it.
 *
 * It can be used with fuzzy_update and fuzzy_digest independently of
 * the original. It must be disposed with fuzzy_free like the original
 * has to be cleared in this way.
 * @param state The fuzzy state
 * @return the cloned fuzzy_state or NULL on failure
 */
extern /*@only@*/ /*@null@*/ struct fuzzy_state *fuzzy_clone(const struct fuzzy_state *state);

/**
 * @brief Set fixed length of input
 *
 * If we know the file size to compute fuzzy digest, we can boost
 * computation by restricting range of blocksize.
 * @param state The fuzzy state
 * @param total_fixed_length Total length of the data to generate digest
 * @return 0 on success or -1 on failure
 */
extern int fuzzy_set_total_input_length(struct fuzzy_state *state, uint_least64_t total_fixed_length);

/**
 * @brief Feed the data contained in the given buffer to the state.
 *
 * When an error occurs, the state is undefined. In that case it must not be
 * passed to any function besides fuzzy_free.
 * @param state The fuzzy state
 * @param buffer The data to be hashes
 * @param buffer_size The length of the given buffer
 * @return zero on success, non-zero on error
 */
extern int fuzzy_update(struct fuzzy_state *state,
			const unsigned char *buffer,
			size_t buffer_size);

/**
 * @brief Obtain the fuzzy hash from the state.
 *
 * This operation does not change the state at all. It reports the hash for the
 * concatenation of the data previously fed using fuzzy_update.
 * @param state The fuzzy state
 * @param result Where the fuzzy hash is stored. This variable
 * must be allocated to hold at least FUZZY_MAX_RESULT bytes.
 * @param flags is a bitwise or of FUZZY_FLAG_* macros. The absence of flags is
 * represented by a zero.
 * @return zero on success, non-zero on error
 */
extern int fuzzy_digest(const struct fuzzy_state *state,
			/*@out@*/ char *result,
			unsigned int flags);

/**
 * @brief Dispose a fuzzy state.
 * @param state The fuzzy state to dispose
 */
extern void fuzzy_free(/*@only@*/ struct fuzzy_state *state);

/**
 * @brief Compute the fuzzy hash of a buffer
 *
 * The computes the fuzzy hash of the first buf_len bytes of the buffer.
 * It is the caller's responsibility to append the filename,
 * if any, to result after computation.
 * @param buf The data to be fuzzy hashed
 * @param buf_len The length of the data being hashed
 * @param result Where the fuzzy hash of buf is stored. This variable
 * must be allocated to hold at least FUZZY_MAX_RESULT bytes.
 * @return Returns zero on success, non-zero on error.
 */
extern int fuzzy_hash_buf(const unsigned char *buf,
			  uint32_t buf_len,
			  /*@out@*/ char *result);

/**
 * @brief Compute the fuzzy hash of a file using an open handle
 *
 * Computes the fuzzy hash of the contents of the open file, starting
 * at the beginning of the file. When finished, the file pointer is
 * returned to its original position. If an error occurs, the file
 * pointer's value is undefined.
 * It is the callers's responsibility to append the filename
 * to the result after computation.
 * @param handle Open handle to the file to be hashed
 * @param result Where the fuzzy hash of the file is stored. This
 * variable must be allocated to hold at least FUZZY_MAX_RESULT bytes.
 * @return Returns zero on success, non-zero on error
 */
extern int fuzzy_hash_file(FILE *handle, /*@out@*/ char *result);

/**
 * @brief Compute the fuzzy hash of a stream using an open handle
 *
 * Computes the fuzzy hash of the contents of the open stream, starting at the
 * current file position until reaching EOF. Unlike fuzzy_hash_file the stream
 * is never seeked. If an error occurs, the result as well as the file position
 * are undefined.
 * It is the callers's responsibility to append the filename
 * to the result after computation.
 * @param handle Open handle to the stream to be hashed
 * @param result Where the fuzzy hash of the file is stored. This
 * variable must be allocated to hold at least FUZZY_MAX_RESULT bytes.
 * @return Returns zero on success, non-zero on error
 */
extern int fuzzy_hash_stream(FILE *handle, /*@out@*/ char *result);

/**
 * @brief Compute the fuzzy hash of a file
 *
 * Opens, reads, and hashes the contents of the file 'filename'
 * The result must be allocated to hold FUZZY_MAX_RESULT characters.
 * It is the caller's responsibility to append the filename
 * to the result after computation.
 * @param filename The file to be hashed
 * @param result Where the fuzzy hash of the file is stored. This
 * variable must be allocated to hold at least FUZZY_MAX_RESULT bytes.
 * @return Returns zero on success, non-zero on error.
 */
extern int fuzzy_hash_filename(const char *filename, /*@out@*/ char * result);

/// Computes the match score between two fuzzy hash signatures.
/// @return Returns a value from zero to 100 indicating the
/// match score of the
/// two signatures. A match score of zero indicates the signatures
/// did not match. When an error occurs, such as if one of the
/// inputs is NULL, returns -1.
extern int fuzzy_compare(const char *sig1, const char *sig2);

/** Length of an individual fuzzy hash signature component. */
#define SPAMSUM_LENGTH 64

/** The longest possible length for a fuzzy hash signature
 * (without the filename) */
#define FUZZY_MAX_RESULT (2 * SPAMSUM_LENGTH + 20)

#ifdef __cplusplus
}
#endif

#endif
