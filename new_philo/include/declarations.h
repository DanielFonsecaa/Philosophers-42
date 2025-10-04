/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declarations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 23:12:18 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/04 11:46:21 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATIONS_H
# define DECLARATIONS_H

//Mutexes
# define WRONG_CODE "Wrong code for handle"
# define MUTEX_VAL_INV "The value specifed by mutex is invalid"
# define ATTR_INV "The value specifed by attr is invalid"
# define DEADLCK "The current thread already owns the mutex. Will deadlock"
# define THREAD_NOT_OWN "The current thread does not own the mutex."
# define PR_NOT_MEM "The process can't allocate enough memory to another mutex"
# define MUTEX_LOCKED "Mutex is locked"

//Threads
# define TH_NO_RSC "No resources to create another thread\n"
# define NOT_JOINABLE "The value specifed is not joinable \n"
# define DEADLOCK "Deadlock was detected\n"
# define NO_PERM "The caller does not have permission \n" 
# define NOT_FOUND "No thread was found by the given thread ID \n" 

// Color text
# define R  "\033[0m"
# define RST  "\033[0m"
# define RED  "\033[1;31m"
# define GRN  "\033[1;32m"
# define Y  "\033[1;33m"
# define BLU  "\033[1;34m"
# define MAG  "\033[1;35m"
# define CYN  "\033[1;36m"
# define W  "\033[1;37m"
# define B "\033[1m"
# define UNDL "\033[4m"
#endif