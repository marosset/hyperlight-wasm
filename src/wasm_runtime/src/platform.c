/*
Copyright 2024 The Hyperlight Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>

typedef void (*wasmtime_setjmp_cb_t)(void *, void *);

bool wasmtime_setjmp(const uint8_t **jmp_buf_out,
                     bool (*callback)(uint8_t *, uint8_t *), uint8_t *payload,
                     uint8_t *callee)
{
  jmp_buf buf;

  if (setjmp(buf) != 0) {
    return false;
  }
  *jmp_buf_out = (uint8_t *)&buf;
  return callback(payload, callee);
}

void wasmtime_longjmp(const uint8_t *jmp_buf_ptr) {
  longjmp(*(jmp_buf *)jmp_buf_ptr, 1);
}
