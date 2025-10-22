#pragma once
#ifndef TASHI_VERTEX_CONTEXT_H
#define TASHI_VERTEX_CONTEXT_H

/**
 * @brief Opaque context handle for Tashi Vertex.
 *
 * The TVContext represents the main context for Tashi Vertex and must be
 * initialized before using most other functions. This opaque handle encapsulates
 * internal state and configuration required for operations.
 */
typedef struct TVContext TVContext;

/**
 * @brief Initialize a new context for Tashi Vertex.
 */
void tv_context_new(TVContext** ctx);

#endif // TASHI_VERTEX_CONTEXT_H
