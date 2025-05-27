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
- Si **cmd est vide -> on le prend qd meme
- Erreurs de syntax ne doivent pas quitter minishell
- . . . . . . . . lance une commande somehow
- cat vide apres un pipi
- Signaux dans heredoc

