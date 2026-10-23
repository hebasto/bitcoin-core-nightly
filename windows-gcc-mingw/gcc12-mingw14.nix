# Cross toolchain for Windows: GCC 12 with mingw-w64 14.0.0 (UCRT, posix threads).
#
# Usage: nix-shell windows-gcc-mingw/gcc12-mingw14.nix
let
  # GCC 12 has been removed from current nixpkgs; NixOS 25.05 is the last release
  # that packages it. Its 12.4.0 is bumped to the final 12.5.0 release.
  channel = fetchTarball "https://channels.nixos.org/nixos-25.05/nixexprs.tar.xz";
  nixpkgs = (import channel { }).applyPatches {
    name = "nixpkgs-25.05-gcc-12.5.0";
    src = channel;
    postPatch = ''
      substituteInPlace pkgs/development/compilers/gcc/versions.nix \
        --replace-fail '"12" = "12.4.0";' '"12" = "12.5.0";' \
        --replace-fail '"12.4.0" = "sha256-cE9lJgTMvMsUvavzR4yVEciXiLEss7v/3tNzQZFqkXU=";' \
                       '"12.5.0" = "sha256-cc03PQ8EYV5mxbWxTUnBpMGgjvp7MGJc0kCxG6tAYrM=";'
    '';
  };
  pkgs = import nixpkgs {
    crossSystem = {
      config = "x86_64-w64-mingw32";
      libc = "ucrt";
    };
    overlays = [
      (final: prev:
        prev.lib.optionalAttrs prev.stdenv.targetPlatform.isMinGW {
          # The cross compiler, and the stage-1 compiler that builds the mingw-w64 runtime.
          gcc = prev.gcc12.override (old: {
            cc = old.cc.overrideAttrs (_: {
              # In NixOS 25.05, the winpthreads include directory leaks from here into the
              # host compiler flags, and its pthread.h breaks the build of GCC's own host
              # tools. The target flags carry winpthreads anyway.
              depsTargetTarget = [ ];
            });
          });
          gccWithoutTargetLibc = prev.gccWithoutTargetLibc.override (old: {
            cc = old.cc.override { majorMinorVersion = "12"; };
          });
          # The posix thread model (winpthreads), as in the common MinGW-w64 toolchains.
          threadsCross = {
            model = "posix";
            package = final.targetPackages.windows.mingw_w64_pthreads or final.windows.mingw_w64_pthreads;
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
