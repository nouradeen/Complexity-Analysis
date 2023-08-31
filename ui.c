#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ui.h"
#include "io.h"
#include "analyze.h"

static void ui_invalid_input()
{
	printf("info> bad input\n");
}
static void ui_exit()
{
	printf("info> bye\n");
}
static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}
static void ui_line(char c, int n)
{
	while (n-- > 0)
	{
		putchar(c);
	}
	putchar('\n');
}
static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i = 0; i < num_options; i++)
	{
		printf("    %c) %s\n", 'a' + i, options[i]);
	}
}
static void ui_menu()
{
	const char *options[] = {
		"Menu",							 // a
		"Exit\n",						 // b
		"Bubble sort best case",		 // c
		"Bubble sort worst case",		 // d
		"Bubble sort average case\n",	 // e
		"Insertion sort best case",		 // f
		"Insertion sort worst case",	 // g
		"Insertion sort average case\n", // h
		"Quick sort best case",			 // i
		"Quick sort worst case",		 // j
		"Quick sort average case\n",	 // k
		"Linear search best case",		 // l
		"Linear search worst case",		 // m
		"Linear search average case\n",	 // n
		"Binary search best case",		 // o
		"Binary search worst case",		 // p
		"Binary search average case"	 // q
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

void table_title(notation_t notation)
{
	ui_line('~', SECOND_MENU_WIDTH);
	char O_calc_text[][8] = {"T/1", "T/logn", "T/n", "T/nlogn", "T/n²", "T/n³"};														// Array of strings for the time complexity
	printf("size\ttime T(s)\t\t%s\t\t\t\t%s\t\t\t\t%s\n", O_calc_text[notation - 1], O_calc_text[notation], O_calc_text[notation + 1]); // Printing the time complexity and the previous and the after
}

void display(result_t *result, notation_t notation)
{
	double (*O_calc[6])(double time, int length); // Array of Function pointer
	// Array with function pointer to use as a parameter for functiones.
	O_calc[0] = T_1;
	O_calc[1] = T_logN;
	O_calc[2] = T_N;
	O_calc[3] = T_NlogN;
	O_calc[4] = T_N2;
	O_calc[5] = T_N3;

	table_title(notation); // Print the header of the table

	for (int i = 0; i < RESULT_ROWS; i++)
	{ // Print the results in the table
		printf("%d\t%0.8f\t\t%.10e\t\t%.10e\t\t%.10e\n", result[i].size, result[i].time, O_calc[notation - 1](result[i].time, result[i].size), O_calc[notation](result[i].time, result[i].size), O_calc[notation + 1](result[i].time, result[i].size));
	}

	// FILE *gnuplot = popen("gnuplot", "w");
	// fprintf(gnuplot, "set xlabel 'SIZE'\n");
	// fprintf(gnuplot, "set ylabel 'TIME'\n");
	// fprintf(gnuplot, "plot '-' smooth csplines\n");
	// for (int i = 0; i < RESULT_ROWS; i++)
	// 	fprintf(gnuplot, "%g %g\n", (double)result[i].size, result[i].time);
	// fprintf(gnuplot, "e\n");
	// fflush(gnuplot);
}

void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];
	Big_notation_t *notation = malloc(sizeof(*notation)); // allocate memory for "notaion to use outside the function"

	show_menu = true;
	running = true;
	while (running)
	{
		srand(clock());
		if (show_menu)
		{
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice())
		{
		case 'a': // Done
			printf("\e[1;1H\e[2J");
			show_menu = true;
			break;
		case 'b': // Done
			running = false;
			break;
		// Bubble sort
		case 'c':
			printf("\e[1;1H\e[2J");
			benchmark(bubble_sort_t, best_t, result, RESULT_ROWS, notation, sortedArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tbubble sort: best\t\t\t\n");
			display(result, notation->best);
			break;
		case 'd':
			printf("\e[1;1H\e[2J");
			benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS, notation, reversedArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tbubble sort: worst\t\t\t\n");
			display(result, notation->worst);
			break;
		case 'e':
			printf("\e[1;1H\e[2J");
			benchmark(bubble_sort_t, average_t, result, RESULT_ROWS, notation, randomArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tbubble sort: average\t\t\t\n");
			display(result, notation->average);
			break;

		case 'f':
			printf("\e[1;1H\e[2J");
			benchmark(insertion_sort_t, best_t, result, RESULT_ROWS, notation, sortedArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tinsertion sort: best\t\t\t\n");
			display(result, notation->best);
			break;
		case 'g':
			printf("\e[1;1H\e[2J");
			benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS, notation, reversedArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tinsertion sort: worst\t\t\t\n");
			display(result, notation->worst);
			break;
		case 'h':
			printf("\e[1;1H\e[2J");
			benchmark(insertion_sort_t, average_t, result, RESULT_ROWS, notation, randomArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tinsertion sort: average\t\t\t\n");
			display(result, notation->average);
			break;

		case 'i':
			printf("\e[1;1H\e[2J");
			benchmark(quick_sort_t, best_t, result, RESULT_ROWS, notation, sortedArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tquick sort: best\t\t\t\n");
			display(result, notation->best);
			break;
		case 'j':
			printf("\e[1;1H\e[2J");
			benchmark(quick_sort_t, worst_t, result, RESULT_ROWS, notation, quicksortArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tquick sort: worst\t\t\t\n");
			display(result, notation->worst);
			break;
		case 'k':
			printf("\e[1;1H\e[2J");
			benchmark(quick_sort_t, average_t, result, RESULT_ROWS, notation, randomArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tquick sort: average\t\t\t\n");
			display(result, notation->average);
			break;

		case 'l':
			printf("\e[1;1H\e[2J");
			benchmark(linear_search_t, best_t, result, RESULT_ROWS, notation, sortedArray, 0);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tlinear search: best\t\t\t\n");
			display(result, notation->best);
			break;
		case 'm':
			printf("\e[1;1H\e[2J");
			benchmark(linear_search_t, worst_t, result, RESULT_ROWS, notation, randomArray, -1);
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tlinear search: worst\t\t\t\n");
			display(result, notation->worst);
			break;
		case 'n':
			printf("\e[1;1H\e[2J");
			benchmark(linear_search_t, average_t, result, RESULT_ROWS, notation, randomArray, rand());
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tlinear search: average\t\t\t\n");
			display(result, notation->average);
			break;

		case 'o':
			printf("\e[1;1H\e[2J");
			benchmark(binary_search_t, best_t, result, RESULT_ROWS, notation, sortedArray, (SIZE_START / 2));
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tbinary search: best\t\t\t\n");
			display(result, notation->best);
			break;
		case 'p':
			printf("\e[1;1H\e[2J");
			benchmark(binary_search_t, worst_t, result, RESULT_ROWS, notation, sortedArray, rand());
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tbinary search: worst\t\t\t\n");
			display(result, notation->worst);
			break;
		case 'q':
			printf("\e[1;1H\e[2J");
			benchmark(binary_search_t, average_t, result, RESULT_ROWS, notation, sortedArray, rand());
			ui_line('*', SECOND_MENU_WIDTH);
			printf("\t\t\t\t\t\tbinary search: average\t\t\t\n");
			display(result, notation->average);
			break;

		// Invalid input
		default:
			show_menu = false;
			ui_invalid_input();
			break;
		}
	}
	free(notation);
	ui_exit();
}
