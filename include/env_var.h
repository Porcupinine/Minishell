/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:32:37 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:32:49 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

#include "lexical_analyzer.h"

void	search_for_equals(t_tokens *tokens);
#endif //ENV_VAR_H
