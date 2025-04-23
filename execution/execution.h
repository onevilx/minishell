/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:29:31 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/23 15:34:25 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../includes/miniheader.h"


int		execute_builtin(char **args);
void	builtin_cd(char **args);
void	builtin_pwd(char **args);
void	builtin_env(char **args);
void	builtin_exit(char **args);
void	builtin_echo(char **args);
void	builtin_unset(char **args);
void	builtin_export(char **args);

#endif
