import os

print("test")
def describe_tree(root="src"):
    lines = []

    for root_dir, dirs, files in os.walk(root):
        level = root_dir.replace(root, "").count(os.sep)
        indent = "│   " * level
        folder_name = os.path.basename(root_dir)

        lines.append(f"{indent}├── {folder_name}/")

        sub_indent = "│   " * (level + 1)
        for f in files:
            lines.append(f"{sub_indent}├── {f}")

    return "\n".join(lines)


if __name__ == "__main__":
    output = describe_tree("src")

    print("\nPROJECT STRUCTURE\n")
    print(output)

    with open("project_structure.txt", "w", encoding="utf-8") as f:
        f.write(output)

    print("\nSaved to project_structure.txt")
    input("\nPress ENTER to exit...")