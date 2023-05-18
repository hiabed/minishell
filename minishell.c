/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/17 15:27:14 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int main() {
    char* command = NULL;

    // Loop until the user enters "exit"
    while (strcmp(command, "exit") != 0) {
        // Display the prompt and read the user's input
        // command = readline("Enter a command: ");

        // Add the command to the history
        // add_history(command);

        // Process the command
        printf("You entered: %s\n", command);

        // Free the memory allocated by readline
        free(command);
    }

    return 0;
}