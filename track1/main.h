/*
 * Main.h
 *
 *  Created on: May 18, 2023
 *      Author: gogoCow
 */

#ifndef MAIN_H
#define MAIN_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#define NULL 0
#define false 0
#define true !false
typedef void (*cyclic_ptr)(void);
extern void run_startup (void);
extern void run_cyclic (void);
extern int main (void);

#endif  /*MAIN_H*/
