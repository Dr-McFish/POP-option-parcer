#ifndef GENERIC_OPTION_H
# define GENERIC_OPTION_H

typedef struct option_ptr {
	enum opt_type{UNASIGED_OPT, BOOL_OPT, STRING_OPT, INT_OPT} type;
	void* opt_ptr;
	bool was_used;
}				option_ptr_t;

#endif
