#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ch.h"
#include "chprintf.h"
#include "uip.h"
#include "http.h"
#include "util.h"
#include "oven.h"
#include "ui.h"
#include "temperature.h"

static const char *http_seps = " \r\n";

static const char http_resp_ok[] = \
								   "HTTP/1.1 200\r\n" \
								   "\r\n";

static const char http_resp_serverfault[] = \
									"HTTP/1.1 500\r\n" \
									"\r\n";

static const char http_resp_notimp[] = \
									"HTTP/1.1 501\r\n" \
									"\r\n";

static const char http_resp_redir[] = \
									 "HTTP/1.1 301\r\n" \
									 "Location: /\r\n" \
									 "\r\n";

static const char http_resp_badreq[] = \
									  "HTTP/1.1 4˝\r\n" \
									  "\r\n";

struct http_file {
	char path[10];
	const uint8_t *data;
	const unsigned int *len;
	void (*get_handler)(const struct http_file *);
	void (*post_handler)(const struct http_file *);
};

static void http_handle_static(const struct http_file *file)
{
	uip_conn->appstate.remaining = *file->len;
	uip_conn->appstate.buff = file->data;
}

static void http_handle_status(const struct http_file *file)
{
	char sbuf[128];
	int len;

	len = chsnprintf(sbuf, ARRAY_SIZE(sbuf),
			"HTTP/1.1 200\r\n"
			"Content-Type: application/json\r\n"
			"\r\n"
			"{"
			"\"temp_board\": %d,"
			"\"temp_oven\": %d,"
			"\"oven_time\": %d,"
			"\"is_running\": %s"
			"}",
			temperature_board, temperature_oven, oven_current_time(),
			oven_is_running() ? "true" : "false");
	uip_send(sbuf, len);
}

static void http_handle_profile_get(const struct http_file *file)
{
	char sbuf[10 * OVEN_PROFILE_MAXLEN];
	int len = 0;
	int i;

	for (i = 0; oven_profile[i].time != OVEN_ENTRY_INVALID; i++) {
		len += chsnprintf(&sbuf[len], ARRAY_SIZE(sbuf) - len, "%d %d\n",
				oven_profile[i].time,
				oven_profile[i].temp);
	}

	uip_send(sbuf, len);
}

static void http_handle_profile_post(const struct http_file *file)
{
	char buf[128];
	char *uptr;
	char *tok;
	int eints[2];
	int datalen;
	unsigned int i;
	unsigned int k;

	uptr = memmem(uip_appdata, uip_datalen(), "\r\n\r\n", 4);

	if (uptr == NULL) { /* Probably invalid data */
		uip_send(http_resp_badreq, sizeof(http_resp_badreq));
		return;
	}

	uptr += 4;

	/* Account for the terminationg \0 */
	datalen = uip_datalen() - (uptr - (char *)uip_appdata) + 1;
	/* Three characters are minimum needed to encode at least one entry
	 * We also cannot handle strings longer than our work buffer
	 * */
	if (datalen <= 4 || datalen > (int)sizeof(buf)) {
		uip_send(http_resp_badreq, sizeof(http_resp_badreq));
		return;
	}

	memcpy(buf, uptr, datalen);
	buf[datalen] = '\0';

	tok = strtok(buf, " \n");

	for (i = 0; i < ARRAY_SIZE(oven_profile) - 1; i++) {
		for (k = 0; k < 2; k++) {
			eints[k] = atoi(tok);
			tok = strtok(NULL, " \n");
			if (k == 0 && tok == NULL) {
				i--;
				goto exit;
			}
		}
		oven_profile[i].time = eints[0];
		oven_profile[i].temp = eints[1];
	}

exit:
	oven_profile[i + 1].time = OVEN_ENTRY_INVALID;

	uip_send(http_resp_ok, sizeof(http_resp_notimp));
}

static void http_handle_start()
{
	if (oven_is_running()) {
		uip_send(http_resp_serverfault, sizeof(http_resp_serverfault));
		return;
	}
	oven_start();
	uip_send(http_resp_ok, sizeof(http_resp_ok));
}

static void http_handle_stop()
{
	if (!oven_is_running()) {
		uip_send(http_resp_serverfault, sizeof(http_resp_serverfault));
		return;
	}
	oven_stop();
	uip_send(http_resp_ok, sizeof(http_resp_ok));
}

static const struct http_file http_files[] = {
	{ "/", ui_min_html, &ui_min_html_len, http_handle_static, NULL },
	{ "/ui.css", ui_min_css, &ui_min_css_len, http_handle_static, NULL },
	{ "/ui.js", ui_min_js, &ui_min_js_len, http_handle_static, NULL },
	{ "/status", NULL, NULL, http_handle_status, NULL },
	{ "/profile", NULL, NULL, http_handle_profile_get, http_handle_profile_post },
	{ "/start", NULL, NULL, NULL, http_handle_start },
	{ "/stop", NULL, NULL, NULL, http_handle_stop },
};

static void http_appcall_newdata()
{
	char buf[20];
	char *method;
	char *url;
	unsigned int i = 0;
	bool isget = false;

	strncpy(buf, uip_appdata, ARRAY_SIZE(buf));

	buf[ARRAY_SIZE(buf) - 1] = 0;

	method = strtok(buf, http_seps);
	url = strtok(NULL, http_seps);

	/* Get method */
	if (strcmp(method, "GET") == 0) {
		isget = true;
	} else if (strcmp(method, "POST") != 0) {
		uip_send(http_resp_notimp, ARRAY_SIZE(http_resp_notimp));
		return;
	}

	/* Select file */
	for (i = 0; i < ARRAY_SIZE(http_files); i++) {
		if (strcmp(url, http_files[i].path) == 0) {
			if (isget && http_files[i].get_handler)
				http_files[i].get_handler(&http_files[i]);
			else if (http_files[i].post_handler)
				http_files[i].post_handler(&http_files[i]);
			else
				uip_send(http_resp_notimp, ARRAY_SIZE(http_resp_notimp));
			return;
		}
	}

	/* Not found */
	uip_send(http_resp_redir, ARRAY_SIZE(http_resp_redir));
}

void http_appcall()
{
	int i;

	if (uip_newdata()) {
		http_appcall_newdata();
	} else if (uip_acked() || uip_poll()) {
		/* If we still have data to send, continue, if not, then close */
		if (uip_conn->appstate.remaining == 0) {
			uip_close();
			return;
		}
		i = uip_conn->appstate.remaining > uip_mss()
			? uip_mss() : uip_conn->appstate.remaining;
		uip_send(uip_conn->appstate.buff, i);
		uip_conn->appstate.remaining -= i;
		uip_conn->appstate.buff += i;
	}
}
