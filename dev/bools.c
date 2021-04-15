#include "bool_array.h"
#include <stdlib.h>

bool get_b_at_index(bools b, int idx){
	return((b >> idx) & 0b00000001);
}

bool get_bs_at_index(bools* bs, int idx){
	return(get_b_at_index(bs[idx / 8], idx % 8));
}


void set_b_at_index(bools b, int idx, bool set) {
	b = b | ((set ? 0b00000001 : 0b00000000) << idx);
}
void set_bs_at_index(bools* bs, int idx, bool set) {
	set_b_at_index(bs[idx/8], idx % 8, set);
}


bools* alloc_bools(size_t n)
{
	return (bools*)malloc(N_BOOLS_TO_N_BYTES(n));
}