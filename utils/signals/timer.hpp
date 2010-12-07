// Copyright 2010, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// * Neither the name of Google Inc. nor the names of its contributors
//   may be used to endorse or promote products derived from this software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/// \file utils/signals/timer.hpp
/// Provides the signals::timer class.

#if !defined(UTILS_SIGNALS_TIMER_HPP)
#define UTILS_SIGNALS_TIMER_HPP

#include <memory>

#include "utils/noncopyable.hpp"

namespace utils {
namespace signals {


/// Function type for the callback executed when a timer expires.
typedef void (*timer_callback)(void);


/// Represents a time delta to describe deadlines.
/// TODO(jmmv): It may be worth to split this into a separate file and make
/// every field strongly-typed (at least in the constructor) so that it is not
/// easy to swap integers by mistake.
struct timedelta {
    /// The amount of seconds in the time delta.
    unsigned int seconds;

    /// The amount of microseconds in the time delta.
    unsigned long useconds;

    timedelta(void);
    timedelta(const unsigned int, const unsigned long);

    bool operator==(const timedelta&) const;
};


/// A RAII class to program a timer.
class timer : noncopyable {
    struct impl;
    std::auto_ptr< impl > _pimpl;

public:
    timer(const timedelta&, const timer_callback);
    ~timer(void);

    void unprogram(void);
};


} // namespace signals
} // namespace utils

#endif // !defined(UTILS_SIGNALS_TIMER_HPP)