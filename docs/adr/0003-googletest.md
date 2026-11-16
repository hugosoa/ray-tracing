# 3. Use GoogleTest for unit tests

## Status

Accepted

## Context

We work in TDD, so we need a C++ unit-test framework to write the tests and report results through CTest.

Alternatives considered:

- **Catch2:** a popular C++ test framework.
- **GoogleTest:** a popular C++ test framework from Google.

## Decision

We will use GoogleTest because it is widely used and well documented.

It is downloaded by CMake's `FetchContent` during the configure step, pinned to version 1.15.2 with a SHA-256 checksum. `gtest_discover_tests` registers each `TEST` with CTest.

## Consequences

- Plenty of documentation, examples and answers are available, which helps a team new to C++.
- Nothing needs installing by hand. CMake fetches the pinned version.
- The first configure needs network access to download GoogleTest.
- GoogleTest is compiled with the project, which makes the first build slower.
- Tests are written with macros (`TEST`, `EXPECT_EQ`, ...), which can produce hard-to-read compiler errors.
- Switching to another framework later would mean rewriting every test file.
