#!/usr/bin/env python3
import argparse
import hashlib
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

SOURCE_EXTS = {".cpp", ".cc", ".cxx", ".hpp", ".h", ".hh", ".hxx"}
CPP_EXTS = {".cpp", ".cc", ".cxx"}
HEADER_EXTS = {".hpp", ".h", ".hh", ".hxx"}

EXCLUDED_DIR_NAMES = {
    ".git",
    "build",
    "cmake-build-debug",
    "cmake-build-release",
    "third_party",
    "assets",
}

EXCLUDED_PATH_PARTS = {
    "Framework",
}

ALLOWED_MAGIC_NUMBERS = {"0", "1", "-1"}

CHECKS = [
    "warning-log",
    "manual-memory",
    "file-structure",
    "duplicate-code",
    "enum-magic",
    "utils-enums",
    "visibility",
    "no-type-checks",
    "static-const-virtual",
    "inheritance-design",
    "initializer-list",
    "casts",
    "globals-scope",
]


def rel(path: Path | str) -> str:
    path = Path(path)
    try:
        return path.relative_to(ROOT).as_posix()
    except ValueError:
        return path.as_posix()


class Reporter:
    def __init__(self) -> None:
        self.errors = 0
        self.warnings = 0

    def error(self, path: Path | str, line: int, msg: str) -> None:
        self.errors += 1
        print(f"::error file={rel(path)},line={line}::{msg}")

    def warn(self, path: Path | str, line: int, msg: str) -> None:
        self.warnings += 1
        print(f"::warning file={rel(path)},line={line}::{msg}")


def is_excluded_path(path: Path) -> bool:
    parts = set(path.parts)
    if parts & EXCLUDED_DIR_NAMES:
        return True
    if parts & EXCLUDED_PATH_PARTS:
        return True
    return False


def is_user_source(path: Path) -> bool:
    if path.suffix not in SOURCE_EXTS:
        return False
    if is_excluded_path(path):
        return False
    r = rel(path)
    return r.startswith("src/") or r.startswith("include/")


def source_files() -> list[Path]:
    files: list[Path] = []
    for base in [ROOT / "src", ROOT / "include"]:
        if not base.exists():
            continue
        for path in base.rglob("*"):
            if path.is_file() and is_user_source(path):
                files.append(path)
    return sorted(files)


def read_raw_lines(path: Path) -> list[str]:
    try:
        return path.read_text(encoding="utf-8", errors="ignore").splitlines()
    except Exception:
        return []


def strip_strings(line: str) -> str:
    line = re.sub(r'"(?:\\.|[^"\\])*"', '""', line)
    line = re.sub(r"'(?:\\.|[^'\\])*'", "''", line)
    return line


def strip_line_comment(line: str) -> str:
    return line.split("//", 1)[0]


def stripped_lines(path: Path) -> list[str]:
    raw = read_raw_lines(path)
    result: list[str] = []
    in_block = False

    for line in raw:
        out = ""
        i = 0
        while i < len(line):
            if in_block:
                end = line.find("*/", i)
                if end == -1:
                    i = len(line)
                else:
                    in_block = False
                    i = end + 2
            else:
                block = line.find("/*", i)
                slash = line.find("//", i)

                if slash != -1 and (block == -1 or slash < block):
                    out += line[i:slash]
                    break

                if block == -1:
                    out += line[i:]
                    break

                out += line[i:block]
                in_block = True
                i = block + 2

        result.append(strip_strings(out))
    return result


def suppressed(raw_line: str, check_name: str) -> bool:
    return "NOLINT" in raw_line and (check_name in raw_line or "hw8" in raw_line)


def check_warning_log(rep: Reporter, build_log: str) -> None:
    log_path = ROOT / build_log
    if not log_path.exists():
        rep.error(build_log, 1, "L01: build log not found; run CMake build and capture build.log")
        return

    for i, line in enumerate(log_path.read_text(errors="ignore").splitlines(), 1):
        lower = line.lower()
        has_warning = "warning:" in lower or re.search(r"\bwarning\s+C\d+", line)
        if not has_warning:
            continue

        normalized = line.replace("\\", "/")
        is_own = ("/src/" in normalized or "/include/" in normalized or "src/" in normalized or "include/" in normalized)
        is_framework = "/Framework/" in normalized or "third_party/" in normalized

        if is_own and not is_framework:
            rep.error(build_log, i, "L01: warning from your own code: " + line.strip())


def check_manual_memory(rep: Reporter) -> None:
    patterns = [
        (r"(?<!operator\s)\bnew\s+", "manual new; use std::make_shared/std::make_unique or containers"),
        (r"(?<!operator\s)\bdelete\s+", "manual delete; object lifetime should be owned by smart pointers/containers"),
        (r"\bmalloc\s*\(", "malloc is manual memory management; use containers/smart pointers"),
        (r"\bfree\s*\(", "free is manual memory management; use containers/smart pointers"),
        (r"std::shared_ptr\s*<[^>]+>\s*[\(\{]\s*this\s*[\)\}]", "do not create shared_ptr<T>(this); use shared_from_this only when safe"),
    ]

    for path in source_files():
        raw = read_raw_lines(path)
        code = stripped_lines(path)
        for i, line in enumerate(code, 1):
            if suppressed(raw[i - 1], "manual-memory"):
                continue
            for pattern, msg in patterns:
                if re.search(pattern, line):
                    rep.error(path, i, f"L02: {msg}")


def check_file_structure(rep: Reporter) -> None:
    user_cpp = [p for p in source_files() if p.suffix in CPP_EXTS]
    user_hpp = [p for p in source_files() if p.suffix in HEADER_EXTS]

    if not user_cpp:
        rep.error("src", 1, "L03: no user .cpp file found outside Framework/third_party")
    if not user_hpp:
        rep.error("include", 1, "L03: no user .hpp/.h file found outside Framework/third_party")

    src_root = ROOT / "src"
    root_cmake = ROOT / "CMakeLists.txt"
    root_cmake_text = root_cmake.read_text(encoding="utf-8", errors="ignore") if root_cmake.exists() else ""

    source_dirs = sorted({p.parent for p in user_cpp if p.parent != src_root})
    for directory in source_dirs:
        cmake_file = directory / "CMakeLists.txt"
        if not cmake_file.exists():
            rep.error(cmake_file, 1, "L03: each source subdirectory containing .cpp files should have CMakeLists.txt")
            continue

        text = cmake_file.read_text(encoding="utf-8", errors="ignore")
        if "add_library" not in text:
            rep.error(cmake_file, 1, "L03: subdirectory CMakeLists.txt should usually use add_library(...)")

        top = directory.relative_to(src_root).parts[0]
        if root_cmake.exists() and not re.search(rf"add_subdirectory\s*\(\s*{re.escape(top)}\s*\)", root_cmake_text):
            rep.warn(root_cmake, 1, f"L03: root CMakeLists.txt may be missing add_subdirectory({top})")


def significant_line(line: str) -> str:
    s = re.sub(r"\s+", "", line)
    if len(s) < 8:
        return ""
    if s in {"{", "}", "};", "public:", "private:", "protected:"}:
        return ""
    if s.startswith("#include") or s.startswith("usingnamespace"):
        return ""
    if s.startswith("assert("):
        return ""
    return s


def check_duplicate_code(rep: Reporter) -> None:
    window = 8
    seen: dict[str, tuple[Path, int]] = {}
    reported = 0

    for path in source_files():
        lines = stripped_lines(path)
        sigs: list[tuple[int, str]] = []
        for i, line in enumerate(lines, 1):
            s = significant_line(line)
            if s:
                sigs.append((i, s))

        for idx in range(0, max(0, len(sigs) - window + 1)):
            block = tuple(s for _, s in sigs[idx:idx + window])
            key = hashlib.sha1("\n".join(block).encode()).hexdigest()
            cur_line = sigs[idx][0]

            if key in seen:
                old_path, old_line = seen[key]
                if old_path != path or abs(old_line - cur_line) > window:
                    rep.error(path, cur_line, f"L04: duplicated code block also appears at {rel(old_path)}:{old_line}; consider moving common logic into a base class/helper")
                    reported += 1
                    if reported >= 20:
                        return
            else:
                seen[key] = (path, cur_line)


def check_enum_magic(rep: Reporter) -> None:
    numeric = re.compile(r"(?<![\w.])[-+]?\d+(?:\.\d+)?f?(?![\w.])")

    for path in source_files():
        raw = read_raw_lines(path)
        lines = stripped_lines(path)

        for i, line in enumerate(lines, 1):
            raw_line = raw[i - 1] if i - 1 < len(raw) else ""

            if suppressed(raw_line, "enum-magic"):
                continue

            if re.search(r"\benum\s+(?!class\b|struct\b)", line):
                rep.error(path, i, "L05: use scoped enum, i.e. enum class, instead of plain enum")

            skip_magic = any(token in line for token in [
                "constexpr",
                "const ",
                "enum ",
                "#",
                "case ",
                "static_assert",
                "return 0",
            ])

            if skip_magic:
                continue

            for match in numeric.finditer(line):
                value = match.group(0).rstrip("f")
                if value in ALLOWED_MAGIC_NUMBERS:
                    continue
                rep.error(path, i, f"L05: possible magic number `{match.group(0)}`; define a named constexpr constant or use utils.hpp enum/constants")


def check_utils_enums(rep: Reporter) -> None:
    patterns = [
        (r"\bChangeImage\s*\(\s*\d+", "ChangeImage should use ImageID::XXX, not raw number"),
        (r"\bPlayAnimation\s*\(\s*\d+", "PlayAnimation should use AnimID::XXX, not raw number"),
        (r"\bImageID\s*[\(\{]\s*\d+", "do not construct ImageID from raw number"),
        (r"\bAnimID\s*[\(\{]\s*\d+", "do not construct AnimID from raw number"),
        (r"\bLayerID\s*[\(\{]\s*\d+", "do not construct LayerID from raw number"),
        (r"static_cast\s*<\s*(ImageID|AnimID|LayerID)\s*>\s*\(\s*\d+", "do not static_cast raw number into framework enum"),
        (r"\b(ImageID|AnimID|LayerID)\s+\w+\s*=\s*\d+", "enum variable should be initialized from utils.hpp enum value"),
    ]

    for path in source_files():
        raw = read_raw_lines(path)
        lines = stripped_lines(path)
        for i, line in enumerate(lines, 1):
            if suppressed(raw[i - 1], "utils-enums"):
                continue
            for pattern, msg in patterns:
                if re.search(pattern, line):
                    rep.error(path, i, f"L06: {msg}")


def looks_like_public_data_member(line: str) -> bool:
    s = line.strip()
    if not s.endswith(";"):
        return False
    if "(" in s or ")" in s:
        return False
    if s in {"public:", "private:", "protected:", "};"}:
        return False
    banned_starts = (
        "using ",
        "typedef ",
        "friend ",
        "enum ",
        "class ",
        "struct ",
        "static_assert",
    )
    if s.startswith(banned_starts):
        return False
    allowed_public_constants = (
        "static constexpr ",
        "static const ",
        "inline static constexpr ",
        "inline static const ",
    )
    if s.startswith(allowed_public_constants):
        return False
    return True


def check_visibility(rep: Reporter) -> None:
    for path in source_files():
        raw = read_raw_lines(path)
        lines = stripped_lines(path)

        in_class = False
        class_name = ""
        access = "private"
        brace_depth = 0
        class_kind = "class"

        for i, line in enumerate(lines, 1):
            raw_line = raw[i - 1] if i - 1 < len(raw) else ""

            start = re.search(r"\b(class|struct)\s+(\w+)[^{;]*\{", line)
            if not in_class and start:
                in_class = True
                class_kind = start.group(1)
                class_name = start.group(2)
                access = "private" if class_kind == "class" else "public"
                brace_depth = line.count("{") - line.count("}")
                continue

            if not in_class:
                continue

            label = re.match(r"\s*(public|private|protected)\s*:\s*$", line)
            if label:
                access = label.group(1)

            if suppressed(raw_line, "visibility"):
                brace_depth += line.count("{") - line.count("}")
                if brace_depth <= 0:
                    in_class = False
                continue

            if access == "public" and looks_like_public_data_member(line):
                rep.error(path, i, f"L07: public data member in {class_name}; make it private unless this is a deliberately simple aggregate")
            elif access == "protected" and looks_like_public_data_member(line):
                rep.warn(path, i, f"L07: protected data member in {class_name}; avoid protected data unless subclass access is truly necessary")

            brace_depth += line.count("{") - line.count("}")
            if brace_depth <= 0:
                in_class = False


def check_no_type_checks(rep: Reporter) -> None:
    patterns = [
        (r"\bdynamic_cast\s*<", "do not use dynamic_cast to identify concrete object type"),
        (r"\btypeid\s*\(", "do not use typeid to identify concrete object type"),
        (r"\bGetImageID\s*\(", "do not expose/use ImageID to identify object type"),
        (r"\bimageID\b.*==|==.*\bimageID\b", "do not compare imageID to identify object type"),
        (r"\bImageID::\w+.*==|==.*\bImageID::\w+", "do not compare ImageID to identify concrete type"),
        (r"\bGetCurrentAnimation\s*\(\s*\).*==|==.*\bGetCurrentAnimation\s*\(", "animation ID should not be used as concrete type check"),
    ]

    for path in source_files():
        raw = read_raw_lines(path)
        lines = stripped_lines(path)
        for i, line in enumerate(lines, 1):
            if suppressed(raw[i - 1], "no-type-checks"):
                continue
            for pattern, msg in patterns:
                if re.search(pattern, line):
                    rep.error(path, i, f"L08: {msg}; prefer virtual functions, broad category enum, or polymorphic behavior")


def check_static_const_virtual(rep: Reporter, clang_tidy_log: str) -> None:
    log_path = ROOT / clang_tidy_log
    if log_path.exists():
        for i, line in enumerate(log_path.read_text(errors="ignore").splitlines(), 1):
            lower = line.lower()
            useful = (
                "convert-member-functions-to-static" in lower
                or "make-member-function-const" in lower
                or "modernize-use-override" in lower
            )
            if useful and "framework" not in lower and "third_party" not in lower:
                rep.error(clang_tidy_log, i, "L09 clang-tidy: " + line.strip())

    getter_like = re.compile(
        r"\b(?:bool|int|double|float|size_t|std::size_t|std::string|[A-Z]\w+(?:::\w+)?)\s+"
        r"(?:Get|Is|Has|Can|Should)\w*\s*\([^)]*\)\s*(?:override\s*)?[;{]"
    )

    for path in source_files():
        raw = read_raw_lines(path)
        lines = stripped_lines(path)
        for i, line in enumerate(lines, 1):
            if suppressed(raw[i - 1], "static-const-virtual"):
                continue
            if getter_like.search(line):
                if " const" not in line and "static " not in line:
                    rep.error(path, i, "L09: getter/query-like member function probably should be const")


def check_inheritance_design(rep: Reporter) -> None:
    bad_pairs = {
        ("Repeater", "Peashooter"): "Repeater should usually share a Shooter base with Peashooter, not inherit from Peashooter",
        ("DoublePeaShooter", "Peashooter"): "double shooter should usually share a Shooter base with Peashooter",
        ("DoubleShooter", "Peashooter"): "double shooter should usually share a Shooter base with Peashooter",
    }

    suspicious_specific_bases = {
        "RegularZombie": "special zombies should usually inherit from Zombie base, not RegularZombie, unless you can justify it",
        "Sunflower": "other plants should usually inherit from Plant base, not Sunflower",
        "Peashooter": "other shooters should usually inherit from Shooter base, not Peashooter",
    }

    for path in source_files():
        raw = read_raw_lines(path)
        lines = stripped_lines(path)

        for i, line in enumerate(lines, 1):
            if suppressed(raw[i - 1], "inheritance-design"):
                continue

            m = re.search(r"\bclass\s+(\w+)\s*:\s*public\s+(\w+)", line)
            if not m:
                continue

            child, base = m.group(1), m.group(2)

            if (child, base) in bad_pairs:
                rep.error(path, i, f"L10: {bad_pairs[(child, base)]}")

            if base in suspicious_specific_bases and child != base:
                if child not in {"RegularZombie"}:
                    rep.warn(path, i, f"L10: suspicious inheritance: {child} : {base}; {suspicious_specific_bases[base]}")


def collect_class_names() -> set[str]:
    names: set[str] = set()
    for path in source_files():
        for line in stripped_lines(path):
            m = re.search(r"\b(class|struct)\s+(\w+)\b", line)
            if m:
                names.add(m.group(2))
    return names


def check_initializer_list(rep: Reporter, clang_tidy_log: str) -> None:
    log_path = ROOT / clang_tidy_log
    if log_path.exists():
        for i, line in enumerate(log_path.read_text(errors="ignore").splitlines(), 1):
            lower = line.lower()
            if "pro-type-member-init" in lower and "framework" not in lower and "third_party" not in lower:
                rep.error(clang_tidy_log, i, "L11 clang-tidy: " + line.strip())

    class_names = collect_class_names()

    for path in source_files():
        raw = read_raw_lines(path)
        lines = stripped_lines(path)

        for i, line in enumerate(lines, 1):
            if suppressed(raw[i - 1], "initializer-list"):
                continue

            m = re.search(r"(?:\b(\w+)::)?\b(\w+)\s*\([^;]*\)\s*(?::[^{]+)?\{", line)
            if not m:
                continue

            ctor_name = m.group(2)
            if ctor_name not in class_names:
                continue

            has_init_list = ":" in line.split("{", 1)[0]
            if has_init_list:
                continue

            body_preview = "\n".join(lines[i:i + 15])
            if re.search(r"\bm_\w+\s*=", body_preview):
                rep.error(path, i, f"L11: constructor `{ctor_name}` assigns members in body; prefer constructor initializer list")


def check_casts(rep: Reporter) -> None:
    c_style_cast = re.compile(
        r"\(\s*(?:"
        r"int|double|float|bool|char|long|short|unsigned|signed|size_t|std::size_t|"
        r"[A-Z]\w+(?:::\w+)?\s*\*?|[A-Z]\w+(?:::\w+)?\s*&?"
        r")\s*\)\s*[\w\(]"
    )

    for path in source_files():
        raw = read_raw_lines(path)
        lines = stripped_lines(path)
        for i, line in enumerate(lines, 1):
            if suppressed(raw[i - 1], "casts"):
                continue

            if c_style_cast.search(line):
                rep.error(path, i, "L12: C-style cast detected; use static_cast/const_cast/reinterpret_cast only when truly necessary")

            if "dynamic_cast" in line:
                rep.error(path, i, "L12/L08: dynamic_cast is also a concrete type check; avoid it in this project")


def check_globals_scope(rep: Reporter, cppcheck_log: str) -> None:
    for path in source_files():
        raw = read_raw_lines(path)
        lines = stripped_lines(path)
        brace_depth = 0

        for i, line in enumerate(lines, 1):
            raw_line = raw[i - 1] if i - 1 < len(raw) else ""

            stripped = line.strip()
            if not stripped:
                continue

            if brace_depth == 0:
                if suppressed(raw_line, "globals-scope"):
                    pass
                elif looks_like_global_variable(stripped):
                    rep.error(path, i, "L13: possible non-const global variable; prefer member variables, local variables, or constexpr constants")

            brace_depth += line.count("{") - line.count("}")

    log_path = ROOT / cppcheck_log
    if log_path.exists():
        for i, line in enumerate(log_path.read_text(errors="ignore").splitlines(), 1):
            lower = line.lower()
            if "variablescope" in lower and "framework" not in lower and "third_party" not in lower:
                rep.error(cppcheck_log, i, "L13 cppcheck: variable can probably be declared closer to first use: " + line.strip())


def looks_like_global_variable(line: str) -> bool:
    if not line.endswith(";"):
        return False
    if "(" in line or ")" in line:
        return False

    skip_starts = (
        "#",
        "using ",
        "typedef ",
        "class ",
        "struct ",
        "enum ",
        "namespace ",
        "extern ",
        "static_assert",
        "template ",
    )
    if line.startswith(skip_starts):
        return False

    allowed_const = (
        "const ",
        "constexpr ",
        "static const ",
        "static constexpr ",
        "inline constexpr ",
        "inline static constexpr ",
        "inline const ",
    )
    if line.startswith(allowed_const):
        return False

    return bool(re.search(r"\b[A-Za-z_]\w*(?:::\w+)?(?:<[^;]+>)?\s+[*&]?\s*[A-Za-z_]\w*\s*(?:=|\{|;)", line))


def run_check(name: str, args: argparse.Namespace, rep: Reporter) -> None:
    if name == "warning-log":
        check_warning_log(rep, args.build_log)
    elif name == "manual-memory":
        check_manual_memory(rep)
    elif name == "file-structure":
        check_file_structure(rep)
    elif name == "duplicate-code":
        check_duplicate_code(rep)
    elif name == "enum-magic":
        check_enum_magic(rep)
    elif name == "utils-enums":
        check_utils_enums(rep)
    elif name == "visibility":
        check_visibility(rep)
    elif name == "no-type-checks":
        check_no_type_checks(rep)
    elif name == "static-const-virtual":
        check_static_const_virtual(rep, args.clang_tidy_log)
    elif name == "inheritance-design":
        check_inheritance_design(rep)
    elif name == "initializer-list":
        check_initializer_list(rep, args.clang_tidy_log)
    elif name == "casts":
        check_casts(rep)
    elif name == "globals-scope":
        check_globals_scope(rep, args.cppcheck_log)
    else:
        raise ValueError(f"unknown check: {name}")


def main() -> int:
    parser = argparse.ArgumentParser(description="CS100 HW8 code quality linter")
    parser.add_argument("--check", choices=CHECKS)
    parser.add_argument("--all", action="store_true")
    parser.add_argument("--build-log", default="build.log")
    parser.add_argument("--clang-tidy-log", default="clang_tidy.log")
    parser.add_argument("--cppcheck-log", default="cppcheck.log")
    args = parser.parse_args()

    if not args.all and not args.check:
        parser.error("use --all or --check CHECK_NAME")

    rep = Reporter()

    selected = CHECKS if args.all else [args.check]
    for name in selected:
        run_check(name, args, rep)

    print(f"HW8 lint finished: {rep.errors} error(s), {rep.warnings} warning(s).")
    return 1 if rep.errors else 0


if __name__ == "__main__":
    sys.exit(main())