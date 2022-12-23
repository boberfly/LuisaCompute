#include <runtime/dynamic_buffer.h>
#include <core/logging.h>
namespace luisa::compute::detail {
LC_RUNTIME_API void log_diff_elements(size_t src, size_t dst) {
    LUISA_ERROR_WITH_LOCATION(
        "Incompatible buffer views with different element counts (src = {}, dst = {}).",
        src, dst);
}
LC_RUNTIME_API void log_unable_hold(size_t size, size_t dst) {
    LUISA_ERROR_WITH_LOCATION(
        "Unable to hold any element (with size = {}) in buffer view (with size = {}).",
        size, dst);
}
LC_RUNTIME_API void log_subview_overflow(size_t offset, size_t ele_size, size_t size) {
    LUISA_ERROR_WITH_LOCATION(
        "Subview (with offset_elements = {}, size_elements = {}) "
        "overflows buffer view (with size_elements = {}).",
        offset, ele_size, size);
}
LC_RUNTIME_API void log_invalid_align(size_t offset, size_t dst) {
    LUISA_ERROR_WITH_LOCATION(
        "Invalid buffer view offset {} for elements with alignment {}.",
        offset, dst);
}
}// namespace luisa::compute::detail