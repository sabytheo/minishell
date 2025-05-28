#A FAIRe

- Ligne vide ------------------------------------------ GOOD
- Erreurs de syntax ne doivent pas quitter minishell -- GOOD
- Heredoc
- Double free cmd "$PWD"
- echo expand "$"
- "$EMPTY" -> permission denied / Bash just return
- Si **cmd est vide -> on le prend qd meme
- . . . . . . . . lance une commande somehow
- cat vide apres un pipe
- Signaux dans heredoc


#BESOIN DE CHECK SI ON A LA PERMISSION POUR UN FICHIER/DOSSIER
#BESOIN DE CHECK SI LA COMMANDE S'EXE AVEC UN FICHIER OU UN DOSSIER
	- Pouvoir differencier fichier et dossier

- cd sans permissions fichiers ---------------------------------------------- GOOD ?
- /directory -> code erreur 127 / "No such file or directory" ---------------
	- Fonction is_valid_cmd (Pas la bonne fonction)
- try to execute a dir -> code erreur 126 / "Is a directory"
	- Fonction findpath -> need to differencier path de commandes et path classique
- executable sans permission -> code erreur 126 / "permission denied"
- execute non existent file -> code erreur 127 / "No such file or directory"

