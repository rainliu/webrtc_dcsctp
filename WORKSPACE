load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Bazel Skylib.
http_archive(
    name = "bazel_skylib",
    urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz"],
    sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
)

# Bazel platform rules.
http_archive(
    name = "platforms",
    sha256 = "a879ea428c6d56ab0ec18224f976515948822451473a80d06c2e50af0bbe5121",
    strip_prefix = "platforms-da5541f26b7de1dc8e04c075c99df5351742a4a2",
    urls = ["https://github.com/bazelbuild/platforms/archive/da5541f26b7de1dc8e04c075c99df5351742a4a2.zip"],  # 2022-05-27
)

# Abseil LTS 20220623.1
http_archive(
  name = "com_google_absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/refs/tags/20220623.1.zip"],
  strip_prefix = "abseil-cpp-20220623.1",
  sha256 = "54707f411cb62a26a776dad5fd60829098c181700edcd022ea5c2ca49e9b7ef1",
)

# Local third_party abseil-cpp
#local_repository(
#    name = "com_google_absl",
#    path = "./third_party/abseil-cpp/",
#)

# Google Test
#http_archive(
#  name = "com_google_googletest",
#  urls = ["https://github.com/google/googletest/archive/10b1902d893ea8cc43c69541d70868f91af3646b.zip"],
#  strip_prefix = "googletest-10b1902d893ea8cc43c69541d70868f91af3646b",
#  sha256 = "7c7709af5d0c3c2514674261f9fc321b3f1099a2c57f13d0e56187d193c07e81",
#)
#
## C++ rules for Bazel.
#http_archive(
#    name = "rules_cc",
#    urls = ["https://github.com/bazelbuild/rules_cc/archive/9e10b8a6db775b1ecd358d8ddd3dab379a2c29a5.zip"],
#    strip_prefix = "rules_cc-9e10b8a6db775b1ecd358d8ddd3dab379a2c29a5",
#    sha256 = "954b7a3efc8752da957ae193a13b9133da227bdacf5ceb111f2e11264f7e8c95",
#)

