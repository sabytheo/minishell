#A FAIRe

- Ligne vide
------------ GOOD
- Erreurs de syntax ne doivent pas quitter minishell
------------ GOOD
- Si **cmd est vide -> on le prend qd meme
------------ GOOD

- Multiples Heredoc
------------ GOOD
- echo "$" -> Bash write $
------------ ON RETOURNE UNE LIGNE VIDE (Pb d'expand)
- "$EMPTY" -> Bash just return
------------ PROBLEME DANS PATH CAR c'est avec n' importe quelle variable qui existe pas
- . . . . . . . . lance une commande somehow
------------ GOOD
- cat vide apres un pipe

- Signaux dans heredoc
------------ GOOD


- cd sans permissions fichiers
------------ GOOD

- /directory -> code erreur 127 / "No such file or directory
------------ GOOD

- executable sans permission -> code erreur 126 / "permission denied"
------------ GOOD

- execute non existent file -> code erreur 127 / "No such file or directory"
------------ GOOD

- try to execute a dir -> code erreur 126 + "Is a directory"
------------ GOOD

- Double free cmd "$PWD"
------------ GOOD

- ls /etc/ into tab into ctrl + c into espace -> invalid read sur le readline

-----
 - Si ./ -> open -> pour voir permission
 - Si / -> is a dir
 - Si . -> bash: .: filename argument required / .: usage: . filename [arguments]
...more to determine

- Le free enlevé de is_valid_cmd qui debug $PWD, donne un leak lors d'autres commandes
