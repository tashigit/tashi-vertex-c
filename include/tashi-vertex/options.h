#ifndef TASHI_VERTEX_OPTIONS_H
#define TASHI_VERTEX_OPTIONS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tashi-vertex/error.h>

/**
 * @brief Opaque container of options for Tashi Vertex.
 */
typedef struct TVOptions TVOptions;

/**
 * @brief Initializes a default set of options.
 */
extern TVResult tv_options_new(TVOptions** options);

/**
 * @brief Sets the base minimum event interval (in microseconds).
 */
extern TVResult tv_options_set_base_min_event_interval_us(TVOptions* options, uint64_t interval);

/**
 * @brief Enables or disables reporting of gossip events.
 */
extern TVResult tv_options_set_report_gossip_events(TVOptions* options, bool enabled);

/**
 * @brief Selects the shape of the connection overlay.
 *
 * `0` is the full mesh (the default): every node connects to every other.
 * `1` is the experimental grid: connections are bounded to roughly 2*sqrt(N)
 * and events from unconnected creators arrive through standing relays, at
 * the cost of one extra hop. Any other value is rejected with
 * `TV_ERROR_ARGUMENT`.
 */
extern TVResult tv_options_set_topology(TVOptions* options, uint8_t topology);

/**
 * @brief Sets the number of seconds a creator can fall behind before being kicked.
 *
 * If a creator falls behind for this many seconds or more, we will vote to kick them.
 *
 * If a negative value is passed for `seconds`, we will never vote to kick.
 */
extern TVResult tv_options_set_fallen_behind_kick_s(TVOptions* options, int64_t kick);

/**
 * @brief Sets the heartbeat interval (in microseconds).
 *
 * When there is no data to finalize, we create empty events at this interval to keep the session
 * alive.
 *
 * Defaults to 500 milliseconds.
 */
extern TVResult tv_options_set_heartbeat_us(TVOptions* options, uint64_t heartbeat);

/**
 * @brief Sets the target acknowledgment latency (in milliseconds).
 *
 * As throughput across the session increases, the ack latency increases.
 * When the ack latency rises above this threshold, we vote that throughput
 * across the session should not increase further.
 *
 * If this threshold is lower than our uncongested ping, then we'll erroneously always
 * vote to restrict throughput.
 *
 * Defaults to 400 ms
 */
extern TVResult tv_options_set_target_ack_latency_ms(TVOptions* options, uint32_t latency);

/**
 * @brief Sets the maximum acknowledgment latency (in milliseconds).
 *
 * If ack latency rises above this threshold, we vote to gradually reduce throughput
 * across the session to bring it down.
 *
 * Defaults to 600 ms.
 */
extern TVResult tv_options_set_max_ack_latency_ms(TVOptions* options, uint32_t latency);

/**
 * @brief Sets the throttle acknowledgment latency (in milliseconds).
 *
 * If ack latency rises above this threshold, we vote to drastically restrict throughput
 * across the session as an emergency measure.
 *
 * Defaults to 900 ms.
 */
extern TVResult tv_options_set_throttle_ack_latency_ms(TVOptions* options, uint32_t latency);

/**
 * @brief Sets the reset acknowledgment latency (in milliseconds).
 *
 * If ack latency rises above this threshold, we vote to reset throughput restriction to its initial
 * value. This is a last-ditch effort to recover from rising ack latency.
 *
 * Defaults to 2000 ms.
 */
extern TVResult tv_options_set_reset_ack_latency_ms(TVOptions* options, uint32_t latency);

/**
 * @brief Enables or disables dynamic epoch sizing.
 *
 * If `true`, we will vote to resize the epoch depending on network conditions.
 *
 * Defaults to `true`.
 *
 * Depending on network conditions, rounds may pass more quickly or more slowly.
 *
 * Whenever a creator joins or leaves, they'll have to wait out the epoch before the
 * address book change takes effect.
 *
 * A leaving creator doesn't want to wait too long, and a joining creator needs a sufficiently long
 * window in which to join.
 *
 * Creators who don't disable this config option will automatically vote to keep epoch lengths in
 * the range of 1 to 3 seconds.
 */
extern TVResult tv_options_set_enable_dynamic_epoch_size(TVOptions* options, bool enabled);

/**
 * @brief Sets the transaction channel size.
 *
 * The maximum number of transactions to buffer before applying backpressure.
 *
 * Defaults to 32.
 */
extern TVResult tv_options_set_transaction_channel_size(TVOptions* options, size_t size);

/**
 * @brief Sets the maximum number of unacknowledged bytes.
 *
 * How many bytes worth of transactions that haven't yet been seen by
 * the network to pull from the transaction buffer.
 *
 * Defaults to `500 MiB`.
 */
extern TVResult tv_options_set_max_unacknowledged_bytes(TVOptions* options, size_t bytes);

/**
 * @brief Sets the maximum number of blocking verify threads.
 *
 * Above a constant threshold, signature verifications are sent to a blocking thread pool
 * instead of using spare compute time in Tokio's core thread pool.
 *
 * This sets the maximum number of threads to spawn for blocking verifications.
 *
 * It cannot be zero or else events that grow larger than the threshold cannot be verified.
 *
 * Defaults to the number of CPU cores available.
 */
extern TVResult tv_options_set_max_blocking_verify_threads(TVOptions* options, size_t threads);

/**
 * @brief Enables or disables state sharing.
 *
 * Defaults to `false`.
 */
extern TVResult tv_options_set_enable_state_sharing(TVOptions* options, bool enabled);

/**
 * @brief Sets the number of epoch states to cache.
 *
 * When state sharing is enabled, this is the number of epoch states to cache.
 *
 * If a fallen behind creator fails to download an epoch's state in time,
 * they will have to restart the download.
 *
 * Defaults to 3.
 */
extern TVResult tv_options_set_epoch_states_to_cache(TVOptions* options, uint16_t epochs);

/**
 * @brief Enables or disables hole punching.
 *
 * If `true`, we will attempt to use UDP hole punching to establish
 * direct connections between creators behind NATs.
 *
 * Defaults to `true`.
 */
extern TVResult tv_options_set_enable_hole_punching(TVOptions* options, bool enabled);

/**
 * @brief Gets the base minimum event interval (in microseconds).
 */
extern TVResult tv_options_get_base_min_event_interval_us(const TVOptions* options,
                                                          uint64_t* interval);

/**
 * @brief Gets whether reporting of gossip events is enabled.
 */
extern TVResult tv_options_get_report_gossip_events(const TVOptions* options, bool* enabled);

/**
 * @brief Gets the number of seconds a creator can fall behind before being kicked.
 */
extern TVResult tv_options_get_fallen_behind_kick_s(const TVOptions* options, int64_t* seconds);

/**
 * @brief Gets the heartbeat interval (in microseconds).
 */
extern TVResult tv_options_get_heartbeat_us(const TVOptions* options, uint64_t* interval);

/**
 * @brief Gets the target acknowledgment latency (in milliseconds).
 */
extern TVResult tv_options_get_target_ack_latency_ms(const TVOptions* options, uint32_t* latency);

/**
 * @brief Gets the maximum acknowledgment latency (in milliseconds).
 */
extern TVResult tv_options_get_max_ack_latency_ms(const TVOptions* options, uint32_t* latency);

/**
 * @brief Gets the throttle acknowledgment latency (in milliseconds).
 */
extern TVResult tv_options_get_throttle_ack_latency_ms(const TVOptions* options, uint32_t* latency);

/**
 * @brief Gets the reset acknowledgment latency (in milliseconds).
 */
extern TVResult tv_options_get_reset_ack_latency_ms(const TVOptions* options, uint32_t* latency);

/**
 * @brief Gets whether dynamic epoch sizing is enabled.
 */
extern TVResult tv_options_get_enable_dynamic_epoch_size(const TVOptions* options, bool* enabled);

/**
 * @brief Gets the transaction channel size.
 */
extern TVResult tv_options_get_transaction_channel_size(const TVOptions* options, size_t* size);

/**
 * @brief Gets the maximum number of unacknowledged bytes.
 */
extern TVResult tv_options_get_max_unacknowledged_bytes(const TVOptions* options, size_t* bytes);

/**
 * @brief Gets the maximum number of blocking verify threads.
 */
extern TVResult tv_options_get_max_blocking_verify_threads(const TVOptions* options,
                                                           size_t* threads);

/**
 * @brief Gets whether state sharing is enabled.
 */
extern TVResult tv_options_get_enable_state_sharing(const TVOptions* options, bool* enabled);

/**
 * @brief Gets the number of epoch states to cache.
 */
extern TVResult tv_options_get_epoch_states_to_cache(const TVOptions* options, uint16_t* epochs);

/**
 * @brief Gets whether hole punching is enabled.
 */
extern TVResult tv_options_get_enable_hole_punching(const TVOptions* options, bool* enabled);

/**
 * @brief Sets the directory the engine uses to persist consensus events.
 *
 * The path is interpreted as a UTF-8 NUL-terminated string. Pass `NULL` to
 * clear the configured path (engine reverts to in-memory-only behaviour).
 *
 * Persistence requires the engine to have been built with the
 * `persistence-rocksdb` feature; without it, the path is recorded but a
 * warning is logged at engine start and persistence stays disabled.
 */
extern TVResult tv_options_set_storage_path(TVOptions* options, const char* path);

/**
 * @brief Reads the configured storage path into `buf` as a UTF-8 NUL-terminated
 *        string, and writes the byte length (excluding the NUL) to `out_len`.
 *
 * `snprintf`-style calling convention:
 *   - If no path is configured, writes `out_len = 0`. If `buf` is non-null
 *     and `buf_len >= 1`, also writes a single NUL byte.
 *   - If a path is configured and `buf_len > required`, writes
 *     `required + 1` bytes (path + NUL) and `out_len = required`.
 *   - If `buf_len <= required`, writes nothing into `buf` and sets
 *     `out_len = required` so the caller can resize and retry.
 */
extern TVResult tv_options_get_storage_path(const TVOptions* options, char* buf, size_t buf_len,
                                            size_t* out_len);

/**
 * @brief Enables or disables strict (ECDSA) re-verification of persisted events
 *        at engine startup.
 *
 * Defaults to `false`, which trusts that bytes-on-disk were already verified
 * before they were written. Flip on for paranoid builds where on-disk tampering
 * is in the threat model.
 */
extern TVResult tv_options_set_strict_replay_verify(TVOptions* options, bool enabled);

/**
 * @brief Gets the current value of the strict-replay-verify flag.
 */
extern TVResult tv_options_get_strict_replay_verify(const TVOptions* options, bool* enabled);

/**
 * @brief Makes the engine wait for `push_application_state_proof` calls instead
 *        of auto-filling empty state proofs at each epoch transition.
 *
 * Defaults to `false` (auto-fill). Set to `true` only if your application
 * reliably supplies a state proof for every epoch — otherwise consensus
 * will deadlock at the next epoch boundary.
 *
 * This is independent of tv_options_set_enable_state_sharing(): the latter
 * controls whether peers may request our state, this one controls whether
 * the engine itself produces empty state proofs to keep consensus moving.
 */
extern TVResult tv_options_set_wait_for_state_report(TVOptions* options, bool enabled);

/**
 * @brief Gets the current value of the wait-for-state-report flag.
 */
extern TVResult tv_options_get_wait_for_state_report(const TVOptions* options, bool* enabled);

#endif  // TASHI_VERTEX_OPTIONS_H
