// Check and dump C++ feature test defines
//
// See https://en.cppreference.com/w/cpp/feature_test

#include <string>
#include <utility>
#include <iostream>
#include <cassert>
#include <functional>

/*

Updating from /usr/include/:

comm -13 <(grep check features.cpp | grep -o '__cpp_\w*' | sort -u) <(grep --binary-files=without-match -ro '__cpp_\w*' -h . /usr/include/ | sort -u) | awk '{ print "check(" $1 ");";}'

Updating from web:

comm -13 <(grep check features.cpp | grep -o '__cpp_\w*' | sort -u) \
	<(wget -q -O- 'https://en.cppreference.com/mwiki/index.php?title=cpp/feature_test&action=raw' | \
	sed 's/_}}{{c|/_/' | grep -o '__cpp\w*' | sort -u) | \
	awk '{ print "check(" $1 ");";}'

Tip: append result of  snippets above to this file.

Builing table:

join <(join <(join <(./11) <(./14))  <(./17)) <(./20) > a.csv

*/

using namespace std;

// Run checks as global constructors automatically
// without manual operations

#define concat2(a,b) a##b

#define concat(a,b) concat2(a,b)

#define u(a) concat(a,__LINE__)

#define check2(x, y) do { cout << x; if (string(x) != #y) cout << " " << #y; else cout << " ------"; cout << endl; } while (0)

#define check(x) class c##x { public: c##x() { check2(#x, x); }} c##x

// Just append new check at the end of the file

check(__GNUC__);
check(__GNUC_MINOR__);
check(__GNUC_PATCHLEVEL__);
check(__GNUG__);
check(__clang__);
check(__clang_major__);
check(__clang_minor__);
check(__clang_patchlevel__);
check(__cplusplus);
check(__cpp_exceptions);
check(__cpp_rtti);
check(__cpp_static_assert);
check(__cpp_delegating_constructors);
check(__cpp_rvalue_references);
check(__cpp_alias_templates);
check(__cpp_variadic_templates);
check(__cpp_unicode_characters);
check(__cpp_constexpr);
check(__cpp_decltype);
check(__cpp_raw_strings);
check(__cpp_ref_qualifiers);
check(__cpp_unicode_literals);
check(__cpp_initializer_lists);
check(__cpp_threadsafe_static_init);
check(__cpp_attributes);
check(__cpp_nsdmi);
check(__cpp_user_defined_literals);
check(__cpp_lambdas);
check(__cpp_range_based_for);
check(__cpp_lib_result_of_sfinae);
check(__cpp_binary_literals);
check(__cpp_lib_is_null_pointer);
check(__cpp_lib_allocator_is_always_equal);
check(__cpp_lib_allocator_traits_is_always_equal);
check(__cpp_lib_incomplete_container_elements);
check(__cpp_inheriting_constructors);
check(__cpp_hex_float);

// C++14

check(__cpp_aggregate_nsdmi);
check(__cpp_decltype_auto);
check(__cpp_generic_lambdas);
check(__cpp_init_captures);
check(__cpp_lib_exchange_function);
check(__cpp_lib_integer_sequence);
check(__cpp_lib_integral_constant_callable);
check(__cpp_lib_robust_nonmodifying_seq_ops);
check(__cpp_lib_string_udls);
check(__cpp_lib_transformation_trait_aliases);
check(__cpp_lib_tuples_by_type);
check(__cpp_return_type_deduction);
check(__cpp_variable_templates);
check(__cpp_sized_deallocation);
check(__cpp_lib_is_final);
check(__cpp_lib_make_reverse_iterator);
check(__cpp_lib_tuple_element_t);
check(__cpp_lib_transparent_operators);

// C++17

check(__cpp_enumerator_attributes);
check(__cpp_lib_invoke);
check(__cpp_lib_nonmember_container_access);
check(__cpp_lib_uncaught_exceptions);
check(__cpp_lib_unordered_map_insertion);
check(__cpp_lib_unordered_map_try_emplace);
check(__cpp_lib_void_t);
check(__cpp_namespace_attributes);
check(__cpp_nontype_template_args);
check(__cpp_lib_bool_constant);
check(__cpp_lib_as_const);
check(__cpp_lib_logical_traits);
check(__cpp_lib_type_trait_variable_templates);
check(__cpp_noexcept_function_type);
check(__cpp_aggregate_bases);
check(__cpp_capture_star_this);
check(__cpp_fold_expressions);
check(__cpp_lib_addressof_constexpr);
check(__cpp_lib_apply);
check(__cpp_lib_array_constexpr);
check(__cpp_lib_boyer_moore_searcher);
check(__cpp_lib_clamp);
check(__cpp_lib_is_swappable);
check(__cpp_lib_not_fn);
check(__cpp_lib_sample);
check(__cpp_lib_string_view);
check(__cpp_aligned_new);
check(__cpp_guaranteed_copy_elision);
check(__cpp_if_constexpr);
check(__cpp_inline_variables);
check(__cpp_lib_has_unique_object_representations);
check(__cpp_lib_launder);
check(__cpp_lib_make_from_tuple);
check(__cpp_lib_node_extract);
check(__cpp_lib_optional);
check(__cpp_lib_raw_memory_algorithms);
check(__cpp_nontype_template_parameter_auto);
check(__cpp_structured_bindings);
check(__cpp_lib_constexpr_char_traits);
check(__cpp_template_template_args);
check(__cpp_variadic_using);
check(__cpp_deduction_guides);
check(__cpp_lib_is_aggregate);
check(__cpp_lib_is_invocable);

// C++20 gcc-9

check(__cpp_transactional_memory);
check(__cpp_concepts);
check(__cpp_conditional_explicit);
check(__cpp_impl_destroying_delete);
check(__cpp_lib_destroying_delete);
check(__cpp_nontype_template_parameter_class);
check(__cpp_char8_t);
check(__cpp_lib_char8_t);
check(__cpp_lib_is_constant_evaluated);
check(__cpp_lib_erase_if);
check(__cpp_lib_bounded_array_traits);
check(__cpp_lib_bind_front);

// Not yet implemented

check(__cpp_aggregate_paren_init);
check(__cpp_consteval);
check(__cpp_constexpr_in_decltype);
check(__cpp_constinit);
check(__cpp_coroutines);
check(__cpp_impl_three_way_comparison);
check(__cpp_lib_any);
check(__cpp_lib_assume_aligned);
check(__cpp_lib_atomic_flag_test);
check(__cpp_lib_atomic_float);
check(__cpp_lib_atomic_is_always_lock_free);
check(__cpp_lib_atomic_lock_free_type_aliases);
check(__cpp_lib_atomic_ref);
check(__cpp_lib_atomic_shared_ptr);
check(__cpp_lib_atomic_value_initialization);
check(__cpp_lib_atomic_wait);
check(__cpp_lib_barrier);
check(__cpp_lib_bit_cast);
check(__cpp_lib_bitops);
check(__cpp_lib_byte);
check(__cpp_lib_chrono);
check(__cpp_lib_chrono_udls);
check(__cpp_lib_complex_udls);
check(__cpp_lib_concepts);
check(__cpp_lib_constexpr);
check(__cpp_lib_constexpr_algorithms);
check(__cpp_lib_constexpr_complex);
check(__cpp_lib_constexpr_dynamic_alloc);
check(__cpp_lib_constexpr_functional);
check(__cpp_lib_constexpr_iterator);
check(__cpp_lib_constexpr_memory);
check(__cpp_lib_constexpr_numeric);
check(__cpp_lib_constexpr_string);
check(__cpp_lib_constexpr_string_view);
check(__cpp_lib_constexpr_swap_algorithms);
check(__cpp_lib_constexpr_tuple);
check(__cpp_lib_constexpr_utility);
check(__cpp_lib_constexpr_vector);
check(__cpp_lib_enable_shared_from_this);
check(__cpp_lib_endian);
check(__cpp_lib_execution);
check(__cpp_lib_experimental_any);
check(__cpp_lib_experimental_boyer_moore_searching);
check(__cpp_lib_experimental_detect);
check(__cpp_lib_experimental_erase_if);
check(__cpp_lib_experimental_filesystem);
check(__cpp_lib_experimental_gcd_lcm);
check(__cpp_lib_experimental_logical_traits);
check(__cpp_lib_experimental_make_array);
check(__cpp_lib_experimental_memory_resources);
check(__cpp_lib_experimental_net);
check(__cpp_lib_experimental_net_extensible);
check(__cpp_lib_experimental_not_fn);
check(__cpp_lib_experimental_observer_ptr);
check(__cpp_lib_experimental_optional);
check(__cpp_lib_experimental_ostream_joiner);
check(__cpp_lib_experimental_randint);
check(__cpp_lib_experimental_sample);
check(__cpp_lib_experimental_source_location);
check(__cpp_lib_experimental_string_view);
check(__cpp_lib_experimental_tuple);
check(__cpp_lib_experimental_type_trait_variable_templates);
check(__cpp_lib_filesystem);
check(__cpp_lib_format);
check(__cpp_lib_gcd);
check(__cpp_lib_gcd_lcm);
check(__cpp_lib_generic_associative_lookup);
check(__cpp_lib_generic_unordered_lookup);
check(__cpp_lib_hardware_interference_size);
check(__cpp_lib_hypot);
check(__cpp_lib_int_pow2);
check(__cpp_lib_interpolate);
check(__cpp_lib_is_layout_compatible);
check(__cpp_lib_is_pointer_interconvertible);
check(__cpp_lib_jthread);
check(__cpp_lib_latch);
check(__cpp_lib_lcm);
check(__cpp_lib_list_remove_return_type);
check(__cpp_lib_make_unique);
check(__cpp_lib_map_insertion);
check(__cpp_lib_map_try_emplace);
check(__cpp_lib_math_constants);
check(__cpp_lib_math_special_functions);
check(__cpp_lib_memory_resource);
check(__cpp_lib_nothrow_convertible);
check(__cpp_lib_null_iterators);
check(__cpp_lib_parallel_algorithm);
check(__cpp_lib_polymorphic_allocator);
check(__cpp_lib_quoted_string_io);
check(__cpp_lib_ranges);
check(__cpp_lib_remove_cvref);
check(__cpp_lib_scoped_lock);
check(__cpp_lib_semaphore);
check(__cpp_lib_shared_mutex);
check(__cpp_lib_shared_ptr_arrays);
check(__cpp_lib_shared_ptr_weak_type);
check(__cpp_lib_shared_timed_mutex);
check(__cpp_lib_shift);
check(__cpp_lib_smart_ptr_default_init);
check(__cpp_lib_source_location);
check(__cpp_lib_span);
check(__cpp_lib_ssize);
check(__cpp_lib_starts_ends_with);
check(__cpp_lib_syncbuf);
check(__cpp_lib_three_way_comparison);
check(__cpp_lib_to_address);
check(__cpp_lib_to_array);
check(__cpp_lib_to_chars);
check(__cpp_lib_type_identity);
check(__cpp_lib_unwrap_ref);
check(__cpp_lib_variant);
