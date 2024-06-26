/*
 * Copyright 2023 The OpenXLA Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef XLA_PYTHON_IFRT_PROXY_CLIENT_MEMORY_H_
#define XLA_PYTHON_IFRT_PROXY_CLIENT_MEMORY_H_

#include <string>
#include <utility>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "xla/pjrt/pjrt_client.h"
#include "xla/python/ifrt/device.h"
#include "xla/python/ifrt/memory.h"

namespace xla {
namespace ifrt {
namespace proxy {

class Memory : public xla::ifrt::Memory {
 public:
  Memory(int id, std::string memory_space_kind, std::string debug_string,
         std::string to_string)
      : id_(id),
        memory_space_kind_(std::move(memory_space_kind)),
        debug_string_(std::move(debug_string)),
        to_string_(std::move(to_string)) {}

  // Not copyable or movable: IFRT expects `string_view` from
  // `memory_space_kind()` to be stable throughout the client's lifetime.
  Memory(const Memory& other) = delete;
  Memory& operator=(const Memory& other) = delete;

  PjRtClient* client() const override { return nullptr; }

  absl::Span<xla::ifrt::Device* const> devices() const override {
    return devices_;
  }

  int id() const override { return id_; }

  absl::string_view memory_space_kind() const override {
    return memory_space_kind_;
  }

  absl::string_view DebugString() const override { return debug_string_; }

  absl::string_view ToString() const override { return to_string_; }

 private:
  friend class Client;  // For `devices_` initialization.

  int id_;
  std::vector<xla::ifrt::Device*> devices_;
  std::string memory_space_kind_;
  std::string debug_string_;
  std::string to_string_;
};

}  // namespace proxy
}  // namespace ifrt
}  // namespace xla

#endif  // XLA_PYTHON_IFRT_PROXY_CLIENT_MEMORY_H_
