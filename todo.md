#Check Erreurs :
	Parcourir une premiere fois la liste
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
	printf_fd? pour pouvoir écrire sur la sortie d'erreur, possibilite de gerer des variables?


#Exemple de retours d'erreurs sur bash --posix
	egache@z4r10p1:~/work/minishell_te/minishell$ echo < > |
	bash: syntax error near unexpected token `>'

	egache@z4r10p1:~/work/minishell_te/minishell$ < > |
	bash: syntax error near unexpected token `>'

	egache@z4r10p1:~/work/minishell_te/minishell$ |
	bash: syntax error near unexpected token `|'

	egache@z4r10p1:~/work/minishell_te/minishell$ >
	bash: syntax error near unexpected token `newline'

	egache@z4r10p1:~/work/minishell_te/minishell$ <
	bash: syntax error near unexpected token `newline'

	egache@z4r10p1:~/work/minishell_te/minishell$ fggdf
	fggdf: command not found

	egache@z4r10p1:~/work/minishell_te/minishell$ fggdf hgffgf hggf
	fggdf: command not found

	bash-5.1$ cat salut
	cat: salut: No such file or directory


#CHECK ERRORS TOKENS

check si cmd valid
	si faux -> erreur "command not found"
	check si +1 is cmd valid
		si vrai -> erreur (en fonction de la commande)
check si OPERATEUR
	check si +1 OPERATEUR OU NULL
		si vrai
			si OPERATEUR	-> syntax error near unexpected token `>>'
			si NULL			-> syntax error near unexpected token `newline'

