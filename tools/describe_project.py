import os
from pathlib import Path

print("Script iniciado")
# Carpetas a ignorar
IGNORE_DIRS = {
    ".git",
    ".pio",
    "__pycache__",
    "build",
    ".vscode"
}

# Extensiones relevantes
VALID_EXT = {".h", ".hpp", ".cpp", ".c", ".ino"}

def describe_layer(path_parts):
    """
    Determina la capa conceptual basada en la ruta.
    """
    if "src" in path_parts:
        if "core" in path_parts:
            return "[CORE]"
        if "app" in path_parts:
            return "[APP]"
        return "[SRC]"
    if "lib" in path_parts:
        if "drivers" in path_parts:
            return "[DRIVER]"
        if "services" in path_parts:
            return "[SERVICE]"
        if "event_sources" in path_parts:
            return "[EVENT_SOURCE]"
        return "[LIB]"
    if "config" in path_parts:
        return "[CONFIG]"
    return ""


def build_tree(root_path):
    root = Path(root_path)
    lines = []

    for path in sorted(root.rglob("*")):
        if any(part in IGNORE_DIRS for part in path.parts):
            continue

        if path.is_file() and path.suffix not in VALID_EXT:
            continue

        rel = path.relative_to(root)
        indent = "│   " * (len(rel.parts) - 1)
        name = rel.name

        layer = describe_layer(rel.parts)

        if path.is_dir():
            lines.append(f"{indent}📂 {name}")
        else:
            size_kb = round(path.stat().st_size / 1024, 1)
            lines.append(f"{indent}📄 {name} {layer} ({size_kb} KB)")

    return "\n".join(lines)


if __name__ == "__main__":
    project_root = "."  # Cambia si lo ejecutas desde otro lugar
    print("\nProject Structure:\n")
    print(build_tree(project_root))
