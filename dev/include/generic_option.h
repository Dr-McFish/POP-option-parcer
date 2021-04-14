#ifndef GENERIC_OPTION_H
# define GENERIC_OPTION_H

typedef struct generic_option {
	enum opt_type{BOOL_OPT, STRING_OPT, INT_OPT} type;
	void* opt_ptr;
}				generic_option_t;

#endif
