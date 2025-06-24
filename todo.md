#A FAIRe

 - Si . -> bash: .: filename argument required / .: usage: . filename [arguments]
- ./minishell dans minishell
- Check tous les mallocs
- Normer toutes les fonctions
- Faire des tests
- Valider minishell

#REFACTO R1 :

CLEAN.C

EXEC_SINGLE.C
	- execute_single_command
		- Split la fonction avec une fonction exec_bin
		- Voir pour modifier "before builtins"

EXEC_TOKENS.C
	- extract_redirections
	- split_tokens

EXEC.C
	- Rename fichier
		- Voir en fonctions des fonctions dans le fichier
		- Peut etre diviser en 2 fichiers : exec_builtins \ exec_bin

MAIN.c
	- main

isatty pour ./minishell | ./minishell


