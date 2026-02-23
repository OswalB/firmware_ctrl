import os
import shutil
import re

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
SRC = os.path.join(ROOT, "src")
LIB = os.path.join(ROOT, "lib")
OUT = os.path.join(ROOT, "wokwi")

INCLUDE_RE = re.compile(r'#include\s+[<"]([^">]+)[">]')

def clean_out():
    if os.path.exists(OUT):
        shutil.rmtree(OUT)
    os.makedirs(OUT)

def fix_includes(text):
    def repl(match):
        inc = match.group(1)
        if "/" in inc:
            inc = inc.split("/")[-1]
        return f'#include "{inc}"'
    return INCLUDE_RE.sub(repl, text)

def copy_and_fix(src, dst):
    with open(src, "r", encoding="utf-8") as f:
        content = f.read()
    content = fix_includes(content)
    with open(os.path.join(OUT, dst), "w", encoding="utf-8") as f:
        f.write(content)

def export():
    clean_out()

    # main.cpp -> sketch.ino
    copy_and_fix(os.path.join(SRC, "main.cpp"), "sketch.ino")

    # recorrer lib/*
    for module in os.listdir(LIB):
        module_path = os.path.join(LIB, module)

        include_dir = os.path.join(module_path, "include")
        src_dir = os.path.join(module_path, "src")

        if os.path.isdir(include_dir):
            for f in os.listdir(include_dir):
                if f.endswith(".h"):
                    copy_and_fix(os.path.join(include_dir, f), f)

        if os.path.isdir(src_dir):
            for f in os.listdir(src_dir):
                if f.endswith(".cpp"):
                    copy_and_fix(os.path.join(src_dir, f), f)

    print("✅ Proyecto exportado a /wokwi")

if __name__ == "__main__":
    export()
