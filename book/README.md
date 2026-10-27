# Editing the book

## TeXLive

To compile the book a recent LaTeX version is required. The author went through

https://tug.org/texlive/

and downloaded the installer.

The author installed the distribution on his local account, so he changed the
TEXDIR to '~/.local/texlive/2026' and, as well, enabled the option "create 
symlinks to standard directories", where he set the binary directory to 
'~/.local/bin'.

In addition, he's using the following ~/.latexmkrc:
    
    $pdflatex = 'lualatex -file-line-error %O %S';
    $pdf_mode = 1;

Some versions of TeXLive do not have all fonts updated related to KpMath-Sans. To
fix this issue do

    # Find where the new file lives
    kpsewhich KpMathSans-Regular.otf
    # e.g. ~/texlive/2026/texmf-dist/fonts/opentype/public/kpfonts-otf/KpMathSans-Regular.otf

    # Symlink the old name → new file (in the same directory)
    ln -s KpMathSans-Regular.otf KpMath-Sans.otf
    ln -s KpMathSans-Bold.otf KpMath-SansBold.otf

    texhash
