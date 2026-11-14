/*
 * SPDX-FileCopyrightText: 2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <unistd.h>

// Android 17 turned AOSP libion into stubs, so ion_close() returns -1 without
// closing anything. libsfp_teegw (Samsung secure fingerprint TEE gateway)
// frees its qseecom DMA-BUF shared buffers with ion_close(fd); with the stub
// every TZ session leaks ~5 MB until the qseecom CMA region is exhausted and
// fingerprint auth fails with "BAuthSessionOpen Fail 29".
// Restore the pre-17 behaviour: ion_close() is just close().
extern "C" int ion_close(int fd) {
    int ret = close(fd);
    if (ret < 0) return -errno;
    return ret;
}
