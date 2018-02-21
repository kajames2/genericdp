((nil . ((company-clang-arguments . ("-I.include/")))))

(defvar include-path (list ("include" "include/genericdp" "src" "test")))
(dir-locals-set-class-variables 'genericdp
'((c-mode . ((eval . (setq flycheck-clang-include-path include-path))))))

(dir-locals-set-class-variables 'genericdp
'((c++-mode . ((eval . (setq flycheck-clang-include-path include-path))))))
