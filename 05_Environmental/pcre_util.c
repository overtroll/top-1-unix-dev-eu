#include "pcre_util.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include <pcre2.h>

Result result(String s, bool error) {
	Result r;
	r.s = s;
	r.error = error;
	return r;
}

Result pcre_process(String pattern_, String text_) {
	PCRE2_SPTR pattern = static_cast(PCRE2_SPTR)(pattern_);
	PCRE2_SPTR text = static_cast(PCRE2_SPTR)(text_);
	PCRE2_SIZE text_length = static_cast(PCRE2_SIZE)(strlen(text));

	PCRE2_SIZE err_offs;
	int err_num;

#ifdef UTF
	uint32_t options = PCRE2_UCP;
#else
	uint32_t options = 0;
#endif

	pcre2_code_8* re = pcre2_compile_8(pattern, PCRE2_ZERO_TERMINATED, options, &err_num, &err_offs, nullptr);

	if (re == nullptr) {
		String s = newa(char, 228);
		pcre2_get_error_message_8(err_num, s, sizeof(s));
		return result(s, false);
	}

	pcre2_match_data_8* match_data = pcre2_match_data_create_from_pattern_8(re, nullptr);
	int rc = pcre2_match_8(re, text,  text_length, 0, 0, match_data, nullptr);

	if (rc < 0) {
		String s = newa(char, 228);
		sprintf(s, "Matching error");
		pcre2_match_data_free_8(match_data);
		pcre2_code_free_8(re);

		return result(s, true);
	}

	PCRE2_SIZE* ovector = pcre2_get_ovector_pointer_8(match_data);

	size_t len = 0;
	for (int i = 0; i < 2 * rc; i += 2) {
		len += ovector[i + 1] - ovector[i] + 1;
	}

	String s = newa(char, len + 1);
	s[len] = 0;

	String write_to = s;
	for (int i = 0; i < 2 * rc; i += 2) {
		size_t cur_len = ovector[i + 1] - ovector[i];
		memcpy(write_to, text + ovector[i], cur_len);
		write_to += cur_len;
		*(write_to++) = '\n';
	}

	assert(write_to == s + len);
	pcre2_match_data_free_8(match_data);
	pcre2_code_free_8(re);
	return result(s, false);
};
