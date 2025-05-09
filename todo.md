#Check Erreurs : DONE ./ ./
	Parcourir une premiere fois la liste\
			- CHECKER ERREURS DE SYNTAXE
			- Checker doublons de variables ou operateurs (par exemple : <<<<<, <<|)
#Exec :
	Avant toute commande -> parcourir la liste (c'est surement du parsing)
		- Si on trouve un heredoc << -> Exec en premier.
	Reparcourir la liste tant qu'on trouve pas un pipe
		Check si on trouve < ou > ou >> ET SKIP <<
			- Si type != 0 -> change le fd (dup2 a a executer apres les commandes)
		Execute la commande
			- Check le ERRNO pour voir si erreur ou non
	Reparcourir a partir du pipe
		- Redirection pipe THEO
		- Si un pipe fail, qd meme executer le suivant

#En fonction  :

if check_errors == yes
	return ;
if heredoc == yes
	do heredoc;
if operator == yes
	change fd
strcmp pour trouver la commande a exec
	execute commande correspondante
if pipe == yes
	execute command with old output

#Fonction a faire:


#check sur un autre minishell :

bash-5.1$ caca | caca | >
bash: syntax error near unexpected token `newline'

caca | echo salut


#A VOIR

- errno.h / Une variable errno existe deja !!!
