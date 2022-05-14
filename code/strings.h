#ifndef STRINGS_H
#define STRINGS_H

void concatenate_two_strings(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result);

void concatenate_two_strings_aux(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result, int order);

void replicate_string(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void split_string_by_substring(STACK_ELEM *main, STACK_ELEM *sub, STACK *new);

void find_substring_index(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void remove_first_element_from_string(STACK *s, STACK_ELEM x, STACK_ELEM *result);

void remove_last_element_from_string(STACK *s, STACK_ELEM x, STACK_ELEM *result);

void get_char_at_index(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void check_strings_equality(STACK *s, STACK_ELEM x, STACK_ELEM y, long to_push, STACK_ELEM *result);

void check_strings_less(STACK *s, STACK_ELEM x, STACK_ELEM y, long to_push, STACK_ELEM *result);

void take_from_string(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void check_strings_more(STACK *s, STACK_ELEM x, STACK_ELEM y, long to_push, STACK_ELEM *result);

void drop_from_string(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

#endif
