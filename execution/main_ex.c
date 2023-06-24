/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:12:43 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/23 20:59:13 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char** rment(t_env* p)
{
    	char** d;
		int n = 0;
		t_env* tem;

		tem = p;
		while (tem)
		{
			tem = tem->next;
			n++;
		}
		d = malloc(sizeof(char*) * (n + 1));
		n = 0;
		while (p)
		{
			d[n] = p->content;
			p = p->next;
			n++;
		}
        d[n] = NULL;
        return(d);
}

char* get_path(t_env* p)
{
    while (p)
    {
        if (ft_strcmp("PATH", p->key) == 0)
            return(p->content);
        p = p->next;
    }
    return(NULL);
}

char** join_cmd(char* d, char** s)
{
    char** p;
    if (s && *s)
    {
        p = malloc(sizeof(char*) * (3));
        p[0] = ft_strdup(d);
        p[1] = ft_strdup(s[0]);
        return(p[2] = NULL, p);
    }
    p = malloc(sizeof(char*) * (2));
    p[0] = ft_strdup(d);
    p[1] = NULL;
    return(p);

}

char *get_path_cmd(t_env* p, char* d, char** s)
{
    char* g;
    char** c;

    g = get_path(p); 
    c = ft_split(g + 5, ':');
    // if (access(d, F_OK) == 0)
    // {

        // if (opendir())

    // }
    if (access(d, X_OK) == 0)
        execve(d, join_cmd(d, s), NULL);
    int i = 0;
    while (c[i])
    {
        char* syt = ft_strjoin(c[i], "/");
        char* buff = ft_strjoin(syt, d);
       // printf("%s\n", buff);
        if (access(buff, F_OK) == 0)
            return(buff);
        i++;
    }
    return(NULL);
}
void one_cmd(t_env* p, t_token* ptr)
{
    int id = fork();
    if (id == 0)
    {
        // printf("(%d)\n", ptr->out);
      // printf("*%d*\n", g_g.pipefd);
        if (g_g.pipefd > 0)
            dup2(g_g.pipefd, 0);
        if (ptr->fd > 0)
            dup2(ptr->fd, 0);
        if (ptr->out > 0)
            dup2(ptr->out, 1);
        if (get_path_cmd(p, ptr->cmd, ptr->arg) == NULL)
        {
            printf("minishell: %s: command not found\n", ptr->cmd);
            // perror("%s, commd not fond\n", ptr->cmd);
            exit(127);
        }
        execve(get_path_cmd(p, ptr->cmd, ptr->arg), join_cmd(ptr->cmd, ptr->arg), NULL);
    }
}
// void multi_cmd(t_env* p, t_token* ptr)
// {
//     int		pip_2[2];
//     int		pip[2];
//     char	*path;
//     int i = ft_lstsize(ptr);
//     int j = ft_lstsize(ptr) - 1;
//     int id = fork();
//     if (id == 0)
//     {
//         //dup2(pip[1], 1);
//         dup2(ptr->fd, 0);
//         if (get_path_cmd(p, ptr->cmd, ptr->arg) == NULL)
//         {
//             perror("commd not fond\n");
//             exit(127);
//         }
//         // dup2(f1, 0);
//         // dup2(pip[1], 1);
//         close(pip[0]);
//         // close(f1);
//         execve(get_path_cmd(p, ptr->cmd, ptr->arg), join_cmd(ptr->cmd, ptr->arg), NULL);
//         perror("execve");
//         exit(1);
//     }
//     while (i != j)
// 	{
// 		pipe(pip_2);
// 		id = fork();
// 		if (id == 0)
// 		{
//             path = get_path_cmd(p, ptr->cmd, ptr->arg);
//             if (path == NULL)
//             {
//                 perror("commd not fond\n");
//                 exit(127);
//             }
//             dup2(pip[0], 0);
// 			dup2(pip_2[1], 1);
// 			close(pip_2[0]);
// 			execve(path, join_cmd(ptr->cmd, ptr->arg), p);
// 			perror("execve: ");
// 			exit(1);
// 		}
// 		close(pip_2[1]);
// 		*pip = *pip_2;
// 		freepath(ptr);
// 		i++;
//     }
//     char    *path2;
//     int		id = fork();
//     if (id == 0)
//     {
//         path2 = get_path_cmd(p, ptr->cmd, ptr->arg);
//         if (path2 == NULL)
//         {
//             perror("commd not fond\n");
//             exit(127);
//         }
//         // dup2(f2, 1);
//         dup2(pip[0], 0);
//         close(pip[1]);
//         // close(f2);
//         execve(path2, join_cmd(ptr->cmd, ptr->arg), p);
//         perror("execve: ");
//         exit(1);
//     }
// 	close(pip[0]);
// 	close(pip[1]);
// 	freepath(ptr); 
// }
int	ft_lstsize_1(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
// void first_cmd(t_env* p, t_token* ptr)
// {
//     int id = fork();
//     if (id == 0)
//     {
//         if (g_g.pipefd > 0)
//             dup2(g_g.pipefd, 0);
//         else if (ptr->fd > 0)
//             dup2(ptr->fd, 0);
//         else if (ptr->out > 0)
//             dup2(ptr->out, 1);
//         else if (pipe > 0)
//             dup2(g_g.pipe_2, 1);
//         if (get_path_cmd(p, ptr->cmd, ptr->arg) == NULL)
//         {
//             perror("commd not fond\n");
//             exit(127);
//         }
//         execve(get_path_cmd(p, ptr->cmd, ptr->arg), join_cmd(ptr->cmd, ptr->arg), NULL);
//     }
// }
// void midel_cmd(t_env* p, t_token* ptr)
// {
//     char* path;
    
//     pipe(g_g.pipe_2);
//     int id = forc();
//     if (id == 0)
//     {
//         path = get_path_cmd(p, ptr->cmd, ptr->arg);
//         if (path == NULL)
//         {
//             perror("commd not fond\n");
//             exit(127);
//         }
//         dup2(g_g.pipe_2, 0);
//         close(g_g.pipe_2);
//         execve(path, join_cmd(ptr->cmd, ptr->arg), p);
//         perror("execve: ");
//         exit(1);
//     }
// }
void main_ex(t_env* p, t_token* ptr)
{
    
    // here_doc(ptr);
    if (ft_lstsize_1(ptr) == 1)
        one_cmd(p, ptr);
    // else if (ft_lstsize(ptr) > 1)
    // {
    //     int pip[2];
    //     pipe(pip);
    //     g_g.pipe_2 = pip[1];
    //     first_cmd(p, ptr);
    //     while (ptr->next)
    //     {
    //         midel_cmd(p, ptr);
    //         ptr = ptr->next;
    //     }
    //     last_cmd();
    // }
    //     multi_cmd(p, ptr);
        // printf("%s\n",get_path_cmd(p, ptr->cmd, ptr->arg));
    // while (ptr)
    // {
    // 	 printf("*(%s)*\n", ptr->cmd)
    //  	ptr Œ ptr->next;
    //  }
    while (wait(NULL) != -1)
		;
}