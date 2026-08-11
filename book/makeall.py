#!/usr/bin/env python3
"""
resolve_tex.py

Recursively resolves all \input and \include commands in a LaTeX file.
Writes the complete document to a single file.

Usage:
    python3 resolve_tex.py c-kurs.tex all.tex
"""

import re
import os
import sys
from pathlib import Path

# ============================================================
# Configuration
# ============================================================

# Track visited files to avoid infinite loops
visited_files = set()

# For debugging
VERBOSE = False

# ============================================================
# Core Functions
# ============================================================

def resolve_tex(filepath, depth=0):
    """
    Recursively resolve \input and \include commands in a LaTeX file.
    
    Args:
        filepath: Path to the .tex file
        depth: Current recursion depth (for debugging)
    
    Returns:
        str: The resolved content with all includes expanded
    """
    # Normalize path
    filepath = os.path.abspath(filepath)
    
    # Check for circular includes
    if filepath in visited_files:
        if VERBOSE:
            print(f"{'  ' * depth}⚠️  Circular include detected: {filepath}")
        return f"% [Circular include: {os.path.basename(filepath)}]\n"
    
    # Mark as visited
    visited_files.add(filepath)
    
    # Check if file exists
    if not os.path.exists(filepath):
        if VERBOSE:
            print(f"{'  ' * depth}❌ File not found: {filepath}")
        return f"% [File not found: {os.path.basename(filepath)}]\n"
    
    if VERBOSE:
        print(f"{'  ' * depth}📄 Resolving: {os.path.basename(filepath)}")
    
    # Read file
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
        return f"% [Error reading: {os.path.basename(filepath)}]\n"
    
    # Pattern for \input{...} and \include{...}
    # Handles:
    #   - \input{file}
    #   - \input{file.tex}
    #   - \input{path/file}
    #   - \input{./path/file}
    #   - \include{file}
    pattern = r'\\(?:input|include)\{([^}]*)\}'
    
    def replace_match(match):
        """Replace a single \input or \include with its content."""
        sub_path = match.group(1).strip()
        
        # Handle paths
        if not sub_path.endswith('.tex'):
            sub_path += '.tex'
        
        # Resolve relative to current file
        current_dir = os.path.dirname(filepath)
        full_path = os.path.join(current_dir, sub_path)
        
        # Check if resolved path exists
        if os.path.exists(full_path):
            # Recursively resolve the included file
            return resolve_tex(full_path, depth + 1)
        
        # Try alternative: maybe it's in the same directory as the main file?
        # (This is a fallback for some LaTeX setups)
        if depth > 0:
            # Try the main file's directory
            main_dir = os.path.dirname(sys.argv[1]) if len(sys.argv) > 1 else '.'
            alt_path = os.path.join(main_dir, sub_path)
            if os.path.exists(alt_path):
                return resolve_tex(alt_path, depth + 1)
        
        # If file not found, leave the original command
        if VERBOSE:
            print(f"{'  ' * depth}⚠️  Not found: {sub_path}")
        return match.group(0)
    
    # Replace all \input and \include commands
    resolved_content = re.sub(pattern, replace_match, content)
    
    return resolved_content


# ============================================================
# Main Function
# ============================================================

def main():
    global VERBOSE
    
    # Parse command line arguments
    if len(sys.argv) < 2:
        print("Usage: python3 resolve_tex.py <main.tex> [output.tex]")
        print("")
        print("Examples:")
        print("  python3 resolve_tex.py c-kurs.tex all.tex")
        print("  python3 resolve_tex.py c-kurs.tex > all.tex")
        sys.exit(1)
    
    main_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else None
    
    # Enable verbose mode if requested
    if '-v' in sys.argv or '--verbose' in sys.argv:
        VERBOSE = True
    
    # Resolve the main file
    try:
        resolved = resolve_tex(main_file)
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
    
    # Write output
    if output_file:
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(resolved)
        print(f"✅ Resolved document written to: {output_file}")
        print(f"   Processed {len(visited_files)} files")
    else:
        # Print to stdout
        print(resolved)
        print(f"\n% Processed {len(visited_files)} files", file=sys.stderr)


# ============================================================
# Entry Point
# ============================================================

if __name__ == '__main__':
    main()