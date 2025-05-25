/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 10:14:20 by tsaby             #+#    #+#             */
/*   Updated: 2025/05/25 11:34:24 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int exec_builtins_with_cmd(t_minishell *minishell, t_cmds *cmd)
{
    int     len;

    minishell->error_code = 0;
    len = ft_strlen(cmd->args[0]);
    if (ft_strncmp(cmd->args[0], "cd", len) == 0 && len == 2)
        ft_cd(minishell, &cmd);
    else if (ft_strncmp(cmd->args[0], "echo", len) == 0 && len == 4)
        ft_echo(minishell, &cmd);
    else if (ft_strncmp(cmd->args[0], "env", len) == 0 && len == 3)
        ft_env(minishell);
    else if (ft_strncmp(cmd->args[0], "exit", len) == 0 && len == 4)
        return (0);
    else if (ft_strncmp(cmd->args[0], "export", len) == 0 && len == 6)
        ft_export(minishell);
    else if (ft_strncmp(cmd->args[0], "pwd", len) == 0 && len == 3)
        ft_pwd();
    else if (ft_strncmp(cmd->args[0], "unset", len) == 0 && len == 5)
        ft_unset(minishell);
    return (0);
}

void execute_child_process(t_minishell *minishell, t_cmds *cmd, int **pipes, int cmd_index, int cmd_count)
{
    int i;

    // Configurer les pipes
    if (cmd_index > 0) // Pas la première commande
    {
        if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
        {
            perror("dup2 stdin");
            exit(1);
        }
    }

    if (cmd_index < cmd_count - 1) // Pas la dernière commande
    {
        if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
        {
            perror("dup2 stdout");
            exit(1);
        }
    }

    // Fermer tous les pipes dans l'enfant
    i = 0;
    while (i < cmd_count - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }

    // Configurer les redirections spécifiques à cette commande
    if (setup_redirections(cmd->redirs, minishell) < 0)
        exit(1);

    // Exécuter la commande
    if (minishell->cmdfound == false)
        exit(0);

    if (is_a_builtins(cmd->args[0]))
    {
        exec_builtins_with_cmd(minishell, cmd);
        exit(0);
    }
    else
    {
        char *path = find_path(cmd->args[0], minishell->envp_tab, 0);
        if (path)
        {
            execve(path, cmd->args, minishell->envp_tab);
            perror("execve");
        }
        else
        {
            fprintf(stderr, "%s: command not found\n", cmd->args[0]);
            exit(127);
        }
    }
    exit(1);
}

void cleanup_pipes(int **pipes, int pipe_count)
{
    int i;

    i = 0;
    while (i < pipe_count)
    {
        if (pipes[i])
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
            free(pipes[i]);
        }
        i++;
    }
    free(pipes);
}

void execute_piped_command(t_minishell *minishell, t_cmds *cmds)
{
    t_cmds  *current;
    int     **pipes;
    pid_t   *pids;
    int     cmd_count;
    int     i;
    int     status;

    // Compter le nombre de commandes
    current = cmds;
    cmd_count = 0;
    while (current)
    {
        cmd_count++;
        current = current->next;
    }

    // Allouer la mémoire pour les pipes et les PIDs
    pipes = malloc(sizeof(int *) * (cmd_count - 1));
    pids = malloc(sizeof(pid_t) * cmd_count);
    if (!pipes || !pids)
    {
        perror("malloc");
        return;
    }

    // Créer tous les pipes
    i = 0;
    while (i < cmd_count - 1)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            cleanup_pipes(pipes, i);
            free(pids);
            return;
        }
        i++;
    }

    // Exécuter chaque commande
    current = cmds;
    i = 0;
    while (i < cmd_count)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            // Processus enfant
            execute_child_process(minishell, current, pipes, i, cmd_count);
            exit_and_clear_child(1, minishell);
        }
        else if (pids[i] < 0)
        {
            perror("fork");
            cleanup_pipes(pipes, cmd_count - 1);
            free(pids);
            return;
        }
        current = current->next;
        i++;
    }

    // Fermer tous les pipes dans le processus parent
    i = 0;
    while (i < cmd_count - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }

    // Attendre tous les processus enfants
    i = 0;
    while (i < cmd_count)
    {
        waitpid(pids[i], &status, 0);
        if (i == cmd_count - 1) // Seul le dernier processus compte pour le code de retour
        {
            if (WIFEXITED(status))
                minishell->error_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                minishell->error_code = 128 + WTERMSIG(status);
        }
        i++;
    }

    // Nettoyer
    cleanup_pipes(pipes, cmd_count - 1);
    free(pids);
}
