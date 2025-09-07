#include "exceptions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COL_TRACE_PR(x, c, e)	printf("%.*s%s", __meta->x.str, __trace->x, c);\
						printf("%.*s", __meta->x.end - __meta->x.str, __trace->x + __meta->x.str);\
						printf("%s%s\n", e, __trace->x + __meta->x.end)



unsigned int __find_string_string(const char* string, const char* in){
	unsigned int* __bad_value = malloc(sizeof(unsigned int) * 256);
	if (!__bad_value)
		return 0;
	size_t len_in = strlen(in), len_str = strlen(string);
	// populate bad map table with value size(in) - i + 1
	for (int i = 0; i < len_in; i++) {
		__bad_value[in[i]] = len_in - i + 1;
	}
	return 0;
}

Trace* __create_formatted_trace(
	const char* msg, const char* ctx, const char* des, const char* com
){
	Trace* __trace = malloc(sizeof(Trace));
	if (!__trace)
		return NULL;
	__trace->msg = msg;
	__trace->ctx = ctx;
	__trace->des = des;
	__trace->com = com;
	return __trace;
}

Trace* __create_highlight_trace(
	const char* msg, const char* ctx, const char* des, const char* com, 
	const char* m_w, const char* x_w, const char* d_w, const char* c_w
){
	Trace* __trace = __create_formatted_trace(msg, ctx, des, com);
	struct _highlight_metadata* _metadata = malloc(sizeof(struct _highlight_metadata));
	if (!_metadata)
		return __trace;
	_metadata->msg.str = __find_string_string(msg, m_w);
	_metadata->ctx.str = __find_string_string(ctx, x_w);
	_metadata->des.str = __find_string_string(des, d_w);
	_metadata->com.str = __find_string_string(com, c_w);
	_metadata->msg.end = __find_string_string(msg, m_w);
	_metadata->ctx.end = __find_string_string(ctx, x_w);
	_metadata->des.end = __find_string_string(des, d_w);
	_metadata->com.end = __find_string_string(com, c_w);
	__trace->_metadata = _metadata;
	return __trace;
}

Trace* __create_annotated_trace(
	const char* msg, const char* ctx, const char* des, const char* com,
	const char* m_w, const char* x_w, const char* d_w, const char* c_w,
	const char* m_a, const char* x_a, const char* d_a, const char* c_a
){
	Trace* __trace = __create_formatted_trace(msg, ctx, des, com);
	struct _annotated_metadata* _metadata = malloc(sizeof(struct _annotated_metadata));
	if (!_metadata)
		return __trace;
	_metadata->msg.str = __find_string_string(msg, m_w);
	_metadata->ctx.str = __find_string_string(ctx, x_w);
	_metadata->des.str = __find_string_string(des, d_w);
	_metadata->com.str = __find_string_string(com, c_w);
	_metadata->msg.ann = m_a;
	_metadata->ctx.ann = x_a;
	_metadata->des.ann = d_a;
	_metadata->com.ann = c_a;
	__trace->_metadata = _metadata;
	return __trace;
}

void __print_formatted_trace(Trace* __trace){
	printf("%s\n", __trace->msg);
	printf("\t%s\n", __trace->ctx);
	printf("\t%s\n", __trace->com);
	printf("%s\n", __trace->des);
}

void __print_highlight_trace(Trace* __trace){
	struct _highlight_metadata* __meta = __trace->_metadata;
	COL_TRACE_PR(msg, COLORED_FOREGROUND(255, 255, 170), DEFAULT_FOREGROUND);
	COL_TRACE_PR(ctx, COLORED_FOREGROUND(255, 170, 170), DEFAULT_FOREGROUND);
	COL_TRACE_PR(com, COLORED_FOREGROUND(170, 170, 255), DEFAULT_FOREGROUND);
	COL_TRACE_PR(des, COLORED_FOREGROUND(170, 255, 170), DEFAULT_FOREGROUND);
}

void __print_annotated_trace(Trace* __trace)
{}

void __remove_formatted_trace(Trace * __trace){
	free(__trace);
}

void __remove_highlight_trace(Trace * __trace){
	free(__trace->_metadata);
	free(__trace);
}

void __remove_annotated_trace(Trace * __trace){
	free(__trace->_metadata);
	free(__trace);
}




