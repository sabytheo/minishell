#A FAIRe

- Ligne vide
------------ GOOD
- Erreurs de syntax ne doivent pas quitter minishell
------------ GOOD
- Multiples Heredoc
------------ PAS PRIS EN CHARGE
- echo "$" -> Bash write $
------------ ON RETOURNE UNE LIGNE VIDE (Pb d'expand)
- "$EMPTY" -> Bash just return
------------ execve : permission denied
- Si **cmd est vide -> on le prend qd meme
------------ GOOD
- . . . . . . . . lance une commande somehow
- cat vide apres un pipe
- Signaux dans heredoc
------------ SE RENSEIGNER / TO DO


#BESOIN DE CHECK SI ON A LA PERMISSION POUR UN FICHIER/DOSSIER
#BESOIN DE CHECK SI LA COMMANDE S'EXE AVEC UN FICHIER OU UN DOSSIER
	- Pouvoir differencier fichier et dossier

- cd sans permissions fichiers
------------ GOOD

- /directory -> code erreur 127 / "No such file or directory
------------ GOOD

- executable sans permission -> code erreur 126 / "permission denied"
------------ Pour l'instant on a 127 avec "No such file or directory"

- execute non existent file -> code erreur 127 / "No such file or directory" ------------ GOOD

- try to execute a dir -> code erreur 126 + "Is a directory"
------------ "No such file or directory" + code 127
- Double free cmd "$PWD"
------------ DOUBLE FREE + SEGFAULT

- ls /etc/ + tab into ctrl + c into espace -> invalid read sur le readline

-----
 - Si ./ -> open -> pour voir permission
 - Si / -> is a dir
 - Si . -> bash: .: filename argument required / .: usage: . filename [arguments]
...more to determine


