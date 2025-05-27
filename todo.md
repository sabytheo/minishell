#A FAIRe

- Heredoc
- Double free cmd "$PWD"
- Ligne vide
- cd sans permissions fichiers
- echo expand "$"
- "$EMPTY" -> permission denied / Bash just return
- executable sans permission -> code erreur 126 / "permission denied"
- execute non existent file -> code erreur 127 / "No such file or directory"
- try to execute a dir -> code erreur 126 / "Is a directory"
- /directory -> code erreur 127 / "No such file or directory"
