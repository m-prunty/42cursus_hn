 *This project has been created as part of the 42 curriculum by maprunty@student.42heilbronn.de*

## Push_swap

## Description
` The Push swap project is a simple yet highly structured algorithmic challenge: you
need to sort data.`
given a list of integers, two 'stacks' and a limited set of instructions, sort in as few instructions possible.

I implemented three different algo's namely Bubble Sort, Radix and the Heilbronn K Sort.
Bubble sort here was solely a proof of concept to ensure my linked list and all operations worked correctly.
Next I implemented a binary Radix Sort however the number of operations was too high.
After discussion with a number of peers I was introduced to the K_sort algorithm by ashadrin and 
further refined my approach with help from mrazem.

### Operations:

|push|swap|rotate|revrotate|
|---|---|---|---|
|pa|sa|ra|rra|
|pb|sb|rb|rrb|
|  |ss|rr|rrr|

### Structures
I used a number of structs to store info;
the t_ps struct holds the stacks, flags, an array of all elements,  a t_count struct to hold the ops count,  and initial disorder.
```
typedef struct s_ps
{
	t_stack		stks[2];
	int			curstk;
	t_psflag	flags[2];
	t_element	*elements;
	t_count		count;
	int			disorder;
	int			fd;
}	t_ps;
```
the t_stack struct holds a pointer to the head of each stack, the length 'n', the name (a or b), alogside a sorted btree of the full list.
```
typedef struct s_stack
{
	char	name;
	int		n;
	t_list	*head;
	t_btree *root;
}	t_stack;

```
This is the element struct. I initialise an array of n elements on setup, storing these in the t_ps struct. The integer values are populated and the final sort index is determined by using a binary sort tree. The data pointer of t_list points at each of these elements
```
typedef struct s_element
{
	int		value;
	int		idx;
	int		sort;
	int		sorted;
}	t_element;

```
t_count is a struct to hold the count of each operation.
```
typedef struct s_count
{
	int	tot;
	int	p[2];
	int	s[2];
	int	ss[1];
	int	r[2];
	int	rr[2];
	int	rrs[2];
}	t_count;
```
## Instructions
** relevant information about compilation, installation, and/or execution **
Run `make` in the root directory.
Exec `./push_swap <flags> <array of INTs>`
__note__: input can be given as `./push_swap 1 2 3` or `./push_swap "1 2 3"`

## Resources
manpages and Stackoverflow helped brushing up on linked lists and structures
geeksforgeeks helped with the different algorithms
Disscussion with peers ashadrin and mrazem brought me to the k_sort algo.
gdb and Chatgpt were used to help with debugging.
