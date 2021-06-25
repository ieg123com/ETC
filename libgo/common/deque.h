#pragma once

#include <deque>

namespace co
{
    template <typename T, typename Alloc = std::allocator<T>>
    using Deque = std::deque<T, Alloc>;

    // TODO: 瀹炵幇澶氲涓€鍐欑嚎绋嫔畨鍏ㄧ殑deque

} // namespace co
