#ifndef TASHI_VERTEX_POINTER_H
#define TASHI_VERTEX_POINTER_H

/**
 * @brief Opaque pointer handle for values managed by Tashi Vertex.
 *
 * @see tv_free() to release memory associated with a TVPointer.
 */
typedef struct TVPointer TVPointer;

/**
 * @brief Free memory associated with a Tashi Vertex pointer.
 *
 * Releases the memory and resources associated with a TVPointer instance.
 * After calling this function, the pointer should not be used again.
 *
 * @param ptr Pointer to the TVPointer to free. If NULL, this function does nothing.
 *
 * @note It is safe to call this function with a NULL pointer.
 * @note After freeing, the pointer becomes invalid and should not be dereferenced.
 * @warning Using a TVPointer after it has been freed results in undefined behavior.
 */
void tv_free(void* ptr);

#endif  // TASHI_VERTEX_POINTER_H
