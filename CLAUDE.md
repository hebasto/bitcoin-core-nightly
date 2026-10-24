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
- Nightly workflows chain on `Manager` via `workflow_run` and report to CDash; see `clang.yml` for the reference layout.
