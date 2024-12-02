/*
 * Copyright (C) 2024 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_LIBARTBASE_BASE_PIDFD_H_
#define ART_LIBARTBASE_BASE_PIDFD_H_

#include <cstdint>
#include <cstdio>

#include "android-base/unique_fd.h"

#ifdef __BIONIC__
#include <sys/pidfd.h>
#endif

namespace art {

[[maybe_unused]] static android::base::unique_fd PidfdOpen(pid_t pid, uint32_t flags) {
#ifdef __BIONIC__
  return android::base::unique_fd(pidfd_open(pid, flags));
#else
  // There is no glibc wrapper for pidfd_open.
#ifndef SYS_pidfd_open
  constexpr int SYS_pidfd_open = 434;
#endif
  return android::base::unique_fd(syscall(SYS_pidfd_open, pid, flags));
#endif
}

}  // namespace art

#endif  // ART_LIBARTBASE_BASE_PIDFD_H_