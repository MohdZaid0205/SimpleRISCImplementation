#include "exceptions.h"

#define COL_TRACE_PR(trace, meta, x, c, e, p)\
		printf("%s%.*s%s", p, meta->x.str, trace->x, c);\
		printf("%.*s", meta->x.end - meta->x.str, trace->x + meta->x.str);\
		printf("%s%s\n", e, trace->x + meta->x.end)



unsigned int __find_string_string(const char* pattern, const char* text){
	int m = strlen(pattern), n = strlen(text);
	if (m == 0) return 0;
	if (m >  n) return 0;

	for (size_t i = 0; i <= n - m; ++i) {
		size_t j = 0;
		for (; j < m; ++j) {
			if (text[i + j] != pattern[j]) break;
		}
		if (j == m) return (unsigned int)i;
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
	__trace->_metadata = NULL;
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
	_metadata->msg.str = __find_string_string(m_w, msg);
	_metadata->ctx.str = __find_string_string(x_w, ctx);
	_metadata->des.str = __find_string_string(d_w, des);
	_metadata->com.str = __find_string_string(c_w, com);
	_metadata->msg.end = _metadata->msg.str + strlen(m_w);
	_metadata->ctx.end = _metadata->ctx.str + strlen(x_w);
	_metadata->des.end = _metadata->des.str + strlen(d_w);
	_metadata->com.end = _metadata->com.str + strlen(c_w);
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
	printf("\t\t%s\n", __trace->ctx);
	printf("\t%s\n", __trace->com);
	printf("\t%s\n", __trace->des);
}

void __print_highlight_trace(Trace* __trace){
	struct _highlight_metadata* __meta = __trace->_metadata;
	COL_TRACE_PR(__trace, __meta, msg, COLORED_FOREGROUND(255, 150, 150), DEFAULT_FOREGROUND, "\0\0");
	COL_TRACE_PR(__trace, __meta, ctx, COLORED_FOREGROUND(255, 150, 150), DEFAULT_FOREGROUND, "\t\t");
	COL_TRACE_PR(__trace, __meta, com, COLORED_FOREGROUND(255, 150, 150), DEFAULT_FOREGROUND, "\t\0");
	COL_TRACE_PR(__trace, __meta, des, COLORED_FOREGROUND(255, 150, 150), DEFAULT_FOREGROUND, "\t\0");
}

void __print_annotated_trace(Trace* __trace)
{}

void __remove_formatted_trace(Trace * __trace){
	if (__trace->_metadata)
		free(__trace->_metadata);
	if (__trace)
		free(__trace);
}

void __remove_highlight_trace(Trace * __trace){
	if (__trace->_metadata)
		free(__trace->_metadata);
	if (__trace)
		free(__trace);
}

void __remove_annotated_trace(Trace * __trace){
	if (__trace->_metadata)
		free(__trace->_metadata);
	if (__trace)
		free(__trace);
}
