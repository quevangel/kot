
				#pragma once
				
		
				
			#define DEFINE_STRING_MAP(name, value_type)\
		\
			struct name {\
				value_type value;\
				bool has_value;\
				struct name *transition[256];\
			};\
		\
			struct name* name##_new() {\
				struct name *rtn = malloc(sizeof(struct name));\
				rtn->has_value = 0;\
				for (int i = 0; i < 256; i++)\
					rtn->transition[i] = NULL;\
				return rtn;\
			}\
		\
			value_type* name##_search(struct name *rt, const char *beg, const char *end) {\
				for (;beg != end; beg++) {\
					rt = rt->transition[(int)*beg];\
					if (rt == NULL) return NULL;\
				}\
				if (rt->has_value) return &(rt->value);\
				else return NULL;\
			}\
		\
			value_type *name##_set(struct name *rt, const char *beg, const char *end, value_type v) {\
				for (;beg != end; beg++) {\
					if (rt->transition[(int)*beg] != NULL) {\
						rt = rt->transition[(int)*beg];\
					} else {\
						struct name *t = name##_new();\
						rt->transition[(int)*beg] = t;\
						rt = t;\
					}\
				}\
				rt->has_value = true;\
				rt->value = v;\
				return &(rt->value);\
			}\
		\
			value_type *name##_get(struct name *rt, const char *beg, const char *end, value_type (*vcons)()) {\
				for (;beg != end; beg++) {\
					if (rt->transition[(int)*beg] != NULL) {\
						rt = rt->transition[(int)*beg];\
					} else {\
						struct name *t = name##_new();\
						rt->transition[(int)*beg] = t;\
						rt = t;\
					}\
				}\
				if (!rt->has_value) {\
					rt->value = vcons();\
					rt->has_value = true;\
				}\
				return &(rt->value);\
			}\
		
			