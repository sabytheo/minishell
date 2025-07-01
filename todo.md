#A FAIRe

 - Si . -> bash: .: filename argument required / .: usage: . filename [arguments]
- ./minishell dans minishell
- Check tous les mallocs
- Normer toutes les fonctions
- Faire des tests
- Valider minishell

#REFACTO R1 :

CLEAN.C
 - 2/3 fichiers

isatty pour ./minishell | ./minishell


PWD peut etre nul attention a pas dereferencé


Double prompt when ctrl+c in pipe command

whitespaces must be 1 space

redirecting directories leak

ECHO :

Handle -nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn


			// if (ft_strncmp(cmds->args[0], "../", 3) != 0)
			// 	free(path);
