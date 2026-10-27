# Conventions for this repository

## Git

- Author commits as `Hennadii Stepanov <32963518+hebasto@users.noreply.github.com>`.
- When asked to act on behalf of someone (e.g. GingerAgent), set both the commit author and the committer to them. Never mention the authorship in the PR description or anywhere else; it follows from the commit metadata.
- Name branches `YYMMDD-topic`, e.g. `261019-gcc-snapshot`, and base them on the current `main`.
- Push to the `YYMMDD-topic` branch and open the PR from it, even when the session assigns a `claude/...` branch; this convention wins over the session default.
- Follow-ups to a merged PR go on a new branch from `main`, never on the merged branch.
- Rewriting history on an unmerged PR branch is fine (`git push --force-with-lease`).
- Fold small follow-ups (review fixes, tweaks on the same lines) into the commit they belong to instead of adding new commits; a new commit is for a distinct change.

## Workflows

- Invoke GNU Make as `gmake`.
- Pin runner labels explicitly (e.g. `ubuntu-26.04`, `ubuntu-26.04-arm`) for jobs that build on the host. Jobs that run in a `container:` or boot a VM via vmactions use `ubuntu-latest`, since the host image does not affect the build.
- Pass `HOST=` to depends only when cross-compiling.
- Nightly workflows chain on `Manager` via `workflow_run` and report to CDash. `clang.yml` is a convenient starting point for a new workflow, but layout may differ per platform; what every CDash job must satisfy is:
  - it builds `bitcoin/bitcoin` master, or a PR merge ref while a platform fix is pending upstream (the clang-cl jobs and bitcoin/bitcoin#31507), and reports the underlying master commit to CDash via `ctest_update()`;
  - its `ctest_update()` uses the shared form, `set(CTEST_UPDATE_COMMAND not-run/git)` plus `CTEST_UPDATE_VERSION_OVERRIDE`, never `CTEST_GIT_COMMAND` or `CTEST_UPDATE_VERSION_ONLY`: a real git would list local modifications and report a patched tree as an update error;
  - it starts the `Nightly` group only when chained from `Manager`, and `Experimental` otherwise;
  - configure, build, and test failures each fail the job (`ctest_test()` needs the `RETURN_VALUE` check);
  - the submit step runs with `if: always()`;
  - unit tests get `DIR_UNIT_TEST_DATA` pointing at `script_assets_test.json` from bitcoin-core/qa-assets;
  - the job name and `CTEST_BUILD_NAME` are identical and name disabled features (`no GUI`, `no IPC`, `no ZMQ`).
- Attach the compiler's `-v` output as a CDash note (`CTEST_NOTES_FILES`) only where the toolchain is not fixed by the build name: compiler snapshots, rolling releases, and compilers from third-party package repositories. For pinned OS releases, CMake's compiler identification in the configure output is enough.
