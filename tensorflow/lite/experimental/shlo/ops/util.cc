/* Copyright 2024 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include "tensorflow/lite/experimental/shlo/ops/util.h"

#include "absl/status/status.h"
#include "tensorflow/lite/experimental/shlo/data_type.h"
#include "tensorflow/lite/experimental/shlo/shape.h"
#include "tensorflow/lite/experimental/shlo/tensor.h"

namespace shlo_ref {

absl::Status Propagate(const Shape& input_shape, Shape& output_shape) {
  if (output_shape.Dimensions().empty()) {
    output_shape = input_shape;
  } else {
    if (output_shape != input_shape) {
      return absl::FailedPreconditionError(
          "The specified output tensor shape is not compatible with the input "
          "shape.");
    }
  }
  return absl::OkStatus();
}

bool IsBoolTensor(const Tensor& tensor) {
  return !tensor.IsQuantized() && IsBool(tensor.StorageType());
}

bool IsSignedIntTensor(const Tensor& tensor) {
  return !tensor.IsQuantized() && IsSignedInteger(tensor.StorageType());
}

bool IsUnsignedIntTensor(const Tensor& tensor) {
  return !tensor.IsQuantized() && IsUnsignedInteger(tensor.StorageType());
}

bool IsIntTensor(const Tensor& tensor) {
  return !tensor.IsQuantized() && IsInteger(tensor.StorageType());
}

bool IsFloatTensor(const Tensor& tensor) {
  return !tensor.IsQuantized() && IsFloat(tensor.StorageType());
}

bool IsQuantizedPerTensorTensor(const Tensor& tensor) {
  return tensor.IsPerTensorQuantized();
}

bool IsQuantizedPerAxisTensor(const Tensor& tensor) {
  return tensor.IsPerAxisQuantized();
}

absl::Status CheckSameBaselineType(CheckCtx ctx, const Tensor& tensor1,
                                   const Tensor& tensor2) {
  if (BaselineType(tensor1.element_type()) !=
      BaselineType(tensor2.element_type())) {
    return absl::FailedPreconditionError(
        "stablehlo." + ctx.op_name +
        ": baseline type constraint is not satisfied.");
  }
  return absl::OkStatus();
}

}  // namespace shlo_ref
