#!/usr/bin/env python3
# Inline one level of project-local #include directives (those resolvable under SRC)
# into FILE, each header at most once; keep system/Boost includes untouched.
import re, sys, os
src, path, seen_path = sys.argv[1], sys.argv[2], sys.argv[3]
seen = set(open(seen_path).read().split()) if os.path.exists(seen_path) else set()
inc = re.compile(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]')
out, changed = [], False
for line in open(path):
    m = inc.match(line)
    if m:
        rel = m.group(1)
        full = os.path.join(src, rel)
        if os.path.isfile(full):
            changed = True
            if rel in seen:
                continue                      # already inlined once; drop duplicate include
            seen.add(rel)
            out.append(f'// ---- begin {rel} ----\n')
            for l in open(full):
                if l.strip().startswith('#pragma once'):
                    continue
                out.append(l)
            out.append(f'// ---- end {rel} ----\n')
            continue
    out.append(line)
open(path, 'w').writelines(out)
open(seen_path, 'w').write('\n'.join(sorted(seen)))
print('changed' if changed else 'unchanged')
