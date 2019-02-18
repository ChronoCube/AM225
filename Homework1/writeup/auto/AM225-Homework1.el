(TeX-add-style-hook
 "AM225-Homework1"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("geometry" "margin=1in") ("mathdesign" "charter")))
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "geometry"
    "mathtools"
    "verbatim"
    "amsthm"
    "mathdesign"
    "inconsolata"
    "graphicx")
   (TeX-add-symbols
    "P")
   (LaTeX-add-labels
    "2c")
   (LaTeX-add-amsthm-newtheorems
    "lemma"
    "note"))
 :latex)

