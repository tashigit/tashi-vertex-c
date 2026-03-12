#!/usr/bin/env bash
# Package tashi-vertex-c for release.
# Run from the repo root. Expects include/ and lib/ to exist.
#
# On macOS, fixes the dylib install name so it's relocatable (@rpath).
# Without this, the dylib embeds an absolute build path and fails on other machines.

set -e

VERSION="${1:?Usage: $0 <version>}"
OUTPUT="tashi-vertex-${VERSION}.zip"

if [[ ! -d include ]] || [[ ! -d lib ]]; then
  echo "Error: include/ and lib/ must exist. Run from repo root." >&2
  exit 1
fi

# Fix macOS dylib install name before packaging
if [[ "$(uname)" == "Darwin" ]]; then
  DYLIB="lib/libtashi-vertex.dylib"
  if [[ -f "$DYLIB" ]]; then
    install_name_tool -id "@rpath/libtashi-vertex.dylib" "$DYLIB"
    echo "Fixed dylib install name for relocatability"
  fi
fi

# Create release zip (include CMakeLists.txt if present for FetchContent)
CONTENTS=(include lib)
[[ -f CMakeLists.txt ]] && CONTENTS+=(CMakeLists.txt)
zip -r "$OUTPUT" "${CONTENTS[@]}"
echo "Created $OUTPUT"
