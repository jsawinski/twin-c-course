import re, os

def resolve_tex(file, visited=None):
    if visited is None: visited = set()
    file = os.path.abspath(file)
    if file in visited: return ""
    visited.add(file)
    with open(file, 'r', encoding='utf-8') as f:
        content = f.read()
    def replace(m):
        sub = m.group(1).strip()
        if not sub.endswith('.tex'): sub += '.tex'
        sub_path = os.path.join(os.path.dirname(file), sub)
        if os.path.exists(sub_path):
            return resolve_tex(sub_path, visited)
        return m.group(0)  # Fallback
    return re.sub(r'\\(?:input|include)\{([^}]*)\}', replace, content)

# Anwendung:
result = resolve_tex('c-kurs.tex')
with open('all.tex', 'w', encoding='utf-8') as f:
    f.write(result)
