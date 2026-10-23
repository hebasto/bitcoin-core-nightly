# Cross toolchain for Windows: GCC 15 with mingw-w64 14.0.0 (UCRT, posix threads).
#
# Usage: nix-shell windows-gcc-mingw/gcc15-mingw14.nix
let
  pkgs = import (fetchTarball "https://channels.nixos.org/nixos-unstable/nixexprs.tar.xz") {
    crossSystem = {
      config = "x86_64-w64-mingw32";
      libc = "ucrt";
    };
    overlays = [
      (final: prev:
        prev.lib.optionalAttrs prev.stdenv.targetPlatform.isMinGW {
          # The cross compiler, and the stage-1 compiler that builds the mingw-w64 runtime.
          gcc = prev.gcc15;
          gccWithoutTargetLibc = prev.gccWithoutTargetLibc.override (old: {
            cc = old.cc.override { majorMinorVersion = "15"; };
          });
          # The posix thread model (winpthreads), as in the common MinGW-w64 toolchains.
          threads = {
            model = "posix";
            package = final.windows.pthreads;
          };
          # The mingw-w64 headers and runtime.
          windows = prev.windows.overrideScope (_: wprev: {
            mingw_w64_headers = wprev.mingw_w64_headers.overrideAttrs (_: rec {
              version = "14.0.0";
              src = final.fetchurl {
                url = "mirror://sourceforge/mingw-w64/mingw-w64-v${version}.tar.bz2";
                hash = "sha256-bq+SHZ65h9OCCzZOqXdbwZuWXsgUkLb91xZSbCjhmVw=";
              };
            });
          });
        })
    ];
  };
in
pkgs.mkShell {
  # The native compiler, for the build tools in depends.
  depsBuildBuild = [ pkgs.buildPackages.stdenv.cc ];
  nativeBuildInputs = [ pkgs.buildPackages.cmake ];
}
